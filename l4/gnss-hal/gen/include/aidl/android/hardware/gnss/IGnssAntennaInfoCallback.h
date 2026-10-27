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
#include <aidl/android/hardware/gnss/IGnssAntennaInfoCallback.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class IGnssAntennaInfoCallbackDelegator;

class IGnssAntennaInfoCallback : public ::ndk::ICInterface {
public:
  typedef IGnssAntennaInfoCallbackDelegator DefaultDelegator;
  static const char* descriptor;
  IGnssAntennaInfoCallback();
  virtual ~IGnssAntennaInfoCallback();

  class Row {
  public:
    typedef std::false_type fixed_size;
    static const char* descriptor;

    std::vector<double> row;

    binder_status_t readFromParcel(const AParcel* parcel);
    binder_status_t writeToParcel(AParcel* parcel) const;

    inline bool operator==(const Row& _rhs) const {
      return std::tie(row) == std::tie(_rhs.row);
    }
    inline bool operator<(const Row& _rhs) const {
      return std::tie(row) < std::tie(_rhs.row);
    }
    inline bool operator!=(const Row& _rhs) const {
      return !(*this == _rhs);
    }
    inline bool operator>(const Row& _rhs) const {
      return _rhs < *this;
    }
    inline bool operator>=(const Row& _rhs) const {
      return !(*this < _rhs);
    }
    inline bool operator<=(const Row& _rhs) const {
      return !(_rhs < *this);
    }

    static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
    inline std::string toString() const {
      std::ostringstream _aidl_os;
      _aidl_os << "Row{";
      _aidl_os << "row: " << ::android::internal::ToString(row);
      _aidl_os << "}";
      return _aidl_os.str();
    }
  };
  class Coord {
  public:
    typedef std::false_type fixed_size;
    static const char* descriptor;

    double x = 0.000000;
    double xUncertainty = 0.000000;
    double y = 0.000000;
    double yUncertainty = 0.000000;
    double z = 0.000000;
    double zUncertainty = 0.000000;

    binder_status_t readFromParcel(const AParcel* parcel);
    binder_status_t writeToParcel(AParcel* parcel) const;

    inline bool operator==(const Coord& _rhs) const {
      return std::tie(x, xUncertainty, y, yUncertainty, z, zUncertainty) == std::tie(_rhs.x, _rhs.xUncertainty, _rhs.y, _rhs.yUncertainty, _rhs.z, _rhs.zUncertainty);
    }
    inline bool operator<(const Coord& _rhs) const {
      return std::tie(x, xUncertainty, y, yUncertainty, z, zUncertainty) < std::tie(_rhs.x, _rhs.xUncertainty, _rhs.y, _rhs.yUncertainty, _rhs.z, _rhs.zUncertainty);
    }
    inline bool operator!=(const Coord& _rhs) const {
      return !(*this == _rhs);
    }
    inline bool operator>(const Coord& _rhs) const {
      return _rhs < *this;
    }
    inline bool operator>=(const Coord& _rhs) const {
      return !(*this < _rhs);
    }
    inline bool operator<=(const Coord& _rhs) const {
      return !(_rhs < *this);
    }

    static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
    inline std::string toString() const {
      std::ostringstream _aidl_os;
      _aidl_os << "Coord{";
      _aidl_os << "x: " << ::android::internal::ToString(x);
      _aidl_os << ", xUncertainty: " << ::android::internal::ToString(xUncertainty);
      _aidl_os << ", y: " << ::android::internal::ToString(y);
      _aidl_os << ", yUncertainty: " << ::android::internal::ToString(yUncertainty);
      _aidl_os << ", z: " << ::android::internal::ToString(z);
      _aidl_os << ", zUncertainty: " << ::android::internal::ToString(zUncertainty);
      _aidl_os << "}";
      return _aidl_os.str();
    }
  };
  class GnssAntennaInfo {
  public:
    typedef std::false_type fixed_size;
    static const char* descriptor;

    int64_t carrierFrequencyHz = 0L;
    ::aidl::android::hardware::gnss::IGnssAntennaInfoCallback::Coord phaseCenterOffsetCoordinateMillimeters;
    std::vector<::aidl::android::hardware::gnss::IGnssAntennaInfoCallback::Row> phaseCenterVariationCorrectionMillimeters;
    std::vector<::aidl::android::hardware::gnss::IGnssAntennaInfoCallback::Row> phaseCenterVariationCorrectionUncertaintyMillimeters;
    std::vector<::aidl::android::hardware::gnss::IGnssAntennaInfoCallback::Row> signalGainCorrectionDbi;
    std::vector<::aidl::android::hardware::gnss::IGnssAntennaInfoCallback::Row> signalGainCorrectionUncertaintyDbi;

