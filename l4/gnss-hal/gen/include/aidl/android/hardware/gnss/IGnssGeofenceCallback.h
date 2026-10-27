/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -I aidl-src --out=gen/src --header_out=gen/include aidl-src/android/hardware/gnss/BlocklistedSource.aidl aidl-src/android/hardware/gnss/CorrelationVector.aidl aidl-src/android/hardware/gnss/ElapsedRealtime.aidl aidl-src/android/hardware/gnss/GnssClock.aidl aidl-src/android/hardware/gnss/GnssConstellationType.aidl aidl-src/android/hardware/gnss/GnssData.aidl aidl-src/android/hardware/gnss/GnssLocation.aidl aidl-src/android/hardware/gnss/GnssMeasurement.aidl aidl-src/android/hardware/gnss/GnssMultipathIndicator.aidl aidl-src/android/hardware/gnss/GnssPowerStats.aidl aidl-src/android/hardware/gnss/GnssSignalType.aidl aidl-src/android/hardware/gnss/IAGnss.aidl aidl-src/android/hardware/gnss/IAGnssCallback.aidl aidl-src/android/hardware/gnss/IAGnssRil.aidl aidl-src/android/hardware/gnss/IAGnssRilCallback.aidl aidl-src/android/hardware/gnss/IGnss.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfo.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfoCallback.aidl aidl-src/android/hardware/gnss/IGnssBatching.aidl aidl-src/android/hardware/gnss/IGnssBatchingCallback.aidl aidl-src/android/hardware/gnss/IGnssCallback.aidl aidl-src/android/hardware/gnss/IGnssConfiguration.aidl aidl-src/android/hardware/gnss/IGnssDebug.aidl aidl-src/android/hardware/gnss/IGnssGeofence.aidl aidl-src/android/hardware/gnss/IGnssGeofenceCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementInterface.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageCallback.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageInterface.aidl aidl-src/android/hardware/gnss/IGnssPowerIndication.aidl aidl-src/android/hardware/gnss/IGnssPowerIndicationCallback.aidl aidl-src/android/hardware/gnss/IGnssPsds.aidl aidl-src/android/hardware/gnss/IGnssPsdsCallback.aidl aidl-src/android/hardware/gnss/PsdsType.aidl aidl-src/android/hardware/gnss/SatelliteClockInfo.aidl aidl-src/android/hardware/gnss/SatellitePositionEcef.aidl aidl-src/android/hardware/gnss/SatellitePvt.aidl aidl-src/android/hardware/gnss/SatelliteVelocityEcef.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsCallback.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsInterface.aidl aidl-src/android/hardware/gnss/measurement_corrections/MeasurementCorrections.aidl aidl-src/android/hardware/gnss/measurement_corrections/ReflectingPlane.aidl aidl-src/android/hardware/gnss/measurement_corrections/SingleSatCorrection.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControl.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControlCallback.aidl
 */
#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <android/binder_interface_utils.h>
#include <aidl/android/hardware/gnss/GnssLocation.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::gnss {
class GnssLocation;
}  // namespace aidl::android::hardware::gnss
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class IGnssGeofenceCallbackDelegator;

class IGnssGeofenceCallback : public ::ndk::ICInterface {
public:
  typedef IGnssGeofenceCallbackDelegator DefaultDelegator;
  static const char* descriptor;
  IGnssGeofenceCallback();
  virtual ~IGnssGeofenceCallback();

  enum : int32_t { ENTERED = 1 };
  enum : int32_t { EXITED = 2 };
  enum : int32_t { UNCERTAIN = 4 };
  enum : int32_t { UNAVAILABLE = 1 };
  enum : int32_t { AVAILABLE = 2 };
  enum : int32_t { OPERATION_SUCCESS = 0 };
  enum : int32_t { ERROR_TOO_MANY_GEOFENCES = -100 };
  enum : int32_t { ERROR_ID_EXISTS = -101 };
  enum : int32_t { ERROR_ID_UNKNOWN = -102 };
  enum : int32_t { ERROR_INVALID_TRANSITION = -103 };
  enum : int32_t { ERROR_GENERIC = -149 };
  static constexpr uint32_t TRANSACTION_gnssGeofenceTransitionCb = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_gnssGeofenceStatusCb = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_gnssGeofenceAddCb = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_gnssGeofenceRemoveCb = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_gnssGeofencePauseCb = FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_gnssGeofenceResumeCb = FIRST_CALL_TRANSACTION + 5;

  static std::shared_ptr<IGnssGeofenceCallback> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IGnssGeofenceCallback>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IGnssGeofenceCallback>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IGnssGeofenceCallback>& impl);
  static const std::shared_ptr<IGnssGeofenceCallback>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus gnssGeofenceTransitionCb(int32_t in_geofenceId, const ::aidl::android::hardware::gnss::GnssLocation& in_location, int32_t in_transition, int64_t in_timestampMillis) = 0;
  virtual ::ndk::ScopedAStatus gnssGeofenceStatusCb(int32_t in_availability, const ::aidl::android::hardware::gnss::GnssLocation& in_lastLocation) = 0;
  virtual ::ndk::ScopedAStatus gnssGeofenceAddCb(int32_t in_geofenceId, int32_t in_status) = 0;
  virtual ::ndk::ScopedAStatus gnssGeofenceRemoveCb(int32_t in_geofenceId, int32_t in_status) = 0;
  virtual ::ndk::ScopedAStatus gnssGeofencePauseCb(int32_t in_geofenceId, int32_t in_status) = 0;
  virtual ::ndk::ScopedAStatus gnssGeofenceResumeCb(int32_t in_geofenceId, int32_t in_status) = 0;
private:
  static std::shared_ptr<IGnssGeofenceCallback> default_impl;
};
class IGnssGeofenceCallbackDefault : public IGnssGeofenceCallback {
public:
  ::ndk::ScopedAStatus gnssGeofenceTransitionCb(int32_t in_geofenceId, const ::aidl::android::hardware::gnss::GnssLocation& in_location, int32_t in_transition, int64_t in_timestampMillis) override;
  ::ndk::ScopedAStatus gnssGeofenceStatusCb(int32_t in_availability, const ::aidl::android::hardware::gnss::GnssLocation& in_lastLocation) override;
  ::ndk::ScopedAStatus gnssGeofenceAddCb(int32_t in_geofenceId, int32_t in_status) override;
  ::ndk::ScopedAStatus gnssGeofenceRemoveCb(int32_t in_geofenceId, int32_t in_status) override;
  ::ndk::ScopedAStatus gnssGeofencePauseCb(int32_t in_geofenceId, int32_t in_status) override;
  ::ndk::ScopedAStatus gnssGeofenceResumeCb(int32_t in_geofenceId, int32_t in_status) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
