/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -I aidl-src --out=gen/src --header_out=gen/include aidl-src/android/hardware/gnss/BlocklistedSource.aidl aidl-src/android/hardware/gnss/CorrelationVector.aidl aidl-src/android/hardware/gnss/ElapsedRealtime.aidl aidl-src/android/hardware/gnss/GnssClock.aidl aidl-src/android/hardware/gnss/GnssConstellationType.aidl aidl-src/android/hardware/gnss/GnssData.aidl aidl-src/android/hardware/gnss/GnssLocation.aidl aidl-src/android/hardware/gnss/GnssMeasurement.aidl aidl-src/android/hardware/gnss/GnssMultipathIndicator.aidl aidl-src/android/hardware/gnss/GnssPowerStats.aidl aidl-src/android/hardware/gnss/GnssSignalType.aidl aidl-src/android/hardware/gnss/IAGnss.aidl aidl-src/android/hardware/gnss/IAGnssCallback.aidl aidl-src/android/hardware/gnss/IAGnssRil.aidl aidl-src/android/hardware/gnss/IAGnssRilCallback.aidl aidl-src/android/hardware/gnss/IGnss.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfo.aidl aidl-src/android/hardware/gnss/IGnssAntennaInfoCallback.aidl aidl-src/android/hardware/gnss/IGnssBatching.aidl aidl-src/android/hardware/gnss/IGnssBatchingCallback.aidl aidl-src/android/hardware/gnss/IGnssCallback.aidl aidl-src/android/hardware/gnss/IGnssConfiguration.aidl aidl-src/android/hardware/gnss/IGnssDebug.aidl aidl-src/android/hardware/gnss/IGnssGeofence.aidl aidl-src/android/hardware/gnss/IGnssGeofenceCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementCallback.aidl aidl-src/android/hardware/gnss/IGnssMeasurementInterface.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageCallback.aidl aidl-src/android/hardware/gnss/IGnssNavigationMessageInterface.aidl aidl-src/android/hardware/gnss/IGnssPowerIndication.aidl aidl-src/android/hardware/gnss/IGnssPowerIndicationCallback.aidl aidl-src/android/hardware/gnss/IGnssPsds.aidl aidl-src/android/hardware/gnss/IGnssPsdsCallback.aidl aidl-src/android/hardware/gnss/PsdsType.aidl aidl-src/android/hardware/gnss/SatelliteClockInfo.aidl aidl-src/android/hardware/gnss/SatellitePositionEcef.aidl aidl-src/android/hardware/gnss/SatellitePvt.aidl aidl-src/android/hardware/gnss/SatelliteVelocityEcef.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsCallback.aidl aidl-src/android/hardware/gnss/measurement_corrections/IMeasurementCorrectionsInterface.aidl aidl-src/android/hardware/gnss/measurement_corrections/MeasurementCorrections.aidl aidl-src/android/hardware/gnss/measurement_corrections/ReflectingPlane.aidl aidl-src/android/hardware/gnss/measurement_corrections/SingleSatCorrection.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControl.aidl aidl-src/android/hardware/gnss/visibility_control/IGnssVisibilityControlCallback.aidl
 */
#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <android/binder_enums.h>
#include <android/binder_interface_utils.h>
#include <android/binder_parcelable_utils.h>
#include <android/binder_to_string.h>
#include <aidl/android/hardware/gnss/GnssConstellationType.h>
#include <aidl/android/hardware/gnss/IGnssDebug.h>
#include <aidl/android/hardware/gnss/SatellitePvt.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class IGnssDebugDelegator;

class IGnssDebug : public ::ndk::ICInterface {
public:
  typedef IGnssDebugDelegator DefaultDelegator;
  static const char* descriptor;
  IGnssDebug();
  virtual ~IGnssDebug();

  enum class SatelliteEphemerisType : int32_t {
    EPHEMERIS = 0,
    ALMANAC_ONLY = 1,
    NOT_AVAILABLE = 2,
  };

  enum class SatelliteEphemerisHealth : int32_t {
    GOOD = 0,
    BAD = 1,
    UNKNOWN = 2,
  };

  class TimeDebug {
  public:
    typedef std::false_type fixed_size;
    static const char* descriptor;

    int64_t timeEstimateMs = 0L;
    float timeUncertaintyNs = 0.000000f;
    float frequencyUncertaintyNsPerSec = 0.000000f;

