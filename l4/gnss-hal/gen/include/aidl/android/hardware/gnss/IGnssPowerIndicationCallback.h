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
#include <aidl/android/hardware/gnss/GnssPowerStats.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::gnss {
class GnssPowerStats;
}  // namespace aidl::android::hardware::gnss
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class IGnssPowerIndicationCallbackDelegator;

class IGnssPowerIndicationCallback : public ::ndk::ICInterface {
public:
  typedef IGnssPowerIndicationCallbackDelegator DefaultDelegator;
  static const char* descriptor;
  IGnssPowerIndicationCallback();
  virtual ~IGnssPowerIndicationCallback();

  enum : int32_t { CAPABILITY_TOTAL = 1 };
  enum : int32_t { CAPABILITY_SINGLEBAND_TRACKING = 2 };
  enum : int32_t { CAPABILITY_MULTIBAND_TRACKING = 4 };
  enum : int32_t { CAPABILITY_SINGLEBAND_ACQUISITION = 8 };
  enum : int32_t { CAPABILITY_MULTIBAND_ACQUISITION = 16 };
  enum : int32_t { CAPABILITY_OTHER_MODES = 32 };
  static constexpr uint32_t TRANSACTION_setCapabilitiesCb = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_gnssPowerStatsCb = FIRST_CALL_TRANSACTION + 1;

  static std::shared_ptr<IGnssPowerIndicationCallback> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IGnssPowerIndicationCallback>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IGnssPowerIndicationCallback>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IGnssPowerIndicationCallback>& impl);
  static const std::shared_ptr<IGnssPowerIndicationCallback>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus setCapabilitiesCb(int32_t in_capabilities) = 0;
  virtual ::ndk::ScopedAStatus gnssPowerStatsCb(const ::aidl::android::hardware::gnss::GnssPowerStats& in_gnssPowerStats) = 0;
private:
  static std::shared_ptr<IGnssPowerIndicationCallback> default_impl;
};
class IGnssPowerIndicationCallbackDefault : public IGnssPowerIndicationCallback {
public:
  ::ndk::ScopedAStatus setCapabilitiesCb(int32_t in_capabilities) override;
  ::ndk::ScopedAStatus gnssPowerStatsCb(const ::aidl::android::hardware::gnss::GnssPowerStats& in_gnssPowerStats) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
