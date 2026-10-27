/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -I aidl-src --out=gen/src --header_out=gen/include aidl-src/android/hardware/gnss/BlocklistedSource.aidl aidl-src/android/hardware/gnss/CorrelationVector.aidl aidl-src/android/hardware/gnss/ElapsedRealtime.aidl aidl-src/android/hardware/gnss/GnssClock.aidl aidl-src/android/hardware/gnss/GnssConstellationType.aidl aidl-src/android/hardware/gnss/GnssData.aidl aidl-src/android/hardware/gnss/GnssLocation.aidl aidl-src/android/hardware/gnss/GnssMeasurement.aidl aidl-src/android/hardware/gnss/GnssMultipathIndicator.aidl aidl-src/android/hardware/gnss/GnssPowerStats.aidl aidl-src/android/hardware/gnss/GnssSignalType.aidl aidl-src/android/hardware/gnss/IAGnss.aidl aidl-src/android/hardware/gnss/IAGnssCallback.aidl aidl-src/android/hardware/gnss/IAGnssRil.aidl aidl-src/android/hardware/gnss/IAGnssRilCallback.aidl aidl-src/android/hardware/gnss/IGnss.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfo.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfoCallback.aidl aidl-src/android/hardware/gnss/IGnssBatching.aidl aidl-src/android/hardware/gnss/IGnssBatchingCallback.aidl aidl-src/android/hardware/gnss/IGnssCallback.aidl aidl-src/android/hardware/gnss/IGnssConfiguration.aidl aidl-src/android/hardware/gnss/IGnssDebug.aidl aidl-src/android/hardware/gnss/IGnssGeofence.aidl aidl-src/android/hardware/gnss/IGnssGeofenceCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementInterface.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageCallback.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageInterface.aidl aidl-src/android/hardware/gnss/IGnssPowerIndication.aidl aidl-src/android/hardware/gnss/IGnssPowerIndicationCallback.aidl aidl-src/android/hardware/gnss/IGnssPsds.aidl aidl-src/android/hardware/gnss/IGnssPsdsCallback.aidl aidl-src/android/hardware/gnss/PsdsType.aidl aidl-src/android/hardware/gnss/SatelliteClockInfo.aidl aidl-src/android/hardware/gnss/SatellitePositionEcef.aidl aidl-src/android/hardware/gnss/SatellitePvt.aidl aidl-src/android/hardware/gnss/SatelliteVelocityEcef.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsCallback.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsInterface.aidl aidl-src/android/hardware/gnss/measurement_corrections/MeasurementCorrections.aidl aidl-src/android/hardware/gnss/measurement_corrections/ReflectingPlane.aidl aidl-src/android/hardware/gnss/measurement_corrections/SingleSatCorrection.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControl.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControlCallback.aidl
 */
#include "aidl/android/hardware/gnss/IGnssPsds.h"

#include <android/binder_parcel_utils.h>
#include <aidl/android/hardware/gnss/BnGnssPsds.h>
#include <aidl/android/hardware/gnss/BnGnssPsdsCallback.h>
#include <aidl/android/hardware/gnss/BpGnssPsds.h>
#include <aidl/android/hardware/gnss/BpGnssPsdsCallback.h>
#include <aidl/android/hardware/gnss/IGnssPsdsCallback.h>

namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
static binder_status_t _aidl_android_hardware_gnss_IGnssPsds_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnGnssPsds> _aidl_impl = std::static_pointer_cast<BnGnssPsds>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*injectPsdsData*/): {
      ::aidl::android::hardware::gnss::PsdsType in_psdsType;
      std::vector<uint8_t> in_psdsData;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_psdsType);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_psdsData);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->injectPsdsData(in_psdsType, in_psdsData);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*setCallback*/): {
      std::shared_ptr<::aidl::android::hardware::gnss::IGnssPsdsCallback> in_callback;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_callback);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->setCallback(in_callback);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_hardware_gnss_IGnssPsds_clazz = ::ndk::ICInterface::defineClass(IGnssPsds::descriptor, _aidl_android_hardware_gnss_IGnssPsds_onTransact);

BpGnssPsds::BpGnssPsds(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpGnssPsds::~BpGnssPsds() {}

::ndk::ScopedAStatus BpGnssPsds::injectPsdsData(::aidl::android::hardware::gnss::PsdsType in_psdsType, const std::vector<uint8_t>& in_psdsData) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_psdsType);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_psdsData);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 0 /*injectPsdsData*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IGnssPsds::getDefaultImpl()) {
    _aidl_status = IGnssPsds::getDefaultImpl()->injectPsdsData(in_psdsType, in_psdsData);
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
::ndk::ScopedAStatus BpGnssPsds::setCallback(const std::shared_ptr<::aidl::android::hardware::gnss::IGnssPsdsCallback>& in_callback) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_callback);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 1 /*setCallback*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IGnssPsds::getDefaultImpl()) {
    _aidl_status = IGnssPsds::getDefaultImpl()->setCallback(in_callback);
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
// Source for BnGnssPsds
BnGnssPsds::BnGnssPsds() {}
BnGnssPsds::~BnGnssPsds() {}
::ndk::SpAIBinder BnGnssPsds::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_hardware_gnss_IGnssPsds_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markVintfStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IGnssPsds
const char* IGnssPsds::descriptor = "android.hardware.gnss.IGnssPsds";
IGnssPsds::IGnssPsds() {}
IGnssPsds::~IGnssPsds() {}


std::shared_ptr<IGnssPsds> IGnssPsds::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_hardware_gnss_IGnssPsds_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpGnssPsds>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IGnssPsds>(interface);
  }
  return ::ndk::SharedRefBase::make<BpGnssPsds>(binder);
}

binder_status_t IGnssPsds::writeToParcel(AParcel* parcel, const std::shared_ptr<IGnssPsds>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IGnssPsds::readFromParcel(const AParcel* parcel, std::shared_ptr<IGnssPsds>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IGnssPsds::fromBinder(binder);
  return STATUS_OK;
}
bool IGnssPsds::setDefaultImpl(const std::shared_ptr<IGnssPsds>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IGnssPsds::default_impl);
  if (impl) {
    IGnssPsds::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IGnssPsds>& IGnssPsds::getDefaultImpl() {
  return IGnssPsds::default_impl;
}
std::shared_ptr<IGnssPsds> IGnssPsds::default_impl = nullptr;
::ndk::ScopedAStatus IGnssPsdsDefault::injectPsdsData(::aidl::android::hardware::gnss::PsdsType /*in_psdsType*/, const std::vector<uint8_t>& /*in_psdsData*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IGnssPsdsDefault::setCallback(const std::shared_ptr<::aidl::android::hardware::gnss::IGnssPsdsCallback>& /*in_callback*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IGnssPsdsDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IGnssPsdsDefault::isRemote() {
  return false;
}
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
