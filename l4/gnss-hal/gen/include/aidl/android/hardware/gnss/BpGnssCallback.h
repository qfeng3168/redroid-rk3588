/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -I aidl-src --out=gen/src --header_out=gen/include aidl-src/android/hardware/gnss/BlocklistedSource.aidl aidl-src/android/hardware/gnss/CorrelationVector.aidl aidl-src/android/hardware/gnss/ElapsedRealtime.aidl aidl-src/android/hardware/gnss/GnssClock.aidl aidl-src/android/hardware/gnss/GnssConstellationType.aidl aidl-src/android/hardware/gnss/GnssData.aidl aidl-src/android/hardware/gnss/GnssLocation.aidl aidl-src/android/hardware/gnss/GnssMeasurement.aidl aidl-src/android/hardware/gnss/GnssMultipathIndicator.aidl aidl-src/android/hardware/gnss/GnssPowerStats.aidl aidl-src/android/hardware/gnss/GnssSignalType.aidl aidl-src/android/hardware/gnss/IAGnss.aidl aidl-src/android/hardware/gnss/IAGnssCallback.aidl aidl-src/android/hardware/gnss/IAGnssRil.aidl aidl-src/android/hardware/gnss/IAGnssRilCallback.aidl aidl-src/android/hardware/gnss/IGnss.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfo.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfoCallback.aidl aidl-src/android/hardware/gnss/IGnssBatching.aidl aidl-src/android/hardware/gnss/IGnssBatchingCallback.aidl aidl-src/android/hardware/gnss/IGnssCallback.aidl aidl-src/android/hardware/gnss/IGnssConfiguration.aidl aidl-src/android/hardware/gnss/IGnssDebug.aidl aidl-src/android/hardware/gnss/IGnssGeofence.aidl aidl-src/android/hardware/gnss/IGnssGeofenceCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementInterface.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageCallback.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageInterface.aidl aidl-src/android/hardware/gnss/IGnssPowerIndication.aidl aidl-src/android/hardware/gnss/IGnssPowerIndicationCallback.aidl aidl-src/android/hardware/gnss/IGnssPsds.aidl aidl-src/android/hardware/gnss/IGnssPsdsCallback.aidl aidl-src/android/hardware/gnss/PsdsType.aidl aidl-src/android/hardware/gnss/SatelliteClockInfo.aidl aidl-src/android/hardware/gnss/SatellitePositionEcef.aidl aidl-src/android/hardware/gnss/SatellitePvt.aidl aidl-src/android/hardware/gnss/SatelliteVelocityEcef.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsCallback.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsInterface.aidl aidl-src/android/hardware/gnss/measurement_corrections/MeasurementCorrections.aidl aidl-src/android/hardware/gnss/measurement_corrections/ReflectingPlane.aidl aidl-src/android/hardware/gnss/measurement_corrections/SingleSatCorrection.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControl.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControlCallback.aidl
 */
#pragma once

#include "aidl/android/hardware/gnss/IGnssCallback.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class BpGnssCallback : public ::ndk::BpCInterface<IGnssCallback> {
public:
  explicit BpGnssCallback(const ::ndk::SpAIBinder& binder);
  virtual ~BpGnssCallback();

  ::ndk::ScopedAStatus gnssSetCapabilitiesCb(int32_t in_capabilities) override;
  ::ndk::ScopedAStatus gnssStatusCb(::aidl::android::hardware::gnss::IGnssCallback::GnssStatusValue in_status) override;
  ::ndk::ScopedAStatus gnssSvStatusCb(const std::vector<::aidl::android::hardware::gnss::IGnssCallback::GnssSvInfo>& in_svInfoList) override;
  ::ndk::ScopedAStatus gnssLocationCb(const ::aidl::android::hardware::gnss::GnssLocation& in_location) override;
  ::ndk::ScopedAStatus gnssNmeaCb(int64_t in_timestamp, const std::string& in_nmea) override;
  ::ndk::ScopedAStatus gnssAcquireWakelockCb() override;
  ::ndk::ScopedAStatus gnssReleaseWakelockCb() override;
  ::ndk::ScopedAStatus gnssSetSystemInfoCb(const ::aidl::android::hardware::gnss::IGnssCallback::GnssSystemInfo& in_info) override;
  ::ndk::ScopedAStatus gnssRequestTimeCb() override;
  ::ndk::ScopedAStatus gnssRequestLocationCb(bool in_independentFromGnss, bool in_isUserEmergency) override;
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
