// L4-M4: Virtual Camera HAL for redroid (RK3588)
// Standalone AIDL ICameraProvider service (android.hardware.camera.provider-V1),
// following the L4-M1/M3 pattern: binderized service + vintf fragment + rc.
// Synthetic frames (color bars / solid / moving marker) written directly into
// framework gralloc buffers via dma-buf mmap; JPEG stills via libjpeg.
// Control: persist.l4.camera.pattern (bars|solid|gradient), .fps (cap).
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <utility>
#include <string>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/dma-buf.h>

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <cutils/properties.h>

#include <aidl/android/hardware/camera/common/Status.h>
#include <aidl/android/hardware/camera/device/BnCameraDevice.h>
#include <aidl/android/hardware/camera/device/BnCameraDeviceSession.h>
#include <aidl/android/hardware/camera/device/ICameraDeviceCallback.h>
#include <aidl/android/hardware/camera/provider/BnCameraProvider.h>
#include <aidl/android/hardware/camera/provider/ICameraProviderCallback.h>

extern "C" {
#include <system/camera_metadata.h>
#include <jpeglib.h>
}

namespace camdev = ::aidl::android::hardware::camera::device;
namespace camprov = ::aidl::android::hardware::camera::provider;
namespace camcommon = ::aidl::android::hardware::camera::common;
using ::aidl::android::hardware::camera::device::CameraMetadata;
using ::ndk::ScopedAStatus;

static const char* kCamId = "0";
static const int32_t kSensorW = 1920;
static const int32_t kSensorH = 1080;
static const int32_t kJpegMaxSize = 8388608;

// ------------------------------------------------------------------ utils
static int64_t bootTimeNs() {
    struct timespec ts; clock_gettime(CLOCK_BOOTTIME, &ts);
    return (int64_t)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}
static ScopedAStatus errStatus(camcommon::Status s) {
    return ScopedAStatus::fromServiceSpecificError(static_cast<int32_t>(s));
}
static std::string propGet(const char* key, const char* def) {
    char buf[PROPERTY_VALUE_MAX] = {};
    property_get(key, buf, def);
    return buf;
}

// ---------------------------------------------------------- metadata build
class MetaBuilder {
  public:
    MetaBuilder(size_t entries, size_t dataBytes)
        : md_(allocate_camera_metadata(entries, dataBytes)) {}
    ~MetaBuilder() { if (md_) free_camera_metadata(md_); }
    camera_metadata_t* raw() { return md_; }
    void addEntry(uint32_t tag, const void* data, size_t count) {
        add_camera_metadata_entry(md_, tag, data, count);
        seen_.push_back(tag);
    }
    void addI32(uint32_t tag, std::initializer_list<int32_t> v) { addEntry(tag, v.begin(), v.size()); }
    void addI64(uint32_t tag, std::initializer_list<int64_t> v) { addEntry(tag, v.begin(), v.size()); }
    void addU8(uint32_t tag, std::initializer_list<int> v) {
        std::vector<uint8_t> b; for (int x : v) b.push_back((uint8_t)x);
        addEntry(tag, b.data(), b.size());
    }
    void addF32(uint32_t tag, std::initializer_list<float> v) { addEntry(tag, v.begin(), v.size()); }
    void addRational(uint32_t tag, std::initializer_list<std::pair<int32_t,int32_t>> v) {
        std::vector<camera_metadata_rational_t> r; for (auto& p : v) r.push_back({p.first, p.second});
        addEntry(tag, r.data(), r.size());
    }
    const std::vector<uint32_t>& seen() const { return seen_; }
    CameraMetadata finish() {
        CameraMetadata out;
        size_t sz = get_camera_metadata_size(md_);
        out.metadata.assign((const uint8_t*)md_, (const uint8_t*)md_ + sz);
        return out;
    }
  private:
    camera_metadata_t* md_ = nullptr;
    std::vector<uint32_t> seen_;
};

