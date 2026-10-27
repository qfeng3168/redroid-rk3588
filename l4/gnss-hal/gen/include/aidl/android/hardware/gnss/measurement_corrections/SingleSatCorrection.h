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
#include <aidl/android/hardware/gnss/GnssConstellationType.h>
#include <aidl/android/hardware/gnss/measurement_corrections/ReflectingPlane.h>
#include <aidl/android/hardware/gnss/measurement_corrections/SingleSatCorrection.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::gnss::measurement_corrections {
class ReflectingPlane;
}  // namespace aidl::android::hardware::gnss::measurement_corrections
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
namespace measurement_corrections {
class SingleSatCorrection {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  class ExcessPathInfo {
  public:
    typedef std::false_type fixed_size;
    static const char* descriptor;

    int32_t excessPathInfoFlags = 0;
    float excessPathLengthMeters = 0.000000f;
    float excessPathLengthUncertaintyMeters = 0.000000f;
    ::aidl::android::hardware::gnss::measurement_corrections::ReflectingPlane reflectingPlane;
    float attenuationDb = 0.000000f;

    binder_status_t readFromParcel(const AParcel* parcel);
    binder_status_t writeToParcel(AParcel* parcel) const;

    inline bool operator==(const ExcessPathInfo& _rhs) const {
      return std::tie(excessPathInfoFlags, excessPathLengthMeters, excessPathLengthUncertaintyMeters, reflectingPlane, attenuationDb) == std::tie(_rhs.excessPathInfoFlags, _rhs.excessPathLengthMeters, _rhs.excessPathLengthUncertaintyMeters, _rhs.reflectingPlane, _rhs.attenuationDb);
    }
    inline bool operator<(const ExcessPathInfo& _rhs) const {
      return std::tie(excessPathInfoFlags, excessPathLengthMeters, excessPathLengthUncertaintyMeters, reflectingPlane, attenuationDb) < std::tie(_rhs.excessPathInfoFlags, _rhs.excessPathLengthMeters, _rhs.excessPathLengthUncertaintyMeters, _rhs.reflectingPlane, _rhs.attenuationDb);
    }
    inline bool operator!=(const ExcessPathInfo& _rhs) const {
      return !(*this == _rhs);
    }
    inline bool operator>(const ExcessPathInfo& _rhs) const {
      return _rhs < *this;
    }
    inline bool operator>=(const ExcessPathInfo& _rhs) const {
      return !(*this < _rhs);
    }
    inline bool operator<=(const ExcessPathInfo& _rhs) const {
      return !(_rhs < *this);
    }

    static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
    enum : int32_t { EXCESS_PATH_INFO_HAS_EXCESS_PATH_LENGTH = 1 };
    enum : int32_t { EXCESS_PATH_INFO_HAS_EXCESS_PATH_LENGTH_UNC = 2 };
    enum : int32_t { EXCESS_PATH_INFO_HAS_REFLECTING_PLANE = 4 };
    enum : int32_t { EXCESS_PATH_INFO_HAS_ATTENUATION = 8 };
    inline std::string toString() const {
      std::ostringstream _aidl_os;
      _aidl_os << "ExcessPathInfo{";
      _aidl_os << "excessPathInfoFlags: " << ::android::internal::ToString(excessPathInfoFlags);
      _aidl_os << ", excessPathLengthMeters: " << ::android::internal::ToString(excessPathLengthMeters);
      _aidl_os << ", excessPathLengthUncertaintyMeters: " << ::android::internal::ToString(excessPathLengthUncertaintyMeters);
      _aidl_os << ", reflectingPlane: " << ::android::internal::ToString(reflectingPlane);
      _aidl_os << ", attenuationDb: " << ::android::internal::ToString(attenuationDb);
      _aidl_os << "}";
      return _aidl_os.str();
    }
  };
  int32_t singleSatCorrectionFlags = 0;
  ::aidl::android::hardware::gnss::GnssConstellationType constellation = ::aidl::android::hardware::gnss::GnssConstellationType(0);
  int32_t svid = 0;
  int64_t carrierFrequencyHz = 0L;
  float probSatIsLos = 0.000000f;
  float combinedExcessPathLengthMeters = 0.000000f;
  float combinedExcessPathLengthUncertaintyMeters = 0.000000f;
  float combinedAttenuationDb = 0.000000f;
  std::vector<::aidl::android::hardware::gnss::measurement_corrections::SingleSatCorrection::ExcessPathInfo> excessPathInfos;

