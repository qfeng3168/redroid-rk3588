// L4-M3: virtual GNSS HAL for the redroid guest (AIDL IGnss V2).
//
// A binderized service implementing android.hardware.gnss.IGnss/default,
// mirroring the L4 sensors service pattern. It synthesizes a plausible
// fix (static position or a slow drift around it), a fixed constellation
// of GPS + BeiDou satellites for SV status, and GGA/RMC NMEA sentences.
//
// Persona and behavior are driven by sysprops (read live each fix):
//   persist.l4.gnss.lat    center latitude   (default 31.230416)
//   persist.l4.gnss.lon    center longitude  (default 121.473701)
//   persist.l4.gnss.alt    altitude meters   (default 8)
//   persist.l4.gnss.acc    horizontal accuracy meters (default 3)
//   persist.l4.gnss.mode   static | drift    (default drift)
// injectLocation()/injectBestLocation() move the center to the injected
// position, which is the control path for the management layer later.

#include <aidl/android/hardware/gnss/BnAGnss.h>
#include <aidl/android/hardware/gnss/BnAGnssRil.h>
#include <aidl/android/hardware/gnss/BnGnss.h>
#include <aidl/android/hardware/gnss/BnGnssAntennaInfo.h>
#include <aidl/android/hardware/gnss/BnGnssConfiguration.h>
#include <aidl/android/hardware/gnss/BnGnssDebug.h>
#include <aidl/android/hardware/gnss/BnGnssMeasurementInterface.h>
#include <aidl/android/hardware/gnss/BnGnssPowerIndication.h>
#include <aidl/android/hardware/gnss/BnGnssBatching.h>
#include <aidl/android/hardware/gnss/BnGnssGeofence.h>
#include <aidl/android/hardware/gnss/BnGnssNavigationMessageInterface.h>
#include <aidl/android/hardware/gnss/BnGnssPsds.h>
#include <aidl/android/hardware/gnss/measurement_corrections/BnMeasurementCorrectionsInterface.h>
#include <aidl/android/hardware/gnss/visibility_control/BnGnssVisibilityControl.h>

#include <android-base/logging.h>
#include <android/binder_auto_utils.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include <chrono>
#include <cmath>
#include <condition_variable>
#include <mutex>
#include <thread>

extern "C" int __system_property_get(const char* name, char* value);

namespace agnss = aidl::android::hardware::gnss;
using agnss::GnssConstellationType;
using agnss::GnssLocation;
using agnss::IGnssCallback;
using ndk::ScopedAStatus;

namespace {

double prop_double(const char* name, double def) {
    char buf[64] = "";
    if (__system_property_get(name, buf) > 0 && buf[0]) {
        char* end = nullptr;
        double v = strtod(buf, &end);
        if (end != buf) return v;
    }
    return def;
}

std::string prop_string(const char* name, const char* def) {
    char buf[64] = "";
    if (__system_property_get(name, buf) > 0 && buf[0]) return buf;
    return def;
}

int64_t wall_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
}
int64_t elapsed_ns() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
                   std::chrono::steady_clock::now().time_since_epoch())
            .count();
}

// ------------------------- no-op extension stubs ---------------------------

class GnssConfigurationImpl : public agnss::BnGnssConfiguration {
    ScopedAStatus setSuplVersion(int32_t) override { return ScopedAStatus::ok(); }
    ScopedAStatus setSuplMode(int32_t) override { return ScopedAStatus::ok(); }
    ScopedAStatus setLppProfile(int32_t) override { return ScopedAStatus::ok(); }
    ScopedAStatus setGlonassPositioningProtocol(int32_t) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus setEmergencySuplPdn(bool) override { return ScopedAStatus::ok(); }
    ScopedAStatus setEsExtensionSec(int32_t) override { return ScopedAStatus::ok(); }
    ScopedAStatus setBlocklist(const std::vector<agnss::BlocklistedSource>&) override {
        return ScopedAStatus::ok();
    }
};

