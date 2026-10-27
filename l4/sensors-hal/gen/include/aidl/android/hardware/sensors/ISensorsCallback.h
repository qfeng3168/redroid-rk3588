/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -Iaidl-src -ogen/src -hgen/include aidl-src/android/hardware/sensors/AdditionalInfo.aidl aidl-src/android/hardware/sensors/DynamicSensorInfo.aidl aidl-src/android/hardware/sensors/Event.aidl aidl-src/android/hardware/sensors/ISensors.aidl aidl-src/android/hardware/sensors/ISensorsCallback.aidl aidl-src/android/hardware/sensors/SensorInfo.aidl aidl-src/android/hardware/sensors/SensorStatus.aidl aidl-src/android/hardware/sensors/SensorType.aidl aidl-src/android/hardware/common/fmq/GrantorDescriptor.aidl aidl-src/android/hardware/common/fmq/MQDescriptor.aidl aidl-src/android/hardware/common/fmq/SynchronizedReadWrite.aidl aidl-src/android/hardware/common/fmq/UnsynchronizedWrite.aidl aidl-src/android/hardware/common/Ashmem.aidl aidl-src/android/hardware/common/NativeHandle.aidl
 */
#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <android/binder_interface_utils.h>
#include <aidl/android/hardware/sensors/SensorInfo.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::sensors {
class SensorInfo;
}  // namespace aidl::android::hardware::sensors
namespace aidl {
namespace android {
namespace hardware {
namespace sensors {
class ISensorsCallbackDelegator;

class ISensorsCallback : public ::ndk::ICInterface {
public:
  typedef ISensorsCallbackDelegator DefaultDelegator;
  static const char* descriptor;
  ISensorsCallback();
  virtual ~ISensorsCallback();

  static constexpr uint32_t TRANSACTION_onDynamicSensorsConnected = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onDynamicSensorsDisconnected = FIRST_CALL_TRANSACTION + 1;

  static std::shared_ptr<ISensorsCallback> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<ISensorsCallback>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<ISensorsCallback>* instance);
  static bool setDefaultImpl(const std::shared_ptr<ISensorsCallback>& impl);
  static const std::shared_ptr<ISensorsCallback>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus onDynamicSensorsConnected(const std::vector<::aidl::android::hardware::sensors::SensorInfo>& in_sensorInfos) = 0;
  virtual ::ndk::ScopedAStatus onDynamicSensorsDisconnected(const std::vector<int32_t>& in_sensorHandles) = 0;
private:
  static std::shared_ptr<ISensorsCallback> default_impl;
};
class ISensorsCallbackDefault : public ISensorsCallback {
public:
  ::ndk::ScopedAStatus onDynamicSensorsConnected(const std::vector<::aidl::android::hardware::sensors::SensorInfo>& in_sensorInfos) override;
  ::ndk::ScopedAStatus onDynamicSensorsDisconnected(const std::vector<int32_t>& in_sensorHandles) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace sensors
}  // namespace hardware
}  // namespace android
}  // namespace aidl
