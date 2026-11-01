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
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace hardware {
namespace camera {
namespace metadata {
enum class CameraMetadataSection : int32_t {
  ANDROID_COLOR_CORRECTION = 0,
  ANDROID_CONTROL = 1,
  ANDROID_DEMOSAIC = 2,
  ANDROID_EDGE = 3,
  ANDROID_FLASH = 4,
  ANDROID_FLASH_INFO = 5,
  ANDROID_HOT_PIXEL = 6,
  ANDROID_JPEG = 7,
  ANDROID_LENS = 8,
  ANDROID_LENS_INFO = 9,
  ANDROID_NOISE_REDUCTION = 10,
  ANDROID_QUIRKS = 11,
  ANDROID_REQUEST = 12,
  ANDROID_SCALER = 13,
  ANDROID_SENSOR = 14,
  ANDROID_SENSOR_INFO = 15,
  ANDROID_SHADING = 16,
  ANDROID_STATISTICS = 17,
  ANDROID_STATISTICS_INFO = 18,
  ANDROID_TONEMAP = 19,
  ANDROID_LED = 20,
  ANDROID_INFO = 21,
  ANDROID_BLACK_LEVEL = 22,
  ANDROID_SYNC = 23,
  ANDROID_REPROCESS = 24,
  ANDROID_DEPTH = 25,
  ANDROID_LOGICAL_MULTI_CAMERA = 26,
  ANDROID_DISTORTION_CORRECTION = 27,
  ANDROID_HEIC = 28,
  ANDROID_HEIC_INFO = 29,
  ANDROID_AUTOMOTIVE = 30,
  ANDROID_AUTOMOTIVE_LENS = 31,
  VENDOR_SECTION = 32768,
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
[[nodiscard]] static inline std::string toString(CameraMetadataSection val) {
  switch(val) {
  case CameraMetadataSection::ANDROID_COLOR_CORRECTION:
    return "ANDROID_COLOR_CORRECTION";
  case CameraMetadataSection::ANDROID_CONTROL:
    return "ANDROID_CONTROL";
  case CameraMetadataSection::ANDROID_DEMOSAIC:
    return "ANDROID_DEMOSAIC";
  case CameraMetadataSection::ANDROID_EDGE:
    return "ANDROID_EDGE";
  case CameraMetadataSection::ANDROID_FLASH:
    return "ANDROID_FLASH";
  case CameraMetadataSection::ANDROID_FLASH_INFO:
    return "ANDROID_FLASH_INFO";
  case CameraMetadataSection::ANDROID_HOT_PIXEL:
    return "ANDROID_HOT_PIXEL";
  case CameraMetadataSection::ANDROID_JPEG:
    return "ANDROID_JPEG";
  case CameraMetadataSection::ANDROID_LENS:
    return "ANDROID_LENS";
  case CameraMetadataSection::ANDROID_LENS_INFO:
    return "ANDROID_LENS_INFO";
  case CameraMetadataSection::ANDROID_NOISE_REDUCTION:
    return "ANDROID_NOISE_REDUCTION";
  case CameraMetadataSection::ANDROID_QUIRKS:
    return "ANDROID_QUIRKS";
  case CameraMetadataSection::ANDROID_REQUEST:
    return "ANDROID_REQUEST";
  case CameraMetadataSection::ANDROID_SCALER:
    return "ANDROID_SCALER";
  case CameraMetadataSection::ANDROID_SENSOR:
    return "ANDROID_SENSOR";
  case CameraMetadataSection::ANDROID_SENSOR_INFO:
    return "ANDROID_SENSOR_INFO";
  case CameraMetadataSection::ANDROID_SHADING:
    return "ANDROID_SHADING";
  case CameraMetadataSection::ANDROID_STATISTICS:
    return "ANDROID_STATISTICS";
  case CameraMetadataSection::ANDROID_STATISTICS_INFO:
    return "ANDROID_STATISTICS_INFO";
  case CameraMetadataSection::ANDROID_TONEMAP:
    return "ANDROID_TONEMAP";
  case CameraMetadataSection::ANDROID_LED:
    return "ANDROID_LED";
  case CameraMetadataSection::ANDROID_INFO:
    return "ANDROID_INFO";
  case CameraMetadataSection::ANDROID_BLACK_LEVEL:
    return "ANDROID_BLACK_LEVEL";
  case CameraMetadataSection::ANDROID_SYNC:
    return "ANDROID_SYNC";
  case CameraMetadataSection::ANDROID_REPROCESS:
    return "ANDROID_REPROCESS";
  case CameraMetadataSection::ANDROID_DEPTH:
    return "ANDROID_DEPTH";
  case CameraMetadataSection::ANDROID_LOGICAL_MULTI_CAMERA:
    return "ANDROID_LOGICAL_MULTI_CAMERA";
  case CameraMetadataSection::ANDROID_DISTORTION_CORRECTION:
    return "ANDROID_DISTORTION_CORRECTION";
  case CameraMetadataSection::ANDROID_HEIC:
    return "ANDROID_HEIC";
  case CameraMetadataSection::ANDROID_HEIC_INFO:
    return "ANDROID_HEIC_INFO";
  case CameraMetadataSection::ANDROID_AUTOMOTIVE:
    return "ANDROID_AUTOMOTIVE";
  case CameraMetadataSection::ANDROID_AUTOMOTIVE_LENS:
    return "ANDROID_AUTOMOTIVE_LENS";
  case CameraMetadataSection::VENDOR_SECTION:
    return "VENDOR_SECTION";
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
constexpr inline std::array<aidl::android::hardware::camera::metadata::CameraMetadataSection, 33> enum_values<aidl::android::hardware::camera::metadata::CameraMetadataSection> = {
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_COLOR_CORRECTION,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_CONTROL,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_DEMOSAIC,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_EDGE,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_FLASH,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_FLASH_INFO,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_HOT_PIXEL,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_JPEG,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_LENS,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_LENS_INFO,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_NOISE_REDUCTION,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_QUIRKS,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_REQUEST,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_SCALER,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_SENSOR,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_SENSOR_INFO,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_SHADING,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_STATISTICS,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_STATISTICS_INFO,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_TONEMAP,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_LED,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_INFO,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_BLACK_LEVEL,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_SYNC,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_REPROCESS,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_DEPTH,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_LOGICAL_MULTI_CAMERA,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_DISTORTION_CORRECTION,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_HEIC,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_HEIC_INFO,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_AUTOMOTIVE,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::ANDROID_AUTOMOTIVE_LENS,
  aidl::android::hardware::camera::metadata::CameraMetadataSection::VENDOR_SECTION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