    binder_status_t readFromParcel(const AParcel* parcel);
    binder_status_t writeToParcel(AParcel* parcel) const;

    inline bool operator==(const GnssAntennaInfo& _rhs) const {
      return std::tie(carrierFrequencyHz, phaseCenterOffsetCoordinateMillimeters, phaseCenterVariationCorrectionMillimeters, phaseCenterVariationCorrectionUncertaintyMillimeters, signalGainCorrectionDbi, signalGainCorrectionUncertaintyDbi) == std::tie(_rhs.carrierFrequencyHz, _rhs.phaseCenterOffsetCoordinateMillimeters, _rhs.phaseCenterVariationCorrectionMillimeters, _rhs.phaseCenterVariationCorrectionUncertaintyMillimeters, _rhs.signalGainCorrectionDbi, _rhs.signalGainCorrectionUncertaintyDbi);
    }
    inline bool operator<(const GnssAntennaInfo& _rhs) const {
      return std::tie(carrierFrequencyHz, phaseCenterOffsetCoordinateMillimeters, phaseCenterVariationCorrectionMillimeters, phaseCenterVariationCorrectionUncertaintyMillimeters, signalGainCorrectionDbi, signalGainCorrectionUncertaintyDbi) < std::tie(_rhs.carrierFrequencyHz, _rhs.phaseCenterOffsetCoordinateMillimeters, _rhs.phaseCenterVariationCorrectionMillimeters, _rhs.phaseCenterVariationCorrectionUncertaintyMillimeters, _rhs.signalGainCorrectionDbi, _rhs.signalGainCorrectionUncertaintyDbi);
    }
    inline bool operator!=(const GnssAntennaInfo& _rhs) const {
      return !(*this == _rhs);
    }
    inline bool operator>(const GnssAntennaInfo& _rhs) const {
      return _rhs < *this;
    }
    inline bool operator>=(const GnssAntennaInfo& _rhs) const {
      return !(*this < _rhs);
    }
    inline bool operator<=(const GnssAntennaInfo& _rhs) const {
      return !(_rhs < *this);
    }

    static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
    inline std::string toString() const {
      std::ostringstream _aidl_os;
      _aidl_os << "GnssAntennaInfo{";
      _aidl_os << "carrierFrequencyHz: " << ::android::internal::ToString(carrierFrequencyHz);
      _aidl_os << ", phaseCenterOffsetCoordinateMillimeters: " << ::android::internal::ToString(phaseCenterOffsetCoordinateMillimeters);
      _aidl_os << ", phaseCenterVariationCorrectionMillimeters: " << ::android::internal::ToString(phaseCenterVariationCorrectionMillimeters);
      _aidl_os << ", phaseCenterVariationCorrectionUncertaintyMillimeters: " << ::android::internal::ToString(phaseCenterVariationCorrectionUncertaintyMillimeters);
      _aidl_os << ", signalGainCorrectionDbi: " << ::android::internal::ToString(signalGainCorrectionDbi);
      _aidl_os << ", signalGainCorrectionUncertaintyDbi: " << ::android::internal::ToString(signalGainCorrectionUncertaintyDbi);
      _aidl_os << "}";
      return _aidl_os.str();
    }
  };
  static constexpr uint32_t TRANSACTION_gnssAntennaInfoCb = FIRST_CALL_TRANSACTION + 0;

  static std::shared_ptr<IGnssAntennaInfoCallback> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IGnssAntennaInfoCallback>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IGnssAntennaInfoCallback>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IGnssAntennaInfoCallback>& impl);
  static const std::shared_ptr<IGnssAntennaInfoCallback>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus gnssAntennaInfoCb(const std::vector<::aidl::android::hardware::gnss::IGnssAntennaInfoCallback::GnssAntennaInfo>& in_gnssAntennaInfos) = 0;
private:
  static std::shared_ptr<IGnssAntennaInfoCallback> default_impl;
};
class IGnssAntennaInfoCallbackDefault : public IGnssAntennaInfoCallback {
public:
  ::ndk::ScopedAStatus gnssAntennaInfoCb(const std::vector<::aidl::android::hardware::gnss::IGnssAntennaInfoCallback::GnssAntennaInfo>& in_gnssAntennaInfos) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
