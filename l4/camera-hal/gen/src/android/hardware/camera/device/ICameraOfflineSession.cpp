/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -I aidl-src --out=gen/src --header_out=gen/include aidl-src/android/hardware/camera/common/CameraDeviceStatus.aidl aidl-src/android/hardware/camera/common/CameraMetadataType.aidl aidl-src/android/hardware/camera/common/CameraResourceCost.aidl aidl-src/android/hardware/camera/common/Status.aidl aidl-src/android/hardware/camera/common/TagBoundaryId.aidl aidl-src/android/hardware/camera/common/TorchModeStatus.aidl aidl-src/android/hardware/camera/common/VendorTag.aidl aidl-src/android/hardware/camera/common/VendorTagSection.aidl aidl-src/android/hardware/camera/device/BufferCache.aidl aidl-src/android/hardware/camera/device/BufferRequest.aidl aidl-src/android/hardware/camera/device/BufferRequestStatus.aidl aidl-src/android/hardware/camera/device/BufferStatus.aidl aidl-src/android/hardware/camera/device/CameraBlob.aidl aidl-src/android/hardware/camera/device/CameraBlobId.aidl aidl-src/android/hardware/camera/device/CameraMetadata.aidl aidl-src/android/hardware/camera/device/CameraOfflineSessionInfo.aidl aidl-src/android/hardware/camera/device/CaptureRequest.aidl aidl-src/android/hardware/camera/device/CaptureResult.aidl aidl-src/android/hardware/camera/device/ErrorCode.aidl aidl-src/android/hardware/camera/device/ErrorMsg.aidl aidl-src/android/hardware/camera/device/HalStream.aidl aidl-src/android/hardware/camera/device/ICameraDevice.aidl aidl-src/android/hardware/camera/device/ICameraDeviceCallback.aidl aidl-src/android/hardware/camera/device/ICameraDeviceSession.aidl aidl-src/android/hardware/camera/device/ICameraInjectionSession.aidl aidl-src/android/hardware/camera/device/ICameraOfflineSession.aidl aidl-src/android/hardware/camera/device/NotifyMsg.aidl aidl-src/android/hardware/camera/device/OfflineRequest.aidl aidl-src/android/hardware/camera/device/OfflineStream.aidl aidl-src/android/hardware/camera/device/PhysicalCameraMetadata.aidl aidl-src/android/hardware/camera/device/PhysicalCameraSetting.aidl aidl-src/android/hardware/camera/device/RequestTemplate.aidl aidl-src/android/hardware/camera/device/ShutterMsg.aidl aidl-src/android/hardware/camera/device/Stream.aidl aidl-src/android/hardware/camera/device/StreamBuffer.aidl aidl-src/android/hardware/camera/device/StreamBufferRequestError.aidl aidl-src/android/hardware/camera/device/StreamBufferRet.aidl aidl-src/android/hardware/camera/device/StreamBuffersVal.aidl aidl-src/android/hardware/camera/device/StreamConfiguration.aidl aidl-src/android/hardware/camera/device/StreamConfigurationMode.aidl aidl-src/android/hardware/camera/device/StreamRotation.aidl aidl-src/android/hardware/camera/device/StreamType.aidl aidl-src/android/hardware/camera/provider/CameraIdAndStreamCombination.aidl aidl-src/android/hardware/camera/provider/ConcurrentCameraIdCombination.aidl aidl-src/android/hardware/camera/provider/ICameraProvider.aidl aidl-src/android/hardware/camera/provider/ICameraProviderCallback.aidl aidl-src/android/hardware/camera/metadata/AutomotiveLensFacing.aidl aidl-src/android/hardware/camera/metadata/AutomotiveLocation.aidl aidl-src/android/hardware/camera/metadata/BlackLevelLock.aidl aidl-src/android/hardware/camera/metadata/CameraMetadataSection.aidl aidl-src/android/hardware/camera/metadata/CameraMetadataSectionStart.aidl aidl-src/android/hardware/camera/metadata/CameraMetadataTag.aidl aidl-src/android/hardware/camera/metadata/ColorCorrectionAberrationMode.aidl aidl-src/android/hardware/camera/metadata/ColorCorrectionMode.aidl aidl-src/android/hardware/camera/metadata/ControlAeAntibandingMode.aidl aidl-src/android/hardware/camera/metadata/ControlAeLock.aidl aidl-src/android/hardware/camera/metadata/ControlAeLockAvailable.aidl aidl-src/android/hardware/camera/metadata/ControlAeMode.aidl aidl-src/android/hardware/camera/metadata/ControlAePrecaptureTrigger.aidl aidl-src/android/hardware/camera/metadata/ControlAeState.aidl aidl-src/android/hardware/camera/metadata/ControlAfMode.aidl aidl-src/android/hardware/camera/metadata/ControlAfSceneChange.aidl aidl-src/android/hardware/camera/metadata/ControlAfState.aidl aidl-src/android/hardware/camera/metadata/ControlAfTrigger.aidl aidl-src/android/hardware/camera/metadata/ControlAwbLock.aidl aidl-src/android/hardware/camera/metadata/ControlAwbLockAvailable.aidl aidl-src/android/hardware/camera/metadata/ControlAwbMode.aidl aidl-src/android/hardware/camera/metadata/ControlAwbState.aidl aidl-src/android/hardware/camera/metadata/ControlCaptureIntent.aidl aidl-src/android/hardware/camera/metadata/ControlEffectMode.aidl aidl-src/android/hardware/camera/metadata/ControlEnableZsl.aidl aidl-src/android/hardware/camera/metadata/ControlExtendedSceneMode.aidl aidl-src/android/hardware/camera/metadata/ControlMode.aidl aidl-src/android/hardware/camera/metadata/ControlSceneMode.aidl aidl-src/android/hardware/camera/metadata/ControlVideoStabilizationMode.aidl aidl-src/android/hardware/camera/metadata/DemosaicMode.aidl aidl-src/android/hardware/camera/metadata/DepthAvailableDepthStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/DepthAvailableDepthStreamConfigurationsMaximumResolution.aidl aidl-src/android/hardware/camera/metadata/DepthAvailableDynamicDepthStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/DepthAvailableDynamicDepthStreamConfigurationsMaximumResolution.aidl aidl-src/android/hardware/camera/metadata/DepthDepthIsExclusive.aidl aidl-src/android/hardware/camera/metadata/DistortionCorrectionMode.aidl aidl-src/android/hardware/camera/metadata/EdgeMode.aidl aidl-src/android/hardware/camera/metadata/FlashInfoAvailable.aidl aidl-src/android/hardware/camera/metadata/FlashMode.aidl aidl-src/android/hardware/camera/metadata/FlashState.aidl aidl-src/android/hardware/camera/metadata/HeicAvailableHeicStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/HeicAvailableHeicStreamConfigurationsMaximumResolution.aidl aidl-src/android/hardware/camera/metadata/HeicInfoSupported.aidl aidl-src/android/hardware/camera/metadata/HotPixelMode.aidl aidl-src/android/hardware/camera/metadata/InfoSupportedBufferManagementVersion.aidl aidl-src/android/hardware/camera/metadata/InfoSupportedHardwareLevel.aidl aidl-src/android/hardware/camera/metadata/LedAvailableLeds.aidl aidl-src/android/hardware/camera/metadata/LedTransmit.aidl aidl-src/android/hardware/camera/metadata/LensFacing.aidl aidl-src/android/hardware/camera/metadata/LensInfoFocusDistanceCalibration.aidl aidl-src/android/hardware/camera/metadata/LensOpticalStabilizationMode.aidl aidl-src/android/hardware/camera/metadata/LensPoseReference.aidl aidl-src/android/hardware/camera/metadata/LensState.aidl aidl-src/android/hardware/camera/metadata/LogicalMultiCameraSensorSyncType.aidl aidl-src/android/hardware/camera/metadata/NoiseReductionMode.aidl aidl-src/android/hardware/camera/metadata/QuirksPartialResult.aidl aidl-src/android/hardware/camera/metadata/RequestAvailableCapabilities.aidl aidl-src/android/hardware/camera/metadata/RequestAvailableDynamicRangeProfilesMap.aidl aidl-src/android/hardware/camera/metadata/RequestMetadataMode.aidl aidl-src/android/hardware/camera/metadata/RequestType.aidl aidl-src/android/hardware/camera/metadata/ScalerAvailableFormats.aidl aidl-src/android/hardware/camera/metadata/ScalerAvailableRecommendedStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/ScalerAvailableStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/ScalerAvailableStreamConfigurationsMaximumResolution.aidl aidl-src/android/hardware/camera/metadata/ScalerAvailableStreamUseCases.aidl aidl-src/android/hardware/camera/metadata/ScalerCroppingType.aidl aidl-src/android/hardware/camera/metadata/ScalerMultiResolutionStreamSupported.aidl aidl-src/android/hardware/camera/metadata/ScalerPhysicalCameraMultiResolutionStreamConfigurations.aidl aidl-src/android/hardware/camera/metadata/ScalerRotateAndCrop.aidl aidl-src/android/hardware/camera/metadata/SensorInfoColorFilterArrangement.aidl aidl-src/android/hardware/camera/metadata/SensorInfoLensShadingApplied.aidl aidl-src/android/hardware/camera/metadata/SensorInfoTimestampSource.aidl aidl-src/android/hardware/camera/metadata/SensorPixelMode.aidl aidl-src/android/hardware/camera/metadata/SensorRawBinningFactorUsed.aidl aidl-src/android/hardware/camera/metadata/SensorReferenceIlluminant1.aidl aidl-src/android/hardware/camera/metadata/SensorTestPatternMode.aidl aidl-src/android/hardware/camera/metadata/ShadingMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsFaceDetectMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsHistogramMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsHotPixelMapMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsLensShadingMapMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsOisDataMode.aidl aidl-src/android/hardware/camera/metadata/StatisticsSceneFlicker.aidl aidl-src/android/hardware/camera/metadata/StatisticsSharpnessMapMode.aidl aidl-src/android/hardware/camera/metadata/SyncFrameNumber.aidl aidl-src/android/hardware/camera/metadata/SyncMaxLatency.aidl aidl-src/android/hardware/camera/metadata/TonemapMode.aidl aidl-src/android/hardware/camera/metadata/TonemapPresetCurve.aidl aidl-src/android/hardware/common/Ashmem.aidl aidl-src/android/hardware/common/MappableFile.aidl aidl-src/android/hardware/common/NativeHandle.aidl aidl-src/android/hardware/common/fmq/MQDescriptor.aidl aidl-src/android/hardware/common/fmq/SynchronizedReadWrite.aidl aidl-src/android/hardware/common/fmq/UnsynchronizedWrite.aidl aidl-src/android/hardware/common/fmq/GrantorDescriptor.aidl aidl-src/android/hardware/graphics/common/AlphaInterpretation.aidl aidl-src/android/hardware/graphics/common/BlendMode.aidl aidl-src/android/hardware/graphics/common/BufferUsage.aidl aidl-src/android/hardware/graphics/common/ChromaSiting.aidl aidl-src/android/hardware/graphics/common/ColorTransform.aidl aidl-src/android/hardware/graphics/common/Compression.aidl aidl-src/android/hardware/graphics/common/Cta861_3.aidl aidl-src/android/hardware/graphics/common/Dataspace.aidl aidl-src/android/hardware/graphics/common/DisplayDecorationSupport.aidl aidl-src/android/hardware/graphics/common/ExtendableType.aidl aidl-src/android/hardware/graphics/common/FRect.aidl aidl-src/android/hardware/graphics/common/HardwareBuffer.aidl aidl-src/android/hardware/graphics/common/HardwareBufferDescription.aidl aidl-src/android/hardware/graphics/common/Hdr.aidl aidl-src/android/hardware/graphics/common/Interlaced.aidl aidl-src/android/hardware/graphics/common/PixelFormat.aidl aidl-src/android/hardware/graphics/common/PlaneLayout.aidl aidl-src/android/hardware/graphics/common/PlaneLayoutComponent.aidl aidl-src/android/hardware/graphics/common/PlaneLayoutComponentType.aidl aidl-src/android/hardware/graphics/common/Point.aidl aidl-src/android/hardware/graphics/common/Rect.aidl aidl-src/android/hardware/graphics/common/Smpte2086.aidl aidl-src/android/hardware/graphics/common/StandardMetadataType.aidl aidl-src/android/hardware/graphics/common/Transform.aidl aidl-src/android/hardware/graphics/common/XyColor.aidl
 */
