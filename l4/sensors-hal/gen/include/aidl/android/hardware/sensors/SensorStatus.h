/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/hatch/workspace/l4-tools/bt35/android-15/aidl --lang=ndk --stability vintf --structured -Iaidl-src -ogen/src -hgen/include aidl-src/android/hardware/sensors/AdditionalInfo.aidl aidl-src/android/hardware/sensors/DynamicSensorInfo.aidl aidl-src/android/hardware/sensors/Event.aidl aidl-src/android/hardware/sensors/ISensors.aidl aidl-src/android/hardware/sensors/ISensorsCallback.aidl aidl-src/android/hardware/sensors/SensorInfo.aidl aidl-src/android/hardware/sensors/SensorStatus.aidl aidl-src/android/hardware/sensors/SensorType.aidl aidl-src/android/hardware/common/fmq/GrantorDescriptor.aidl aidl-src/android/hardware/common/fmq/MQDescriptor.aidl aidl-src/android/hardware/common/fmq/SynchronizedReadWrite.aidl aidl-src/android/hardware/common/fmq/UnsynchronizedWrite.aidl aidl-src/android/hardware/common/Ashmem.aidl aidl-src/android/hardware/common/NativeHandle.aidl
 */
#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <android/binder_enums.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace hardware {
namespace sensors {
enum class SensorStatus : int8_t {
  NO_CONTACT = -1,
  UNRELIABLE = 0,
  ACCURACY_LOW = 1,
  ACCURACY_MEDIUM = 2,
  ACCURACY_HIGH = 3,
};

}  // namespace sensors
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace sensors {
[[nodiscard]] static inline std::string toString(SensorStatus val) {
  switch(val) {
  case SensorStatus::NO_CONTACT:
    return "NO_CONTACT";
  case SensorStatus::UNRELIABLE:
    return "UNRELIABLE";
  case SensorStatus::ACCURACY_LOW:
    return "ACCURACY_LOW";
  case SensorStatus::ACCURACY_MEDIUM:
    return "ACCURACY_MEDIUM";
  case SensorStatus::ACCURACY_HIGH:
    return "ACCURACY_HIGH";
  default:
    return std::to_string(static_cast<int8_t>(val));
  }
}
}  // namespace sensors
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace ndk {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<aidl::android::hardware::sensors::SensorStatus, 5> enum_values<aidl::android::hardware::sensors::SensorStatus> = {
  aidl::android::hardware::sensors::SensorStatus::NO_CONTACT,
  aidl::android::hardware::sensors::SensorStatus::UNRELIABLE,
  aidl::android::hardware::sensors::SensorStatus::ACCURACY_LOW,
  aidl::android::hardware::sensors::SensorStatus::ACCURACY_MEDIUM,
  aidl::android::hardware::sensors::SensorStatus::ACCURACY_HIGH,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
