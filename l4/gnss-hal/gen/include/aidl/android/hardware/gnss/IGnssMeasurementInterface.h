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
#include <android/binder_parcelable_utils.h>
#include <android/binder_to_string.h>
#include <aidl/android/hardware/gnss/IGnssMeasurementCallback.h>
#include <aidl/android/hardware/gnss/IGnssMeasurementInterface.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::gnss {
class IGnssMeasurementCallback;
}  // namespace aidl::android::hardware::gnss
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class IGnssMeasurementInterfaceDelegator;

class IGnssMeasurementInterface : public ::ndk::ICInterface {
public:
  typedef IGnssMeasurementInterfaceDelegator DefaultDelegator;
  static const char* descriptor;
  IGnssMeasurementInterface();
  virtual ~IGnssMeasurementInterface();

  class Options {
  public:
    typedef std::false_type fixed_size;
    static const char* descriptor;

    bool enableFullTracking = false;
    bool enableCorrVecOutputs = false;
    int32_t intervalMs = 0;

    binder_status_t readFromParcel(const AParcel* parcel);
    binder_status_t writeToParcel(AParcel* parcel) const;

    inline bool operator==(const Options& _rhs) const {
      return std::tie(enableFullTracking, enableCorrVecOutputs, intervalMs) == std::tie(_rhs.enableFullTracking, _rhs.enableCorrVecOutputs, _rhs.intervalMs);
    }
    inline bool operator<(const Options& _rhs) const {
      return std::tie(enableFullTracking, enableCorrVecOutputs, intervalMs) < std::tie(_rhs.enableFullTracking, _rhs.enableCorrVecOutputs, _rhs.intervalMs);
    }
    inline bool operator!=(const Options& _rhs) const {
      return !(*this == _rhs);
    }
    inline bool operator>(const Options& _rhs) const {
      return _rhs < *this;
    }
    inline bool operator>=(const Options& _rhs) const {
      return !(*this < _rhs);
    }
    inline bool operator<=(const Options& _rhs) const {
      return !(_rhs < *this);
    }

    static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
    inline std::string toString() const {
      std::ostringstream _aidl_os;
      _aidl_os << "Options{";
      _aidl_os << "enableFullTracking: " << ::android::internal::ToString(enableFullTracking);
      _aidl_os << ", enableCorrVecOutputs: " << ::android::internal::ToString(enableCorrVecOutputs);
      _aidl_os << ", intervalMs: " << ::android::internal::ToString(intervalMs);
      _aidl_os << "}";
      return _aidl_os.str();
    }
  };
  static constexpr uint32_t TRANSACTION_setCallback = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_close = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_setCallbackWithOptions = FIRST_CALL_TRANSACTION + 2;

  static std::shared_ptr<IGnssMeasurementInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IGnssMeasurementInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IGnssMeasurementInterface>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IGnssMeasurementInterface>& impl);
  static const std::shared_ptr<IGnssMeasurementInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus setCallback(const std::shared_ptr<::aidl::android::hardware::gnss::IGnssMeasurementCallback>& in_callback, bool in_enableFullTracking, bool in_enableCorrVecOutputs) = 0;
  virtual ::ndk::ScopedAStatus close() = 0;
  virtual ::ndk::ScopedAStatus setCallbackWithOptions(const std::shared_ptr<::aidl::android::hardware::gnss::IGnssMeasurementCallback>& in_callback, const ::aidl::android::hardware::gnss::IGnssMeasurementInterface::Options& in_options) = 0;
private:
  static std::shared_ptr<IGnssMeasurementInterface> default_impl;
};
class IGnssMeasurementInterfaceDefault : public IGnssMeasurementInterface {
public:
  ::ndk::ScopedAStatus setCallback(const std::shared_ptr<::aidl::android::hardware::gnss::IGnssMeasurementCallback>& in_callback, bool in_enableFullTracking, bool in_enableCorrVecOutputs) override;
  ::ndk::ScopedAStatus close() override;
  ::ndk::ScopedAStatus setCallbackWithOptions(const std::shared_ptr<::aidl::android::hardware::gnss::IGnssMeasurementCallback>& in_callback, const ::aidl::android::hardware::gnss::IGnssMeasurementInterface::Options& in_options) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
