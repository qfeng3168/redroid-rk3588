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
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
namespace measurement_corrections {
class ReflectingPlane {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  double latitudeDegrees = 0.000000;
  double longitudeDegrees = 0.000000;
  double altitudeMeters = 0.000000;
  double reflectingPlaneAzimuthDegrees = 0.000000;

  binder_status_t readFromParcel(const AParcel* parcel);
  binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const ReflectingPlane& _rhs) const {
    return std::tie(latitudeDegrees, longitudeDegrees, altitudeMeters, reflectingPlaneAzimuthDegrees) == std::tie(_rhs.latitudeDegrees, _rhs.longitudeDegrees, _rhs.altitudeMeters, _rhs.reflectingPlaneAzimuthDegrees);
  }
  inline bool operator<(const ReflectingPlane& _rhs) const {
    return std::tie(latitudeDegrees, longitudeDegrees, altitudeMeters, reflectingPlaneAzimuthDegrees) < std::tie(_rhs.latitudeDegrees, _rhs.longitudeDegrees, _rhs.altitudeMeters, _rhs.reflectingPlaneAzimuthDegrees);
  }
  inline bool operator!=(const ReflectingPlane& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const ReflectingPlane& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const ReflectingPlane& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const ReflectingPlane& _rhs) const {
    return !(_rhs < *this);
  }

  static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  inline std::string toString() const {
    std::ostringstream _aidl_os;
    _aidl_os << "ReflectingPlane{";
    _aidl_os << "latitudeDegrees: " << ::android::internal::ToString(latitudeDegrees);
    _aidl_os << ", longitudeDegrees: " << ::android::internal::ToString(longitudeDegrees);
    _aidl_os << ", altitudeMeters: " << ::android::internal::ToString(altitudeMeters);
    _aidl_os << ", reflectingPlaneAzimuthDegrees: " << ::android::internal::ToString(reflectingPlaneAzimuthDegrees);
    _aidl_os << "}";
    return _aidl_os.str();
  }
};
}  // namespace measurement_corrections
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