// --------------------------------------------------------- characteristics
static CameraMetadata buildCharacteristics() {
    MetaBuilder b(180, 6144);
    b.addU8(ANDROID_COLOR_CORRECTION_AVAILABLE_ABERRATION_MODES, {0, 1, 2});
    b.addU8(ANDROID_CONTROL_AE_AVAILABLE_ANTIBANDING_MODES, {0, 1, 2, 3});
    b.addU8(ANDROID_CONTROL_AE_AVAILABLE_MODES, {1});
    b.addI32(ANDROID_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES, {15, 30, 30, 30});
    b.addI32(ANDROID_CONTROL_AE_COMPENSATION_RANGE, {-6, 6});
    b.addRational(ANDROID_CONTROL_AE_COMPENSATION_STEP, {{1, 3}});
    b.addU8(ANDROID_CONTROL_AE_LOCK_AVAILABLE, {1});
    b.addU8(ANDROID_CONTROL_AF_AVAILABLE_MODES, {0});
    b.addU8(ANDROID_CONTROL_AVAILABLE_EFFECTS, {0});
    b.addU8(ANDROID_CONTROL_AVAILABLE_MODES, {0, 1});
    b.addU8(ANDROID_CONTROL_AVAILABLE_SCENE_MODES, {0});
    b.addU8(ANDROID_CONTROL_AVAILABLE_VIDEO_STABILIZATION_MODES, {0});
    b.addU8(ANDROID_CONTROL_AWB_AVAILABLE_MODES, {1, 3, 4, 5, 6});
    b.addU8(ANDROID_CONTROL_AWB_LOCK_AVAILABLE, {1});
    b.addI32(ANDROID_CONTROL_MAX_REGIONS, {0, 0, 0});
    b.addU8(ANDROID_EDGE_AVAILABLE_EDGE_MODES, {0, 1, 2});
    b.addU8(ANDROID_FLASH_INFO_AVAILABLE, {0});
    b.addU8(ANDROID_HOT_PIXEL_AVAILABLE_HOT_PIXEL_MODES, {0, 1, 2});
    b.addU8(ANDROID_INFO_SUPPORTED_HARDWARE_LEVEL, {1});  // LIMITED
    { const char* v = "1.0"; b.addEntry(ANDROID_INFO_VERSION, v, strlen(v) + 1); }
    b.addI32(ANDROID_JPEG_AVAILABLE_THUMBNAIL_SIZES, {0, 0, 160, 120, 320, 240});
    b.addI32(ANDROID_JPEG_MAX_SIZE, {kJpegMaxSize});
    b.addU8(ANDROID_LENS_FACING, {1});  // BACK
    b.addF32(ANDROID_LENS_INFO_AVAILABLE_APERTURES, {2.0f});
    b.addF32(ANDROID_LENS_INFO_AVAILABLE_FOCAL_LENGTHS, {4.0f});
    b.addU8(ANDROID_LENS_INFO_AVAILABLE_OPTICAL_STABILIZATION, {0});
    b.addU8(ANDROID_LENS_INFO_FOCUS_DISTANCE_CALIBRATION, {1});
    b.addF32(ANDROID_LENS_INFO_HYPERFOCAL_DISTANCE, {0.5f});
    b.addF32(ANDROID_LENS_INFO_MINIMUM_FOCUS_DISTANCE, {0.0f});
    b.addU8(ANDROID_NOISE_REDUCTION_AVAILABLE_NOISE_REDUCTION_MODES, {0, 1, 2});
    b.addI32(ANDROID_REQUEST_MAX_NUM_OUTPUT_STREAMS, {0, 3, 1});
    b.addI32(ANDROID_REQUEST_MAX_NUM_INPUT_STREAMS, {0});
    b.addI32(ANDROID_REQUEST_PARTIAL_RESULT_COUNT, {1});
    b.addU8(ANDROID_REQUEST_PIPELINE_MAX_DEPTH, {4});
    b.addF32(ANDROID_SCALER_AVAILABLE_MAX_DIGITAL_ZOOM, {2.0f});
    {
        static const int32_t kSizes[][2] = {{1920,1080},{1280,720},{960,540},{640,480},{352,288},{320,240},{176,144}};
        std::vector<int32_t> cfg;
        std::vector<int64_t> minDur, stall;
        auto addStream = [&](int32_t fmt, int32_t w, int32_t h, int64_t durNs, int64_t stallNs) {
            cfg.insert(cfg.end(), {fmt, w, h, 0});
            minDur.insert(minDur.end(), {fmt, w, h, durNs});
            stall.insert(stall.end(), {fmt, w, h, stallNs});
        };
        for (auto& s : kSizes) {
            addStream(0x22, s[0], s[1], 33333333, 0);  // IMPLEMENTATION_DEFINED
            addStream(0x23, s[0], s[1], 33333333, 0);  // YCbCr_420_888
            addStream(1, s[0], s[1], 33333333, 0);     // RGBA_8888
        }
        addStream(0x21, 1920, 1080, 33333333, 100000000);  // BLOB
        addStream(0x21, 1280, 720, 33333333, 100000000);
        addStream(0x21, 640, 480, 33333333, 100000000);
        b.addEntry(ANDROID_SCALER_AVAILABLE_STREAM_CONFIGURATIONS, cfg.data(), cfg.size());
        b.addEntry(ANDROID_SCALER_AVAILABLE_MIN_FRAME_DURATIONS, minDur.data(), minDur.size());
        b.addEntry(ANDROID_SCALER_AVAILABLE_STALL_DURATIONS, stall.data(), stall.size());
    }
    b.addU8(ANDROID_SCALER_CROPPING_TYPE, {1});  // FREEFORM
    b.addU8(ANDROID_SENSOR_AVAILABLE_TEST_PATTERN_MODES, {0, 1, 2});
    b.addI32(ANDROID_SENSOR_BLACK_LEVEL_PATTERN, {0, 0, 0, 0});
    b.addI32(ANDROID_SENSOR_INFO_ACTIVE_ARRAY_SIZE, {0, 0, kSensorW, kSensorH});
    b.addI32(ANDROID_SENSOR_INFO_PRE_CORRECTION_ACTIVE_ARRAY_SIZE, {0, 0, kSensorW, kSensorH});
    b.addU8(ANDROID_SENSOR_INFO_COLOR_FILTER_ARRANGEMENT, {0});  // RGGB
    b.addI64(ANDROID_SENSOR_INFO_EXPOSURE_TIME_RANGE, {100000, 300000000});
    b.addI64(ANDROID_SENSOR_INFO_MAX_FRAME_DURATION, {333333333});
    b.addF32(ANDROID_SENSOR_INFO_PHYSICAL_SIZE, {4.8f, 3.6f});
    b.addI32(ANDROID_SENSOR_INFO_PIXEL_ARRAY_SIZE, {kSensorW, kSensorH});
    b.addI32(ANDROID_SENSOR_INFO_SENSITIVITY_RANGE, {100, 1600});
    b.addU8(ANDROID_SENSOR_INFO_TIMESTAMP_SOURCE, {1});  // REALTIME
    b.addI32(ANDROID_SENSOR_INFO_WHITE_LEVEL, {1023});
    b.addI32(ANDROID_SENSOR_ORIENTATION, {90});
    b.addU8(ANDROID_SHADING_AVAILABLE_MODES, {0, 1, 2});
    b.addU8(ANDROID_STATISTICS_INFO_AVAILABLE_FACE_DETECT_MODES, {0});
    b.addU8(ANDROID_STATISTICS_INFO_AVAILABLE_LENS_SHADING_MAP_MODES, {0});
    b.addI32(ANDROID_STATISTICS_INFO_MAX_FACE_COUNT, {0});
    b.addI32(ANDROID_SYNC_MAX_LATENCY, {0});  // PER_FRAME_CONTROL
    b.addU8(ANDROID_TONEMAP_AVAILABLE_TONE_MAP_MODES, {0, 1, 2});
    b.addU8(ANDROID_REQUEST_AVAILABLE_CAPABILITIES, {0});  // BACKWARD_COMPATIBLE
    // ---- available keys lists
    std::vector<int32_t> charsKeys;
    for (uint32_t t : b.seen()) charsKeys.push_back((int32_t)t);
    static const int32_t kReqKeys[] = {
        ANDROID_COLOR_CORRECTION_ABERRATION_MODE, ANDROID_COLOR_CORRECTION_MODE,
        ANDROID_CONTROL_AE_ANTIBANDING_MODE, ANDROID_CONTROL_AE_EXPOSURE_COMPENSATION,
        ANDROID_CONTROL_AE_LOCK, ANDROID_CONTROL_AE_MODE, ANDROID_CONTROL_AE_REGIONS,
        ANDROID_CONTROL_AE_TARGET_FPS_RANGE, ANDROID_CONTROL_AE_PRECAPTURE_TRIGGER,
        ANDROID_CONTROL_AF_MODE, ANDROID_CONTROL_AF_REGIONS, ANDROID_CONTROL_AF_TRIGGER,
        ANDROID_CONTROL_AWB_LOCK, ANDROID_CONTROL_AWB_MODE, ANDROID_CONTROL_AWB_REGIONS,
        ANDROID_CONTROL_CAPTURE_INTENT, ANDROID_CONTROL_EFFECT_MODE, ANDROID_CONTROL_MODE,
        ANDROID_CONTROL_SCENE_MODE, ANDROID_CONTROL_VIDEO_STABILIZATION_MODE,
        ANDROID_CONTROL_ENABLE_ZSL, ANDROID_EDGE_MODE, ANDROID_FLASH_MODE,
        ANDROID_HOT_PIXEL_MODE, ANDROID_JPEG_ORIENTATION, ANDROID_JPEG_QUALITY,
        ANDROID_JPEG_THUMBNAIL_QUALITY, ANDROID_JPEG_THUMBNAIL_SIZE,
        ANDROID_LENS_FOCAL_LENGTH, ANDROID_LENS_FOCUS_DISTANCE,
        ANDROID_LENS_OPTICAL_STABILIZATION_MODE, ANDROID_NOISE_REDUCTION_MODE,
        ANDROID_REQUEST_ID, ANDROID_SCALER_CROP_REGION, ANDROID_SENSOR_EXPOSURE_TIME,
        ANDROID_SENSOR_FRAME_DURATION, ANDROID_SENSOR_SENSITIVITY,
        ANDROID_SENSOR_TEST_PATTERN_DATA, ANDROID_SENSOR_TEST_PATTERN_MODE,
        ANDROID_SHADING_MODE, ANDROID_STATISTICS_FACE_DETECT_MODE,
        ANDROID_TONEMAP_CURVE_RED, ANDROID_TONEMAP_CURVE_GREEN, ANDROID_TONEMAP_CURVE_BLUE,
        ANDROID_TONEMAP_MODE, ANDROID_BLACK_LEVEL_LOCK,
    };
    static const int32_t kResKeys[] = {
        ANDROID_COLOR_CORRECTION_ABERRATION_MODE, ANDROID_COLOR_CORRECTION_MODE,
        ANDROID_CONTROL_AE_ANTIBANDING_MODE, ANDROID_CONTROL_AE_EXPOSURE_COMPENSATION,
        ANDROID_CONTROL_AE_LOCK, ANDROID_CONTROL_AE_MODE, ANDROID_CONTROL_AE_REGIONS,
        ANDROID_CONTROL_AE_STATE, ANDROID_CONTROL_AE_TARGET_FPS_RANGE,
        ANDROID_CONTROL_AF_MODE, ANDROID_CONTROL_AF_REGIONS, ANDROID_CONTROL_AF_STATE,
        ANDROID_CONTROL_AWB_LOCK, ANDROID_CONTROL_AWB_MODE, ANDROID_CONTROL_AWB_REGIONS,
        ANDROID_CONTROL_AWB_STATE, ANDROID_CONTROL_CAPTURE_INTENT,
        ANDROID_CONTROL_EFFECT_MODE, ANDROID_CONTROL_MODE, ANDROID_CONTROL_SCENE_MODE,
        ANDROID_CONTROL_VIDEO_STABILIZATION_MODE, ANDROID_EDGE_MODE,
        ANDROID_FLASH_MODE, ANDROID_FLASH_STATE, ANDROID_HOT_PIXEL_MODE,
        ANDROID_JPEG_ORIENTATION, ANDROID_JPEG_QUALITY, ANDROID_JPEG_THUMBNAIL_QUALITY,
        ANDROID_JPEG_THUMBNAIL_SIZE, ANDROID_LENS_FOCAL_LENGTH, ANDROID_LENS_FOCUS_DISTANCE,
        ANDROID_LENS_OPTICAL_STABILIZATION_MODE, ANDROID_LENS_STATE,
        ANDROID_NOISE_REDUCTION_MODE, ANDROID_REQUEST_ID, ANDROID_REQUEST_PIPELINE_DEPTH,
        ANDROID_SCALER_CROP_REGION, ANDROID_SENSOR_EXPOSURE_TIME,
        ANDROID_SENSOR_FRAME_DURATION, ANDROID_SENSOR_ROLLING_SHUTTER_SKEW,
        ANDROID_SENSOR_SENSITIVITY, ANDROID_SENSOR_TIMESTAMP, ANDROID_SHADING_MODE,
        ANDROID_STATISTICS_FACE_DETECT_MODE, ANDROID_STATISTICS_SCENE_FLICKER,
        ANDROID_TONEMAP_CURVE_RED, ANDROID_TONEMAP_CURVE_GREEN, ANDROID_TONEMAP_CURVE_BLUE,
        ANDROID_TONEMAP_MODE, ANDROID_BLACK_LEVEL_LOCK,
        ANDROID_SYNC_FRAME_NUMBER,
    };
    b.addEntry(ANDROID_REQUEST_AVAILABLE_REQUEST_KEYS, kReqKeys, sizeof(kReqKeys) / sizeof(int32_t));
    b.addEntry(ANDROID_REQUEST_AVAILABLE_RESULT_KEYS, kResKeys, sizeof(kResKeys) / sizeof(int32_t));
    b.addEntry(ANDROID_REQUEST_AVAILABLE_CHARACTERISTICS_KEYS, charsKeys.data(), charsKeys.size());
    return b.finish();
}

