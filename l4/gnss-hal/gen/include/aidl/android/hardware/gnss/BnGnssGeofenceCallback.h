/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -I aidl-src --out=gen/src --header_out=gen/include aidl-src/android/hardware/gnss/BlocklistedSource.aidl aidl-src/android/hardware/gnss/CorrelationVector.aidl aidl-src/android/hardware/gnss/ElapsedRealtime.aidl aidl-src/android/hardware/gnss/GnssClock.aidl aidl-src/android/hardware/gnss/GnssConstellationType.aidl aidl-src/android/hardware/gnss/GnssData.aidl aidl-src/android/hardware/gnss/GnssLocation.aidl aidl-src/android/hardware/gnss/GnssMeasurement.aidl aidl-src/android/hardware/gnss/GnssMultipathIndicator.aidl aidl-src/android/hardware/gnss/GnssPowerStats.aidl aidl-src/android/hardware/gnss/GnssSignalType.aidl aidl-src/android/hardware/gnss/IAGnss.aidl aidl-src/android/hardware/gnss/IAGnssCallback.aidl aidl-src/android/hardware/gnss/IAGnssRil.aidl aidl-src/android/hardware/gnss/IAGnssRilCallback.aidl aidl-src/android/hardware/gnss/IGnss.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfo.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfoCallback.aidl aidl-src/android/hardware/gnss/IGnssBatching.aidl aidl-src/android/hardware/gnss/IGnssBatchingCallback.aidl aidl-src/android/hardware/gnss/IGnssCallback.aidl aidl-src/android/hardware/gnss/IGnssConfiguration.aidl aidl-src/android/hardware/gnss/IGnssDebug.aidl aidl-src/android/hardware/gnss/IGnssGeofence.aidl aidl-src/android/hardware/gnss/IGnssGeofenceCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementInterface.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageCallback.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageInterface.aidl aidl-src/android/hardware/gnss/IGnssPowerIndication.aidl aidl-src/android/hardware/gnss/IGnssPowerIndicationCallback.aidl aidl-src/android/hardware/gnss/IGnssPsds.aidl aidl-src/android/hardware/gnss/IGnssPsdsCallback.aidl aidl-src/android/hardware/gnss/PsdsType.aidl aidl-src/android/hardware/gnss/SatelliteClockInfo.aidl aidl-src/android/hardware/gnss/SatellitePositionEcef.aidl aidl-src/android/hardware/gnss/SatellitePvt.aidl aidl-src/android/hardware/gnss/SatelliteVelocityEcef.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsCallback.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsInterface.aidl aidl-src/android/hardware/gnss/measurement_corrections/MeasurementCorrections.aidl aidl-src/android/hardware/gnss/measurement_corrections/ReflectingPlane.aidl aidl-src/android/hardware/gnss/measurement_corrections/SingleSatCorrection.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControl.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControlCallback.aidl
 */
#pragma once

#include "aidl/android/hardware/gnss/IGnssGeofenceCallback.h"

#include <android/binder_ibinder.h>
#include <cassert>

#ifndef __BIONIC__
#ifndef __assert2
#define __assert2(a,b,c,d) ((void)0)
#endif
#endif

namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class BnGnssGeofenceCallback : public ::ndk::BnCInterface<IGnssGeofenceCallback> {
public:
  BnGnssGeofenceCallback();
  virtual ~BnGnssGeofenceCallback();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IGnssGeofenceCallbackDelegator : public BnGnssGeofenceCallback {
public:
  explicit IGnssGeofenceCallbackDelegator(const std::shared_ptr<IGnssGeofenceCallback> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus gnssGeofenceTransitionCb(int32_t in_geofenceId, const ::aidl::android::hardware::gnss::GnssLocation& in_location, int32_t in_transition, int64_t in_timestampMillis) override {
    return _impl->gnssGeofenceTransitionCb(in_geofenceId, in_location, in_transition, in_timestampMillis);
  }
  ::ndk::ScopedAStatus gnssGeofenceStatusCb(int32_t in_availability, const ::aidl::android::hardware::gnss::GnssLocation& in_lastLocation) override {
    return _impl->gnssGeofenceStatusCb(in_availability, in_lastLocation);
  }
  ::ndk::ScopedAStatus gnssGeofenceAddCb(int32_t in_geofenceId, int32_t in_status) override {
    return _impl->gnssGeofenceAddCb(in_geofenceId, in_status);
  }
  ::ndk::ScopedAStatus gnssGeofenceRemoveCb(int32_t in_geofenceId, int32_t in_status) override {
    return _impl->gnssGeofenceRemoveCb(in_geofenceId, in_status);
  }
  ::ndk::ScopedAStatus gnssGeofencePauseCb(int32_t in_geofenceId, int32_t in_status) override {
    return _impl->gnssGeofencePauseCb(in_geofenceId, in_status);
  }
  ::ndk::ScopedAStatus gnssGeofenceResumeCb(int32_t in_geofenceId, int32_t in_status) override {
    return _impl->gnssGeofenceResumeCb(in_geofenceId, in_status);
  }
protected:
private:
  std::shared_ptr<IGnssGeofenceCallback> _impl;
};

}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
