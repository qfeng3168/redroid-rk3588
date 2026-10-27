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
#include <aidl/android/hardware/gnss/ElapsedRealtime.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::gnss {
class ElapsedRealtime;
}  // namespace aidl::android::hardware::gnss
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class GnssLocation {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  int32_t gnssLocationFlags = 0;
  double latitudeDegrees = 0.000000;
  double longitudeDegrees = 0.000000;
  double altitudeMeters = 0.000000;
  double speedMetersPerSec = 0.000000;
  double bearingDegrees = 0.000000;
  double horizontalAccuracyMeters = 0.000000;
  double verticalAccuracyMeters = 0.000000;
  double speedAccuracyMetersPerSecond = 0.000000;
  double bearingAccuracyDegrees = 0.000000;
  int64_t timestampMillis = 0L;
  ::aidl::android::hardware::gnss::ElapsedRealtime elapsedRealtime;

  binder_status_t readFromParcel(const AParcel* parcel);
  binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const GnssLocation& _rhs) const {
    return std::tie(gnssLocationFlags, latitudeDegrees, longitudeDegrees, altitudeMeters, speedMetersPerSec, bearingDegrees, horizontalAccuracyMeters, verticalAccuracyMeters, speedAccuracyMetersPerSecond, bearingAccuracyDegrees, timestampMillis, elapsedRealtime) == std::tie(_rhs.gnssLocationFlags, _rhs.latitudeDegrees, _rhs.longitudeDegrees, _rhs.altitudeMeters, _rhs.speedMetersPerSec, _rhs.bearingDegrees, _rhs.horizontalAccuracyMeters, _rhs.verticalAccuracyMeters, _rhs.speedAccuracyMetersPerSecond, _rhs.bearingAccuracyDegrees, _rhs.timestampMillis, _rhs.elapsedRealtime);
  }
  inline bool operator<(const GnssLocation& _rhs) const {
    return std::tie(gnssLocationFlags, latitudeDegrees, longitudeDegrees, altitudeMeters, speedMetersPerSec, bearingDegrees, horizontalAccuracyMeters, verticalAccuracyMeters, speedAccuracyMetersPerSecond, bearingAccuracyDegrees, timestampMillis, elapsedRealtime) < std::tie(_rhs.gnssLocationFlags, _rhs.latitudeDegrees, _rhs.longitudeDegrees, _rhs.altitudeMeters, _rhs.speedMetersPerSec, _rhs.bearingDegrees, _rhs.horizontalAccuracyMeters, _rhs.verticalAccuracyMeters, _rhs.speedAccuracyMetersPerSecond, _rhs.bearingAccuracyDegrees, _rhs.timestampMillis, _rhs.elapsedRealtime);
  }
  inline bool operator!=(const GnssLocation& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const GnssLocation& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const GnssLocation& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const GnssLocation& _rhs) const {
    return !(_rhs < *this);
  }

  static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  enum : int32_t { HAS_LAT_LONG = 1 };
  enum : int32_t { HAS_ALTITUDE = 2 };
  enum : int32_t { HAS_SPEED = 4 };
  enum : int32_t { HAS_BEARING = 8 };
  enum : int32_t { HAS_HORIZONTAL_ACCURACY = 16 };
  enum : int32_t { HAS_VERTICAL_ACCURACY = 32 };
  enum : int32_t { HAS_SPEED_ACCURACY = 64 };
  enum : int32_t { HAS_BEARING_ACCURACY = 128 };
  inline std::string toString() const {
    std::ostringstream _aidl_os;
    _aidl_os << "GnssLocation{";
    _aidl_os << "gnssLocationFlags: " << ::android::internal::ToString(gnssLocationFlags);
    _aidl_os << ", latitudeDegrees: " << ::android::internal::ToString(latitudeDegrees);
    _aidl_os << ", longitudeDegrees: " << ::android::internal::ToString(longitudeDegrees);
    _aidl_os << ", altitudeMeters: " << ::android::internal::ToString(altitudeMeters);
    _aidl_os << ", speedMetersPerSec: " << ::android::internal::ToString(speedMetersPerSec);
    _aidl_os << ", bearingDegrees: " << ::android::internal::ToString(bearingDegrees);
    _aidl_os << ", horizontalAccuracyMeters: " << ::android::internal::ToString(horizontalAccuracyMeters);
    _aidl_os << ", verticalAccuracyMeters: " << ::android::internal::ToString(verticalAccuracyMeters);
    _aidl_os << ", speedAccuracyMetersPerSecond: " << ::android::internal::ToString(speedAccuracyMetersPerSecond);
    _aidl_os << ", bearingAccuracyDegrees: " << ::android::internal::ToString(bearingAccuracyDegrees);
    _aidl_os << ", timestampMillis: " << ::android::internal::ToString(timestampMillis);
    _aidl_os << ", elapsedRealtime: " << ::android::internal::ToString(elapsedRealtime);
    _aidl_os << "}";
    return _aidl_os.str();
  }
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