// ------------------------------------------------------ default requests
static CameraMetadata buildDefaultRequest(int32_t intent) {
    MetaBuilder b(48, 1024);
    b.addU8(ANDROID_CONTROL_MODE, {1});  // AUTO
    b.addU8(ANDROID_CONTROL_AE_MODE, {1});
    b.addI32(ANDROID_CONTROL_AE_TARGET_FPS_RANGE, {30, 30});
    b.addU8(ANDROID_CONTROL_AE_ANTIBANDING_MODE, {3});  // AUTO
    b.addU8(ANDROID_CONTROL_AF_MODE, {0});  // OFF (fixed focus)
    b.addU8(ANDROID_CONTROL_AWB_MODE, {1});  // AUTO
    b.addU8(ANDROID_CONTROL_CAPTURE_INTENT, {(int)intent});
    b.addU8(ANDROID_COLOR_CORRECTION_MODE, {1});  // FAST
    b.addU8(ANDROID_COLOR_CORRECTION_ABERRATION_MODE, {1});
    b.addU8(ANDROID_EDGE_MODE, {1});
    b.addU8(ANDROID_FLASH_MODE, {0});
    b.addU8(ANDROID_HOT_PIXEL_MODE, {1});
    b.addU8(ANDROID_NOISE_REDUCTION_MODE, {1});
    b.addU8(ANDROID_SHADING_MODE, {1});
    b.addU8(ANDROID_TONEMAP_MODE, {1});
    b.addU8(ANDROID_STATISTICS_FACE_DETECT_MODE, {0});
    b.addF32(ANDROID_LENS_FOCAL_LENGTH, {4.0f});
    b.addF32(ANDROID_LENS_FOCUS_DISTANCE, {0.0f});
    b.addU8(ANDROID_LENS_OPTICAL_STABILIZATION_MODE, {0});
    b.addI32(ANDROID_JPEG_ORIENTATION, {0});
    b.addU8(ANDROID_JPEG_QUALITY, {90});
    b.addU8(ANDROID_JPEG_THUMBNAIL_QUALITY, {85});
    b.addI32(ANDROID_JPEG_THUMBNAIL_SIZE, {0, 0});
    b.addI32(ANDROID_SCALER_CROP_REGION, {0, 0, kSensorW, kSensorH});
    b.addI64(ANDROID_SENSOR_EXPOSURE_TIME, {10000000});
    b.addI64(ANDROID_SENSOR_FRAME_DURATION, {33333333});
    b.addI32(ANDROID_SENSOR_SENSITIVITY, {200});
    b.addI32(ANDROID_SENSOR_TEST_PATTERN_MODE, {0});
    b.addI32(ANDROID_REQUEST_ID, {-1});
    return b.finish();
}

