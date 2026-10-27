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
namespace common {
namespace fmq {
enum class SynchronizedReadWrite : int8_t {
  EMPTY = 0,
};

}  // namespace fmq
}  // namespace common
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace common {
namespace fmq {
[[nodiscard]] static inline std::string toString(SynchronizedReadWrite val) {
  switch(val) {
  case SynchronizedReadWrite::EMPTY:
    return "EMPTY";
  default:
    return std::to_string(static_cast<int8_t>(val));
  }
}
}  // namespace fmq
}  // namespace common
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace ndk {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<aidl::android::hardware::common::fmq::SynchronizedReadWrite, 1> enum_values<aidl::android::hardware::common::fmq::SynchronizedReadWrite> = {
  aidl::android::hardware::common::fmq::SynchronizedReadWrite::EMPTY,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace ndk
