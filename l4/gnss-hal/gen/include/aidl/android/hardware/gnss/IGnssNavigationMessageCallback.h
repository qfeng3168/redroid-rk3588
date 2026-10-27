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
#include <aidl/android/hardware/gnss/IGnssNavigationMessageCallback.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace hardware {
namespace gnss {
class IGnssNavigationMessageCallbackDelegator;

class IGnssNavigationMessageCallback : public ::ndk::ICInterface {
public:
  typedef IGnssNavigationMessageCallbackDelegator DefaultDelegator;
  static const char* descriptor;
  IGnssNavigationMessageCallback();
  virtual ~IGnssNavigationMessageCallback();

  class GnssNavigationMessage {
  public:
    typedef std::false_type fixed_size;
    static const char* descriptor;

    enum class GnssNavigationMessageType : int32_t {
      UNKNOWN = 0,
      GPS_L1CA = 257,
      GPS_L2CNAV = 258,
      GPS_L5CNAV = 259,
      SBS = 513,
      GPS_CNAV2 = 260,
      GLO_L1CA = 769,
      QZS_L1CA = 1025,
      BDS_D1 = 1281,
      BDS_D2 = 1282,
      BDS_CNAV1 = 1283,
      BDS_CNAV2 = 1284,
      GAL_I = 1537,
      GAL_F = 1538,
      IRN_L5CA = 1793,
    };

    int32_t svid = 0;
    ::aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType type = ::aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType(0);
    int32_t status = 0;
    int32_t messageId = 0;
    int32_t submessageId = 0;
    std::vector<uint8_t> data;

    binder_status_t readFromParcel(const AParcel* parcel);
    binder_status_t writeToParcel(AParcel* parcel) const;

    inline bool operator==(const GnssNavigationMessage& _rhs) const {
      return std::tie(svid, type, status, messageId, submessageId, data) == std::tie(_rhs.svid, _rhs.type, _rhs.status, _rhs.messageId, _rhs.submessageId, _rhs.data);
    }
    inline bool operator<(const GnssNavigationMessage& _rhs) const {
      return std::tie(svid, type, status, messageId, submessageId, data) < std::tie(_rhs.svid, _rhs.type, _rhs.status, _rhs.messageId, _rhs.submessageId, _rhs.data);
    }
    inline bool operator!=(const GnssNavigationMessage& _rhs) const {
      return !(*this == _rhs);
    }
    inline bool operator>(const GnssNavigationMessage& _rhs) const {
      return _rhs < *this;
    }
    inline bool operator>=(const GnssNavigationMessage& _rhs) const {
      return !(*this < _rhs);
    }
    inline bool operator<=(const GnssNavigationMessage& _rhs) const {
      return !(_rhs < *this);
    }

    static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
    enum : int32_t { STATUS_PARITY_PASSED = 1 };
    enum : int32_t { STATUS_PARITY_REBUILT = 2 };
    enum : int32_t { STATUS_UNKNOWN = 0 };
    inline std::string toString() const {
      std::ostringstream _aidl_os;
      _aidl_os << "GnssNavigationMessage{";
      _aidl_os << "svid: " << ::android::internal::ToString(svid);
      _aidl_os << ", type: " << ::android::internal::ToString(type);
      _aidl_os << ", status: " << ::android::internal::ToString(status);
      _aidl_os << ", messageId: " << ::android::internal::ToString(messageId);
      _aidl_os << ", submessageId: " << ::android::internal::ToString(submessageId);
      _aidl_os << ", data: " << ::android::internal::ToString(data);
      _aidl_os << "}";
      return _aidl_os.str();
    }
  };
  static constexpr uint32_t TRANSACTION_gnssNavigationMessageCb = FIRST_CALL_TRANSACTION + 0;

  static std::shared_ptr<IGnssNavigationMessageCallback> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IGnssNavigationMessageCallback>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IGnssNavigationMessageCallback>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IGnssNavigationMessageCallback>& impl);
  static const std::shared_ptr<IGnssNavigationMessageCallback>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus gnssNavigationMessageCb(const ::aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage& in_message) = 0;
private:
  static std::shared_ptr<IGnssNavigationMessageCallback> default_impl;
};
class IGnssNavigationMessageCallbackDefault : public IGnssNavigationMessageCallback {
public:
  ::ndk::ScopedAStatus gnssNavigationMessageCb(const ::aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage& in_message) override;
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
[[nodiscard]] static inline std::string toString(IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType val) {
  switch(val) {
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::UNKNOWN:
    return "UNKNOWN";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GPS_L1CA:
    return "GPS_L1CA";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GPS_L2CNAV:
    return "GPS_L2CNAV";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GPS_L5CNAV:
    return "GPS_L5CNAV";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::SBS:
    return "SBS";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GPS_CNAV2:
    return "GPS_CNAV2";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GLO_L1CA:
    return "GLO_L1CA";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::QZS_L1CA:
    return "QZS_L1CA";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::BDS_D1:
    return "BDS_D1";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::BDS_D2:
    return "BDS_D2";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::BDS_CNAV1:
    return "BDS_CNAV1";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::BDS_CNAV2:
    return "BDS_CNAV2";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GAL_I:
    return "GAL_I";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GAL_F:
    return "GAL_F";
  case IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::IRN_L5CA:
    return "IRN_L5CA";
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
constexpr inline std::array<aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType, 15> enum_values<aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType> = {
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::UNKNOWN,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GPS_L1CA,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GPS_L2CNAV,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GPS_L5CNAV,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::SBS,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GPS_CNAV2,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GLO_L1CA,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::QZS_L1CA,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::BDS_D1,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::BDS_D2,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::BDS_CNAV1,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::BDS_CNAV2,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GAL_I,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::GAL_F,
  aidl::android::hardware::gnss::IGnssNavigationMessageCallback::GnssNavigationMessage::GnssNavigationMessageType::IRN_L5CA,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