// --------------------------------------------------------- result metadata
static CameraMetadata buildResultMeta(int64_t timestampNs, int32_t frameNumber) {
    MetaBuilder b(64, 1024);
    b.addU8(ANDROID_CONTROL_MODE, {1});
    b.addU8(ANDROID_CONTROL_AE_MODE, {1});
    b.addU8(ANDROID_CONTROL_AE_STATE, {2});  // CONVERGED
    b.addI32(ANDROID_CONTROL_AE_TARGET_FPS_RANGE, {30, 30});
    b.addU8(ANDROID_CONTROL_AF_MODE, {0});
    b.addU8(ANDROID_CONTROL_AF_STATE, {0});  // INACTIVE
    b.addU8(ANDROID_CONTROL_AWB_MODE, {1});
    b.addU8(ANDROID_CONTROL_AWB_STATE, {2});  // CONVERGED
    b.addU8(ANDROID_COLOR_CORRECTION_MODE, {1});
    b.addU8(ANDROID_COLOR_CORRECTION_ABERRATION_MODE, {1});
    b.addU8(ANDROID_EDGE_MODE, {1});
    b.addU8(ANDROID_FLASH_MODE, {0});
    b.addU8(ANDROID_FLASH_STATE, {0});  // UNAVAILABLE
    b.addU8(ANDROID_HOT_PIXEL_MODE, {1});
    b.addU8(ANDROID_NOISE_REDUCTION_MODE, {1});
    b.addU8(ANDROID_SHADING_MODE, {1});
    b.addU8(ANDROID_TONEMAP_MODE, {1});
    b.addU8(ANDROID_STATISTICS_FACE_DETECT_MODE, {0});
    b.addU8(ANDROID_STATISTICS_SCENE_FLICKER, {0});
    b.addF32(ANDROID_LENS_FOCAL_LENGTH, {4.0f});
    b.addF32(ANDROID_LENS_FOCUS_DISTANCE, {0.0f});
    b.addU8(ANDROID_LENS_OPTICAL_STABILIZATION_MODE, {0});
    b.addU8(ANDROID_LENS_STATE, {0});  // STATIONARY
    b.addI32(ANDROID_JPEG_ORIENTATION, {0});
    b.addU8(ANDROID_JPEG_QUALITY, {90});
    b.addU8(ANDROID_JPEG_THUMBNAIL_QUALITY, {85});
    b.addI32(ANDROID_JPEG_THUMBNAIL_SIZE, {0, 0});
    b.addI32(ANDROID_SCALER_CROP_REGION, {0, 0, kSensorW, kSensorH});
    b.addI64(ANDROID_SENSOR_EXPOSURE_TIME, {10000000});
    b.addI64(ANDROID_SENSOR_FRAME_DURATION, {33333333});
    b.addI64(ANDROID_SENSOR_ROLLING_SHUTTER_SKEW, {1000000});
    b.addI32(ANDROID_SENSOR_SENSITIVITY, {200});
    b.addI64(ANDROID_SENSOR_TIMESTAMP, {timestampNs});
    b.addI32(ANDROID_REQUEST_ID, {-1});
    b.addU8(ANDROID_REQUEST_PIPELINE_DEPTH, {2});
    b.addI64(ANDROID_SYNC_FRAME_NUMBER, {frameNumber});
    b.addU8(ANDROID_BLACK_LEVEL_LOCK, {0});
    return b.finish();
}

