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
#include <aidl/android/hardware/gnss/IGnssGeofenceCallback.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::gnss {
class IGnssGeofenceCallback;
}  // namespace aidl::android::hardware::gnss
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class IGnssGeofenceDelegator;

class IGnssGeofence : public ::ndk::ICInterface {
public:
  typedef IGnssGeofenceDelegator DefaultDelegator;
  static const char* descriptor;
  IGnssGeofence();
  virtual ~IGnssGeofence();

  static constexpr uint32_t TRANSACTION_setCallback = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_addGeofence = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_pauseGeofence = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_resumeGeofence = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_removeGeofence = FIRST_CALL_TRANSACTION + 4;

  static std::shared_ptr<IGnssGeofence> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IGnssGeofence>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IGnssGeofence>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IGnssGeofence>& impl);
  static const std::shared_ptr<IGnssGeofence>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus setCallback(const std::shared_ptr<::aidl::android::hardware::gnss::IGnssGeofenceCallback>& in_callback) = 0;
  virtual ::ndk::ScopedAStatus addGeofence(int32_t in_geofenceId, double in_latitudeDegrees, double in_longitudeDegrees, double in_radiusMeters, int32_t in_lastTransition, int32_t in_monitorTransitions, int32_t in_notificationResponsivenessMs, int32_t in_unknownTimerMs) = 0;
  virtual ::ndk::ScopedAStatus pauseGeofence(int32_t in_geofenceId) = 0;
  virtual ::ndk::ScopedAStatus resumeGeofence(int32_t in_geofenceId, int32_t in_monitorTransitions) = 0;
  virtual ::ndk::ScopedAStatus removeGeofence(int32_t in_geofenceId) = 0;
private:
  static std::shared_ptr<IGnssGeofence> default_impl;
};
class IGnssGeofenceDefault : public IGnssGeofence {
public:
  ::ndk::ScopedAStatus setCallback(const std::shared_ptr<::aidl::android::hardware::gnss::IGnssGeofenceCallback>& in_callback) override;
  ::ndk::ScopedAStatus addGeofence(int32_t in_geofenceId, double in_latitudeDegrees, double in_longitudeDegrees, double in_radiusMeters, int32_t in_lastTransition, int32_t in_monitorTransitions, int32_t in_notificationResponsivenessMs, int32_t in_unknownTimerMs) override;
  ::ndk::ScopedAStatus pauseGeofence(int32_t in_geofenceId) override;
  ::ndk::ScopedAStatus resumeGeofence(int32_t in_geofenceId, int32_t in_monitorTransitions) override;
  ::ndk::ScopedAStatus removeGeofence(int32_t in_geofenceId) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
