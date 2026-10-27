// L4-M1 virtual Sensors HAL service entry point.
// Registers android.hardware.sensors.ISensors/default with servicemanager.

#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <log/log.h>

#include "Sensors.h"

using ::aidl::android::hardware::sensors::Sensors;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    std::shared_ptr<Sensors> sensors = ::ndk::SharedRefBase::make<Sensors>();
    const std::string instance = std::string(Sensors::descriptor) + "/default";
    binder_status_t status =
            AServiceManager_addService(sensors->asBinder().get(), instance.c_str());
    if (status != STATUS_OK) {
        ALOGE("Failed to register %s: %d", instance.c_str(), status);
        return 1;
    }
    ALOGI("Registered %s", instance.c_str());
    ABinderProcess_joinThreadPool();
    return 0;
}
