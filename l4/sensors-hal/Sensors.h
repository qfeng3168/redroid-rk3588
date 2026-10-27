#pragma once

// L4-M1: virtual Sensors HAL for redroid-rk3588 (binderized AIDL service).
// Implements android.hardware.sensors.ISensors/default with synthetic
// accelerometer + gyroscope data. Control channel for the management layer:
//   persist.l4.sensors.mode   : "sine" (default) | "static"
//   persist.l4.sensors.accel  : "x,y,z" used in static mode
//   persist.l4.sensors.gyro   : "x,y,z" used in static mode

#include <aidl/android/hardware/sensors/BnSensors.h>
#include <fmq/AidlMessageQueue.h>
#include <fmq/EventFlag.h>

#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <thread>

namespace aidl::android::hardware::sensors {

class Sensors : public BnSensors {
  public:
    Sensors();
    ~Sensors() override;

    ::ndk::ScopedAStatus activate(int32_t sensorHandle, bool enabled) override;
    ::ndk::ScopedAStatus batch(int32_t sensorHandle, int64_t samplingPeriodNs,
                               int64_t maxReportLatencyNs) override;
    ::ndk::ScopedAStatus configDirectReport(int32_t sensorHandle, int32_t channelHandle,
                                            RateLevel rate, int32_t* _aidl_return) override;
    ::ndk::ScopedAStatus flush(int32_t sensorHandle) override;
    ::ndk::ScopedAStatus getSensorsList(std::vector<SensorInfo>* _aidl_return) override;
    ::ndk::ScopedAStatus initialize(
            const ::aidl::android::hardware::common::fmq::MQDescriptor<
                    Event, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>&
                    eventQueueDescriptor,
            const ::aidl::android::hardware::common::fmq::MQDescriptor<
                    int32_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>&
                    wakeLockDescriptor,
            const std::shared_ptr<ISensorsCallback>& sensorsCallback) override;
    ::ndk::ScopedAStatus injectSensorData(const Event& event) override;
    ::ndk::ScopedAStatus registerDirectChannel(const SharedMemInfo& mem,
                                               int32_t* _aidl_return) override;
    ::ndk::ScopedAStatus setOperationMode(OperationMode mode) override;
    ::ndk::ScopedAStatus unregisterDirectChannel(int32_t channelHandle) override;

  private:
    using EventMQ = ::android::AidlMessageQueue<
            Event, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>;
    using WakeLockMQ = ::android::AidlMessageQueue<
            int32_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>;

    struct SensorState {
        std::atomic<bool> enabled{false};
        std::atomic<int64_t> periodNs{200'000'000};
        std::thread worker;
        std::atomic<bool> workerRun{false};
    };

    std::unique_ptr<EventMQ> mEventQueue;
    std::unique_ptr<WakeLockMQ> mWakeLockQueue;
    ::android::hardware::EventFlag* mEventFlag = nullptr;
    std::shared_ptr<ISensorsCallback> mCallback;
    OperationMode mMode = OperationMode::NORMAL;

    std::map<int32_t, std::unique_ptr<SensorState>> mSensors;
    std::mutex mWriteMutex;

    void startWorkerLocked(int32_t handle);
    void stopWorker(int32_t handle);
    void workerLoop(int32_t handle);
    void postEvent(const Event& event);
    Event makeEvent(int32_t handle, double tSec);
    static int64_t nowNs();
    static std::array<float, 3> readVecProp(const char* key, std::array<float, 3> fallback);
};

}  // namespace aidl::android::hardware::sensors