    binder_status_t readFromParcel(const AParcel* parcel);
    binder_status_t writeToParcel(AParcel* parcel) const;

    inline bool operator==(const TimeDebug& _rhs) const {
      return std::tie(timeEstimateMs, timeUncertaintyNs, frequencyUncertaintyNsPerSec) == std::tie(_rhs.timeEstimateMs, _rhs.timeUncertaintyNs, _rhs.frequencyUncertaintyNsPerSec);
    }
    inline bool operator<(const TimeDebug& _rhs) const {
      return std::tie(timeEstimateMs, timeUncertaintyNs, frequencyUncertaintyNsPerSec) < std::tie(_rhs.timeEstimateMs, _rhs.timeUncertaintyNs, _rhs.frequencyUncertaintyNsPerSec);
    }
    inline bool operator!=(const TimeDebug& _rhs) const {
      return !(*this == _rhs);
    }
    inline bool operator>(const TimeDebug& _rhs) const {
      return _rhs < *this;
    }
    inline bool operator>=(const TimeDebug& _rhs) const {
      return !(*this < _rhs);
    }
    inline bool operator<=(const TimeDebug& _rhs) const {
      return !(_rhs < *this);
    }

    static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
    inline std::string toString() const {
      std::ostringstream _aidl_os;
      _aidl_os << "TimeDebug{";
      _aidl_os << "timeEstimateMs: " << ::android::internal::ToString(timeEstimateMs);
      _aidl_os << ", timeUncertaintyNs: " << ::android::internal::ToString(timeUncertaintyNs);
      _aidl_os << ", frequencyUncertaintyNsPerSec: " << ::android::internal::ToString(frequencyUncertaintyNsPerSec);
      _aidl_os << "}";
      return _aidl_os.str();
    }
  };
  class PositionDebug {
  public:
    typedef std::false_type fixed_size;
    static const char* descriptor;

    bool valid = false;
    double latitudeDegrees = 0.000000;
    double longitudeDegrees = 0.000000;
    float altitudeMeters = 0.000000f;
    float speedMetersPerSec = 0.000000f;
    float bearingDegrees = 0.000000f;
    double horizontalAccuracyMeters = 0.000000;
    double verticalAccuracyMeters = 0.000000;
    double speedAccuracyMetersPerSecond = 0.000000;
    double bearingAccuracyDegrees = 0.000000;
    float ageSeconds = 0.000000f;

    binder_status_t readFromParcel(const AParcel* parcel);
    binder_status_t writeToParcel(AParcel* parcel) const;

    inline bool operator==(const PositionDebug& _rhs) const {
      return std::tie(valid, latitudeDegrees, longitudeDegrees, altitudeMeters, speedMetersPerSec, bearingDegrees, horizontalAccuracyMeters, verticalAccuracyMeters, speedAccuracyMetersPerSecond, bearingAccuracyDegrees, ageSeconds) == std::tie(_rhs.valid, _rhs.latitudeDegrees, _rhs.longitudeDegrees, _rhs.altitudeMeters, _rhs.speedMetersPerSec, _rhs.bearingDegrees, _rhs.horizontalAccuracyMeters, _rhs.verticalAccuracyMeters, _rhs.speedAccuracyMetersPerSecond, _rhs.bearingAccuracyDegrees, _rhs.ageSeconds);
    }
    inline bool operator<(const PositionDebug& _rhs) const {
      return std::tie(valid, latitudeDegrees, longitudeDegrees, altitudeMeters, speedMetersPerSec, bearingDegrees, horizontalAccuracyMeters, verticalAccuracyMeters, speedAccuracyMetersPerSecond, bearingAccuracyDegrees, ageSeconds) < std::tie(_rhs.valid, _rhs.latitudeDegrees, _rhs.longitudeDegrees, _rhs.altitudeMeters, _rhs.speedMetersPerSec, _rhs.bearingDegrees, _rhs.horizontalAccuracyMeters, _rhs.verticalAccuracyMeters, _rhs.speedAccuracyMetersPerSecond, _rhs.bearingAccuracyDegrees, _rhs.ageSeconds);
    }
    inline bool operator!=(const PositionDebug& _rhs) const {
      return !(*this == _rhs);
    }
    inline bool operator>(const PositionDebug& _rhs) const {
      return _rhs < *this;
    }
    inline bool operator>=(const PositionDebug& _rhs) const {
      return !(*this < _rhs);
    }
    inline bool operator<=(const PositionDebug& _rhs) const {
      return !(_rhs < *this);
    }

