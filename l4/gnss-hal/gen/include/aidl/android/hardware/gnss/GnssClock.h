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
#include <aidl/android/hardware/gnss/GnssSignalType.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::gnss {
class GnssSignalType;
}  // namespace aidl::android::hardware::gnss
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class GnssClock {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  int32_t gnssClockFlags = 0;
  int32_t leapSecond = 0;
  int64_t timeNs = 0L;
  double timeUncertaintyNs = 0.000000;
  int64_t fullBiasNs = 0L;
  double biasNs = 0.000000;
  double biasUncertaintyNs = 0.000000;
  double driftNsps = 0.000000;
  double driftUncertaintyNsps = 0.000000;
  int32_t hwClockDiscontinuityCount = 0;
  ::aidl::android::hardware::gnss::GnssSignalType referenceSignalTypeForIsb;

  binder_status_t readFromParcel(const AParcel* parcel);
  binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const GnssClock& _rhs) const {
    return std::tie(gnssClockFlags, leapSecond, timeNs, timeUncertaintyNs, fullBiasNs, biasNs, biasUncertaintyNs, driftNsps, driftUncertaintyNsps, hwClockDiscontinuityCount, referenceSignalTypeForIsb) == std::tie(_rhs.gnssClockFlags, _rhs.leapSecond, _rhs.timeNs, _rhs.timeUncertaintyNs, _rhs.fullBiasNs, _rhs.biasNs, _rhs.biasUncertaintyNs, _rhs.driftNsps, _rhs.driftUncertaintyNsps, _rhs.hwClockDiscontinuityCount, _rhs.referenceSignalTypeForIsb);
  }
  inline bool operator<(const GnssClock& _rhs) const {
    return std::tie(gnssClockFlags, leapSecond, timeNs, timeUncertaintyNs, fullBiasNs, biasNs, biasUncertaintyNs, driftNsps, driftUncertaintyNsps, hwClockDiscontinuityCount, referenceSignalTypeForIsb) < std::tie(_rhs.gnssClockFlags, _rhs.leapSecond, _rhs.timeNs, _rhs.timeUncertaintyNs, _rhs.fullBiasNs, _rhs.biasNs, _rhs.biasUncertaintyNs, _rhs.driftNsps, _rhs.driftUncertaintyNsps, _rhs.hwClockDiscontinuityCount, _rhs.referenceSignalTypeForIsb);
  }
  inline bool operator!=(const GnssClock& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const GnssClock& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const GnssClock& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const GnssClock& _rhs) const {
    return !(_rhs < *this);
  }

  static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  enum : int32_t { HAS_LEAP_SECOND = 1 };
  enum : int32_t { HAS_TIME_UNCERTAINTY = 2 };
  enum : int32_t { HAS_FULL_BIAS = 4 };
  enum : int32_t { HAS_BIAS = 8 };
  enum : int32_t { HAS_BIAS_UNCERTAINTY = 16 };
  enum : int32_t { HAS_DRIFT = 32 };
  enum : int32_t { HAS_DRIFT_UNCERTAINTY = 64 };
  inline std::string toString() const {
    std::ostringstream _aidl_os;
    _aidl_os << "GnssClock{";
    _aidl_os << "gnssClockFlags: " << ::android::internal::ToString(gnssClockFlags);
    _aidl_os << ", leapSecond: " << ::android::internal::ToString(leapSecond);
    _aidl_os << ", timeNs: " << ::android::internal::ToString(timeNs);
    _aidl_os << ", timeUncertaintyNs: " << ::android::internal::ToString(timeUncertaintyNs);
    _aidl_os << ", fullBiasNs: " << ::android::internal::ToString(fullBiasNs);
    _aidl_os << ", biasNs: " << ::android::internal::ToString(biasNs);
    _aidl_os << ", biasUncertaintyNs: " << ::android::internal::ToString(biasUncertaintyNs);
    _aidl_os << ", driftNsps: " << ::android::internal::ToString(driftNsps);
    _aidl_os << ", driftUncertaintyNsps: " << ::android::internal::ToString(driftUncertaintyNsps);
    _aidl_os << ", hwClockDiscontinuityCount: " << ::android::internal::ToString(hwClockDiscontinuityCount);
    _aidl_os << ", referenceSignalTypeForIsb: " << ::android::internal::ToString(referenceSignalTypeForIsb);
    _aidl_os << "}";
    return _aidl_os.str();
  }
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