// ------------------------------------------------------------ frame render
enum class Pattern { BARS, SOLID, GRADIENT };
static const uint8_t kBars[7][3] = {
    {255,255,255},{255,255,0},{0,255,255},{0,255,0},{255,0,255},{255,0,0},{0,0,255}};

static void renderRgbRow(int y, int w, int h, int64_t frame, Pattern mode,
                         const uint8_t solid[3], uint8_t* row) {
    int mx = (int)((frame * 16) % (w > 96 ? w - 96 : w));
    for (int x = 0; x < w; x++) {
        uint8_t r, g, b;
        if (mode == Pattern::SOLID) { r = solid[0]; g = solid[1]; b = solid[2]; }
        else if (mode == Pattern::GRADIENT) {
            r = (uint8_t)(x * 255 / (w - 1)); g = (uint8_t)(y * 255 / (h - 1)); b = 128;
        } else {
            if (y >= h - 32) { uint8_t v = (uint8_t)(x * 255 / (w - 1)); r = g = b = v; }
            else { const uint8_t* c = kBars[x * 7 / w]; r = c[0]; g = c[1]; b = c[2]; }
        }
        // moving marker: white square with black core, proves liveness
        if (y >= 16 && y < 96 && x >= mx && x < mx + 80) {
            bool border = (y < 20 || y >= 92 || x < mx + 4 || x >= mx + 76);
            r = g = b = border ? 255 : 0;
        }
        row[x * 3 + 0] = r; row[x * 3 + 1] = g; row[x * 3 + 2] = b;
    }
}