  binder_status_t readFromParcel(const AParcel* parcel);
  binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const SingleSatCorrection& _rhs) const {
    return std::tie(singleSatCorrectionFlags, constellation, svid, carrierFrequencyHz, probSatIsLos, combinedExcessPathLengthMeters, combinedExcessPathLengthUncertaintyMeters, combinedAttenuationDb, excessPathInfos) == std::tie(_rhs.singleSatCorrectionFlags, _rhs.constellation, _rhs.svid, _rhs.carrierFrequencyHz, _rhs.probSatIsLos, _rhs.combinedExcessPathLengthMeters, _rhs.combinedExcessPathLengthUncertaintyMeters, _rhs.combinedAttenuationDb, _rhs.excessPathInfos);
  }
  inline bool operator<(const SingleSatCorrection& _rhs) const {
    return std::tie(singleSatCorrectionFlags, constellation, svid, carrierFrequencyHz, probSatIsLos, combinedExcessPathLengthMeters, combinedExcessPathLengthUncertaintyMeters, combinedAttenuationDb, excessPathInfos) < std::tie(_rhs.singleSatCorrectionFlags, _rhs.constellation, _rhs.svid, _rhs.carrierFrequencyHz, _rhs.probSatIsLos, _rhs.combinedExcessPathLengthMeters, _rhs.combinedExcessPathLengthUncertaintyMeters, _rhs.combinedAttenuationDb, _rhs.excessPathInfos);
  }
  inline bool operator!=(const SingleSatCorrection& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const SingleSatCorrection& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const SingleSatCorrection& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const SingleSatCorrection& _rhs) const {
    return !(_rhs < *this);
  }

  static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  enum : int32_t { SINGLE_SAT_CORRECTION_HAS_SAT_IS_LOS_PROBABILITY = 1 };
  enum : int32_t { SINGLE_SAT_CORRECTION_HAS_COMBINED_EXCESS_PATH_LENGTH = 2 };
  enum : int32_t { SINGLE_SAT_CORRECTION_HAS_COMBINED_EXCESS_PATH_LENGTH_UNC = 4 };
  enum : int32_t { SINGLE_SAT_CORRECTION_HAS_COMBINED_ATTENUATION = 16 };
  inline std::string toString() const {
    std::ostringstream _aidl_os;
    _aidl_os << "SingleSatCorrection{";
    _aidl_os << "singleSatCorrectionFlags: " << ::android::internal::ToString(singleSatCorrectionFlags);
    _aidl_os << ", constellation: " << ::android::internal::ToString(constellation);
    _aidl_os << ", svid: " << ::android::internal::ToString(svid);
    _aidl_os << ", carrierFrequencyHz: " << ::android::internal::ToString(carrierFrequencyHz);
    _aidl_os << ", probSatIsLos: " << ::android::internal::ToString(probSatIsLos);
    _aidl_os << ", combinedExcessPathLengthMeters: " << ::android::internal::ToString(combinedExcessPathLengthMeters);
    _aidl_os << ", combinedExcessPathLengthUncertaintyMeters: " << ::android::internal::ToString(combinedExcessPathLengthUncertaintyMeters);
    _aidl_os << ", combinedAttenuationDb: " << ::android::internal::ToString(combinedAttenuationDb);
    _aidl_os << ", excessPathInfos: " << ::android::internal::ToString(excessPathInfos);
    _aidl_os << "}";
    return _aidl_os.str();
  }
};
}  // namespace measurement_corrections
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
