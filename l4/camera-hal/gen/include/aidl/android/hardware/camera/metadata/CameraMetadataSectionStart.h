/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -I aidl-src --out=gen/src --header_out=gen/include aidl-src/android/hardware/camera/common/CameraDeviceStatus.aidl aidl-src/android/hardware/camera/common/CameraMetadataType.aidl aidl-src/android/hardware/camera/common/CameraResourceCost.aidl aidl-src/android/hardware/camera/common/Status.aidl aidl-src/android/hardware/camera/common/TagBoundaryId.aidl aidl-src/android/hardware/camera/common/TorchModeStatus.aidl aidl-src/android/hardware/camera/common/VendorTag.aidl aidl-src/android/hardware/camera/common/VendorTagSection.aidl aidl-src/android/hardware/camera/device/BufferCache.aidl aidl-src/android/hardware/camera/device/BufferRequest.aidl aidl-src/android/hardware/camera/device/BufferRequestStatus.aidl aidl-src/android/hardware/camera/device/BufferStatus.aidl aidl-src/android/hardware/camera/device/CameraBlob.aidl aidl-src/android/hardware/camera/device/CameraBlobId.aidl aidl-src/android/hardware/camera/device/CameraMetadata.aidl aidl-src/android/hardware/camera/device/CameraOfflineSessionInfo.aidl aidl-src/android/hardware/camera/device/CaptureRequest.aidl aidl-src/android/hardware/camera/device/CaptureResult.aidl aidl-src/android/hardware/camera/device/ErrorCode.aidl aidl-src/android/hardware/camera/device/ErrorMsg.aidl aidl-src/android/hardware/camera/device/HalStream.aidl aidl-src/android/hardware/camera/device/ICameraDevice.aidl aidl-src/android/hardware/camera/device/ICameraDeviceCallback.aidl aidl-src/android/hardware/camera/device/ICameraDeviceSession.aidl aidl-src/android/hardware/camera/device/ICameraInjectionSession.aidl aidl-src/android/hardware/camera/device/ICameraOfflineSession.aidl aidl-src/android/hardware/camera/device/NotifyMsg.aidl aidl-src/android/hardware/camera/device/OfflineRequest.aidl aidl-src/android/hardware/camera/device/OfflineStream.aidl aidl-src/android/hardware/camera/device/PhysicalCameraMetadata.aidl aidl-src/android/hardware/camera/device/PhysicalCameraSetting.aidl aidl-src/android/hardware/camera/device/RequestTemplate.aidl aidl-src/android/hardware/camera/device/ShutterMsg.aidl aidl-src/android/hardware/camera/device/Stream.aidl aidl-src/android/hardware/camera/device/StreamBuffer.aidl aidl-src/android/hardware/camera/device/StreamBufferRequestError.aidl aidl-src/android/hardware/camera/device/StreamBufferRet.aidl aidl-src/android/hardware/camera/device/StreamBuffersVal.aidl aidl-src/android/hardware/camera/device/StreamConfiguration.aidl aidl-src/android/hardware/camera/device/StreamConfigurationMode.aidl aidl-src/android/hardware/camera/device/StreamRotation.aidl aidl-src/android/hardware/camera/device/StreamType.aidl aidl-src/android/hardware/camera/provider/CameraIdAndStreamCombination.aidl aidl-src/android/hardware/camera/provider/ConcurrentCameraIdCombination.aidl aidl-src/android/hardware/camera/provider/ICameraProvider.aidl aidl-src/android/hardware/camera/provider/ICameraProviderCallback.aidl aidl-src/android/hardware/camera/metadata/AutomotiveLensFacing.aidl aidl-src/android/hardware/camera/metadata/AutomotiveLocation.aidl aidl-src/android/hardware/camera/metadata/BlackLevelLock.aidl aidl-src/android/hardware/camera/metadata/CameraMetadataSection.aidl aidl-src/android/hardware/camera/metadata/CameraMetadataSectionStart.aidl aidl-src/android/hardware/camera/metadata/CameraMetadataTag.aidl aidl-src/android/hardware/camera/metadata/ColorCorrectionAberrationMode.aidl aidl-src/android/hardware/camera/metadata/ColorCorrectionMode.aidl aidl-src/android/hardware/camera/metadata/ControlAeAntibandingMode.aidl aidl-src/android/hardware/camera/metadata/ControlAeLock.aidl aidl-src/android/hardware/camera/metadata/ControlAeLockAvailable.aidl aidl-src/android/hardware/camera/metadata/ControlAeMode.aidl aidl-src/android/hardware/camera/metadata/ControlAePrecaptureTrigger.aidl aidl-src/android/hardware/camera/metadata/ControlAeState.aidl aidl-src/android/hardware/camera/metadata/ControlAfMode.aidl aidl-src/android/hardware/camera/metadata/ControlAfSceneChange.aidl aidl-src/android/hardware/camera/metadata/ControlAfState.aidl aidl-src/android/hardware/camera/metadata/ControlAfTrigger.aidl aidl-src/android/hardware/camera/metadata/ControlAwbLock.aidl aidl-src/android/hardware/camera/metadata/ControlAwbLockAvailable.aidl aidl-src/android/hardware/camera/metadata/ControlAwbMode.aidl aidl-src/android/hardware/camera/metadata/ControlAwbState.aidl aidl-src/android/hardware/camera/metadata/ControlCaptureIntent.aidl aidl-src/android/hardware/camera/metadata/ControlEffectMode.aidl aidl-src/android/hardware/camera/metadata/ControlEnableZsl.aidl aidl-src/android/hardware/camera/metadata/ControlExtendedSceneMode.aidl aidl-src/android/hardware/camera/metadata/ControlMode.aidl aidl-src/android/hardware/camera/metadata/ControlSceneMode.aidl aidl-src/android/hardware/camera/metadata/ControlVideoStabilizationMode.aidl aidl-src/android/hardware/camera/metadata/DemosaicMode.aidl aidl-src/android/hardware/camera/metadata/DepthAvailableDepthStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/DepthAvailableDepthStreamConfigurationsMaximumResolution.aidl aidl-src/android/hardware/camera/metadata/DepthAvailableDynamicDepthStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/DepthAvailableDynamicDepthStreamConfigurationsMaximumResolution.aidl aidl-src/android/hardware/camera/metadata/DepthDepthIsExclusive.aidl aidl-src/android/hardware/camera/metadata/DistortionCorrectionMode.aidl aidl-src/android/hardware/camera/metadata/EdgeMode.aidl aidl-src/android/hardware/camera/metadata/FlashInfoAvailable.aidl aidl-src/android/hardware/camera/metadata/FlashMode.aidl aidl-src/android/hardware/camera/metadata/FlashState.aidl aidl-src/android/hardware/camera/metadata/HeicAvailableHeicStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/HeicAvailableHeicStreamConfigurationsMaximumResolution.aidl aidl-src/android/hardware/camera/metadata/HeicInfoSupported.aidl aidl-src/android/hardware/camera/metadata/HotPixelMode.aidl aidl-src/android/hardware/camera/metadata/InfoSupportedBufferManagementVersion.aidl aidl-src/android/hardware/camera/metadata/InfoSupportedHardwareLevel.aidl aidl-src/android/hardware/camera/metadata/LedAvailableLeds.aidl aidl-src/android/hardware/camera/metadata/LedTransmit.aidl aidl-src/android/hardware/camera/metadata/LensFacing.aidl aidl-src/android/hardware/camera/metadata/LensInfoFocusDistanceCalibration.aidl aidl-src/android/hardware/camera/metadata/LensOpticalStabilizationMode.aidl aidl-src/android/hardware/camera/metadata/LensPoseReference.aidl aidl-src/android/hardware/camera/metadata/LensState.aidl aidl-src/android/hardware/camera/metadata/LogicalMultiCameraSensorSyncType.aidl aidl-src/android/hardware/camera/metadata/NoiseReductionMode.aidl aidl-src/android/hardware/camera/metadata/QuirksPartialResult.aidl aidl-src/android/hardware/camera/metadata/RequestAvailableCapabilities.aidl aidl-src/android/hardware/camera/metadata/RequestAvailableDynamicRangeProfilesMap.aidl aidl-src/android/hardware/camera/metadata/RequestMetadataMode.aidl aidl-src/android/hardware/camera/metadata/RequestType.aidl aidl-src/android/hardware/camera/metadata/ScalerAvailableFormats.aidl aidl-src/android/hardware/camera/metadata/ScalerAvailableRecommendedStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/ScalerAvailableStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/ScalerAvailableStreamConfigurationsMaximumResolution.aidl aidl-src/android/hardware/camera/metadata/ScalerAvailableStreamUseCases.aidl aidl-src/android/hardware/camera/metadata/ScalerCroppingType.aidl aidl-src/android/hardware/camera/metadata/ScalerMultiResolutionStreamSupported.aidl aidl-src/android/hardware/camera/metadata/ScalerPhysicalCameraMultiResolutionStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/ScalerRotateAndCrop.aidl aidl-src/android/hardware/camera/metadata/SensorInfoColorFilterArrangement.aidl aidl-src/android/hardware/camera/metadata/SensorInfoLensShadingApplied.aidl aidl-src/android/hardware/camera/metadata/SensorInfoTimestampSource.aidl aidl-src/android/hardware/camera/metadata/SensorPixelMode.aidl aidl-src/android/hardware/camera/metadata/SensorRawBinningFactorUsed.aidl aidl-src/android/hardware/camera/metadata/SensorReferenceIlluminant1.aidl aidl-src/android/hardware/camera/metadata/SensorTestPatternMode.aidl aidl-src/android/hardware/camera/metadata/ShadingMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsFaceDetectMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsHistogramMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsHotPixelMapMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsLensShadingMapMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsOisDataMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsSceneFlicker.aidl aidl-src/android/hardware/camera/metadata/StatisticsSharpnessMapMode.aidl aidl-src/android/hardware/camera/metadata/SyncFrameNumber.aidl aidl-src/android/hardware/camera/metadata/SyncMaxLatency.aidl aidl-src/android/hardware/camera/metadata/TonemapMode.aidl aidl-src/android/hardware/camera/metadata/TonemapPresetCurve.aidl aidl-src/android/hardware/common/Ashmem.aidl aidl-src/android/hardware/common/MappableFile.aidl aidl-src/android/hardware/common/NativeHandle.aidl aidl-src/android/hardware/common/fmq/MQDescriptor.aidl aidl-src/android/hardware/common/fmq/SynchronizedReadWrite.aidl aidl-src/android/hardware/common/fmq/UnsynchronizedWrite.aidl aidl-src/android/hardware/common/fmq/GrantorDescriptor.aidl aidl-src/android/hardware/graphics/common/AlphaInterpretation.aidl aidl-src/android/hardware/graphics/common/BlendMode.aidl aidl-src/android/hardware/graphics/common/BufferUsage.aidl aidl-src/android/hardware/graphics/common/ChromaSiting.aidl aidl-src/android/hardware/graphics/common/ColorTransform.aidl aidl-src/android/hardware/graphics/common/Compression.aidl aidl-src/android/hardware/graphics/common/Cta861_3.aidl aidl-src/android/hardware/graphics/common/Dataspace.aidl aidl-src/android/hardware/graphics/common/DisplayDecorationSupport.aidl aidl-src/android/hardware/graphics/common/ExtendableType.aidl aidl-src/android/hardware/graphics/common/FRect.aidl aidl-src/android/hardware/graphics/common/HardwareBuffer.aidl aidl-src/android/hardware/graphics/common/HardwareBufferDescription.aidl aidl-src/android/hardware/graphics/common/Hdr.aidl aidl-src/android/hardware/graphics/common/Interlaced.aidl aidl-src/android/hardware/graphics/common/PixelFormat.aidl aidl-src/android/hardware/graphics/common/PlaneLayout.aidl aidl-src/android/hardware/graphics/common/PlaneLayoutComponent.aidl aidl-src/android/hardware/graphics/common/PlaneLayoutComponentType.aidl aidl-src/android/hardware/graphics/common/Point.aidl aidl-src/android/hardware/graphics/common/Rect.aidl aidl-src/android/hardware/graphics/common/Smpte2086.aidl aidl-src/android/hardware/graphics/common/StandardMetadataType.aidl aidl-src/android/hardware/graphics/common/Transform.aidl aidl-src/android/hardware/graphics/common/XyColor.aidl
 */
