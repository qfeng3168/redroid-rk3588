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
enum class SensorReferenceIlluminant1 : int32_t {
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAYLIGHT = 1,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FLUORESCENT = 2,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_TUNGSTEN = 3,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FLASH = 4,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FINE_WEATHER = 9,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_CLOUDY_WEATHER = 10,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_SHADE = 11,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAYLIGHT_FLUORESCENT = 12,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAY_WHITE_FLUORESCENT = 13,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_COOL_WHITE_FLUORESCENT = 14,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_WHITE_FLUORESCENT = 15,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_A = 17,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_B = 18,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_C = 19,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D55 = 20,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D65 = 21,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D75 = 22,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D50 = 23,
  ANDROID_SENSOR_REFERENCE_ILLUMINANT1_ISO_STUDIO_TUNGSTEN = 24,
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
[[nodiscard]] static inline std::string toString(SensorReferenceIlluminant1 val) {
  switch(val) {
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAYLIGHT:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAYLIGHT";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FLUORESCENT:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FLUORESCENT";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_TUNGSTEN:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_TUNGSTEN";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FLASH:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FLASH";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FINE_WEATHER:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FINE_WEATHER";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_CLOUDY_WEATHER:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_CLOUDY_WEATHER";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_SHADE:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_SHADE";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAYLIGHT_FLUORESCENT:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAYLIGHT_FLUORESCENT";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAY_WHITE_FLUORESCENT:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAY_WHITE_FLUORESCENT";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_COOL_WHITE_FLUORESCENT:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_COOL_WHITE_FLUORESCENT";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_WHITE_FLUORESCENT:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_WHITE_FLUORESCENT";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_A:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_A";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_B:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_B";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_C:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_C";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D55:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D55";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D65:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D65";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D75:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D75";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D50:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D50";
  case SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_ISO_STUDIO_TUNGSTEN:
    return "ANDROID_SENSOR_REFERENCE_ILLUMINANT1_ISO_STUDIO_TUNGSTEN";
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
constexpr inline std::array<aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1, 19> enum_values<aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1> = {
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAYLIGHT,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FLUORESCENT,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_TUNGSTEN,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FLASH,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_FINE_WEATHER,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_CLOUDY_WEATHER,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_SHADE,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAYLIGHT_FLUORESCENT,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_DAY_WHITE_FLUORESCENT,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_COOL_WHITE_FLUORESCENT,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_WHITE_FLUORESCENT,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_A,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_B,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_STANDARD_C,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D55,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D65,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D75,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_D50,
  aidl::android::hardware::camera::metadata::SensorReferenceIlluminant1::ANDROID_SENSOR_REFERENCE_ILLUMINANT1_ISO_STUDIO_TUNGSTEN,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