    static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
    inline std::string toString() const {
      std::ostringstream _aidl_os;
      _aidl_os << "PositionDebug{";
      _aidl_os << "valid: " << ::android::internal::ToString(valid);
      _aidl_os << ", latitudeDegrees: " << ::android::internal::ToString(latitudeDegrees);
      _aidl_os << ", longitudeDegrees: " << ::android::internal::ToString(longitudeDegrees);
      _aidl_os << ", altitudeMeters: " << ::android::internal::ToString(altitudeMeters);
      _aidl_os << ", speedMetersPerSec: " << ::android::internal::ToString(speedMetersPerSec);
      _aidl_os << ", bearingDegrees: " << ::android::internal::ToString(bearingDegrees);
      _aidl_os << ", horizontalAccuracyMeters: " << ::android::internal::ToString(horizontalAccuracyMeters);
      _aidl_os << ", verticalAccuracyMeters: " << ::android::internal::ToString(verticalAccuracyMeters);
      _aidl_os << ", speedAccuracyMetersPerSecond: " << ::android::internal::ToString(speedAccuracyMetersPerSecond);
      _aidl_os << ", bearingAccuracyDegrees: " << ::android::internal::ToString(bearingAccuracyDegrees);
      _aidl_os << ", ageSeconds: " << ::android::internal::ToString(ageSeconds);
      _aidl_os << "}";
      return _aidl_os.str();
    }
  };
  class SatelliteData {
  public:
    typedef std::false_type fixed_size;
    static const char* descriptor;

    int32_t svid = 0;
    ::aidl::android::hardware::gnss::GnssConstellationType constellation = ::aidl::android::hardware::gnss::GnssConstellationType(0);
    ::aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisType ephemerisType = ::aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisType(0);
    ::aidl::android::hardware::gnss::SatellitePvt::SatelliteEphemerisSource ephemerisSource = ::aidl::android::hardware::gnss::SatellitePvt::SatelliteEphemerisSource(0);
    ::aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisHealth ephemerisHealth = ::aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisHealth(0);
    float ephemerisAgeSeconds = 0.000000f;
    bool serverPredictionIsAvailable = false;
    float serverPredictionAgeSeconds = 0.000000f;

    binder_status_t readFromParcel(const AParcel* parcel);
    binder_status_t writeToParcel(AParcel* parcel) const;

    inline bool operator==(const SatelliteData& _rhs) const {
      return std::tie(svid, constellation, ephemerisType, ephemerisSource, ephemerisHealth, ephemerisAgeSeconds, serverPredictionIsAvailable, serverPredictionAgeSeconds) == std::tie(_rhs.svid, _rhs.constellation, _rhs.ephemerisType, _rhs.ephemerisSource, _rhs.ephemerisHealth, _rhs.ephemerisAgeSeconds, _rhs.serverPredictionIsAvailable, _rhs.serverPredictionAgeSeconds);
    }
    inline bool operator<(const SatelliteData& _rhs) const {
      return std::tie(svid, constellation, ephemerisType, ephemerisSource, ephemerisHealth, ephemerisAgeSeconds, serverPredictionIsAvailable, serverPredictionAgeSeconds) < std::tie(_rhs.svid, _rhs.constellation, _rhs.ephemerisType, _rhs.ephemerisSource, _rhs.ephemerisHealth, _rhs.ephemerisAgeSeconds, _rhs.serverPredictionIsAvailable, _rhs.serverPredictionAgeSeconds);
    }
    inline bool operator!=(const SatelliteData& _rhs) const {
      return !(*this == _rhs);
    }
    inline bool operator>(const SatelliteData& _rhs) const {
      return _rhs < *this;
    }
    inline bool operator>=(const SatelliteData& _rhs) const {
      return !(*this < _rhs);
    }
    inline bool operator<=(const SatelliteData& _rhs) const {
      return !(_rhs < *this);
    }

