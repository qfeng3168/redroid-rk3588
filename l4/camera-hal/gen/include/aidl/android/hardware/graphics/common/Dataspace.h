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
namespace graphics {
namespace common {
enum class Dataspace : int32_t {
  UNKNOWN = 0,
  ARBITRARY = 1,
  STANDARD_SHIFT = 16,
  STANDARD_MASK = 4128768,
  STANDARD_UNSPECIFIED = 0,
  STANDARD_BT709 = 65536,
  STANDARD_BT601_625 = 131072,
  STANDARD_BT601_625_UNADJUSTED = 196608,
  STANDARD_BT601_525 = 262144,
  STANDARD_BT601_525_UNADJUSTED = 327680,
  STANDARD_BT2020 = 393216,
  STANDARD_BT2020_CONSTANT_LUMINANCE = 458752,
  STANDARD_BT470M = 524288,
  STANDARD_FILM = 589824,
  STANDARD_DCI_P3 = 655360,
  STANDARD_ADOBE_RGB = 720896,
  TRANSFER_SHIFT = 22,
  TRANSFER_MASK = 130023424,
  TRANSFER_UNSPECIFIED = 0,
  TRANSFER_LINEAR = 4194304,
  TRANSFER_SRGB = 8388608,
  TRANSFER_SMPTE_170M = 12582912,
  TRANSFER_GAMMA2_2 = 16777216,
  TRANSFER_GAMMA2_6 = 20971520,
  TRANSFER_GAMMA2_8 = 25165824,
  TRANSFER_ST2084 = 29360128,
  TRANSFER_HLG = 33554432,
  RANGE_SHIFT = 27,
  RANGE_MASK = 939524096,
  RANGE_UNSPECIFIED = 0,
  RANGE_FULL = 134217728,
  RANGE_LIMITED = 268435456,
  RANGE_EXTENDED = 402653184,
  SRGB_LINEAR = 138477568,
  SCRGB_LINEAR = 406913024,
  SRGB = 142671872,
  SCRGB = 411107328,
  JFIF = 146931712,
  BT601_625 = 281149440,
  BT601_525 = 281280512,
  BT709 = 281083904,
  DCI_P3_LINEAR = 139067392,
  DCI_P3 = 155844608,
  DISPLAY_P3_LINEAR = 139067392,
  DISPLAY_P3 = 143261696,
  ADOBE_RGB = 151715840,
  BT2020_LINEAR = 138805248,
  BT2020 = 147193856,
  BT2020_PQ = 163971072,
  DEPTH = 4096,
  SENSOR = 4097,
  BT2020_ITU = 281411584,
  BT2020_ITU_PQ = 298188800,
  BT2020_ITU_HLG = 302383104,
  BT2020_HLG = 168165376,
  DISPLAY_BT2020 = 142999552,
  DYNAMIC_DEPTH = 4098,
  JPEG_APP_SEGMENTS = 4099,
  HEIF = 4100,
  BT709_FULL_RANGE = 146866176,
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {
[[nodiscard]] static inline std::string toString(Dataspace val) {
  switch(val) {
  case Dataspace::UNKNOWN:
    return "UNKNOWN";
  case Dataspace::ARBITRARY:
    return "ARBITRARY";
  case Dataspace::STANDARD_SHIFT:
    return "STANDARD_SHIFT";
  case Dataspace::STANDARD_MASK:
    return "STANDARD_MASK";
  case Dataspace::STANDARD_BT709:
    return "STANDARD_BT709";
  case Dataspace::STANDARD_BT601_625:
    return "STANDARD_BT601_625";
  case Dataspace::STANDARD_BT601_625_UNADJUSTED:
    return "STANDARD_BT601_625_UNADJUSTED";
  case Dataspace::STANDARD_BT601_525:
    return "STANDARD_BT601_525";
  case Dataspace::STANDARD_BT601_525_UNADJUSTED:
    return "STANDARD_BT601_525_UNADJUSTED";
  case Dataspace::STANDARD_BT2020:
    return "STANDARD_BT2020";
  case Dataspace::STANDARD_BT2020_CONSTANT_LUMINANCE:
    return "STANDARD_BT2020_CONSTANT_LUMINANCE";
  case Dataspace::STANDARD_BT470M:
    return "STANDARD_BT470M";
  case Dataspace::STANDARD_FILM:
    return "STANDARD_FILM";
  case Dataspace::STANDARD_DCI_P3:
    return "STANDARD_DCI_P3";
  case Dataspace::STANDARD_ADOBE_RGB:
    return "STANDARD_ADOBE_RGB";
  case Dataspace::TRANSFER_SHIFT:
    return "TRANSFER_SHIFT";
  case Dataspace::TRANSFER_MASK:
    return "TRANSFER_MASK";
  case Dataspace::TRANSFER_LINEAR:
    return "TRANSFER_LINEAR";
  case Dataspace::TRANSFER_SRGB:
    return "TRANSFER_SRGB";
  case Dataspace::TRANSFER_SMPTE_170M:
    return "TRANSFER_SMPTE_170M";
  case Dataspace::TRANSFER_GAMMA2_2:
    return "TRANSFER_GAMMA2_2";
  case Dataspace::TRANSFER_GAMMA2_6:
    return "TRANSFER_GAMMA2_6";
  case Dataspace::TRANSFER_GAMMA2_8:
    return "TRANSFER_GAMMA2_8";
  case Dataspace::TRANSFER_ST2084:
    return "TRANSFER_ST2084";
  case Dataspace::TRANSFER_HLG:
    return "TRANSFER_HLG";
  case Dataspace::RANGE_SHIFT:
    return "RANGE_SHIFT";
  case Dataspace::RANGE_MASK:
    return "RANGE_MASK";
  case Dataspace::RANGE_FULL:
    return "RANGE_FULL";
  case Dataspace::RANGE_LIMITED:
    return "RANGE_LIMITED";
  case Dataspace::RANGE_EXTENDED:
    return "RANGE_EXTENDED";
  case Dataspace::SRGB_LINEAR:
    return "SRGB_LINEAR";
  case Dataspace::SCRGB_LINEAR:
    return "SCRGB_LINEAR";
  case Dataspace::SRGB:
    return "SRGB";
  case Dataspace::SCRGB:
    return "SCRGB";
  case Dataspace::JFIF:
    return "JFIF";
  case Dataspace::BT601_625:
    return "BT601_625";
  case Dataspace::BT601_525:
    return "BT601_525";
  case Dataspace::BT709:
    return "BT709";
  case Dataspace::DCI_P3_LINEAR:
    return "DCI_P3_LINEAR";
  case Dataspace::DCI_P3:
    return "DCI_P3";
  case Dataspace::DISPLAY_P3:
    return "DISPLAY_P3";
  case Dataspace::ADOBE_RGB:
    return "ADOBE_RGB";
  case Dataspace::BT2020_LINEAR:
    return "BT2020_LINEAR";
  case Dataspace::BT2020:
    return "BT2020";
  case Dataspace::BT2020_PQ:
    return "BT2020_PQ";
  case Dataspace::DEPTH:
    return "DEPTH";
  case Dataspace::SENSOR:
    return "SENSOR";
  case Dataspace::BT2020_ITU:
    return "BT2020_ITU";
  case Dataspace::BT2020_ITU_PQ:
    return "BT2020_ITU_PQ";
  case Dataspace::BT2020_ITU_HLG:
    return "BT2020_ITU_HLG";
  case Dataspace::BT2020_HLG:
    return "BT2020_HLG";
  case Dataspace::DISPLAY_BT2020:
    return "DISPLAY_BT2020";
  case Dataspace::DYNAMIC_DEPTH:
    return "DYNAMIC_DEPTH";
  case Dataspace::JPEG_APP_SEGMENTS:
    return "JPEG_APP_SEGMENTS";
  case Dataspace::HEIF:
    return "HEIF";
  case Dataspace::BT709_FULL_RANGE:
    return "BT709_FULL_RANGE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace ndk {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<aidl::android::hardware::graphics::common::Dataspace, 60> enum_values<aidl::android::hardware::graphics::common::Dataspace> = {
  aidl::android::hardware::graphics::common::Dataspace::UNKNOWN,
  aidl::android::hardware::graphics::common::Dataspace::ARBITRARY,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_SHIFT,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_MASK,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_UNSPECIFIED,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_BT709,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_BT601_625,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_BT601_625_UNADJUSTED,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_BT601_525,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_BT601_525_UNADJUSTED,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_BT2020,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_BT2020_CONSTANT_LUMINANCE,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_BT470M,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_FILM,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_DCI_P3,
  aidl::android::hardware::graphics::common::Dataspace::STANDARD_ADOBE_RGB,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_SHIFT,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_MASK,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_UNSPECIFIED,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_LINEAR,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_SRGB,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_SMPTE_170M,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_GAMMA2_2,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_GAMMA2_6,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_GAMMA2_8,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_ST2084,
  aidl::android::hardware::graphics::common::Dataspace::TRANSFER_HLG,
  aidl::android::hardware::graphics::common::Dataspace::RANGE_SHIFT,
  aidl::android::hardware::graphics::common::Dataspace::RANGE_MASK,
  aidl::android::hardware::graphics::common::Dataspace::RANGE_UNSPECIFIED,
  aidl::android::hardware::graphics::common::Dataspace::RANGE_FULL,
  aidl::android::hardware::graphics::common::Dataspace::RANGE_LIMITED,
  aidl::android::hardware::graphics::common::Dataspace::RANGE_EXTENDED,
  aidl::android::hardware::graphics::common::Dataspace::SRGB_LINEAR,
  aidl::android::hardware::graphics::common::Dataspace::SCRGB_LINEAR,
  aidl::android::hardware::graphics::common::Dataspace::SRGB,
  aidl::android::hardware::graphics::common::Dataspace::SCRGB,
  aidl::android::hardware::graphics::common::Dataspace::JFIF,
  aidl::android::hardware::graphics::common::Dataspace::BT601_625,
  aidl::android::hardware::graphics::common::Dataspace::BT601_525,
  aidl::android::hardware::graphics::common::Dataspace::BT709,
  aidl::android::hardware::graphics::common::Dataspace::DCI_P3_LINEAR,
  aidl::android::hardware::graphics::common::Dataspace::DCI_P3,
  aidl::android::hardware::graphics::common::Dataspace::DISPLAY_P3_LINEAR,
  aidl::android::hardware::graphics::common::Dataspace::DISPLAY_P3,
  aidl::android::hardware::graphics::common::Dataspace::ADOBE_RGB,
  aidl::android::hardware::graphics::common::Dataspace::BT2020_LINEAR,
  aidl::android::hardware::graphics::common::Dataspace::BT2020,
  aidl::android::hardware::graphics::common::Dataspace::BT2020_PQ,
  aidl::android::hardware::graphics::common::Dataspace::DEPTH,
  aidl::android::hardware::graphics::common::Dataspace::SENSOR,
  aidl::android::hardware::graphics::common::Dataspace::BT2020_ITU,
  aidl::android::hardware::graphics::common::Dataspace::BT2020_ITU_PQ,
  aidl::android::hardware::graphics::common::Dataspace::BT2020_ITU_HLG,
  aidl::android::hardware::graphics::common::Dataspace::BT2020_HLG,
  aidl::android::hardware::graphics::common::Dataspace::DISPLAY_BT2020,
  aidl::android::hardware::graphics::common::Dataspace::DYNAMIC_DEPTH,
  aidl::android::hardware::graphics::common::Dataspace::JPEG_APP_SEGMENTS,
  aidl::android::hardware::graphics::common::Dataspace::HEIF,
  aidl::android::hardware::graphics::common::Dataspace::BT709_FULL_RANGE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
