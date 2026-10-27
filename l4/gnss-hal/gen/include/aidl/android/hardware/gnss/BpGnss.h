/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -I aidl-src --out=gen/src --header_out=gen/include aidl-src/android/hardware/gnss/BlocklistedSource.aidl aidl-src/android/hardware/gnss/CorrelationVector.aidl aidl-src/android/hardware/gnss/ElapsedRealtime.aidl aidl-src/android/hardware/gnss/GnssClock.aidl aidl-src/android/hardware/gnss/GnssConstellationType.aidl aidl-src/android/hardware/gnss/GnssData.aidl aidl-src/android/hardware/gnss/GnssLocation.aidl aidl-src/android/hardware/gnss/GnssMeasurement.aidl aidl-src/android/hardware/gnss/GnssMultipathIndicator.aidl aidl-src/android/hardware/gnss/GnssPowerStats.aidl aidl-src/android/hardware/gnss/GnssSignalType.aidl aidl-src/android/hardware/gnss/IAGnss.aidl aidl-src/android/hardware/gnss/IAGnssCallback.aidl aidl-src/android/hardware/gnss/IAGnssRil.aidl aidl-src/android/hardware/gnss/IAGnssRilCallback.aidl aidl-src/android/hardware/gnss/IGnss.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfo.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfoCallback.aidl aidl-src/android/hardware/gnss/IGnssBatching.aidl aidl-src/android/hardware/gnss/IGnssBatchingCallback.aidl aidl-src/android/hardware/gnss/IGnssCallback.aidl aidl-src/android/hardware/gnss/IGnssConfiguration.aidl aidl-src/android/hardware/gnss/IGnssDebug.aidl aidl-src/android/hardware/gnss/IGnssGeofence.aidl aidl-src/android/hardware/gnss/IGnssGeofenceCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementInterface.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageCallback.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageInterface.aidl aidl-src/android/hardware/gnss/IGnssPowerIndication.aidl aidl-src/android/hardware/gnss/IGnssPowerIndicationCallback.aidl aidl-src/android/hardware/gnss/IGnssPsds.aidl aidl-src/android/hardware/gnss/IGnssPsdsCallback.aidl aidl-src/android/hardware/gnss/PsdsType.aidl aidl-src/android/hardware/gnss/SatelliteClockInfo.aidl aidl-src/android/hardware/gnss/SatellitePositionEcef.aidl aidl-src/android/hardware/gnss/SatellitePvt.aidl aidl-src/android/hardware/gnss/SatelliteVelocityEcef.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsCallback.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsInterface.aidl aidl-src/android/hardware/gnss/measurement_corrections/MeasurementCorrections.aidl aidl-src/android/hardware/gnss/measurement_corrections/ReflectingPlane.aidl aidl-src/android/hardware/gnss/measurement_corrections/SingleSatCorrection.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControl.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControlCallback.aidl
 */
#pragma once

#include "aidl/android/hardware/gnss/IGnss.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class BpGnss : public ::ndk::BpCInterface<IGnss> {
public:
  explicit BpGnss(const ::ndk::SpAIBinder& binder);
  virtual ~BpGnss();

  ::ndk::ScopedAStatus setCallback(const std::shared_ptr<::aidl::android::hardware::gnss::IGnssCallback>& in_callback) override;
  ::ndk::ScopedAStatus close() override;
  ::ndk::ScopedAStatus getExtensionPsds(std::shared_ptr<::aidl::android::hardware::gnss::IGnssPsds>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionGnssConfiguration(std::shared_ptr<::aidl::android::hardware::gnss::IGnssConfiguration>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionGnssMeasurement(std::shared_ptr<::aidl::android::hardware::gnss::IGnssMeasurementInterface>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionGnssPowerIndication(std::shared_ptr<::aidl::android::hardware::gnss::IGnssPowerIndication>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionGnssBatching(std::shared_ptr<::aidl::android::hardware::gnss::IGnssBatching>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionGnssGeofence(std::shared_ptr<::aidl::android::hardware::gnss::IGnssGeofence>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionGnssNavigationMessage(std::shared_ptr<::aidl::android::hardware::gnss::IGnssNavigationMessageInterface>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionAGnss(std::shared_ptr<::aidl::android::hardware::gnss::IAGnss>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionAGnssRil(std::shared_ptr<::aidl::android::hardware::gnss::IAGnssRil>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionGnssDebug(std::shared_ptr<::aidl::android::hardware::gnss::IGnssDebug>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionGnssVisibilityControl(std::shared_ptr<::aidl::android::hardware::gnss::visibility_control::IGnssVisibilityControl>* _aidl_return) override;
  ::ndk::ScopedAStatus start() override;
  ::ndk::ScopedAStatus stop() override;
  ::ndk::ScopedAStatus injectTime(int64_t in_timeMs, int64_t in_timeReferenceMs, int32_t in_uncertaintyMs) override;
  ::ndk::ScopedAStatus injectLocation(const ::aidl::android::hardware::gnss::GnssLocation& in_location) override;
  ::ndk::ScopedAStatus injectBestLocation(const ::aidl::android::hardware::gnss::GnssLocation& in_location) override;
  ::ndk::ScopedAStatus deleteAidingData(::aidl::android::hardware::gnss::IGnss::GnssAidingData in_aidingDataFlags) override;
  ::ndk::ScopedAStatus setPositionMode(const ::aidl::android::hardware::gnss::IGnss::PositionModeOptions& in_options) override;
  ::ndk::ScopedAStatus getExtensionGnssAntennaInfo(std::shared_ptr<::aidl::android::hardware::gnss::IGnssAntennaInfo>* _aidl_return) override;
  ::ndk::ScopedAStatus getExtensionMeasurementCorrections(std::shared_ptr<::aidl::android::hardware::gnss::measurement_corrections::IMeasurementCorrectionsInterface>* _aidl_return) override;
  ::ndk::ScopedAStatus startSvStatus() override;
  ::ndk::ScopedAStatus stopSvStatus() override;
  ::ndk::ScopedAStatus startNmea() override;
  ::ndk::ScopedAStatus stopNmea() override;
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