    static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
    inline std::string toString() const {
      std::ostringstream _aidl_os;
      _aidl_os << "SatelliteData{";
      _aidl_os << "svid: " << ::android::internal::ToString(svid);
      _aidl_os << ", constellation: " << ::android::internal::ToString(constellation);
      _aidl_os << ", ephemerisType: " << ::android::internal::ToString(ephemerisType);
      _aidl_os << ", ephemerisSource: " << ::android::internal::ToString(ephemerisSource);
      _aidl_os << ", ephemerisHealth: " << ::android::internal::ToString(ephemerisHealth);
      _aidl_os << ", ephemerisAgeSeconds: " << ::android::internal::ToString(ephemerisAgeSeconds);
      _aidl_os << ", serverPredictionIsAvailable: " << ::android::internal::ToString(serverPredictionIsAvailable);
      _aidl_os << ", serverPredictionAgeSeconds: " << ::android::internal::ToString(serverPredictionAgeSeconds);
      _aidl_os << "}";
      return _aidl_os.str();
    }
  };
  class DebugData {
  public:
    typedef std::false_type fixed_size;
    static const char* descriptor;

    ::aidl::android::hardware::gnss::IGnssDebug::PositionDebug position;
    ::aidl::android::hardware::gnss::IGnssDebug::TimeDebug time;
    std::vector<::aidl::android::hardware::gnss::IGnssDebug::SatelliteData> satelliteDataArray;

    binder_status_t readFromParcel(const AParcel* parcel);
    binder_status_t writeToParcel(AParcel* parcel) const;

    inline bool operator==(const DebugData& _rhs) const {
      return std::tie(position, time, satelliteDataArray) == std::tie(_rhs.position, _rhs.time, _rhs.satelliteDataArray);
    }
    inline bool operator<(const DebugData& _rhs) const {
      return std::tie(position, time, satelliteDataArray) < std::tie(_rhs.position, _rhs.time, _rhs.satelliteDataArray);
    }
    inline bool operator!=(const DebugData& _rhs) const {
      return !(*this == _rhs);
    }
    inline bool operator>(const DebugData& _rhs) const {
      return _rhs < *this;
    }
    inline bool operator>=(const DebugData& _rhs) const {
      return !(*this < _rhs);
    }
    inline bool operator<=(const DebugData& _rhs) const {
      return !(_rhs < *this);
    }

    static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
    inline std::string toString() const {
      std::ostringstream _aidl_os;
      _aidl_os << "DebugData{";
      _aidl_os << "position: " << ::android::internal::ToString(position);
      _aidl_os << ", time: " << ::android::internal::ToString(time);
      _aidl_os << ", satelliteDataArray: " << ::android::internal::ToString(satelliteDataArray);
      _aidl_os << "}";
      return _aidl_os.str();
    }
  };
  static constexpr uint32_t TRANSACTION_getDebugData = FIRST_CALL_TRANSACTION + 0;

  static std::shared_ptr<IGnssDebug> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IGnssDebug>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IGnssDebug>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IGnssDebug>& impl);
  static const std::shared_ptr<IGnssDebug>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus getDebugData(::aidl::android::hardware::gnss::IGnssDebug::DebugData* _aidl_return) = 0;
private:
  static std::shared_ptr<IGnssDebug> default_impl;
};
class IGnssDebugDefault : public IGnssDebug {
public:
  ::ndk::ScopedAStatus getDebugData(::aidl::android::hardware::gnss::IGnssDebug::DebugData* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
[[nodiscard]] static inline std::string toString(IGnssDebug::SatelliteEphemerisType val) {
  switch(val) {
  case IGnssDebug::SatelliteEphemerisType::EPHEMERIS:
    return "EPHEMERIS";
  case IGnssDebug::SatelliteEphemerisType::ALMANAC_ONLY:
    return "ALMANAC_ONLY";
  case IGnssDebug::SatelliteEphemerisType::NOT_AVAILABLE:
    return "NOT_AVAILABLE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace ndk {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisType, 3> enum_values<aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisType> = {
  aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisType::EPHEMERIS,
  aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisType::ALMANAC_ONLY,
  aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisType::NOT_AVAILABLE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
[[nodiscard]] static inline std::string toString(IGnssDebug::SatelliteEphemerisHealth val) {
  switch(val) {
  case IGnssDebug::SatelliteEphemerisHealth::GOOD:
    return "GOOD";
  case IGnssDebug::SatelliteEphemerisHealth::BAD:
    return "BAD";
  case IGnssDebug::SatelliteEphemerisHealth::UNKNOWN:
    return "UNKNOWN";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace ndk {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisHealth, 3> enum_values<aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisHealth> = {
  aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisHealth::GOOD,
  aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisHealth::BAD,
  aidl::android::hardware::gnss::IGnssDebug::SatelliteEphemerisHealth::UNKNOWN,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