static inline uint8_t rgb2y(int r, int g, int b) {
    return (uint8_t)(((66 * r + 129 * g + 25 * b + 128) >> 8) + 16);
}
static inline uint8_t rgb2u(int r, int g, int b) {
    return (uint8_t)(((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128);
}
static inline uint8_t rgb2v(int r, int g, int b) {
    return (uint8_t)(((112 * r - 94 * g - 18 * b + 128) >> 8) + 128);
}

// ------------------------------------------------------------ JPEG encode
static bool encodeJpegRgb(const uint8_t* rgb, int w, int h, int quality,
                          uint8_t** outBuf, unsigned long* outSize) {
    jpeg_compress_struct cinfo;
    jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_mem_dest(&cinfo, outBuf, outSize);
    cinfo.image_width = w; cinfo.image_height = h;
    cinfo.input_components = 3; cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);
    while (cinfo.next_scanline < cinfo.image_height) {
        JSAMPROW row = (JSAMPROW)(rgb + (size_t)cinfo.next_scanline * w * 3);
        jpeg_write_scanlines(&cinfo, &row, 1);
    }
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    return *outSize > 0;
}

// ------------------------------------------------------------ buffer fill
static void waitFence(const ::aidl::android::hardware::common::NativeHandle& fence, int timeoutMs) {
    if (fence.fds.empty()) return;
    int fd = fence.fds[0].get();
    if (fd < 0) return;
    struct pollfd p{fd, POLLIN, 0};
    poll(&p, 1, timeoutMs);
}

static bool fillStreamBuffer(const camdev::Stream& stream, int32_t effectiveFormat,
                             ::aidl::android::hardware::common::NativeHandle& handle,
                             int64_t frame, Pattern mode, const uint8_t solid[3]) {
    if (handle.fds.empty()) return false;
    int fd = handle.fds[0].get();
    if (fd < 0) return false;
    off_t size = lseek(fd, 0, SEEK_END);
    if (size <= 0) return false;
    lseek(fd, 0, SEEK_SET);
    void* map = mmap(nullptr, (size_t)size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) return false;
    struct dma_buf_sync sync{};
    sync.flags = DMA_BUF_SYNC_START | DMA_BUF_SYNC_WRITE;
    ioctl(fd, DMA_BUF_IOCTL_SYNC, &sync);
    uint8_t* base = (uint8_t*)map;
    int w = stream.width, h = stream.height;
    std::vector<uint8_t> row((size_t)w * 3);
    bool ok = true;
    if (effectiveFormat == 0x21) {  // BLOB: JPEG + camera_blob footer
        std::vector<uint8_t> rgb((size_t)w * h * 3);
        for (int y = 0; y < h; y++) {
            renderRgbRow(y, w, h, frame, mode, solid, row.data());
            memcpy(rgb.data() + (size_t)y * w * 3, row.data(), (size_t)w * 3);
        }
        uint8_t* jpg = nullptr; unsigned long jpgSize = 0;
        if (encodeJpegRgb(rgb.data(), w, h, 90, &jpg, &jpgSize) &&
            jpgSize + 8 <= (unsigned long)size) {
            memcpy(base, jpg, jpgSize);
            uint32_t footer[2] = {0x00FF /*CAMERA_BLOB_ID_JPEG*/, (uint32_t)jpgSize};
            memcpy(base + size - 8, footer, 8);
        } else ok = false;
        if (jpg) free(jpg);
    } else if (effectiveFormat == 0x23 || effectiveFormat == 0x22) {  // YUV420
        uint8_t* yPlane = base;
        uint8_t* uPlane = base + (size_t)w * h;
        uint8_t* vPlane = uPlane + (size_t)(w / 2) * (h / 2);
        for (int y = 0; y < h; y++) {
            renderRgbRow(y, w, h, frame, mode, solid, row.data());
            for (int x = 0; x < w; x++) {
                int r = row[x*3], g = row[x*3+1], b = row[x*3+2];
                yPlane[y * w + x] = rgb2y(r, g, b);
                if ((y & 1) == 0 && (x & 1) == 0) {
                    uPlane[(y/2) * (w/2) + x/2] = rgb2u(r, g, b);
                    vPlane[(y/2) * (w/2) + x/2] = rgb2v(r, g, b);
                }
            }
        }
    } else if (effectiveFormat == 1) {  // RGBA_8888
        for (int y = 0; y < h; y++) {
            renderRgbRow(y, w, h, frame, mode, solid, row.data());
            uint8_t* dst = base + (size_t)y * w * 4;
            for (int x = 0; x < w; x++) {
                dst[x*4+0] = row[x*3+0]; dst[x*4+1] = row[x*3+1];
                dst[x*4+2] = row[x*3+2]; dst[x*4+3] = 255;
            }
        }
    } else {
        memset(base, 0, (size_t)size < (size_t)w * h ? (size_t)size : (size_t)w * h);
    }
    sync.flags = DMA_BUF_SYNC_END | DMA_BUF_SYNC_WRITE;
    ioctl(fd, DMA_BUF_IOCTL_SYNC, &sync);
    munmap(map, (size_t)size);
    return ok;
}

// --------------------------------------------------------------- session
#include <android/log.h>
#define L4LOG(...) __android_log_print(ANDROID_LOG_INFO, "l4-camera", __VA_ARGS__)
#define L4ERR(...) __android_log_print(ANDROID_LOG_ERROR, "l4-camera", __VA_ARGS__)

using NativeHandle = ::aidl::android::hardware::common::NativeHandle;
using BufferUsage = ::aidl::android::hardware::graphics::common::BufferUsage;
using PixelFormat = ::aidl::android::hardware::graphics::common::PixelFormat;

static NativeHandle dupHandle(const NativeHandle& h) {
    NativeHandle out;
    out.ints = h.ints;
    for (auto& f : h.fds) {
        int d = f.get() >= 0 ? dup(f.get()) : -1;
        out.fds.emplace_back(::ndk::ScopedFileDescriptor(d));
    }
    return out;
}

class CameraSession : public camdev::BnCameraDeviceSession {
  public:
    explicit CameraSession(std::shared_ptr<camdev::ICameraDeviceCallback> cb)
        : callback_(cb) {
        std::string p = propGet("persist.l4.camera.pattern", "bars");
        defaultMode_ = p == "solid" ? Pattern::SOLID : p == "gradient" ? Pattern::GRADIENT : Pattern::BARS;
    }
    ScopedAStatus close() override {
        closed_ = true;
        return ScopedAStatus::ok();
    }
    ScopedAStatus configureStreams(const camdev::StreamConfiguration& in,
                                   std::vector<camdev::HalStream>* out) override {
        if (in.operationMode != camdev::StreamConfigurationMode::NORMAL_MODE)
            return errStatus(camcommon::Status::OPERATION_NOT_SUPPORTED);
        std::lock_guard<std::mutex> lk(mu_);
        streams_.clear();
        for (auto& s : in.streams) {
            int32_t eff = (int32_t)s.format;
            camdev::HalStream hs;
            hs.id = s.id;
            hs.overrideFormat = s.format;
            if (s.format == PixelFormat::IMPLEMENTATION_DEFINED) {
                hs.overrideFormat = PixelFormat::YCBCR_420_888;
                eff = (int32_t)PixelFormat::YCBCR_420_888;
            }
            int64_t usage = (int64_t)s.usage | (int64_t)BufferUsage::CPU_WRITE_OFTEN;
            hs.producerUsage = (BufferUsage)usage;
            hs.consumerUsage = s.usage;
            hs.maxBuffers = 4;
            hs.overrideDataSpace = s.dataSpace;
            hs.physicalCameraId = s.physicalCameraId;
            hs.supportOffline = false;
            out->push_back(hs);
            streams_[s.id] = {s, eff};
            L4LOG("configure stream %d: %dx%d fmt=%d eff=%d usage=%lld",
                  s.id, s.width, s.height, (int)s.format, eff, (long long)usage);
        }
        return ScopedAStatus::ok();
    }
    ScopedAStatus constructDefaultRequestSettings(camdev::RequestTemplate type,
                                                  CameraMetadata* out) override {
        int32_t intent = (int32_t)type;
        if (intent < 1 || intent > 6) intent = 1;
        *out = buildDefaultRequest(intent);
        return ScopedAStatus::ok();
    }
    ScopedAStatus flush() override { return ScopedAStatus::ok(); }
    ScopedAStatus getCaptureRequestMetadataQueue(
            ::aidl::android::hardware::common::fmq::MQDescriptor<int8_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>* out) override {
        *out = {};
        return ScopedAStatus::ok();
    }
    ScopedAStatus getCaptureResultMetadataQueue(
            ::aidl::android::hardware::common::fmq::MQDescriptor<int8_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>* out) override {
        *out = {};
        return ScopedAStatus::ok();
    }
    ScopedAStatus isReconfigurationRequired(const CameraMetadata&, const CameraMetadata&,
                                            bool* out) override {
        *out = false;
        return ScopedAStatus::ok();
    }
    ScopedAStatus signalStreamFlush(const std::vector<int32_t>&, int32_t) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus switchToOffline(const std::vector<int32_t>&,
                                  camdev::CameraOfflineSessionInfo*,
                                  std::shared_ptr<camdev::ICameraOfflineSession>*) override {
        return errStatus(camcommon::Status::OPERATION_NOT_SUPPORTED);
    }
    ScopedAStatus repeatingRequestEnd(int32_t, const std::vector<int32_t>&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus processCaptureRequest(const std::vector<camdev::CaptureRequest>& requests,
                                        const std::vector<camdev::BufferCache>& cachesToRemove,
                                        int32_t* outProcessed) override {
        std::lock_guard<std::mutex> lk(mu_);
        for (auto& c : cachesToRemove) cache_.erase({c.streamId, c.bufferId});
        if (!callback_ || closed_) {
            *outProcessed = 0;
            return errStatus(camcommon::Status::CAMERA_DISCONNECTED);
        }
        // fps throttle (persist.l4.camera.fps, default 30)
        int fps = atoi(propGet("persist.l4.camera.fps", "30").c_str());
        if (fps > 0) {
            int64_t interval = 1000000000LL / fps;
            int64_t now = bootTimeNs();
            if (lastFrameNs_ > 0 && now - lastFrameNs_ < interval)
                usleep((useconds_t)((interval - (now - lastFrameNs_)) / 1000));
        }
        std::vector<camdev::CaptureResult> results;
        for (auto& req : requests) {
            int64_t ts = bootTimeNs();
            lastFrameNs_ = ts;
            // shutter notify first
            camdev::ShutterMsg shutter;
            shutter.frameNumber = req.frameNumber;
            shutter.timestamp = ts;
            shutter.readoutTimestamp = ts + 1000000;
            std::vector<camdev::NotifyMsg> msgs;
            msgs.push_back(camdev::NotifyMsg::make<camdev::NotifyMsg::Tag::shutter>(shutter));
            callback_->notify(msgs);
            // per-request pattern override
            Pattern mode = defaultMode_;
            uint8_t solid[3] = {64, 192, 64};
            if (!req.settings.metadata.empty()) {
                camera_metadata_ro_entry e;
                const camera_metadata_t* m = (const camera_metadata_t*)req.settings.metadata.data();
                if (find_camera_metadata_ro_entry(m, ANDROID_SENSOR_TEST_PATTERN_MODE, &e) == 0 &&
                    e.count >= 1) {
                    if (e.data.i32[0] == 1) {  // SOLID_COLOR
                        mode = Pattern::SOLID;
                        camera_metadata_ro_entry d;
                        if (find_camera_metadata_ro_entry(m, ANDROID_SENSOR_TEST_PATTERN_DATA, &d) == 0 &&
                            d.count >= 4) {
                            solid[0] = (uint8_t)(d.data.i32[0] >> 2);
                            solid[1] = (uint8_t)(d.data.i32[1] >> 2);
                            solid[2] = (uint8_t)(d.data.i32[3] >> 2);
                        }
                    } else if (e.data.i32[0] == 2) mode = defaultMode_;  // COLOR_BARS fixture ~ bars
                }
            }
            camdev::CaptureResult res;
            res.frameNumber = req.frameNumber;
            res.partialResult = 1;
            res.result = buildResultMeta(ts, req.frameNumber);
            for (auto& ob : req.outputBuffers) {
                camdev::StreamBuffer rb;
                rb.streamId = ob.streamId;
                rb.bufferId = ob.bufferId;
                rb.buffer = {};
                rb.status = camdev::BufferStatus::ERROR;
                auto sit = streams_.find(ob.streamId);
                NativeHandle* handlePtr = nullptr;
                NativeHandle localHandle;
                if (!ob.buffer.fds.empty()) {
                    auto key = std::make_pair(ob.streamId, ob.bufferId);
                    if (!cache_.count(key)) cache_[key] = dupHandle(ob.buffer);
                    localHandle = dupHandle(ob.buffer);
                    handlePtr = &localHandle;
                } else {
                    auto cit = cache_.find({ob.streamId, ob.bufferId});
                    if (cit != cache_.end()) handlePtr = &cit->second;
                }
                if (sit != streams_.end() && handlePtr) {
                    waitFence(ob.acquireFence, 300);
                    if (frameCount_ < 3) {
                        std::string ints;
                        for (int v : handlePtr->ints) { ints += std::to_string(v); ints += ","; }
                        L4LOG("buf stream=%d id=%lld fds=%zu ints=[%s]", ob.streamId,
                              (long long)ob.bufferId, handlePtr->fds.size(), ints.c_str());
                    }
                    if (fillStreamBuffer(sit->second.first, sit->second.second,
                                         *handlePtr, frameCount_, mode, solid))
                        rb.status = camdev::BufferStatus::OK;
                }
                res.outputBuffers.push_back(std::move(rb));
            }
            if (!req.inputBuffer.buffer.fds.empty()) {
                // Echo ids only: StreamBuffer/NativeHandle are move-only, and
                // the framework releases input buffers by bufferId.
                camdev::StreamBuffer ib;
                ib.streamId = req.inputBuffer.streamId;
                ib.bufferId = req.inputBuffer.bufferId;
                ib.status = camdev::BufferStatus::OK;
                res.inputBuffer = std::move(ib);
            }
            results.push_back(std::move(res));
            frameCount_++;
        }
        *outProcessed = (int32_t)requests.size();
        auto st = callback_->processCaptureResult(results);
        if (!st.isOk()) L4ERR("processCaptureResult failed: %s", st.getDescription().c_str());
        return ScopedAStatus::ok();
    }

  private:
    std::shared_ptr<camdev::ICameraDeviceCallback> callback_;
    std::mutex mu_;
    std::map<int32_t, std::pair<camdev::Stream, int32_t>> streams_;
    std::map<std::pair<int32_t, int64_t>, NativeHandle> cache_;
    Pattern defaultMode_ = Pattern::BARS;
    int64_t lastFrameNs_ = 0;
    int64_t frameCount_ = 0;
    bool closed_ = false;
};

// ---------------------------------------------------------------- device
class CameraDevice : public camdev::BnCameraDevice {
  public:
    ScopedAStatus getCameraCharacteristics(CameraMetadata* out) override {
        static CameraMetadata chars = buildCharacteristics();
        *out = chars;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getPhysicalCameraCharacteristics(const std::string&, CameraMetadata*) override {
        return errStatus(camcommon::Status::ILLEGAL_ARGUMENT);
    }
    ScopedAStatus getResourceCost(camcommon::CameraResourceCost* out) override {
        out->resourceCost = 100;
        out->conflictingDevices.clear();
        return ScopedAStatus::ok();
    }
    ScopedAStatus isStreamCombinationSupported(const camdev::StreamConfiguration& in,
                                               bool* out) override {
        *out = true;
        for (auto& s : in.streams) {
            int32_t f = (int32_t)s.format;
            if (!(f == 0x21 || f == 0x22 || f == 0x23 || f == 1)) *out = false;
            if (s.width > kSensorW || s.height > kSensorH) *out = false;
        }
        return ScopedAStatus::ok();
    }
    ScopedAStatus open(const std::shared_ptr<camdev::ICameraDeviceCallback>& cb,
                       std::shared_ptr<camdev::ICameraDeviceSession>* out) override {
        L4LOG("device open");
        *out = ndk::SharedRefBase::make<CameraSession>(cb);
        return ScopedAStatus::ok();
    }
    ScopedAStatus openInjectionSession(const std::shared_ptr<camdev::ICameraDeviceCallback>&,
                                       std::shared_ptr<camdev::ICameraInjectionSession>*) override {
        return errStatus(camcommon::Status::OPERATION_NOT_SUPPORTED);
    }
    ScopedAStatus setTorchMode(bool) override {
        return errStatus(camcommon::Status::OPERATION_NOT_SUPPORTED);
    }
    ScopedAStatus turnOnTorchWithStrengthLevel(int32_t) override {
        return errStatus(camcommon::Status::OPERATION_NOT_SUPPORTED);
    }
    ScopedAStatus getTorchStrengthLevel(int32_t*) override {
        return errStatus(camcommon::Status::OPERATION_NOT_SUPPORTED);
    }
};

// --------------------------------------------------------------- provider
class CameraProvider : public camprov::BnCameraProvider {
  public:
    ScopedAStatus setCallback(const std::shared_ptr<camprov::ICameraProviderCallback>& cb) override {
        callback_ = cb;
        if (cb) {
            auto st = cb->cameraDeviceStatusChange(kCamId, camcommon::CameraDeviceStatus::PRESENT);
            L4LOG("setCallback: notified PRESENT, ok=%d", (int)st.isOk());
        }
        return ScopedAStatus::ok();
    }
    ScopedAStatus getVendorTags(std::vector<camcommon::VendorTagSection>* out) override {
        out->clear();
        return ScopedAStatus::ok();
    }
    ScopedAStatus getCameraIdList(std::vector<std::string>* out) override {
        *out = {kCamId};
        return ScopedAStatus::ok();
    }
    ScopedAStatus getCameraDeviceInterface(const std::string& name,
                                           std::shared_ptr<camdev::ICameraDevice>* out) override {
        L4LOG("getCameraDeviceInterface: %s", name.c_str());
        if (name.find(kCamId) == std::string::npos)
            return errStatus(camcommon::Status::ILLEGAL_ARGUMENT);
        if (!device_) device_ = ndk::SharedRefBase::make<CameraDevice>();
        *out = device_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus notifyDeviceStateChange(int64_t) override { return ScopedAStatus::ok(); }
    ScopedAStatus getConcurrentCameraIds(
            std::vector<camprov::ConcurrentCameraIdCombination>* out) override {
        out->clear();
        return ScopedAStatus::ok();
    }
    ScopedAStatus isConcurrentStreamCombinationSupported(
            const std::vector<camprov::CameraIdAndStreamCombination>&, bool* out) override {
        *out = false;
        return ScopedAStatus::ok();
    }

  private:
    std::shared_ptr<camprov::ICameraProviderCallback> callback_;
    std::shared_ptr<camdev::ICameraDevice> device_;
};

int main() {
    L4LOG("l4 camera provider starting (pattern=%s)",
          propGet("persist.l4.camera.pattern", "bars").c_str());
    ABinderProcess_setThreadPoolMaxThreadCount(8);
    ABinderProcess_startThreadPool();
    auto provider = ndk::SharedRefBase::make<CameraProvider>();
    const std::string instance =
        std::string(camprov::ICameraProvider::descriptor) + "/internal/0";
    binder_status_t status =
        AServiceManager_addService(provider->asBinder().get(), instance.c_str());
    if (status != STATUS_OK) {
        L4ERR("addService %s failed: %d", instance.c_str(), (int)status);
        return 1;
    }
    L4LOG("registered %s", instance.c_str());
    ABinderProcess_joinThreadPool();
    return 0;
}