#include "aidl/android/hardware/camera/device/ICameraOfflineSession.h"

#include <android/binder_parcel_utils.h>
#include <aidl/android/hardware/camera/device/BnCameraDeviceCallback.h>
#include <aidl/android/hardware/camera/device/BnCameraOfflineSession.h>
#include <aidl/android/hardware/camera/device/BpCameraDeviceCallback.h>
#include <aidl/android/hardware/camera/device/BpCameraOfflineSession.h>
#include <aidl/android/hardware/camera/device/ICameraDeviceCallback.h>

namespace aidl {
namespace android {
namespace hardware {
namespace camera {
namespace device {
static binder_status_t _aidl_android_hardware_camera_device_ICameraOfflineSession_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnCameraOfflineSession> _aidl_impl = std::static_pointer_cast<BnCameraOfflineSession>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*close*/): {

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->close();
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*getCaptureResultMetadataQueue*/): {
      ::aidl::android::hardware::common::fmq::MQDescriptor<int8_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite> _aidl_return;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->getCaptureResultMetadataQueue(&_aidl_return);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_out, _aidl_return);
      if (_aidl_ret_status != STATUS_OK) break;

      break;
    }
    case (FIRST_CALL_TRANSACTION + 2 /*setCallback*/): {
      std::shared_ptr<::aidl::android::hardware::camera::device::ICameraDeviceCallback> in_cb;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_cb);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->setCallback(in_cb);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_hardware_camera_device_ICameraOfflineSession_clazz = ::ndk::ICInterface::defineClass(ICameraOfflineSession::descriptor, _aidl_android_hardware_camera_device_ICameraOfflineSession_onTransact);

BpCameraOfflineSession::BpCameraOfflineSession(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpCameraOfflineSession::~BpCameraOfflineSession() {}

::ndk::ScopedAStatus BpCameraOfflineSession::close() {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 0 /*close*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && ICameraOfflineSession::getDefaultImpl()) {
    _aidl_status = ICameraOfflineSession::getDefaultImpl()->close();
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) goto _aidl_status_return;
  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpCameraOfflineSession::getCaptureResultMetadataQueue(::aidl::android::hardware::common::fmq::MQDescriptor<int8_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>* _aidl_return) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 1 /*getCaptureResultMetadataQueue*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && ICameraOfflineSession::getDefaultImpl()) {
    _aidl_status = ICameraOfflineSession::getDefaultImpl()->getCaptureResultMetadataQueue(_aidl_return);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) goto _aidl_status_return;
  _aidl_ret_status = ::ndk::AParcel_readData(_aidl_out.get(), _aidl_return);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpCameraOfflineSession::setCallback(const std::shared_ptr<::aidl::android::hardware::camera::device::ICameraDeviceCallback>& in_cb) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_cb);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 2 /*setCallback*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && ICameraOfflineSession::getDefaultImpl()) {
    _aidl_status = ICameraOfflineSession::getDefaultImpl()->setCallback(in_cb);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) goto _aidl_status_return;
  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnCameraOfflineSession
BnCameraOfflineSession::BnCameraOfflineSession() {}
BnCameraOfflineSession::~BnCameraOfflineSession() {}
::ndk::SpAIBinder BnCameraOfflineSession::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_hardware_camera_device_ICameraOfflineSession_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markVintfStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for ICameraOfflineSession
const char* ICameraOfflineSession::descriptor = "android.hardware.camera.device.ICameraOfflineSession";
ICameraOfflineSession::ICameraOfflineSession() {}
ICameraOfflineSession::~ICameraOfflineSession() {}


std::shared_ptr<ICameraOfflineSession> ICameraOfflineSession::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_hardware_camera_device_ICameraOfflineSession_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpCameraOfflineSession>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<ICameraOfflineSession>(interface);
  }
  return ::ndk::SharedRefBase::make<BpCameraOfflineSession>(binder);
}

binder_status_t ICameraOfflineSession::writeToParcel(AParcel* parcel, const std::shared_ptr<ICameraOfflineSession>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t ICameraOfflineSession::readFromParcel(const AParcel* parcel, std::shared_ptr<ICameraOfflineSession>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = ICameraOfflineSession::fromBinder(binder);
  return STATUS_OK;
}
bool ICameraOfflineSession::setDefaultImpl(const std::shared_ptr<ICameraOfflineSession>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!ICameraOfflineSession::default_impl);
  if (impl) {
    ICameraOfflineSession::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<ICameraOfflineSession>& ICameraOfflineSession::getDefaultImpl() {
  return ICameraOfflineSession::default_impl;
}
std::shared_ptr<ICameraOfflineSession> ICameraOfflineSession::default_impl = nullptr;
::ndk::ScopedAStatus ICameraOfflineSessionDefault::close() {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus ICameraOfflineSessionDefault::getCaptureResultMetadataQueue(::aidl::android::hardware::common::fmq::MQDescriptor<int8_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>* /*_aidl_return*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus ICameraOfflineSessionDefault::setCallback(const std::shared_ptr<::aidl::android::hardware::camera::device::ICameraDeviceCallback>& /*in_cb*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder ICameraOfflineSessionDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool ICameraOfflineSessionDefault::isRemote() {
  return false;
}
}  // namespace device
}  // namespace camera
}  // namespace hardware
}  // namespace android
}  // namespace aidl
