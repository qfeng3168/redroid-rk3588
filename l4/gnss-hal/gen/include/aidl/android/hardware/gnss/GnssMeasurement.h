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
#include <aidl/android/hardware/gnss/CorrelationVector.h>
#include <aidl/android/hardware/gnss/GnssMultipathIndicator.h>
#include <aidl/android/hardware/gnss/GnssSignalType.h>
#include <aidl/android/hardware/gnss/SatellitePvt.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::gnss {
class CorrelationVector;
class GnssSignalType;
class SatellitePvt;
}  // namespace aidl::android::hardware::gnss
namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class GnssMeasurement {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  int32_t flags = 0;
  int32_t svid = 0;
  ::aidl::android::hardware::gnss::GnssSignalType signalType;
  double timeOffsetNs = 0.000000;
  int32_t state = 0;
  int64_t receivedSvTimeInNs = 0L;
  int64_t receivedSvTimeUncertaintyInNs = 0L;
  double antennaCN0DbHz = 0.000000;
  double basebandCN0DbHz = 0.000000;
  double pseudorangeRateMps = 0.000000;
  double pseudorangeRateUncertaintyMps = 0.000000;
  int32_t accumulatedDeltaRangeState = 0;
  double accumulatedDeltaRangeM = 0.000000;
  double accumulatedDeltaRangeUncertaintyM = 0.000000;
  int64_t carrierCycles = 0L;
  double carrierPhase = 0.000000;
  double carrierPhaseUncertainty = 0.000000;
  ::aidl::android::hardware::gnss::GnssMultipathIndicator multipathIndicator = ::aidl::android::hardware::gnss::GnssMultipathIndicator::UNKNOWN;
  double snrDb = 0.000000;
  double agcLevelDb = 0.000000;
  double fullInterSignalBiasNs = 0.000000;
  double fullInterSignalBiasUncertaintyNs = 0.000000;
  double satelliteInterSignalBiasNs = 0.000000;
  double satelliteInterSignalBiasUncertaintyNs = 0.000000;
  ::aidl::android::hardware::gnss::SatellitePvt satellitePvt;
  std::vector<::aidl::android::hardware::gnss::CorrelationVector> correlationVectors;

  binder_status_t readFromParcel(const AParcel* parcel);
  binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const GnssMeasurement& _rhs) const {
    return std::tie(flags, svid, signalType, timeOffsetNs, state, receivedSvTimeInNs, receivedSvTimeUncertaintyInNs, antennaCN0DbHz, basebandCN0DbHz, pseudorangeRateMps, pseudorangeRateUncertaintyMps, accumulatedDeltaRangeState, accumulatedDeltaRangeM, accumulatedDeltaRangeUncertaintyM, carrierCycles, carrierPhase, carrierPhaseUncertainty, multipathIndicator, snrDb, agcLevelDb, fullInterSignalBiasNs, fullInterSignalBiasUncertaintyNs, satelliteInterSignalBiasNs, satelliteInterSignalBiasUncertaintyNs, satellitePvt, correlationVectors) == std::tie(_rhs.flags, _rhs.svid, _rhs.signalType, _rhs.timeOffsetNs, _rhs.state, _rhs.receivedSvTimeInNs, _rhs.receivedSvTimeUncertaintyInNs, _rhs.antennaCN0DbHz, _rhs.basebandCN0DbHz, _rhs.pseudorangeRateMps, _rhs.pseudorangeRateUncertaintyMps, _rhs.accumulatedDeltaRangeState, _rhs.accumulatedDeltaRangeM, _rhs.accumulatedDeltaRangeUncertaintyM, _rhs.carrierCycles, _rhs.carrierPhase, _rhs.carrierPhaseUncertainty, _rhs.multipathIndicator, _rhs.snrDb, _rhs.agcLevelDb, _rhs.fullInterSignalBiasNs, _rhs.fullInterSignalBiasUncertaintyNs, _rhs.satelliteInterSignalBiasNs, _rhs.satelliteInterSignalBiasUncertaintyNs, _rhs.satellitePvt, _rhs.correlationVectors);
  }
  inline bool operator<(const GnssMeasurement& _rhs) const {
    return std::tie(flags, svid, signalType, timeOffsetNs, state, receivedSvTimeInNs, receivedSvTimeUncertaintyInNs, antennaCN0DbHz, basebandCN0DbHz, pseudorangeRateMps, pseudorangeRateUncertaintyMps, accumulatedDeltaRangeState, accumulatedDeltaRangeM, accumulatedDeltaRangeUncertaintyM, carrierCycles, carrierPhase, carrierPhaseUncertainty, multipathIndicator, snrDb, agcLevelDb, fullInterSignalBiasNs, fullInterSignalBiasUncertaintyNs, satelliteInterSignalBiasNs, satelliteInterSignalBiasUncertaintyNs, satellitePvt, correlationVectors) < std::tie(_rhs.flags, _rhs.svid, _rhs.signalType, _rhs.timeOffsetNs, _rhs.state, _rhs.receivedSvTimeInNs, _rhs.receivedSvTimeUncertaintyInNs, _rhs.antennaCN0DbHz, _rhs.basebandCN0DbHz, _rhs.pseudorangeRateMps, _rhs.pseudorangeRateUncertaintyMps, _rhs.accumulatedDeltaRangeState, _rhs.accumulatedDeltaRangeM, _rhs.accumulatedDeltaRangeUncertaintyM, _rhs.carrierCycles, _rhs.carrierPhase, _rhs.carrierPhaseUncertainty, _rhs.multipathIndicator, _rhs.snrDb, _rhs.agcLevelDb, _rhs.fullInterSignalBiasNs, _rhs.fullInterSignalBiasUncertaintyNs, _rhs.satelliteInterSignalBiasNs, _rhs.satelliteInterSignalBiasUncertaintyNs, _rhs.satellitePvt, _rhs.correlationVectors);
  }
  inline bool operator!=(const GnssMeasurement& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const GnssMeasurement& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const GnssMeasurement& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const GnssMeasurement& _rhs) const {
    return !(_rhs < *this);
  }

  static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  enum : int32_t { HAS_SNR = 1 };
  enum : int32_t { HAS_CARRIER_FREQUENCY = 512 };
  enum : int32_t { HAS_CARRIER_CYCLES = 1024 };
  enum : int32_t { HAS_CARRIER_PHASE = 2048 };
  enum : int32_t { HAS_CARRIER_PHASE_UNCERTAINTY = 4096 };
  enum : int32_t { HAS_AUTOMATIC_GAIN_CONTROL = 8192 };
  enum : int32_t { HAS_FULL_ISB = 65536 };
  enum : int32_t { HAS_FULL_ISB_UNCERTAINTY = 131072 };
  enum : int32_t { HAS_SATELLITE_ISB = 262144 };
  enum : int32_t { HAS_SATELLITE_ISB_UNCERTAINTY = 524288 };
  enum : int32_t { HAS_SATELLITE_PVT = 1048576 };
  enum : int32_t { HAS_CORRELATION_VECTOR = 2097152 };
  enum : int32_t { STATE_UNKNOWN = 0 };
  enum : int32_t { STATE_CODE_LOCK = 1 };
  enum : int32_t { STATE_BIT_SYNC = 2 };
  enum : int32_t { STATE_SUBFRAME_SYNC = 4 };
  enum : int32_t { STATE_TOW_DECODED = 8 };
  enum : int32_t { STATE_MSEC_AMBIGUOUS = 16 };
  enum : int32_t { STATE_SYMBOL_SYNC = 32 };
  enum : int32_t { STATE_GLO_STRING_SYNC = 64 };
  enum : int32_t { STATE_GLO_TOD_DECODED = 128 };
  enum : int32_t { STATE_BDS_D2_BIT_SYNC = 256 };
  enum : int32_t { STATE_BDS_D2_SUBFRAME_SYNC = 512 };
  enum : int32_t { STATE_GAL_E1BC_CODE_LOCK = 1024 };
  enum : int32_t { STATE_GAL_E1C_2ND_CODE_LOCK = 2048 };
  enum : int32_t { STATE_GAL_E1B_PAGE_SYNC = 4096 };
  enum : int32_t { STATE_SBAS_SYNC = 8192 };
  enum : int32_t { STATE_TOW_KNOWN = 16384 };
  enum : int32_t { STATE_GLO_TOD_KNOWN = 32768 };
  enum : int32_t { STATE_2ND_CODE_LOCK = 65536 };
  enum : int32_t { ADR_STATE_UNKNOWN = 0 };
  enum : int32_t { ADR_STATE_VALID = 1 };
  enum : int32_t { ADR_STATE_RESET = 2 };
  enum : int32_t { ADR_STATE_CYCLE_SLIP = 4 };
  enum : int32_t { ADR_STATE_HALF_CYCLE_RESOLVED = 8 };
  inline std::string toString() const {
    std::ostringstream _aidl_os;
    _aidl_os << "GnssMeasurement{";
    _aidl_os << "flags: " << ::android::internal::ToString(flags);
    _aidl_os << ", svid: " << ::android::internal::ToString(svid);
    _aidl_os << ", signalType: " << ::android::internal::ToString(signalType);
    _aidl_os << ", timeOffsetNs: " << ::android::internal::ToString(timeOffsetNs);
    _aidl_os << ", state: " << ::android::internal::ToString(state);
    _aidl_os << ", receivedSvTimeInNs: " << ::android::internal::ToString(receivedSvTimeInNs);
    _aidl_os << ", receivedSvTimeUncertaintyInNs: " << ::android::internal::ToString(receivedSvTimeUncertaintyInNs);
    _aidl_os << ", antennaCN0DbHz: " << ::android::internal::ToString(antennaCN0DbHz);
    _aidl_os << ", basebandCN0DbHz: " << ::android::internal::ToString(basebandCN0DbHz);
    _aidl_os << ", pseudorangeRateMps: " << ::android::internal::ToString(pseudorangeRateMps);
    _aidl_os << ", pseudorangeRateUncertaintyMps: " << ::android::internal::ToString(pseudorangeRateUncertaintyMps);
    _aidl_os << ", accumulatedDeltaRangeState: " << ::android::internal::ToString(accumulatedDeltaRangeState);
    _aidl_os << ", accumulatedDeltaRangeM: " << ::android::internal::ToString(accumulatedDeltaRangeM);
    _aidl_os << ", accumulatedDeltaRangeUncertaintyM: " << ::android::internal::ToString(accumulatedDeltaRangeUncertaintyM);
    _aidl_os << ", carrierCycles: " << ::android::internal::ToString(carrierCycles);
    _aidl_os << ", carrierPhase: " << ::android::internal::ToString(carrierPhase);
    _aidl_os << ", carrierPhaseUncertainty: " << ::android::internal::ToString(carrierPhaseUncertainty);
    _aidl_os << ", multipathIndicator: " << ::android::internal::ToString(multipathIndicator);
    _aidl_os << ", snrDb: " << ::android::internal::ToString(snrDb);
    _aidl_os << ", agcLevelDb: " << ::android::internal::ToString(agcLevelDb);
    _aidl_os << ", fullInterSignalBiasNs: " << ::android::internal::ToString(fullInterSignalBiasNs);
    _aidl_os << ", fullInterSignalBiasUncertaintyNs: " << ::android::internal::ToString(fullInterSignalBiasUncertaintyNs);
    _aidl_os << ", satelliteInterSignalBiasNs: " << ::android::internal::ToString(satelliteInterSignalBiasNs);
    _aidl_os << ", satelliteInterSignalBiasUncertaintyNs: " << ::android::internal::ToString(satelliteInterSignalBiasUncertaintyNs);
    _aidl_os << ", satellitePvt: " << ::android::internal::ToString(satellitePvt);
    _aidl_os << ", correlationVectors: " << ::android::internal::ToString(correlationVectors);
    _aidl_os << "}";
    return _aidl_os.str();
  }
};
}  // namespace gnss
}  // namespace hardware
}  // namespace android
}  // namespace aidl
