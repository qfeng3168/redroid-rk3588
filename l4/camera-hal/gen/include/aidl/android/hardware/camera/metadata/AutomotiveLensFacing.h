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
enum class AutomotiveLensFacing : int32_t {
  ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_OTHER = 0,
  ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_FRONT = 1,
  ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_REAR = 2,
  ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_LEFT = 3,
  ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_RIGHT = 4,
  ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_OTHER = 5,
  ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_LEFT = 6,
  ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_CENTER = 7,
  ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_RIGHT = 8,
  ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_LEFT = 9,
  ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_CENTER = 10,
  ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_RIGHT = 11,
  ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_LEFT = 12,
  ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_CENTER = 13,
  ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_RIGHT = 14,
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
[[nodiscard]] static inline std::string toString(AutomotiveLensFacing val) {
  switch(val) {
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_OTHER:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_OTHER";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_FRONT:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_FRONT";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_REAR:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_REAR";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_LEFT:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_LEFT";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_RIGHT:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_RIGHT";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_OTHER:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_OTHER";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_LEFT:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_LEFT";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_CENTER:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_CENTER";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_RIGHT:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_RIGHT";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_LEFT:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_LEFT";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_CENTER:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_CENTER";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_RIGHT:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_RIGHT";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_LEFT:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_LEFT";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_CENTER:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_CENTER";
  case AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_RIGHT:
    return "ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_RIGHT";
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
constexpr inline std::array<aidl::android::hardware::camera::metadata::AutomotiveLensFacing, 15> enum_values<aidl::android::hardware::camera::metadata::AutomotiveLensFacing> = {
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_OTHER,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_FRONT,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_REAR,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_LEFT,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_EXTERIOR_RIGHT,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_OTHER,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_LEFT,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_CENTER,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_1_RIGHT,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_LEFT,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_CENTER,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_2_RIGHT,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_LEFT,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_CENTER,
  aidl::android::hardware::camera::metadata::AutomotiveLensFacing::ANDROID_AUTOMOTIVE_LENS_FACING_INTERIOR_SEAT_ROW_3_RIGHT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