class AGnssImpl : public agnss::BnAGnss {
    ScopedAStatus setCallback(const std::shared_ptr<agnss::IAGnssCallback>&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus dataConnClosed() override { return ScopedAStatus::ok(); }
    ScopedAStatus dataConnFailed() override { return ScopedAStatus::ok(); }
    ScopedAStatus setServer(agnss::IAGnssCallback::AGnssType, const std::string&,
                            int32_t) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus dataConnOpen(int64_t, const std::string&,
                               agnss::IAGnss::ApnIpType) override {
        return ScopedAStatus::ok();
    }
};

class AGnssRilImpl : public agnss::BnAGnssRil {
    ScopedAStatus setCallback(
            const std::shared_ptr<agnss::IAGnssRilCallback>&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus setRefLocation(const agnss::IAGnssRil::AGnssRefLocation&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus setSetId(agnss::IAGnssRil::SetIdType, const std::string&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus updateNetworkState(
            const agnss::IAGnssRil::NetworkAttributes&) override {
        return ScopedAStatus::ok();
    }
};

class GnssDebugImpl : public agnss::BnGnssDebug {
    ScopedAStatus getDebugData(agnss::IGnssDebug::DebugData* out) override {
        *out = agnss::IGnssDebug::DebugData();
        return ScopedAStatus::ok();
    }
};

class GnssMeasurementImpl : public agnss::BnGnssMeasurementInterface {
    ScopedAStatus setCallback(const std::shared_ptr<agnss::IGnssMeasurementCallback>&,
                              bool, bool) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus close() override { return ScopedAStatus::ok(); }
    ScopedAStatus setCallbackWithOptions(
            const std::shared_ptr<agnss::IGnssMeasurementCallback>&,
            const agnss::IGnssMeasurementInterface::Options&) override {
        return ScopedAStatus::ok();
    }
};

class GnssPowerIndicationImpl : public agnss::BnGnssPowerIndication {
    std::shared_ptr<agnss::IGnssPowerIndicationCallback> cb_;
    ScopedAStatus setCallback(
            const std::shared_ptr<agnss::IGnssPowerIndicationCallback>& cb) override {
        cb_ = cb;
        return ScopedAStatus::ok();
    }
    ScopedAStatus requestGnssPowerStats() override {
        if (cb_) {
            agnss::GnssPowerStats stats;
            stats.elapsedRealtime.flags = agnss::ElapsedRealtime::HAS_TIMESTAMP_NS | agnss::ElapsedRealtime::HAS_TIME_UNCERTAINTY_NS;
            stats.elapsedRealtime.timestampNs = elapsed_ns();
            stats.elapsedRealtime.timeUncertaintyNs = 1000000;
            cb_->gnssPowerStatsCb(stats);
        }
        return ScopedAStatus::ok();
    }
};

class GnssAntennaInfoImpl : public agnss::BnGnssAntennaInfo {
    ScopedAStatus setCallback(
            const std::shared_ptr<agnss::IGnssAntennaInfoCallback>&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus close() override { return ScopedAStatus::ok(); }
};

class GnssVisibilityControlImpl
        : public agnss::visibility_control::BnGnssVisibilityControl {
    ScopedAStatus enableNfwLocationAccess(const std::vector<std::string>&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus setCallback(const std::shared_ptr<
                              agnss::visibility_control::IGnssVisibilityControlCallback>&)
            override {
        return ScopedAStatus::ok();
    }
};

class GnssPsdsImpl : public agnss::BnGnssPsds {
    ScopedAStatus setCallback(
            const std::shared_ptr<agnss::IGnssPsdsCallback>&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus injectPsdsData(agnss::PsdsType,
                                 const std::vector<uint8_t>&) override {
        return ScopedAStatus::ok();
    }
};

class GnssBatchingImpl : public agnss::BnGnssBatching {
    ScopedAStatus init(
            const std::shared_ptr<agnss::IGnssBatchingCallback>&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus getBatchSize(int32_t* out) override {
        *out = 0;
        return ScopedAStatus::ok();
    }
    ScopedAStatus start(const agnss::IGnssBatching::Options&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus flush() override { return ScopedAStatus::ok(); }
    ScopedAStatus stop() override { return ScopedAStatus::ok(); }
    ScopedAStatus cleanup() override { return ScopedAStatus::ok(); }
};

class GnssGeofenceImpl : public agnss::BnGnssGeofence {
    ScopedAStatus setCallback(
            const std::shared_ptr<agnss::IGnssGeofenceCallback>&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus addGeofence(int32_t, double, double, double, int32_t, int32_t,
                              int32_t, int32_t) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus pauseGeofence(int32_t) override { return ScopedAStatus::ok(); }
    ScopedAStatus resumeGeofence(int32_t, int32_t) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus removeGeofence(int32_t) override { return ScopedAStatus::ok(); }
};

class GnssNavigationMessageImpl : public agnss::BnGnssNavigationMessageInterface {
    ScopedAStatus setCallback(
            const std::shared_ptr<agnss::IGnssNavigationMessageCallback>&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus close() override { return ScopedAStatus::ok(); }
};

class MeasurementCorrectionsImpl
        : public agnss::measurement_corrections::BnMeasurementCorrectionsInterface {
    ScopedAStatus setCorrections(
            const agnss::measurement_corrections::MeasurementCorrections&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus setCallback(const std::shared_ptr<
                              agnss::measurement_corrections::IMeasurementCorrectionsCallback>&)
            override {
        return ScopedAStatus::ok();
    }
};

// ------------------------------- engine ------------------------------------

struct SatDef {
    int svid;
    GnssConstellationType constellation;
    float elev, azim, cn0;
    int64_t freqHz;
    bool used;
};

const SatDef kSats[] = {
        {5, GnssConstellationType::GPS, 62, 40, 44, 1575420000L, true},
        {7, GnssConstellationType::GPS, 35, 95, 38, 1575420000L, true},
        {9, GnssConstellationType::GPS, 18, 150, 33, 1575420000L, true},
        {13, GnssConstellationType::GPS, 71, 205, 45, 1575420000L, true},
        {15, GnssConstellationType::GPS, 27, 260, 35, 1575420000L, true},
        {20, GnssConstellationType::GPS, 48, 310, 41, 1575420000L, true},
        {24, GnssConstellationType::GPS, 12, 75, 29, 1575420000L, false},
        {29, GnssConstellationType::GPS, 55, 175, 40, 1575420000L, true},
        {206, GnssConstellationType::BEIDOU, 44, 120, 42, 1561098000L, true},
        {211, GnssConstellationType::BEIDOU, 23, 190, 34, 1561098000L, true},
        {216, GnssConstellationType::BEIDOU, 66, 285, 43, 1561098000L, true},
        {222, GnssConstellationType::BEIDOU, 31, 25, 36, 1561098000L, false},
        {228, GnssConstellationType::BEIDOU, 15, 225, 30, 1561098000L, false},
        {233, GnssConstellationType::BEIDOU, 52, 340, 39, 1561098000L, true},
};

std::string nmea_sentence(const std::string& body) {
    unsigned char cs = 0;
    for (char c : body) cs ^= (unsigned char)c;
    char buf[256];
    snprintf(buf, sizeof buf, "$%s*%02X", body.c_str(), cs);
    return buf;
}

}  // namespace

class GnssImpl : public agnss::BnGnss {
  public:
    GnssImpl() {
        config_ = ndk::SharedRefBase::make<GnssConfigurationImpl>();
        agnss_ = ndk::SharedRefBase::make<AGnssImpl>();
        agnssRil_ = ndk::SharedRefBase::make<AGnssRilImpl>();
        debug_ = ndk::SharedRefBase::make<GnssDebugImpl>();
        measurement_ = ndk::SharedRefBase::make<GnssMeasurementImpl>();
        power_ = ndk::SharedRefBase::make<GnssPowerIndicationImpl>();
        antenna_ = ndk::SharedRefBase::make<GnssAntennaInfoImpl>();
        visibility_ = ndk::SharedRefBase::make<GnssVisibilityControlImpl>();
        psds_ = ndk::SharedRefBase::make<GnssPsdsImpl>();
        batching_ = ndk::SharedRefBase::make<GnssBatchingImpl>();
        geofence_ = ndk::SharedRefBase::make<GnssGeofenceImpl>();
        navMessage_ = ndk::SharedRefBase::make<GnssNavigationMessageImpl>();
        measurementCorrections_ = ndk::SharedRefBase::make<MeasurementCorrectionsImpl>();
    }
    ~GnssImpl() override {
        {
            std::lock_guard<std::mutex> lk(m_);
            stopThread_ = true;
        }
        cv_.notify_all();
        if (worker_.joinable()) worker_.join();
    }

    // ---------------- IGnss ----------------
    ScopedAStatus setCallback(const std::shared_ptr<IGnssCallback>& cb) override {
        std::lock_guard<std::mutex> lk(m_);
        cb_ = cb;
        if (cb_) {
            agnss::IGnssCallback::GnssSystemInfo info;
            info.yearOfHw = 2026;
            info.name = "redroid-l4";
            cb_->gnssSetSystemInfoCb(info);
            cb_->gnssSetCapabilitiesCb(kCaps);
            cb_->gnssStatusCb(IGnssCallback::GnssStatusValue::ENGINE_ON);
        }
        return ScopedAStatus::ok();
    }
    ScopedAStatus close() override {
        std::shared_ptr<IGnssCallback> cb;
        {
            std::lock_guard<std::mutex> lk(m_);
            locating_ = svOn_ = nmeaOn_ = false;
            cb = cb_;
            cb_.reset();
        }
        cv_.notify_all();
        if (cb) cb->gnssStatusCb(IGnssCallback::GnssStatusValue::ENGINE_OFF);
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionPsds(
            std::shared_ptr<agnss::IGnssPsds>* out) override {
        // The framework JNI dereferences the Psds extension without a null
        // check (GnssPsdsAidl::setCallback segfaults system_server), so this
        // must never be null in this guest build. Same for the other
        // @nullable extensions below.
        *out = psds_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionGnssConfiguration(
            std::shared_ptr<agnss::IGnssConfiguration>* out) override {
        *out = config_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionGnssMeasurement(
            std::shared_ptr<agnss::IGnssMeasurementInterface>* out) override {
        *out = measurement_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionGnssPowerIndication(
            std::shared_ptr<agnss::IGnssPowerIndication>* out) override {
        *out = power_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionGnssBatching(
            std::shared_ptr<agnss::IGnssBatching>* out) override {
        *out = batching_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionGnssGeofence(
            std::shared_ptr<agnss::IGnssGeofence>* out) override {
        *out = geofence_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionGnssNavigationMessage(
            std::shared_ptr<agnss::IGnssNavigationMessageInterface>* out) override {
        *out = navMessage_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionAGnss(std::shared_ptr<agnss::IAGnss>* out) override {
        *out = agnss_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionAGnssRil(
            std::shared_ptr<agnss::IAGnssRil>* out) override {
        *out = agnssRil_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionGnssDebug(
            std::shared_ptr<agnss::IGnssDebug>* out) override {
        *out = debug_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionGnssVisibilityControl(
            std::shared_ptr<agnss::visibility_control::IGnssVisibilityControl>* out)
            override {
        *out = visibility_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus start() override {
        std::shared_ptr<IGnssCallback> cb;
        {
            std::lock_guard<std::mutex> lk(m_);
            locating_ = true;
            cb = cb_;
            ensureWorkerLocked();
        }
        cv_.notify_all();
        if (cb) cb->gnssStatusCb(IGnssCallback::GnssStatusValue::SESSION_BEGIN);
        return ScopedAStatus::ok();
    }
    ScopedAStatus stop() override {
        std::shared_ptr<IGnssCallback> cb;
        {
            std::lock_guard<std::mutex> lk(m_);
            locating_ = false;
            cb = cb_;
        }
        cv_.notify_all();
        if (cb) cb->gnssStatusCb(IGnssCallback::GnssStatusValue::SESSION_END);
        return ScopedAStatus::ok();
    }
    ScopedAStatus injectTime(int64_t, int64_t, int32_t) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus injectLocation(const GnssLocation& loc) override {
        adopt(loc);
        return ScopedAStatus::ok();
    }
    ScopedAStatus injectBestLocation(const GnssLocation& loc) override {
        adopt(loc);
        return ScopedAStatus::ok();
    }
    ScopedAStatus deleteAidingData(agnss::IGnss::GnssAidingData) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus setPositionMode(const agnss::IGnss::PositionModeOptions& o) override {
        {
            std::lock_guard<std::mutex> lk(m_);
            intervalMs_ = o.minIntervalMs > 0 ? o.minIntervalMs : 1000;
            singleShot_ =
                    o.recurrence == agnss::IGnss::GnssPositionRecurrence::RECURRENCE_SINGLE;
        }
        cv_.notify_all();
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionGnssAntennaInfo(
            std::shared_ptr<agnss::IGnssAntennaInfo>* out) override {
        *out = antenna_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus getExtensionMeasurementCorrections(
            std::shared_ptr<agnss::measurement_corrections::IMeasurementCorrectionsInterface>*
                    out) override {
        *out = measurementCorrections_;
        return ScopedAStatus::ok();
    }
    ScopedAStatus startSvStatus() override {
        {
            std::lock_guard<std::mutex> lk(m_);
            svOn_ = true;
            ensureWorkerLocked();
        }
        cv_.notify_all();
        return ScopedAStatus::ok();
    }
    ScopedAStatus stopSvStatus() override {
        {
            std::lock_guard<std::mutex> lk(m_);
            svOn_ = false;
        }
        cv_.notify_all();
        return ScopedAStatus::ok();
    }
    ScopedAStatus startNmea() override {
        {
            std::lock_guard<std::mutex> lk(m_);
            nmeaOn_ = true;
            ensureWorkerLocked();
        }
        cv_.notify_all();
        return ScopedAStatus::ok();
    }
    ScopedAStatus stopNmea() override {
        {
            std::lock_guard<std::mutex> lk(m_);
            nmeaOn_ = false;
        }
        cv_.notify_all();
        return ScopedAStatus::ok();
    }

  private:
    static constexpr int kCaps = IGnssCallback::CAPABILITY_SCHEDULING |
                                 IGnssCallback::CAPABILITY_SINGLE_SHOT |
                                 IGnssCallback::CAPABILITY_ON_DEMAND_TIME;

    void adopt(const GnssLocation& loc) {
        std::lock_guard<std::mutex> lk(m_);
        if (loc.gnssLocationFlags & GnssLocation::HAS_LAT_LONG) {
            centerLat_ = loc.latitudeDegrees;
            centerLon_ = loc.longitudeDegrees;
            centerSet_ = true;
        }
        if (loc.gnssLocationFlags & GnssLocation::HAS_ALTITUDE)
            centerAlt_ = loc.altitudeMeters;
    }

    void ensureWorkerLocked() {
        if (!worker_.joinable()) worker_ = std::thread(&GnssImpl::run, this);
    }

    GnssLocation makeFix(double tSec) {
        double lat = centerSet_ ? centerLat_ : prop_double("persist.l4.gnss.lat", 31.230416);
        double lon = centerSet_ ? centerLon_ : prop_double("persist.l4.gnss.lon", 121.473701);
        double alt = centerSet_ ? centerAlt_ : prop_double("persist.l4.gnss.alt", 8.0);
        double acc = prop_double("persist.l4.gnss.acc", 3.0);
        bool drift = prop_string("persist.l4.gnss.mode", "drift") != "static";
        double speed = 0, bearing = 0;
        if (drift) {
            // Slow wander within ~20 m of the center (degree offsets).
            double dLat = (18.0 * std::sin(tSec / 47.0) + 7.0 * std::sin(tSec / 13.0 + 1.7)) /
                          111320.0;
            double dLon = (16.0 * std::cos(tSec / 53.0) + 6.0 * std::sin(tSec / 11.0 + 0.6)) /
                          (111320.0 * std::cos(lat * M_PI / 180.0));
            lat += dLat;
            lon += dLon;
            speed = 0.9;
            bearing = std::fmod(tSec * 3.0, 360.0);
            if (bearing < 0) bearing += 360.0;
        }
        GnssLocation loc;
        loc.gnssLocationFlags = GnssLocation::HAS_LAT_LONG | GnssLocation::HAS_ALTITUDE |
                                GnssLocation::HAS_SPEED | GnssLocation::HAS_BEARING |
                                GnssLocation::HAS_HORIZONTAL_ACCURACY |
                                GnssLocation::HAS_VERTICAL_ACCURACY |
                                GnssLocation::HAS_SPEED_ACCURACY |
                                GnssLocation::HAS_BEARING_ACCURACY;
        loc.latitudeDegrees = lat;
        loc.longitudeDegrees = lon;
        loc.altitudeMeters = alt;
        loc.speedMetersPerSec = speed;
        loc.bearingDegrees = bearing;
        loc.horizontalAccuracyMeters = acc;
        loc.verticalAccuracyMeters = 5.0;
        loc.speedAccuracyMetersPerSecond = 0.5;
        loc.bearingAccuracyDegrees = 5.0;
        loc.timestampMillis = wall_ms();
        loc.elapsedRealtime.flags = agnss::ElapsedRealtime::HAS_TIMESTAMP_NS | agnss::ElapsedRealtime::HAS_TIME_UNCERTAINTY_NS;
        loc.elapsedRealtime.timestampNs = elapsed_ns();
        loc.elapsedRealtime.timeUncertaintyNs = 1000000;
        return loc;
    }

    std::vector<IGnssCallback::GnssSvInfo> makeSv(double tSec) {
        std::vector<IGnssCallback::GnssSvInfo> out;
        int i = 0;
        for (const SatDef& s : kSats) {
            IGnssCallback::GnssSvInfo v;
            v.svid = s.svid;
            v.constellation = s.constellation;
            float wobble = (float)(1.5 * std::sin(tSec / 9.0 + i * 1.3));
            v.cN0Dbhz = s.cn0 + wobble;
            v.basebandCN0DbHz = v.cN0Dbhz - 2.0f;
            v.elevationDegrees = s.elev;
            v.azimuthDegrees = s.azim;
            v.carrierFrequencyHz = s.freqHz;
            // GnssSvFlags is a scoped enum: combine as plain ints.
            v.svFlag = (int32_t)IGnssCallback::GnssSvFlags::HAS_EPHEMERIS_DATA |
                       (int32_t)IGnssCallback::GnssSvFlags::HAS_ALMANAC_DATA |
                       (int32_t)IGnssCallback::GnssSvFlags::HAS_CARRIER_FREQUENCY |
                       (s.used ? (int32_t)IGnssCallback::GnssSvFlags::USED_IN_FIX : 0);
            out.push_back(v);
            i++;
        }
        return out;
    }

    void sendNmea(const std::shared_ptr<IGnssCallback>& cb, const GnssLocation& loc) {
        // UTC time from the wall clock.
        int64_t ms = loc.timestampMillis;
        time_t secs = ms / 1000;
        struct tm tmv;
        gmtime_r(&secs, &tmv);
        double alat = std::fabs(loc.latitudeDegrees);
        double alon = std::fabs(loc.longitudeDegrees);
        int latD = (int)alat, lonD = (int)alon;
        double latM = (alat - latD) * 60.0, lonM = (alon - lonD) * 60.0;
        char body[256];
        snprintf(body, sizeof body,
                 "GPGGA,%02d%02d%05.2f,%02d%07.4f,%c,%03d%07.4f,%c,1,11,0.9,%.1f,M,0.0,M,,",
                 tmv.tm_hour, tmv.tm_min, tmv.tm_sec + (ms % 1000) / 1000.0, latD, latM,
                 loc.latitudeDegrees >= 0 ? 'N' : 'S', lonD, lonM,
                 loc.longitudeDegrees >= 0 ? 'E' : 'W', loc.altitudeMeters);
        cb->gnssNmeaCb(ms, nmea_sentence(body));
        double knots = loc.speedMetersPerSec * 1.943844;
        snprintf(body, sizeof body,
                 "GPRMC,%02d%02d%05.2f,A,%02d%07.4f,%c,%03d%07.4f,%c,%.2f,%.1f,%02d%02d%02d,,,A",
                 tmv.tm_hour, tmv.tm_min, tmv.tm_sec + (ms % 1000) / 1000.0, latD, latM,
                 loc.latitudeDegrees >= 0 ? 'N' : 'S', lonD, lonM,
                 loc.longitudeDegrees >= 0 ? 'E' : 'W', knots, loc.bearingDegrees,
                 tmv.tm_mday, tmv.tm_mon + 1, (tmv.tm_year + 1900) % 100);
        cb->gnssNmeaCb(ms, nmea_sentence(body));
    }

    void run() {
        std::unique_lock<std::mutex> lk(m_);
        while (!stopThread_) {
            bool active = (locating_ || svOn_ || nmeaOn_) && cb_ != nullptr;
            if (!active) {
                cv_.wait(lk, [&] { return stopThread_ || ((locating_ || svOn_ || nmeaOn_) && cb_); });
                continue;
            }
            int interval = intervalMs_ < 200 ? 200 : intervalMs_;
            auto cb = cb_;
            bool doLoc = locating_, doSv = svOn_, doNmea = nmeaOn_;
            bool single = singleShot_;
            lk.unlock();
            double tSec = elapsed_ns() / 1e9;
            GnssLocation fix = makeFix(tSec);
            if (doLoc) cb->gnssLocationCb(fix);
            if (doSv) cb->gnssSvStatusCb(makeSv(tSec));
            if (doNmea) sendNmea(cb, fix);
            lk.lock();
            if (single && doLoc) {
                locating_ = false;
                lk.unlock();
                cb->gnssStatusCb(IGnssCallback::GnssStatusValue::SESSION_END);
                lk.lock();
            }
            cv_.wait_for(lk, std::chrono::milliseconds(interval),
                         [&] { return stopThread_; });
        }
    }

    std::mutex m_;
    std::condition_variable cv_;
    std::thread worker_;
    bool stopThread_ = false;
    std::shared_ptr<IGnssCallback> cb_;
    bool locating_ = false, svOn_ = false, nmeaOn_ = false;
    bool singleShot_ = false;
    int intervalMs_ = 1000;
    bool centerSet_ = false;
    double centerLat_ = 0, centerLon_ = 0, centerAlt_ = 0;

    std::shared_ptr<agnss::IGnssConfiguration> config_;
    std::shared_ptr<agnss::IAGnss> agnss_;
    std::shared_ptr<agnss::IAGnssRil> agnssRil_;
    std::shared_ptr<agnss::IGnssDebug> debug_;
    std::shared_ptr<agnss::IGnssMeasurementInterface> measurement_;
    std::shared_ptr<agnss::IGnssPowerIndication> power_;
    std::shared_ptr<agnss::IGnssAntennaInfo> antenna_;
    std::shared_ptr<agnss::visibility_control::IGnssVisibilityControl> visibility_;
    std::shared_ptr<agnss::IGnssPsds> psds_;
    std::shared_ptr<agnss::IGnssBatching> batching_;
    std::shared_ptr<agnss::IGnssGeofence> geofence_;
    std::shared_ptr<agnss::IGnssNavigationMessageInterface> navMessage_;
    std::shared_ptr<agnss::measurement_corrections::IMeasurementCorrectionsInterface>
            measurementCorrections_;
};

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(4);
    ABinderProcess_startThreadPool();

    auto impl = ndk::SharedRefBase::make<GnssImpl>();
    const std::string instance = std::string(GnssImpl::descriptor) + "/default";
    binder_status_t status =
            AServiceManager_addService(impl->asBinder().get(), instance.c_str());
    CHECK_EQ(status, STATUS_OK) << "failed to register " << instance;

    ABinderProcess_joinThreadPool();
    return 0;
}
