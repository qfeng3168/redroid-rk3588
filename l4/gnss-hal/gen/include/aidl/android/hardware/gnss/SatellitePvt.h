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
#include <aidl/android/hardware/gnss/SatelliteClockInfo.h>
#include <aidl/android/hardware/gnss/SatellitePositionEcef.h>
#include <aidl/android/hardware/gnss/SatellitePvt.h>
#include <aidl/android/hardware/gnss/SatelliteVelocityEcef.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::gnss {
class SatelliteClockInfo;
class SatellitePositionEcef;
class SatelliteVelocityEcef;
}  // namespace aidl::android::hardware::gnss
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class SatellitePvt {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  enum class SatelliteEphemerisSource : int32_t {
    DEMODULATED = 0,
    SERVER_NORMAL = 1,
    SERVER_LONG_TERM = 2,
    OTHER = 3,
  };

  int32_t flags = 0;
  ::aidl::android::hardware::gnss::SatellitePositionEcef satPosEcef;
  ::aidl::android::hardware::gnss::SatelliteVelocityEcef satVelEcef;
  ::aidl::android::hardware::gnss::SatelliteClockInfo satClockInfo;
  double ionoDelayMeters = 0.000000;
  double tropoDelayMeters = 0.000000;
  int64_t timeOfClockSeconds = 0L;
  int32_t issueOfDataClock = 0;
  int64_t timeOfEphemerisSeconds = 0L;
  int32_t issueOfDataEphemeris = 0;
  ::aidl::android::hardware::gnss::SatellitePvt::SatelliteEphemerisSource ephemerisSource = ::aidl::android::hardware::gnss::SatellitePvt::SatelliteEphemerisSource::OTHER;

  binder_status_t readFromParcel(const AParcel* parcel);
  binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const SatellitePvt& _rhs) const {
    return std::tie(flags, satPosEcef, satVelEcef, satClockInfo, ionoDelayMeters, tropoDelayMeters, timeOfClockSeconds, issueOfDataClock, timeOfEphemerisSeconds, issueOfDataEphemeris, ephemerisSource) == std::tie(_rhs.flags, _rhs.satPosEcef, _rhs.satVelEcef, _rhs.satClockInfo, _rhs.ionoDelayMeters, _rhs.tropoDelayMeters, _rhs.timeOfClockSeconds, _rhs.issueOfDataClock, _rhs.timeOfEphemerisSeconds, _rhs.issueOfDataEphemeris, _rhs.ephemerisSource);
  }
  inline bool operator<(const SatellitePvt& _rhs) const {
    return std::tie(flags, satPosEcef, satVelEcef, satClockInfo, ionoDelayMeters, tropoDelayMeters, timeOfClockSeconds, issueOfDataClock, timeOfEphemerisSeconds, issueOfDataEphemeris, ephemerisSource) < std::tie(_rhs.flags, _rhs.satPosEcef, _rhs.satVelEcef, _rhs.satClockInfo, _rhs.ionoDelayMeters, _rhs.tropoDelayMeters, _rhs.timeOfClockSeconds, _rhs.issueOfDataClock, _rhs.timeOfEphemerisSeconds, _rhs.issueOfDataEphemeris, _rhs.ephemerisSource);
  }
  inline bool operator!=(const SatellitePvt& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const SatellitePvt& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const SatellitePvt& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const SatellitePvt& _rhs) const {
    return !(_rhs < *this);
  }

  static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  enum : int32_t { HAS_POSITION_VELOCITY_CLOCK_INFO = 1 };
  enum : int32_t { HAS_IONO = 2 };
  enum : int32_t { HAS_TROPO = 4 };
  inline std::string toString() const {
    std::ostringstream _aidl_os;
    _aidl_os << "SatellitePvt{";
    _aidl_os << "flags: " << ::android::internal::ToString(flags);
    _aidl_os << ", satPosEcef: " << ::android::internal::ToString(satPosEcef);
    _aidl_os << ", satVelEcef: " << ::android::internal::ToString(satVelEcef);
    _aidl_os << ", satClockInfo: " << ::android::internal::ToString(satClockInfo);
    _aidl_os << ", ionoDelayMeters: " << ::android::internal::ToString(ionoDelayMeters);
    _aidl_os << ", tropoDelayMeters: " << ::android::internal::ToString(tropoDelayMeters);
    _aidl_os << ", timeOfClockSeconds: " << ::android::internal::ToString(timeOfClockSeconds);
    _aidl_os << ", issueOfDataClock: " << ::android::internal::ToString(issueOfDataClock);
    _aidl_os << ", timeOfEphemerisSeconds: " << ::android::internal::ToString(timeOfEphemerisSeconds);
    _aidl_os << ", issueOfDataEphemeris: " << ::android::internal::ToString(issueOfDataEphemeris);
    _aidl_os << ", ephemerisSource: " << ::android::internal::ToString(ephemerisSource);
    _aidl_os << "}";
    return _aidl_os.str();
  }
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
[[nodiscard]] static inline std::string toString(SatellitePvt::SatelliteEphemerisSource val) {
  switch(val) {
  case SatellitePvt::SatelliteEphemerisSource::DEMODULATED:
    return "DEMODULATED";
  case SatellitePvt::SatelliteEphemerisSource::SERVER_NORMAL:
    return "SERVER_NORMAL";
  case SatellitePvt::SatelliteEphemerisSource::SERVER_LONG_TERM:
    return "SERVER_LONG_TERM";
  case SatellitePvt::SatelliteEphemerisSource::OTHER:
    return "OTHER";
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
constexpr inline std::array<aidl::android::hardware::gnss::SatellitePvt::SatelliteEphemerisSource, 4> enum_values<aidl::android::hardware::gnss::SatellitePvt::SatelliteEphemerisSource> = {
  aidl::android::hardware::gnss::SatellitePvt::SatelliteEphemerisSource::DEMODULATED,
  aidl::android::hardware::gnss::SatellitePvt::SatelliteEphemerisSource::SERVER_NORMAL,
  aidl::android::hardware::gnss::SatellitePvt::SatelliteEphemerisSource::SERVER_LONG_TERM,
  aidl::android::hardware::gnss::SatellitePvt::SatelliteEphemerisSource::OTHER,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
