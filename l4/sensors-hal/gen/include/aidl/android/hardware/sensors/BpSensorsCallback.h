/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -Iaidl-src -ogen/src -hgen/include aidl-src/android/hardware/sensors/AdditionalInfo.aidl aidl-src/android/hardware/sensors/DynamicSensorInfo.aidl aidl-src/android/hardware/sensors/Event.aidl aidl-src/android/hardware/sensors/ISensors.aidl aidl-src/android/hardware/sensors/ISensorsCallback.aidl aidl-src/android/hardware/sensors/SensorInfo.aidl aidl-src/android/hardware/sensors/SensorStatus.aidl aidl-src/android/hardware/sensors/SensorType.aidl aidl-src/android/hardware/common/fmq/GrantorDescriptor.aidl aidl-src/android/hardware/common/fmq/MQDescriptor.aidl aidl-src/android/hardware/common/fmq/SynchronizedReadWrite.aidl aidl-src/android/hardware/common/fmq/UnsynchronizedWrite.aidl aidl-src/android/hardware/common/Ashmem.aidl aidl-src/android/hardware/common/NativeHandle.aidl
 */
#pragma once

#include "aidl/android/hardware/sensors/ISensorsCallback.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace android {
namespace hardware {
namespace sensors {
class BpSensorsCallback : public ::ndk::BpCInterface<ISensorsCallback> {
public:
  explicit BpSensorsCallback(const ::ndk::SpAIBinder& binder);
  virtual ~BpSensorsCallback();

  ::ndk::ScopedAStatus onDynamicSensorsConnected(const std::vector<::aidl::android::hardware::sensors::SensorInfo>& in_sensorInfos) override;
  ::ndk::ScopedAStatus onDynamicSensorsDisconnected(const std::vector<int32_t>& in_sensorHandles) override;
};
}  // namespace sensors
}  // namespace hardware
}  // namespace android
}  // namespace aidl
