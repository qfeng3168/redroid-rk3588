#include "Sensors.h"

#include <android-base/logging.h>
#include <cutils/properties.h>

#include <chrono>
#include <cmath>
#include <cstdlib>

namespace aidl::android::hardware::sensors {

using ::ndk::ScopedAStatus;

static constexpr int32_t kAccelHandle = 1;
static constexpr int32_t kGyroHandle = 2;
static constexpr float kGravity = 9.80665f;

Sensors::Sensors() {
    mSensors[kAccelHandle] = std::make_unique<SensorState>();
    mSensors[kGyroHandle] = std::make_unique<SensorState>();
}

Sensors::~Sensors() {
    for (auto& [handle, state] : mSensors) {
        state->workerRun = false;
        if (state->worker.joinable()) state->worker.join();
    }
    if (mEventFlag != nullptr) {
        ::android::hardware::EventFlag::deleteEventFlag(&mEventFlag);
    }
}

int64_t Sensors::nowNs() {
    struct timespec ts {};
    clock_gettime(CLOCK_BOOTTIME, &ts);
    return static_cast<int64_t>(ts.tv_sec) * 1'000'000'000LL + ts.tv_nsec;
}

std::array<float, 3> Sensors::readVecProp(const char* key, std::array<float, 3> fallback) {
    char buf[PROPERTY_VALUE_MAX] = {};
    if (property_get(key, buf, "") <= 0) return fallback;
    std::array<float, 3> out = fallback;
    if (sscanf(buf, "%f,%f,%f", &out[0], &out[1], &out[2]) != 3) return fallback;
    return out;
}

ScopedAStatus Sensors::getSensorsList(std::vector<SensorInfo>* _aidl_return) {
    SensorInfo accel;
    accel.sensorHandle = kAccelHandle;
    accel.name = "L4 Virtual Accelerometer";
    accel.vendor = "redroid-l4";
    accel.version = 1;
    accel.type = SensorType::ACCELEROMETER;
    accel.typeAsString = "android.sensor.accelerometer";
    accel.maxRange = 8.0f * kGravity;
    accel.resolution = 0.0012f;
    accel.power = 0.15f;
    accel.minDelayUs = 5000;
    accel.fifoReservedEventCount = 0;
    accel.fifoMaxEventCount = 0;
    accel.maxDelayUs = 200000;
    accel.flags = 0;

    SensorInfo gyro;
    gyro.sensorHandle = kGyroHandle;
    gyro.name = "L4 Virtual Gyroscope";
    gyro.vendor = "redroid-l4";
    gyro.version = 1;
    gyro.type = SensorType::GYROSCOPE;
    gyro.typeAsString = "android.sensor.gyroscope";
    gyro.maxRange = 34.9066f;
    gyro.resolution = 0.001f;
    gyro.power = 0.15f;
    gyro.minDelayUs = 5000;
    gyro.fifoReservedEventCount = 0;
    gyro.fifoMaxEventCount = 0;
    gyro.maxDelayUs = 200000;
    gyro.flags = 0;

    *_aidl_return = {accel, gyro};
    return ScopedAStatus::ok();
}

ScopedAStatus Sensors::initialize(
        const ::aidl::android::hardware::common::fmq::MQDescriptor<
                Event, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>&
                eventQueueDescriptor,
        const ::aidl::android::hardware::common::fmq::MQDescriptor<
                int32_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>&
                wakeLockDescriptor,
        const std::shared_ptr<ISensorsCallback>& sensorsCallback) {
    mEventQueue = std::make_unique<EventMQ>(eventQueueDescriptor, true);
    if (mEventQueue == nullptr || !mEventQueue->isValid()) {
        LOG(ERROR) << "Failed to create event FMQ";
        return ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
    }
    mWakeLockQueue = std::make_unique<WakeLockMQ>(wakeLockDescriptor, true);
    if (mWakeLockQueue == nullptr || !mWakeLockQueue->isValid()) {
        LOG(ERROR) << "Failed to create wakelock FMQ";
        return ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
    }
    if (::android::hardware::EventFlag::createEventFlag(mEventQueue->getEventFlagWord(),
                                                         &mEventFlag) != ::android::OK) {
        LOG(ERROR) << "Failed to create event flag";
        return ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
    }
    mCallback = sensorsCallback;
    LOG(INFO) << "L4 sensors HAL initialized (event queue depth "
              << mEventQueue->getQuantumCount() << ")";
    return ScopedAStatus::ok();
}

void Sensors::postEvent(const Event& event) {
    if (mEventQueue == nullptr) return;
    {
        std::lock_guard lock(mWriteMutex);
        if (!mEventQueue->write(&event, 1)) return;  // queue full: drop
    }
    if (mEventFlag != nullptr) {
        mEventFlag->wake(static_cast<uint32_t>(ISensors::WAKE_LOCK_QUEUE_FLAG_BITS_DATA_WRITTEN));
    }
}

Event Sensors::makeEvent(int32_t handle, double t) {
    char mode[PROPERTY_VALUE_MAX] = {};
    property_get("persist.l4.sensors.mode", mode, "sine");
    const bool isStatic = std::string(mode) == "static";

    Event event;
    event.timestamp = nowNs();
    event.sensorHandle = handle;

    Event::EventPayload::Vec3 v;
    v.status = SensorStatus::ACCURACY_HIGH;
    if (handle == kAccelHandle) {
        event.sensorType = SensorType::ACCELEROMETER;
        if (isStatic) {
            auto a = readVecProp("persist.l4.sensors.accel", {0.0f, 0.0f, kGravity});
            v.x = a[0];
            v.y = a[1];
            v.z = a[2];
        } else {
            // Slow sway: gravity vector tilts on two incommensurate periods.
            v.x = 3.1f * std::sin(t * 0.90);
            v.y = 3.1f * std::sin(t * 0.57 + 1.3);
            float rem = kGravity * kGravity - v.x * v.x - v.y * v.y;
            v.z = rem > 0 ? std::sqrt(rem) : 0.0f;
        }
    } else {
        event.sensorType = SensorType::GYROSCOPE;
        if (isStatic) {
            auto g = readVecProp("persist.l4.sensors.gyro", {0.0f, 0.0f, 0.0f});
            v.x = g[0];
            v.y = g[1];
            v.z = g[2];
        } else {
            v.x = 0.28f * std::sin(t * 1.70);
            v.y = 0.28f * std::sin(t * 1.31 + 2.0);
            v.z = 0.12f * std::sin(t * 0.53 + 0.7);
        }
    }
    // Small deterministic jitter so values don't look machine-frozen.
    const float jitter = 0.004f * std::sin(t * 37.0 + handle * 11.0);
    v.x += jitter;
    v.y += jitter * 0.6f;

    event.payload = Event::EventPayload::make<Event::EventPayload::Tag::vec3>(v);
    return event;
}

void Sensors::workerLoop(int32_t handle) {
    auto& state = mSensors[handle];
    const auto t0 = std::chrono::steady_clock::now();
    while (state->workerRun) {
        const int64_t periodNs = state->periodNs;
        auto tickStart = std::chrono::steady_clock::now();
        double t = std::chrono::duration<double>(tickStart - t0).count();
        postEvent(makeEvent(handle, t));
        auto elapsed = std::chrono::steady_clock::now() - tickStart;
        auto sleepFor = std::chrono::nanoseconds(periodNs) - elapsed;
        if (sleepFor.count() > 0) std::this_thread::sleep_for(sleepFor);
    }
}

void Sensors::startWorkerLocked(int32_t handle) {
    auto& state = mSensors[handle];
    if (state->workerRun) return;
    state->workerRun = true;
    state->worker = std::thread(&Sensors::workerLoop, this, handle);
}

void Sensors::stopWorker(int32_t handle) {
    auto& state = mSensors[handle];
    state->workerRun = false;
    if (state->worker.joinable()) state->worker.join();
}

ScopedAStatus Sensors::activate(int32_t sensorHandle, bool enabled) {
    auto it = mSensors.find(sensorHandle);
    if (it == mSensors.end()) return ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
    it->second->enabled = enabled;
    if (enabled) {
        startWorkerLocked(sensorHandle);
    } else {
        stopWorker(sensorHandle);
    }
    return ScopedAStatus::ok();
}

ScopedAStatus Sensors::batch(int32_t sensorHandle, int64_t samplingPeriodNs,
                             int64_t /* maxReportLatencyNs */) {
    auto it = mSensors.find(sensorHandle);
    if (it == mSensors.end()) return ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
    if (samplingPeriodNs < 5'000'000) samplingPeriodNs = 5'000'000;        // 200 Hz cap
    if (samplingPeriodNs > 1'000'000'000) samplingPeriodNs = 1'000'000'000;  // 1 Hz floor
    it->second->periodNs = samplingPeriodNs;
    return ScopedAStatus::ok();
}

ScopedAStatus Sensors::flush(int32_t sensorHandle) {
    if (mSensors.find(sensorHandle) == mSensors.end()) {
        return ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
    }
    Event event;
    event.timestamp = nowNs();
    event.sensorHandle = sensorHandle;
    event.sensorType = SensorType::META_DATA;
    Event::EventPayload::MetaData meta;
    meta.what = Event::EventPayload::MetaData::MetaDataEventType::META_DATA_FLUSH_COMPLETE;
    event.payload = Event::EventPayload::make<Event::EventPayload::Tag::meta>(meta);
    postEvent(event);
    return ScopedAStatus::ok();
}

ScopedAStatus Sensors::setOperationMode(OperationMode mode) {
    mMode = mode;
    return ScopedAStatus::ok();
}

ScopedAStatus Sensors::injectSensorData(const Event& event) {
    if (mMode != OperationMode::DATA_INJECTION) {
        return ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
    }
    Event copy = event;
    copy.timestamp = nowNs();
    postEvent(copy);
    return ScopedAStatus::ok();
}

ScopedAStatus Sensors::registerDirectChannel(const SharedMemInfo& /* mem */,
                                             int32_t* _aidl_return) {
    *_aidl_return = -1;
    return ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ScopedAStatus Sensors::unregisterDirectChannel(int32_t /* channelHandle */) {
    return ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ScopedAStatus Sensors::configDirectReport(int32_t /* sensorHandle */,
                                          int32_t /* channelHandle */, RateLevel /* rate */,
                                          int32_t* _aidl_return) {
    *_aidl_return = -1;
    return ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

}  // namespace aidl::android::hardware::sensors