#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <android/binder_enums.h>
#include <aidl/android/hardware/camera/metadata/CameraMetadataSection.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace hardware {
namespace camera {
namespace metadata {
enum class CameraMetadataSectionStart : int32_t {
  ANDROID_COLOR_CORRECTION_START = 0,
  ANDROID_CONTROL_START = 65536,
  ANDROID_DEMOSAIC_START = 131072,
  ANDROID_EDGE_START = 196608,
  ANDROID_FLASH_START = 262144,
  ANDROID_FLASH_INFO_START = 327680,
  ANDROID_HOT_PIXEL_START = 393216,
  ANDROID_JPEG_START = 458752,
  ANDROID_LENS_START = 524288,
  ANDROID_LENS_INFO_START = 589824,
  ANDROID_NOISE_REDUCTION_START = 655360,
  ANDROID_QUIRKS_START = 720896,
  ANDROID_REQUEST_START = 786432,
  ANDROID_SCALER_START = 851968,
  ANDROID_SENSOR_START = 917504,
  ANDROID_SENSOR_INFO_START = 983040,
  ANDROID_SHADING_START = 1048576,
  ANDROID_STATISTICS_START = 1114112,
  ANDROID_STATISTICS_INFO_START = 1179648,
  ANDROID_TONEMAP_START = 1245184,
  ANDROID_LED_START = 1310720,
  ANDROID_INFO_START = 1376256,
  ANDROID_BLACK_LEVEL_START = 1441792,
  ANDROID_SYNC_START = 1507328,
  ANDROID_REPROCESS_START = 1572864,
  ANDROID_DEPTH_START = 1638400,
  ANDROID_LOGICAL_MULTI_CAMERA_START = 1703936,
  ANDROID_DISTORTION_CORRECTION_START = 1769472,
  ANDROID_HEIC_START = 1835008,
  ANDROID_HEIC_INFO_START = 1900544,
  ANDROID_AUTOMOTIVE_START = 1966080,
  ANDROID_AUTOMOTIVE_LENS_START = 2031616,
  VENDOR_SECTION_START = -2147483648,
};

}  // namespace metadata
}  // namespace camera
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace camera {
namespace metadata {
[[nodiscard]] static inline std::string toString(CameraMetadataSectionStart val) {
  switch(val) {
  case CameraMetadataSectionStart::ANDROID_COLOR_CORRECTION_START:
    return "ANDROID_COLOR_CORRECTION_START";
  case CameraMetadataSectionStart::ANDROID_CONTROL_START:
    return "ANDROID_CONTROL_START";
  case CameraMetadataSectionStart::ANDROID_DEMOSAIC_START:
    return "ANDROID_DEMOSAIC_START";
  case CameraMetadataSectionStart::ANDROID_EDGE_START:
    return "ANDROID_EDGE_START";
  case CameraMetadataSectionStart::ANDROID_FLASH_START:
    return "ANDROID_FLASH_START";
  case CameraMetadataSectionStart::ANDROID_FLASH_INFO_START:
    return "ANDROID_FLASH_INFO_START";
  case CameraMetadataSectionStart::ANDROID_HOT_PIXEL_START:
    return "ANDROID_HOT_PIXEL_START";
  case CameraMetadataSectionStart::ANDROID_JPEG_START:
    return "ANDROID_JPEG_START";
  case CameraMetadataSectionStart::ANDROID_LENS_START:
    return "ANDROID_LENS_START";
  case CameraMetadataSectionStart::ANDROID_LENS_INFO_START:
    return "ANDROID_LENS_INFO_START";
  case CameraMetadataSectionStart::ANDROID_NOISE_REDUCTION_START:
    return "ANDROID_NOISE_REDUCTION_START";
  case CameraMetadataSectionStart::ANDROID_QUIRKS_START:
    return "ANDROID_QUIRKS_START";
  case CameraMetadataSectionStart::ANDROID_REQUEST_START:
    return "ANDROID_REQUEST_START";
  case CameraMetadataSectionStart::ANDROID_SCALER_START:
    return "ANDROID_SCALER_START";
  case CameraMetadataSectionStart::ANDROID_SENSOR_START:
    return "ANDROID_SENSOR_START";
  case CameraMetadataSectionStart::ANDROID_SENSOR_INFO_START:
    return "ANDROID_SENSOR_INFO_START";
  case CameraMetadataSectionStart::ANDROID_SHADING_START:
    return "ANDROID_SHADING_START";
  case CameraMetadataSectionStart::ANDROID_STATISTICS_START:
    return "ANDROID_STATISTICS_START";
  case CameraMetadataSectionStart::ANDROID_STATISTICS_INFO_START:
    return "ANDROID_STATISTICS_INFO_START";
  case CameraMetadataSectionStart::ANDROID_TONEMAP_START:
    return "ANDROID_TONEMAP_START";
  case CameraMetadataSectionStart::ANDROID_LED_START:
    return "ANDROID_LED_START";
  case CameraMetadataSectionStart::ANDROID_INFO_START:
    return "ANDROID_INFO_START";
  case CameraMetadataSectionStart::ANDROID_BLACK_LEVEL_START:
    return "ANDROID_BLACK_LEVEL_START";
  case CameraMetadataSectionStart::ANDROID_SYNC_START:
    return "ANDROID_SYNC_START";
  case CameraMetadataSectionStart::ANDROID_REPROCESS_START:
    return "ANDROID_REPROCESS_START";
  case CameraMetadataSectionStart::ANDROID_DEPTH_START:
    return "ANDROID_DEPTH_START";
  case CameraMetadataSectionStart::ANDROID_LOGICAL_MULTI_CAMERA_START:
    return "ANDROID_LOGICAL_MULTI_CAMERA_START";
  case CameraMetadataSectionStart::ANDROID_DISTORTION_CORRECTION_START:
    return "ANDROID_DISTORTION_CORRECTION_START";
  case CameraMetadataSectionStart::ANDROID_HEIC_START:
    return "ANDROID_HEIC_START";
  case CameraMetadataSectionStart::ANDROID_HEIC_INFO_START:
    return "ANDROID_HEIC_INFO_START";
  case CameraMetadataSectionStart::ANDROID_AUTOMOTIVE_START:
    return "ANDROID_AUTOMOTIVE_START";
  case CameraMetadataSectionStart::ANDROID_AUTOMOTIVE_LENS_START:
    return "ANDROID_AUTOMOTIVE_LENS_START";
  case CameraMetadataSectionStart::VENDOR_SECTION_START:
    return "VENDOR_SECTION_START";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace metadata
}  // namespace camera
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace ndk {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<aidl::android::hardware::camera::metadata::CameraMetadataSectionStart, 33> enum_values<aidl::android::hardware::camera::metadata::CameraMetadataSectionStart> = {
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_COLOR_CORRECTION_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_CONTROL_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_DEMOSAIC_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_EDGE_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_FLASH_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_FLASH_INFO_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_HOT_PIXEL_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_JPEG_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_LENS_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_LENS_INFO_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_NOISE_REDUCTION_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_QUIRKS_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_REQUEST_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_SCALER_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_SENSOR_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_SENSOR_INFO_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_SHADING_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_STATISTICS_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_STATISTICS_INFO_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_TONEMAP_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_LED_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_INFO_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_BLACK_LEVEL_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_SYNC_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_REPROCESS_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_DEPTH_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_LOGICAL_MULTI_CAMERA_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_DISTORTION_CORRECTION_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_HEIC_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_HEIC_INFO_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_AUTOMOTIVE_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::ANDROID_AUTOMOTIVE_LENS_START,
  aidl::android::hardware::camera::metadata::CameraMetadataSectionStart::VENDOR_SECTION_START,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
