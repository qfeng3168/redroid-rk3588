/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -I aidl-src --out=gen/src --header_out=gen/include aidl-src/android/hardware/gnss/BlocklistedSource.aidl aidl-src/android/hardware/gnss/CorrelationVector.aidl aidl-src/android/hardware/gnss/ElapsedRealtime.aidl aidl-src/android/hardware/gnss/GnssClock.aidl aidl-src/android/hardware/gnss/GnssConstellationType.aidl aidl-src/android/hardware/gnss/GnssData.aidl aidl-src/android/hardware/gnss/GnssLocation.aidl aidl-src/android/hardware/gnss/GnssMeasurement.aidl aidl-src/android/hardware/gnss/GnssMultipathIndicator.aidl aidl-src/android/hardware/gnss/GnssPowerStats.aidl aidl-src/android/hardware/gnss/GnssSignalType.aidl aidl-src/android/hardware/gnss/IAGnss.aidl aidl-src/android/hardware/gnss/IAGnssCallback.aidl aidl-src/android/hardware/gnss/IAGnssRil.aidl aidl-src/android/hardware/gnss/IAGnssRilCallback.aidl aidl-src/android/hardware/gnss/IGnss.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfo.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfoCallback.aidl aidl-src/android/hardware/gnss/IGnssBatching.aidl aidl-src/android/hardware/gnss/IGnssBatchingCallback.aidl aidl-src/android/hardware/gnss/IGnssCallback.aidl aidl-src/android/hardware/gnss/IGnssConfiguration.aidl aidl-src/android/hardware/gnss/IGnssDebug.aidl aidl-src/android/hardware/gnss/IGnssGeofence.aidl aidl-src/android/hardware/gnss/IGnssGeofenceCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementInterface.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageCallback.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageInterface.aidl aidl-src/android/hardware/gnss/IGnssPowerIndication.aidl aidl-src/android/hardware/gnss/IGnssPowerIndicationCallback.aidl aidl-src/android/hardware/gnss/IGnssPsds.aidl aidl-src/android/hardware/gnss/IGnssPsdsCallback.aidl aidl-src/android/hardware/gnss/PsdsType.aidl aidl-src/android/hardware/gnss/SatelliteClockInfo.aidl aidl-src/android/hardware/gnss/SatellitePositionEcef.aidl aidl-src/android/hardware/gnss/SatellitePvt.aidl aidl-src/android/hardware/gnss/SatelliteVelocityEcef.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsCallback.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsInterface.aidl aidl-src/android/hardware/gnss/measurement_corrections/MeasurementCorrections.aidl aidl-src/android/hardware/gnss/measurement_corrections/ReflectingPlane.aidl aidl-src/android/hardware/gnss/measurement_corrections/SingleSatCorrection.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControl.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControlCallback.aidl
 */
#include "aidl/android/hardware/gnss/IGnssMeasurementCallback.h"

#include <android/binder_parcel_utils.h>
#include <aidl/android/hardware/gnss/BnGnssMeasurementCallback.h>
#include <aidl/android/hardware/gnss/BpGnssMeasurementCallback.h>

namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
static binder_status_t _aidl_android_hardware_gnss_IGnssMeasurementCallback_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnGnssMeasurementCallback> _aidl_impl = std::static_pointer_cast<BnGnssMeasurementCallback>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*gnssMeasurementCb*/): {
      ::aidl::android::hardware::gnss::GnssData in_data;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_data);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->gnssMeasurementCb(in_data);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_hardware_gnss_IGnssMeasurementCallback_clazz = ::ndk::ICInterface::defineClass(IGnssMeasurementCallback::descriptor, _aidl_android_hardware_gnss_IGnssMeasurementCallback_onTransact);

BpGnssMeasurementCallback::BpGnssMeasurementCallback(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpGnssMeasurementCallback::~BpGnssMeasurementCallback() {}

::ndk::ScopedAStatus BpGnssMeasurementCallback::gnssMeasurementCb(const ::aidl::android::hardware::gnss::GnssData& in_data) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_data);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 0 /*gnssMeasurementCb*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IGnssMeasurementCallback::getDefaultImpl()) {
    _aidl_status = IGnssMeasurementCallback::getDefaultImpl()->gnssMeasurementCb(in_data);
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
// Source for BnGnssMeasurementCallback
BnGnssMeasurementCallback::BnGnssMeasurementCallback() {}
BnGnssMeasurementCallback::~BnGnssMeasurementCallback() {}
::ndk::SpAIBinder BnGnssMeasurementCallback::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_hardware_gnss_IGnssMeasurementCallback_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markVintfStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IGnssMeasurementCallback
const char* IGnssMeasurementCallback::descriptor = "android.hardware.gnss.IGnssMeasurementCallback";
IGnssMeasurementCallback::IGnssMeasurementCallback() {}
IGnssMeasurementCallback::~IGnssMeasurementCallback() {}


std::shared_ptr<IGnssMeasurementCallback> IGnssMeasurementCallback::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_hardware_gnss_IGnssMeasurementCallback_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpGnssMeasurementCallback>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IGnssMeasurementCallback>(interface);
  }
  return ::ndk::SharedRefBase::make<BpGnssMeasurementCallback>(binder);
}

binder_status_t IGnssMeasurementCallback::writeToParcel(AParcel* parcel, const std::shared_ptr<IGnssMeasurementCallback>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IGnssMeasurementCallback::readFromParcel(const AParcel* parcel, std::shared_ptr<IGnssMeasurementCallback>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IGnssMeasurementCallback::fromBinder(binder);
  return STATUS_OK;
}
bool IGnssMeasurementCallback::setDefaultImpl(const std::shared_ptr<IGnssMeasurementCallback>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IGnssMeasurementCallback::default_impl);
  if (impl) {
    IGnssMeasurementCallback::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IGnssMeasurementCallback>& IGnssMeasurementCallback::getDefaultImpl() {
  return IGnssMeasurementCallback::default_impl;
}
std::shared_ptr<IGnssMeasurementCallback> IGnssMeasurementCallback::default_impl = nullptr;
::ndk::ScopedAStatus IGnssMeasurementCallbackDefault::gnssMeasurementCb(const ::aidl::android::hardware::gnss::GnssData& /*in_data*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IGnssMeasurementCallbackDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IGnssMeasurementCallbackDefault::isRemote() {
  return false;
}
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
