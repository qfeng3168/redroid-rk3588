// L4-M4 stream source implementation: HLS (HTTP + m3u8 + MPEG-TS) and
// RTSP (TCP-interleaved RTP, Basic/Digest auth) sources feeding an
// AMediaCodec software H.264 decoder.
#include "stream.h"

#include <algorithm>
#include <atomic>
#include <cerrno>
#include <condition_variable>
#include <chrono>
#include <functional>
#include <sstream>
#include <cstring>
#include <mutex>
#include <string>
#include <thread>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#include <android/log.h>
#define SLOG(...) __android_log_print(ANDROID_LOG_INFO, "l4-camstream", __VA_ARGS__)
#define SERR(...) __android_log_print(ANDROID_LOG_ERROR, "l4-camstream", __VA_ARGS__)

extern "C" int property_get(const char* key, char* value, const char* def);

// ------------------------------------------------------------ NDK media
extern "C" {
typedef struct AMediaCodec AMediaCodec;
typedef struct AMediaFormat AMediaFormat;
typedef int32_t media_status_t;
typedef struct {
    int32_t offset; size_t size; int64_t presentationTimeUs; uint32_t flags;
} AMediaCodecBufferInfo;
AMediaCodec* AMediaCodec_createDecoderByType(const char* mime);
media_status_t AMediaCodec_configure(AMediaCodec*, const AMediaFormat*, void*, void*, uint32_t);
media_status_t AMediaCodec_start(AMediaCodec*);
media_status_t AMediaCodec_stop(AMediaCodec*);
media_status_t AMediaCodec_delete(AMediaCodec*);
ssize_t AMediaCodec_dequeueInputBuffer(AMediaCodec*, int64_t timeoutUs);
uint8_t* AMediaCodec_getInputBuffer(AMediaCodec*, size_t idx, size_t* outSize);
media_status_t AMediaCodec_queueInputBuffer(AMediaCodec*, size_t idx, size_t off, size_t size, uint64_t pts, uint32_t flags);
ssize_t AMediaCodec_dequeueOutputBuffer(AMediaCodec*, AMediaCodecBufferInfo*, int64_t timeoutUs);
uint8_t* AMediaCodec_getOutputBuffer(AMediaCodec*, size_t idx, size_t* outSize);
media_status_t AMediaCodec_releaseOutputBuffer(AMediaCodec*, size_t idx, bool render);
AMediaFormat* AMediaCodec_getOutputFormat(AMediaCodec*);
AMediaFormat* AMediaFormat_new();
void AMediaFormat_delete(AMediaFormat*);
void AMediaFormat_setString(AMediaFormat*, const char* name, const char* value);
void AMediaFormat_setInt32(AMediaFormat*, const char* name, int32_t value);
void AMediaFormat_setBuffer(AMediaFormat*, const char* name, const void* data, size_t size);
bool AMediaFormat_getInt32(AMediaFormat*, const char* name, int32_t* out);
}

static int64_t nowMs() {
    struct timespec ts; clock_gettime(CLOCK_BOOTTIME, &ts);
    return (int64_t)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

// ------------------------------------------------------------ HTTP fetch
struct Url {
    std::string host; int port = 80; std::string path = "/";
};

static bool parseHttpUrl(const std::string& u, Url* out) {
    if (u.rfind("http://", 0) != 0) return false;
    std::string rest = u.substr(7);
    size_t slash = rest.find('/');
    std::string hostport = slash == std::string::npos ? rest : rest.substr(0, slash);
    out->path = slash == std::string::npos ? "/" : rest.substr(slash);
    size_t colon = hostport.rfind(':');
    if (colon != std::string::npos) {
        out->host = hostport.substr(0, colon);
        out->port = atoi(hostport.substr(colon + 1).c_str());
    } else { out->host = hostport; out->port = 80; }
    return !out->host.empty();
}

static std::string resolveUrl(const std::string& base, const std::string& rel) {
    if (rel.rfind("http://", 0) == 0 || rel.rfind("https://", 0) == 0) return rel;
    Url b; if (!parseHttpUrl(base, &b)) return rel;
    std::string origin = "http://" + b.host + ":" + std::to_string(b.port);
    if (!rel.empty() && rel[0] == '/') return origin + rel;
    size_t slash = b.path.rfind('/');
    return origin + b.path.substr(0, slash + 1) + rel;
}

// One-shot HTTP/1.1 GET. Handles Content-Length, chunked, close-delimited
// bodies and one level of redirect. Returns false on any failure.
static bool httpGet(const std::string& url, std::string* body, int depth = 0) {
    Url u;
    if (!parseHttpUrl(url, &u)) { SERR("http: bad url %s", url.c_str()); return false; }
    struct sockaddr_storage saddr{}; socklen_t slen = 0;
    struct in_addr v4;
    struct addrinfo* res = nullptr;
    if (inet_pton(AF_INET, u.host.c_str(), &v4) == 1) {
        auto* sin = (struct sockaddr_in*)&saddr;
        sin->sin_family = AF_INET; sin->sin_port = htons((uint16_t)u.port);
        sin->sin_addr = v4; slen = sizeof(*sin);
    } else {
        struct addrinfo hints{}; hints.ai_socktype = SOCK_STREAM;
        if (getaddrinfo(u.host.c_str(), std::to_string(u.port).c_str(), &hints, &res) != 0 || !res) {
            SERR("http: dns fail %s", u.host.c_str()); return false;
        }
        memcpy(&saddr, res->ai_addr, res->ai_addrlen); slen = (socklen_t)res->ai_addrlen;
    }
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { if (res) freeaddrinfo(res); SERR("http: socket errno %d", errno); return false; }
    struct timeval tv{5, 0};
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    int flags = fcntl(fd, F_GETFL, 0); fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    int rc = connect(fd, (struct sockaddr*)&saddr, slen);
    if (rc != 0 && errno != EINPROGRESS) {
        SERR("http: connect %s:%d errno %d", u.host.c_str(), u.port, errno);
        close(fd); if (res) freeaddrinfo(res); return false;
    }
    if (rc != 0) {
        fd_set wf; FD_ZERO(&wf); FD_SET(fd, &wf);
        struct timeval ctv{5, 0};
        if (select(fd + 1, nullptr, &wf, nullptr, &ctv) <= 0) {
            SERR("http: connect timeout %s", u.host.c_str());
            close(fd); if (res) freeaddrinfo(res); return false;
        }
        int err = 0; socklen_t elen = sizeof(err);
        getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &elen);
        if (err != 0) {
            SERR("http: connect %s:%d so_error %d", u.host.c_str(), u.port, err);
            close(fd); if (res) freeaddrinfo(res); return false;
        }
    }
    fcntl(fd, F_SETFL, flags);
    if (res) freeaddrinfo(res);
    std::string req = "GET " + u.path + " HTTP/1.1\r\nHost: " + u.host +
                      "\r\nUser-Agent: l4-camera\r\nConnection: close\r\n\r\n";
    if (send(fd, req.data(), req.size(), MSG_NOSIGNAL) != (ssize_t)req.size()) {
        SERR("http: send errno %d", errno); close(fd); return false;
    }
    std::string raw; char buf[16384];
    while (true) {
        ssize_t n = recv(fd, buf, sizeof(buf), 0);
        if (n < 0) { close(fd); return false; }
        if (n == 0) break;
        raw.append(buf, (size_t)n);
        if (raw.size() > 32 * 1024 * 1024) { close(fd); return false; }
    }
    close(fd);
    size_t hdrEnd = raw.find("\r\n\r\n");
    if (hdrEnd == std::string::npos) return false;
    std::string hdr = raw.substr(0, hdrEnd);
    int code = 0; sscanf(hdr.c_str(), "HTTP/%*s %d", &code);
    if ((code == 301 || code == 302 || code == 307 || code == 308) && depth < 2) {
        size_t p = hdr.find("Location:");
        if (p == std::string::npos) p = hdr.find("location:");
        if (p == std::string::npos) return false;
        size_t e = hdr.find("\r\n", p);
        std::string loc = hdr.substr(p + 9, e - p - 9);
        while (!loc.empty() && (loc[0] == ' ' || loc[0] == '\t')) loc.erase(0, 1);
        return httpGet(resolveUrl(url, loc), body, depth + 1);
    }
    if (code != 200) { SERR("http: %s -> %d", url.c_str(), code); return false; }
    std::string data = raw.substr(hdrEnd + 4);
    bool chunked = hdr.find("chunked") != std::string::npos;
    if (chunked) {
        std::string out; size_t pos = 0;
        while (pos < data.size()) {
            size_t e = data.find("\r\n", pos);
            if (e == std::string::npos) break;
            long sz = strtol(data.substr(pos, e - pos).c_str(), nullptr, 16);
            if (sz <= 0) break;
            out.append(data, e + 2, (size_t)sz);
            pos = e + 2 + (size_t)sz + 2;
        }
        data = std::move(out);
    } else {
        size_t p = hdr.find("Content-Length:");
        if (p == std::string::npos) p = hdr.find("content-length:");
        if (p != std::string::npos) {
            long len = strtol(hdr.c_str() + p + 15, nullptr, 10);
            if ((long)data.size() > len) data.resize((size_t)len);
        }
    }
    *body = std::move(data);
    return true;
}

// ------------------------------------------------------------ SPS parsing
struct BitReader {
    const uint8_t* d; size_t n; size_t bit = 0;
    int u1() { if (bit / 8 >= n) return 0; int v = (d[bit / 8] >> (7 - (bit % 8))) & 1; bit++; return v; }
    int bits(int k) { int v = 0; for (int i = 0; i < k; i++) v = (v << 1) | u1(); return v; }
    int ue() { int z = 0; while (u1() == 0 && z < 32) z++; return (1 << z) - 1 + bits(z); }
    int se() { int v = ue(); return (v & 1) ? (v + 1) / 2 : -(v / 2); }
};
// Parse SPS NAL (without start code, with emulation prevention bytes)
// into width/height. Good enough for standard High/Main/Baseline SPS.
static bool parseSps(const uint8_t* nal, size_t len, int* outW, int* outH) {
    std::vector<uint8_t> rb;
    for (size_t i = 0; i < len; i++) {
        if (i >= 2 && nal[i - 2] == 0 && nal[i - 1] == 0 && nal[i] == 3) continue;
        rb.push_back(nal[i]);
    }
    if (rb.size() < 4) return false;
    BitReader br{rb.data(), rb.size()};
    br.bits(8);                       // forbidden + type
    int profile = br.bits(8); br.bits(8); br.bits(8);
    br.ue();                          // sps id
    int chroma = 1;
    if (profile == 100 || profile == 110 || profile == 122 || profile == 244 ||
        profile == 44 || profile == 83 || profile == 86 || profile == 118 ||
        profile == 128 || profile == 138 || profile == 139 || profile == 134 || profile == 135) {
        chroma = br.ue();
        if (chroma == 3) br.u1();
        br.ue(); br.ue(); br.u1();
        if (br.u1()) { /* scaling lists: rare in camera streams; bail */ return false; }
    }
    br.ue();                          // log2_max_frame_num
    int poc = br.ue();
    if (poc == 0) br.ue(); else if (poc == 1) { br.u1(); br.se(); br.se(); br.ue(); }
    br.ue();                          // max_num_ref_frames
    br.u1();                          // gaps
    int wmb = br.ue() + 1, hmb = br.ue() + 1;
    int frameMbsOnly = br.u1();
    if (!frameMbsOnly) br.u1();
    br.u1();                          // direct_8x8
    int cropL = 0, cropR = 0, cropT = 0, cropB = 0;
    if (br.u1()) { cropL = br.ue(); cropR = br.ue(); cropT = br.ue(); cropB = br.ue(); }
    int subW = (chroma == 1 || chroma == 2) ? 2 : 1;
    int subH = (chroma == 1 || chroma == 3 ? 2 : 1);
    int w = wmb * 16 - (cropL + cropR) * subW;
    int h = hmb * 16 * (2 - frameMbsOnly) - (cropT + cropB) * subH * (2 - frameMbsOnly);
    if (w <= 0 || h <= 0 || w > 7680 || h > 4320) return false;
    *outW = w; *outH = h; return true;
}

// ------------------------------------------------------------ H.264 decode
class H264Decoder {
  public:
    ~H264Decoder() { destroy(); }
    // (Re)configure when SPS changes. sps/pps include Annex-B start codes.
    bool configure(const std::vector<uint8_t>& sps, const std::vector<uint8_t>& pps, int w, int h) {
        destroy();
        codec_ = AMediaCodec_createDecoderByType("video/avc");
        if (!codec_) { SERR("codec create failed"); return false; }
        AMediaFormat* f = AMediaFormat_new();
        AMediaFormat_setString(f, "mime", "video/avc");
        AMediaFormat_setInt32(f, "width", w);
        AMediaFormat_setInt32(f, "height", h);
        AMediaFormat_setBuffer(f, "csd-0", sps.data(), sps.size());
        AMediaFormat_setBuffer(f, "csd-1", pps.data(), pps.size());
        media_status_t st = AMediaCodec_configure(codec_, f, nullptr, nullptr, 0);
        AMediaFormat_delete(f);
        if (st != 0) { SERR("codec configure -> %d", (int)st); destroy(); return false; }
        st = AMediaCodec_start(codec_);
        if (st != 0) { SERR("codec start -> %d", (int)st); destroy(); return false; }
        SLOG("codec running %dx%d", w, h);
        pts_ = 0;
        convThread_ = std::thread([this] { convertLoop(); });
        return true;
    }
    void feed(const uint8_t* data, size_t size) {
        if (!codec_) return;
        size_t off = 0;
        while (off < size) {
            ssize_t idx = AMediaCodec_dequeueInputBuffer(codec_, 100000);
            if (idx < 0) { drain(0); continue; }
            size_t cap = 0; uint8_t* buf = AMediaCodec_getInputBuffer(codec_, (size_t)idx, &cap);
            if (!buf) return;
            size_t chunk = size - off < cap ? size - off : cap;
            memcpy(buf, data + off, chunk);
            AMediaCodec_queueInputBuffer(codec_, (size_t)idx, 0, chunk, pts_, 0);
            pts_ += 33333;
            off += chunk;
        }
        drain(0);
    }
    // Drain decoded frames. Only the NEWEST queued frame is kept: its
    // raw YUV is memcpy'd out (sub-ms) and handed to the convert thread;
    // the codec buffer is released immediately. Converting inline here
    // costs ~70ms/frame on this guest and starves the codec's pools,
    // which is what made the pipeline fall behind live.
    void drain(int64_t timeoutUs) {
        if (!codec_) return;
        ssize_t held = -1; AMediaCodecBufferInfo heldInfo{};
        while (true) {
            AMediaCodecBufferInfo info{};
            ssize_t idx = AMediaCodec_dequeueOutputBuffer(codec_, &info, timeoutUs);
            if (idx < 0) break;
            if (held >= 0) AMediaCodec_releaseOutputBuffer(codec_, (size_t)held, false);
            held = idx; heldInfo = info;
            timeoutUs = 0;
        }
        if (held < 0) return;
        statOuts_++;
        size_t cap = 0;
        uint8_t* buf = AMediaCodec_getOutputBuffer(codec_, (size_t)held, &cap);
        if (buf && heldInfo.size > 0 && sink_) {
            auto raw = std::make_shared<RawFrame>();
            if (readFormat(raw.get())) {
                size_t need = (size_t)raw->stride * raw->sliceH * 3 / 2;
                if ((size_t)heldInfo.size >= need) {
                    raw->yuv.assign(buf + heldInfo.offset, buf + heldInfo.offset + need);
                    std::lock_guard<std::mutex> lk(rawM_);
                    raw->seq = ++rawSeq_;
                    rawSlot_ = raw;
                    rawCv_.notify_one();
                }
            }
        }
        AMediaCodec_releaseOutputBuffer(codec_, (size_t)held, false);
    }
    std::function<void(std::shared_ptr<StreamFrame>)> sink_;
    // diagnostics (read by the HLS loop per segment)
    long long statOuts_ = 0, statConvertMs_ = 0, statConverts_ = 0;
    long long statFmtMs_ = 0, statLoopMs_ = 0;

    struct RawFrame {
        std::vector<uint8_t> yuv;
        int stride = 0, sliceH = 0, color = 0;
        int cropL = 0, cropT = 0, cropR = -1, cropB = -1;
        uint64_t seq = 0;
    };
    bool readFormat(RawFrame* raw) {
        AMediaFormat* f = AMediaCodec_getOutputFormat(codec_);
        if (!f) return false;
        int32_t w = 0, h = 0;
        AMediaFormat_getInt32(f, "width", &w); AMediaFormat_getInt32(f, "height", &h);
        AMediaFormat_getInt32(f, "stride", &raw->stride);
        AMediaFormat_getInt32(f, "slice-height", &raw->sliceH);
        AMediaFormat_getInt32(f, "color-format", &raw->color);
        raw->cropR = w - 1; raw->cropB = h - 1;
        AMediaFormat_getInt32(f, "crop-left", &raw->cropL);
        AMediaFormat_getInt32(f, "crop-top", &raw->cropT);
        AMediaFormat_getInt32(f, "crop-right", &raw->cropR);
        AMediaFormat_getInt32(f, "crop-bottom", &raw->cropB);
        AMediaFormat_delete(f);
        if (w <= 0 || h <= 0 || raw->stride < w) return false;
        if (raw->sliceH < h) raw->sliceH = h;
        return true;
    }
    void convertLoop() {
        uint64_t done = 0;
        while (true) {
            std::shared_ptr<RawFrame> raw;
            {
                std::unique_lock<std::mutex> lk(rawM_);
                rawCv_.wait(lk, [&] { return convStop_ || (rawSlot_ && rawSlot_->seq != done); });
                if (convStop_) return;
                raw = rawSlot_;
            }
            done = raw->seq;
            int64_t t0 = nowMs();
            auto fr = convertRaw(*raw);
            statLoopMs_ += nowMs() - t0; statConverts_++;
            if (fr && sink_) {
                if ((++frames_ % 150) == 1)
                    SLOG("stream frame %dx%d #%lld", fr->width, fr->height, (long long)frames_);
                sink_(fr);
            }
        }
    }

  private:
    void destroy() {
        {
            std::lock_guard<std::mutex> lk(rawM_);
            convStop_ = true;
        }
        rawCv_.notify_all();
        if (convThread_.joinable()) convThread_.join();
        convStop_ = false;
        if (codec_) { AMediaCodec_stop(codec_); AMediaCodec_delete(codec_); codec_ = nullptr; }
    }
    std::shared_ptr<StreamFrame> convertRaw(const RawFrame& raw) {
        const uint8_t* buf = raw.yuv.data();
        int stride = raw.stride, sliceH = raw.sliceH, color = raw.color;
        int cropL = raw.cropL, cropT = raw.cropT, cropR = raw.cropR, cropB = raw.cropB;
        int cw = cropR - cropL + 1, ch = cropB - cropT + 1;
        if (cw <= 0 || ch <= 0) return nullptr;
        auto fr = std::make_shared<StreamFrame>();
        fr->width = cw; fr->height = ch; fr->boottimeMs = nowMs();
        fr->rgb.resize((size_t)cw * ch * 3);
        const uint8_t* yPlane = buf;
        const uint8_t* uvBase = buf + (size_t)stride * sliceH;
        bool semiPlanar = (color != 19 /* COLOR_FormatYUV420Planar */);
        auto clip = [](int v) { return (uint8_t)(v < 0 ? 0 : v > 255 ? 255 : v); };
        for (int y = 0; y < ch; y++) {
            int sy = y + cropT;
            const uint8_t* yRow = yPlane + (size_t)sy * stride + cropL;
            const uint8_t* uvRow = uvBase + (size_t)(sy / 2) * stride;
            const uint8_t* uRow = uvBase + (size_t)(sy / 2) * (stride / 2);
            const uint8_t* vRow = uvBase + (size_t)(stride / 2) * (sliceH / 2) + (size_t)(sy / 2) * (stride / 2);
            uint8_t* out = fr->rgb.data() + (size_t)y * cw * 3;
            for (int x = 0; x < cw; x += 2) {
                int cx = (x + cropL) / 2;
                int u, v;
                if (semiPlanar) { u = uvRow[cx * 2]; v = uvRow[cx * 2 + 1]; }
                else { u = uRow[cx]; v = vRow[cx]; }
                int d = u - 128, e = v - 128;
                int du = -100 * d, dv = 409 * e, gu = 516 * d, gv = -208 * e;
                for (int k = 0; k < 2 && x + k < cw; k++) {
                    int c = yRow[x + k] - 16;
                    out[(x + k) * 3 + 0] = clip((298 * c + dv + 128) >> 8);
                    out[(x + k) * 3 + 1] = clip((298 * c + du + gv + 128) >> 8);
                    out[(x + k) * 3 + 2] = clip((298 * c + gu + 128) >> 8);
                }
            }
        }
        return fr;
    }
    AMediaCodec* codec_ = nullptr;
    int64_t pts_ = 0;
    long long frames_ = 0;
    std::mutex rawM_;
    std::condition_variable rawCv_;
    std::shared_ptr<RawFrame> rawSlot_;
    uint64_t rawSeq_ = 0;
    bool convStop_ = false;
    std::thread convThread_;
};

// ------------------------------------------- NAL / access-unit pump
// Shared by the TS path (Annex-B byte stream) and the RTP path (single
// NAL units, marker bit ends the AU). Groups NALs into access units,
// tracks SPS/PPS and configures the decoder on first sight.
class NalPump {
  public:
    explicit NalPump(H264Decoder* dec) : dec_(dec) {}
    // Annex-B byte stream (start-code delimited), arbitrary chunking.
    void feedAnnexB(const uint8_t* data, size_t size) {
        stream_.insert(stream_.end(), data, data + size);
        while (true) {
            auto findSc = [&](size_t from, size_t* scLen) -> long {
                for (size_t i = from; i + 2 < stream_.size(); i++) {
                    if (stream_[i] == 0 && stream_[i + 1] == 0 &&
                        (stream_[i + 2] == 1)) { *scLen = 3; return (long)i; }
                    if (i + 3 < stream_.size() && stream_[i] == 0 && stream_[i + 1] == 0 &&
                        stream_[i + 2] == 0 && stream_[i + 3] == 1) { *scLen = 4; return (long)i; }
                }
                return -1;
            };
            size_t sc1 = 0, sc2 = 0;
            long p0 = findSc(0, &sc1);
            if (p0 < 0) { if (stream_.size() > 4 * 1024 * 1024) stream_.clear(); return; }
            long p1 = findSc((size_t)p0 + sc1, &sc2);
            if (p1 < 0) {
                if (p0 > 0) stream_.erase(stream_.begin(), stream_.begin() + p0);
                return;  // wait for more data to complete this NAL
            }
            std::vector<uint8_t> nal(stream_.begin() + p0, stream_.begin() + p1);
            stream_.erase(stream_.begin(), stream_.begin() + p1);
            onNal(nal);
        }
    }
    // One NAL unit without a start code (RTP single-NAL / STAP-A member /
    // reassembled FU-A).
    void feedNal(const uint8_t* data, size_t size) {
        std::vector<uint8_t> nal = {0, 0, 0, 1};
        nal.insert(nal.end(), data, data + size);
        onNal(nal);
    }
    // RTP marker bit: the current AU is complete.
    void endAccessUnit() { flushAu(); }
    // SPS/PPS from out-of-band config (SDP sprop-parameter-sets), raw
    // NAL bytes without start codes.
    void seedSpsPps(const std::vector<uint8_t>& sps, const std::vector<uint8_t>& pps) {
        if (!sps.empty()) feedNal(sps.data(), sps.size());
        if (!pps.empty()) feedNal(pps.data(), pps.size());
    }

  private:
    // first_mb_in_slice of a VCL NAL: first ue(v) of the slice header.
    static bool sliceStartsFrame(const uint8_t* p, size_t n) {
        uint8_t tmp[8]; size_t m = 0;
        for (size_t i = 0; i < n && m < sizeof(tmp); i++) {
            if (i >= 2 && p[i - 2] == 0 && p[i - 1] == 0 && p[i] == 3) continue;
            tmp[m++] = p[i];
        }
        if (m == 0) return false;
        BitReader br{tmp, m};
        return br.ue() == 0;
    }
    void onNal(const std::vector<uint8_t>& nal) {
        size_t scLen = (nal.size() >= 4 && nal[2] == 0) ? 4 : 3;
        if (nal.size() <= scLen) return;
        int type = nal[scLen] & 0x1F;
        bool vcl = (type == 1 || type == 5);
        if ((type == 9 || type == 7 || type == 8) && auHasVcl_) flushAu();
        // x264 emits no AUDs and SPS/PPS only at IDR: without this, a
        // whole GOP would accumulate into one "AU". A VCL NAL whose
        // slice starts at macroblock 0 opens a new frame.
        if (vcl && auHasVcl_ && nal.size() > scLen + 1 &&
            sliceStartsFrame(nal.data() + scLen + 1, nal.size() - scLen - 1))
            flushAu();
        if (type == 7) {  // SPS
            sps_.assign(nal.begin(), nal.end());
            int w, h;
            if (parseSps(nal.data() + scLen, nal.size() - scLen, &w, &h)) { spsW_ = w; spsH_ = h; }
        } else if (type == 8) {
            pps_.assign(nal.begin(), nal.end());
        }
        if (!sps_.empty() && !pps_.empty() && !decReady_) {
            if (dec_->configure(sps_, pps_, spsW_ > 0 ? spsW_ : 1280, spsH_ > 0 ? spsH_ : 720)) {
                decReady_ = true; SLOG("nal: decoder configured from SPS %dx%d", spsW_, spsH_);
            }
        }
        au_.insert(au_.end(), nal.begin(), nal.end());
        if (vcl) auHasVcl_ = true;
    }
    void flushAu() {
        if (!au_.empty() && decReady_) dec_->feed(au_.data(), au_.size());
        au_.clear(); auHasVcl_ = false;
    }
    H264Decoder* dec_;
    std::vector<uint8_t> stream_, au_, sps_, pps_;
    bool auHasVcl_ = false, decReady_ = false;
    int spsW_ = 0, spsH_ = 0;
};

// ------------------------------------------- TS demux
// Feeds the H.264 elementary stream of an MPEG-TS into a NalPump.
class TsPump {
  public:
    explicit TsPump(H264Decoder* dec) : nal_(dec) {}
    void push(const uint8_t* data, size_t size) {
        buf_.insert(buf_.end(), data, data + size);
        size_t pos = 0;
        while (buf_.size() - pos >= 188) {
            if (buf_[pos] != 0x47) {  // resync
                auto it = std::find(buf_.begin() + (long)pos + 1, buf_.end(), 0x47);
                pos = (size_t)(it - buf_.begin());
                if (buf_.size() - pos < 188) break;
                continue;
            }
            packet(buf_.data() + pos);
            pos += 188;
        }
        buf_.erase(buf_.begin(), buf_.begin() + (long)pos);
    }

  private:
    void packet(const uint8_t* p) {
        bool pusi = p[1] & 0x40;
        int pid = ((p[1] & 0x1F) << 8) | p[2];
        int afc = (p[3] >> 4) & 3;
        size_t off = 4;
        if (afc == 2 || afc == 3) off += 1 + p[4];
        if (afc == 0 || off >= 188) return;
        const uint8_t* pl = p + off; size_t pln = 188 - off;
        if (pid == 0) {  // PAT
            if (pusi) { const uint8_t* q = pl + 1 + pl[0]; parsePat(q, 188 - (size_t)(q - p)); }
            return;
        }
        if (pid == pmtPid_) {
            if (pusi) { const uint8_t* q = pl + 1 + pl[0]; parsePmt(q, 188 - (size_t)(q - p)); }
            return;
        }
        if (pid != videoPid_) return;
        if (pusi) {
            // New PES: payload starts after the PES header.
            if (pln < 9 || pl[0] != 0 || pl[1] != 0 || pl[2] != 1) return;
            size_t hdr = 9 + pl[8];
            if (hdr >= pln) return;
            pl += hdr; pln -= hdr;
            nal_.endAccessUnit();
        }
        nal_.feedAnnexB(pl, pln);
    }
    void parsePat(const uint8_t* q, size_t n) {
        if (n < 12) return;
        int secLen = ((q[1] & 0x0F) << 8) | q[2];
        size_t end = 3 + (size_t)secLen - 4;
        for (size_t i = 8; i + 4 <= end && i + 4 <= n; i += 4) {
            int prog = (q[i] << 8) | q[i + 1];
            int pid = ((q[i + 2] & 0x1F) << 8) | q[i + 3];
            if (prog != 0) pmtPid_ = pid;
        }
    }
    void parsePmt(const uint8_t* q, size_t n) {
        if (n < 12) return;
        int secLen = ((q[1] & 0x0F) << 8) | q[2];
        int progInfoLen = ((q[10] & 0x0F) << 8) | q[11];
        size_t i = 12 + (size_t)progInfoLen;
        size_t end = 3 + (size_t)secLen - 4;
        while (i + 5 <= end && i + 5 <= n) {
            int type = q[i];
            int pid = ((q[i + 1] & 0x1F) << 8) | q[i + 2];
            int esLen = ((q[i + 3] & 0x0F) << 8) | q[i + 4];
            if (type == 0x1B && videoPid_ < 0) { videoPid_ = pid; SLOG("ts: h264 video pid %d", pid); }
            i += 5 + (size_t)esLen;
        }
    }
    NalPump nal_;
    std::vector<uint8_t> buf_;
    int pmtPid_ = -1, videoPid_ = -1;
};


// ------------------------------------------------------------ HLS client
// Follows a live HLS playlist at its live edge, downloads each new
// segment once and pumps the TS bytes into the decoder. One TsPump and
// one decoder live for the whole pipeline run.
static void hlsRun(const std::string& startUrl, std::atomic<bool>& stop, H264Decoder& dec) {
    std::string playlistUrl = startUrl;
    bool masterDone = false;
    long long nextSeq = -1;
    TsPump pump(&dec);
    while (!stop.load()) {
        std::string playlist;
        if (!httpGet(playlistUrl, &playlist)) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }
        if (!masterDone && playlist.find("#EXT-X-STREAM-INF") != std::string::npos) {
            std::istringstream ss(playlist); std::string line; bool inf = false;
            while (std::getline(ss, line)) {
                if (!line.empty() && line.back() == '\r') line.pop_back();
                if (line.rfind("#EXT-X-STREAM-INF", 0) == 0) { inf = true; continue; }
                if (inf && !line.empty() && line[0] != '#') {
                    playlistUrl = resolveUrl(playlistUrl, line);
                    SLOG("hls: variant -> %s", playlistUrl.c_str());
                    break;
                }
            }
            masterDone = true;
            continue;
        }
        masterDone = true;
        long long mediaSeq = 0; int targetDur = 2;
        struct Seg { long long seq; std::string uri; };
        std::vector<Seg> segs;
        {
            std::istringstream ss(playlist); std::string line;
            while (std::getline(ss, line)) {
                if (!line.empty() && line.back() == '\r') line.pop_back();
                if (line.rfind("#EXT-X-MEDIA-SEQUENCE:", 0) == 0)
                    mediaSeq = strtoll(line.c_str() + 22, nullptr, 10);
                else if (line.rfind("#EXT-X-TARGETDURATION:", 0) == 0)
                    targetDur = atoi(line.c_str() + 22);
                else if (!line.empty() && line[0] != '#' &&
                         line.find("#EXT") != 0)
                    segs.push_back({mediaSeq + (long long)segs.size(), line});
            }
        }
        if (segs.empty()) { std::this_thread::sleep_for(std::chrono::seconds(1)); continue; }
        if (nextSeq < 0) nextSeq = segs.back().seq;  // join at the live edge
        bool fetched = false;
        for (auto& s : segs) {
            if (stop.load()) break;
            if (s.seq < nextSeq) continue;
            std::string ts;
            int64_t f0 = nowMs();
            if (httpGet(resolveUrl(playlistUrl, s.uri), &ts)) {
                int64_t f1 = nowMs();
                long long o0 = dec.statOuts_, n0 = dec.statConverts_;
                long long loop0 = dec.statLoopMs_;
                pump.push((const uint8_t*)ts.data(), ts.size());
                int64_t f2 = nowMs();
                SLOG("seg %lld %zuB fetch=%lldms pump=%lldms raw=%lld conv=%lldms/%lld",
                     s.seq, ts.size(), (long long)(f1 - f0), (long long)(f2 - f1),
                     dec.statOuts_ - o0, (long long)(dec.statLoopMs_ - loop0),
                     (long long)(dec.statConverts_ - n0));
                nextSeq = s.seq + 1;
                fetched = true;
            } else {
                SERR("hls: segment %lld failed", s.seq);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        dec.drain(0);
        if (!fetched)
            std::this_thread::sleep_for(std::chrono::milliseconds(
                targetDur > 1 ? 1000 : 500));
    }
}

// ------------------------------------------------------------ RTSP client
// Minimal RTSP client: TCP-interleaved RTP only (the mode every IP
// camera supports), H.264 depacketization (single NAL, STAP-A, FU-A),
// Basic and Digest auth for rtsp://user:pass@host/ URLs.

struct RtspUrl {
    std::string host; int port = 554; std::string path = "/";
    std::string user, pass;
};

static bool parseRtspUrl(const std::string& u, RtspUrl* out) {
    if (u.rfind("rtsp://", 0) != 0) return false;
    std::string rest = u.substr(7);
    size_t slash = rest.find('/');
    std::string hostport = slash == std::string::npos ? rest : rest.substr(0, slash);
    out->path = slash == std::string::npos ? "/" : rest.substr(slash);
    size_t at = hostport.rfind('@');
    if (at != std::string::npos) {
        std::string ui = hostport.substr(0, at);
        hostport = hostport.substr(at + 1);
        size_t c = ui.find(':');
        if (c != std::string::npos) { out->user = ui.substr(0, c); out->pass = ui.substr(c + 1); }
        else out->user = ui;
    }
    size_t colon = hostport.rfind(':');
    if (colon != std::string::npos) {
        out->host = hostport.substr(0, colon);
        out->port = atoi(hostport.substr(colon + 1).c_str());
    } else { out->host = hostport; out->port = 554; }
    return !out->host.empty();
}

// TCP connect with the numeric-IP fast path (getaddrinfo stalls on
// numeric hosts inside this guest — see the HTTP path).
static int tcpConnect(const std::string& host, int port) {
    struct sockaddr_storage saddr{}; socklen_t slen = 0;
    struct in_addr v4;
    struct addrinfo* res = nullptr;
    if (inet_pton(AF_INET, host.c_str(), &v4) == 1) {
        auto* sin = (struct sockaddr_in*)&saddr;
        sin->sin_family = AF_INET; sin->sin_port = htons((uint16_t)port);
        sin->sin_addr = v4; slen = sizeof(*sin);
    } else {
        struct addrinfo hints{}; hints.ai_socktype = SOCK_STREAM;
        if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res) != 0 || !res) {
            SERR("rtsp: dns fail %s", host.c_str()); return -1;
        }
        memcpy(&saddr, res->ai_addr, res->ai_addrlen); slen = (socklen_t)res->ai_addrlen;
    }
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { if (res) freeaddrinfo(res); SERR("rtsp: socket errno %d", errno); return -1; }
    struct timeval tv{5, 0};
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    int flags = fcntl(fd, F_GETFL, 0); fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    int rc = connect(fd, (struct sockaddr*)&saddr, slen);
    if (rc != 0 && errno == EINPROGRESS) {
        fd_set wf; FD_ZERO(&wf); FD_SET(fd, &wf);
        struct timeval tv2{5, 0};
        rc = select(fd + 1, nullptr, &wf, nullptr, &tv2) > 0 ? 0 : -1;
        if (rc == 0) {
            int soErr = 0; socklen_t el = sizeof(soErr);
            getsockopt(fd, SOL_SOCKET, SO_ERROR, &soErr, &el);
            if (soErr != 0) { SERR("rtsp: connect %s:%d so_error %d", host.c_str(), port, soErr); rc = -1; }
        }
    } else if (rc != 0) {
        SERR("rtsp: connect %s:%d errno %d", host.c_str(), port, errno);
    }
    if (res) freeaddrinfo(res);
    if (rc != 0) { close(fd); return -1; }
    fcntl(fd, F_SETFL, flags);
    return fd;
}

static std::string base64Enc(const uint8_t* data, size_t n) {
    static const char* T = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string o;
    for (size_t i = 0; i < n; i += 3) {
        uint32_t v = (uint32_t)data[i] << 16;
        if (i + 1 < n) v |= (uint32_t)data[i + 1] << 8;
        if (i + 2 < n) v |= data[i + 2];
        o += T[(v >> 18) & 63]; o += T[(v >> 12) & 63];
        o += (i + 1 < n) ? T[(v >> 6) & 63] : '=';
        o += (i + 2 < n) ? T[v & 63] : '=';
    }
    return o;
}

static bool base64Dec(const std::string& s, std::vector<uint8_t>* out) {
    auto val = [](char c) -> int {
        if (c >= 'A' && c <= 'Z') return c - 'A';
        if (c >= 'a' && c <= 'z') return c - 'a' + 26;
        if (c >= '0' && c <= '9') return c - '0' + 52;
        if (c == '+') return 62;
        if (c == '/') return 63;
        return -1;
    };
    uint32_t acc = 0; int bits = 0;
    for (char c : s) {
        if (c == '=') break;
        int v = val(c);
        if (v < 0) continue;
        acc = (acc << 6) | (uint32_t)v; bits += 6;
        if (bits >= 8) { bits -= 8; out->push_back((uint8_t)(acc >> bits)); }
    }
    return !out->empty();
}

// Tiny MD5 for Digest auth (public-domain style implementation).
struct Md5 {
    uint32_t h[4] = {0x67452301u, 0xefcdab89u, 0x98badcfeu, 0x10325476u};
    uint64_t bytes = 0;
    uint8_t blk[64]; size_t blkLen = 0;
    void add(const uint8_t* p, size_t n) {
        bytes += n;
        while (n) {
            size_t take = 64 - blkLen; if (take > n) take = n;
            memcpy(blk + blkLen, p, take); blkLen += take; p += take; n -= take;
            if (blkLen == 64) { transform(blk); blkLen = 0; }
        }
    }
    void add(const std::string& s) { add((const uint8_t*)s.data(), s.size()); }
    void finish(uint8_t out[16]) {
        uint64_t bits = bytes * 8;
        uint8_t pad = 0x80; add(&pad, 1);
        uint8_t zero = 0; while (blkLen != 56) add(&zero, 1);
        uint8_t lb[8]; for (int i = 0; i < 8; i++) lb[i] = (uint8_t)(bits >> (8 * i));
        // feed length block directly (add() would count it)
        memcpy(blk + blkLen, lb, 8); transform(blk);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) out[i * 4 + j] = (uint8_t)(h[i] >> (8 * j));
    }
    void transform(const uint8_t* b) {
        static const uint32_t K[64] = {
            0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
            0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
            0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
            0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
            0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
            0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
            0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
            0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};
        static const int S[64] = {7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
                                  5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
                                  4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
                                  6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21};
        uint32_t w[16];
        for (int i = 0; i < 16; i++)
            w[i] = (uint32_t)b[i * 4] | ((uint32_t)b[i * 4 + 1] << 8) |
                   ((uint32_t)b[i * 4 + 2] << 16) | ((uint32_t)b[i * 4 + 3] << 24);
        uint32_t a = h[0], bb = h[1], c = h[2], d = h[3];
        for (int i = 0; i < 64; i++) {
            uint32_t f; int g;
            if (i < 16)      { f = (bb & c) | (~bb & d); g = i; }
            else if (i < 32) { f = (d & bb) | (~d & c); g = (5 * i + 1) & 15; }
            else if (i < 48) { f = bb ^ c ^ d; g = (3 * i + 5) & 15; }
            else             { f = c ^ (bb | ~d); g = (7 * i) & 15; }
            uint32_t tmp = d; d = c; c = bb;
            uint32_t x = a + f + K[i] + w[g];
            bb = bb + ((x << S[i]) | (x >> (32 - S[i])));
            a = tmp;
        }
        h[0] += a; h[1] += bb; h[2] += c; h[3] += d;
    }
};

static std::string md5Hex(const std::string& s) {
    Md5 m; m.add(s); uint8_t d[16]; m.finish(d);
    static const char* H = "0123456789abcdef";
    std::string o;
    for (int i = 0; i < 16; i++) { o += H[d[i] >> 4]; o += H[d[i] & 15]; }
    return o;
}

class RtspSession {
  public:
    RtspSession(const std::string& url, RtspUrl u, std::atomic<bool>& stop, H264Decoder& dec)
        : url_(url), u_(std::move(u)), stop_(stop), dec_(dec), pump_(&dec) {}
    ~RtspSession() { if (fd_ >= 0) close(fd_); }

    bool run() {
        fd_ = tcpConnect(u_.host, u_.port);
        if (fd_ < 0) return false;
        SLOG("rtsp: connected %s:%d%s", u_.host.c_str(), u_.port, u_.path.c_str());
        std::string sdp, wwwAuth;
        int status = 0;
        if (!request("OPTIONS", url_, "", &status, nullptr, nullptr)) return fail("OPTIONS");
        if (!request("DESCRIBE", url_, "Accept: application/sdp\r\n", &status, &sdp, &wwwAuth))
            return fail("DESCRIBE");
        if (status == 401) {
            if (u_.user.empty() || !buildAuth("DESCRIBE", url_, wwwAuth)) {
                SERR("rtsp: 401 and no usable credentials"); return false;
            }
            if (!request("DESCRIBE", url_, "Accept: application/sdp\r\n", &status, &sdp, nullptr))
                return fail("DESCRIBE(auth)");
        }
        if (status != 200) { SERR("rtsp: DESCRIBE -> %d", status); return false; }
        std::string trackUrl;
        if (!parseSdp(sdp, &trackUrl)) { SERR("rtsp: no H.264 video track in SDP"); return false; }
        std::string setupExtra = "Transport: RTP/AVP/TCP;unicast;interleaved=0-1\r\n";
        std::string sess;
        if (!request("SETUP", trackUrl, setupExtra, &status, nullptr, nullptr, &sess))
            return fail("SETUP");
        if (status == 401) {
            if (!buildAuth("SETUP", trackUrl, lastWwwAuth_)) return false;
            if (!request("SETUP", trackUrl, setupExtra, &status, nullptr, nullptr, &sess))
                return fail("SETUP(auth)");
        }
        if (status != 200) { SERR("rtsp: SETUP -> %d", status); return false; }
        size_t sc = sess.find(';');
        session_ = sc == std::string::npos ? sess : sess.substr(0, sc);
        while (!session_.empty() && (session_.back() == ' ' || session_.back() == '\t')) session_.pop_back();
        std::string playExtra = "Session: " + session_ + "\r\nRange: npt=0.000-\r\n";
        if (!request("PLAY", url_, playExtra, &status, nullptr, nullptr)) return fail("PLAY");
        if (status != 200) { SERR("rtsp: PLAY -> %d", status); return false; }
        SLOG("rtsp: playing (session %s)", session_.c_str());
        streamLoop();
        return true;
    }

  private:
    bool fail(const char* what) { SERR("rtsp: %s failed", what); return false; }

    bool parseSdp(const std::string& sdp, std::string* trackUrl) {
        std::istringstream ss(sdp); std::string line;
        bool inVideo = false;
        std::string control, sprop;
        while (std::getline(ss, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.rfind("m=", 0) == 0) inVideo = line.rfind("m=video", 0) == 0;
            if (!inVideo) continue;
            if (line.rfind("a=control:", 0) == 0) control = line.substr(10);
            if (line.rfind("a=fmtp:", 0) == 0) {
                size_t p = line.find("sprop-parameter-sets=");
                if (p != std::string::npos) {
                    sprop = line.substr(p + 21);
                    size_t e = sprop.find(';'); if (e != std::string::npos) sprop = sprop.substr(0, e);
                    while (!sprop.empty() && (sprop.back() == ' ' || sprop.back() == '\r')) sprop.pop_back();
                }
            }
        }
        if (!sprop.empty()) {
            size_t comma = sprop.find(',');
            std::vector<uint8_t> sps, pps;
            if (comma != std::string::npos &&
                base64Dec(sprop.substr(0, comma), &sps) &&
                base64Dec(sprop.substr(comma + 1), &pps)) {
                pump_.seedSpsPps(sps, pps);
                SLOG("rtsp: SPS/PPS seeded from SDP");
            }
        }
        if (control.empty() || control == "*") { *trackUrl = url_; return true; }
        if (control.rfind("rtsp://", 0) == 0) { *trackUrl = control; return true; }
        std::string base = url_;
        if (!base.empty() && base.back() != '/') base += '/';
        *trackUrl = base + control;
        return true;
    }

    bool buildAuth(const char* method, const std::string& uri, const std::string& wwwAuth) {
        if (wwwAuth.rfind("Digest", 0) == 0 || wwwAuth.find("Digest") != std::string::npos) {
            auto param = [&](const char* key) -> std::string {
                std::string k = std::string(key) + "=\"";
                size_t p = wwwAuth.find(k);
                if (p == std::string::npos) {
                    k = std::string(key) + "=";
                    p = wwwAuth.find(k);
                    if (p == std::string::npos) return "";
                    p += k.size();
                    size_t e = wwwAuth.find_first_of(", ", p);
                    return wwwAuth.substr(p, e == std::string::npos ? std::string::npos : e - p);
                }
                p += k.size();
                size_t e = wwwAuth.find('"', p);
                return e == std::string::npos ? "" : wwwAuth.substr(p, e - p);
            };
            std::string realm = param("realm"), nonce = param("nonce"), qop = param("qop");
            if (realm.empty() || nonce.empty()) return false;
            std::string ha1 = md5Hex(u_.user + ":" + realm + ":" + u_.pass);
            std::string ha2 = md5Hex(std::string(method) + ":" + uri);
            std::string resp;
            std::string extra;
            if (!qop.empty()) {
                std::string nc = "00000001", cnonce = "l4cam0001";
                resp = md5Hex(ha1 + ":" + nonce + ":" + nc + ":" + cnonce + ":" + qop + ":" + ha2);
                extra = ", qop=" + qop + ", nc=" + nc + ", cnonce=\"" + cnonce + "\"";
            } else {
                resp = md5Hex(ha1 + ":" + nonce + ":" + ha2);
            }
            authHeader_ = "Authorization: Digest username=\"" + u_.user + "\", realm=\"" + realm +
                          "\", nonce=\"" + nonce + "\", uri=\"" + uri + "\", response=\"" + resp +
                          "\"" + extra + "\r\n";
            return true;
        }
        if (wwwAuth.find("Basic") != std::string::npos) {
            std::string cred = u_.user + ":" + u_.pass;
            authHeader_ = "Authorization: Basic " +
                          base64Enc((const uint8_t*)cred.data(), cred.size()) + "\r\n";
            return true;
        }
        return false;
    }

    bool sendAll(const std::string& s) {
        size_t off = 0;
        while (off < s.size()) {
            ssize_t n = send(fd_, s.data() + off, s.size() - off, MSG_NOSIGNAL);
            if (n < 0) { if (errno == EINTR) continue; return false; }
            off += (size_t)n;
        }
        return true;
    }
    // One recv round: 1 = data appended, 0 = timeout/no data, -1 = EOF/error.
    int fillBuf() {
        char tmp[65536];
        ssize_t n = recv(fd_, tmp, sizeof(tmp), 0);
        if (n > 0) { buf_.append(tmp, (size_t)n); lastDataMs_ = nowMs(); return 1; }
        if (n == 0) return -1;
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) return 0;
        return -1;
    }
    // Consume one buffered message. Returns 1 = message handled,
    // 0 = need more bytes, -1 = stream dead.
    int parseOne(std::string* respBody, int* respStatus, std::string* respWwwAuth,
                 std::string* respSession) {
        while (true) {
            if (buf_.empty()) return 0;
            if ((uint8_t)buf_[0] == '$') {
                if (buf_.size() < 4) return 0;
                size_t len = ((size_t)(uint8_t)buf_[2] << 8) | (uint8_t)buf_[3];
                if (buf_.size() < 4 + len) return 0;
                uint8_t channel = (uint8_t)buf_[1];
                std::string payload = buf_.substr(4, len);
                buf_.erase(0, 4 + len);
                if (channel == 0) handleRtp((const uint8_t*)payload.data(), payload.size());
                return 1;
            }
            if (buf_.rfind("RTSP/", 0) == 0) {
                size_t he = buf_.find("\r\n\r\n");
                if (he == std::string::npos) return 0;
                std::string head = buf_.substr(0, he);
                int clen = 0;
                size_t cp = head.find("Content-Length:");
                if (cp == std::string::npos) cp = head.find("content-length:");
                if (cp != std::string::npos) clen = atoi(head.c_str() + cp + 15);
                if (buf_.size() < he + 4 + (size_t)clen) return 0;
                if (respBody) *respBody = buf_.substr(he + 4, (size_t)clen);
                if (respStatus) {
                    size_t sp = head.find(' ');
                    *respStatus = sp == std::string::npos ? 0 : atoi(head.c_str() + sp + 1);
                }
                auto hdrVal = [&](const char* name) -> std::string {
                    size_t p = head.find(std::string("\r\n") + name + ":");
                    if (p == std::string::npos && head.rfind(std::string(name) + ":", 0) != 0) return "";
                    if (p == std::string::npos) p = 0; else p += 2;
                    p += strlen(name) + 1;
                    while (p < head.size() && (head[p] == ' ' || head[p] == '\t')) p++;
                    size_t e = head.find("\r\n", p);
                    return head.substr(p, e == std::string::npos ? std::string::npos : e - p);
                };
                if (respWwwAuth) *respWwwAuth = hdrVal("WWW-Authenticate");
                if (respSession) *respSession = hdrVal("Session");
                lastWwwAuth_ = hdrVal("WWW-Authenticate");
                buf_.erase(0, he + 4 + (size_t)clen);
                return 1;
            }
            buf_.erase(0, 1);  // resync: drop one byte
        }
    }
    bool request(const char* method, const std::string& uri, const std::string& extra,
                 int* statusOut, std::string* bodyOut, std::string* wwwAuthOut,
                 std::string* sessionOut = nullptr) {
        std::string req = std::string(method) + " " + uri + " RTSP/1.0\r\nCSeq: " +
                          std::to_string(++cseq_) + "\r\nUser-Agent: l4-cam/1.0\r\n" +
                          authHeader_ + extra + "\r\n";
        if (!sendAll(req)) return false;
        int64_t deadline = nowMs() + 10000;
        while (!stop_.load() && nowMs() < deadline) {
            std::string body; int status = 0; std::string wa, sess;
            int r = parseOne(&body, &status, &wa, &sess);
            if (r == 1 && status != 0) {
                if (statusOut) *statusOut = status;
                if (bodyOut) *bodyOut = body;
                if (wwwAuthOut) *wwwAuthOut = wa;
                if (sessionOut) *sessionOut = sess;
                return true;
            }
            if (r == 0) { if (fillBuf() < 0) return false; }
        }
        return false;
    }
    void streamLoop() {
        lastDataMs_ = nowMs();
        int64_t lastKeepalive = nowMs();
        while (!stop_.load()) {
            int r = parseOne(nullptr, nullptr, nullptr, nullptr);
            if (r == 0) {
                if (fillBuf() < 0) { SERR("rtsp: connection closed by server"); return; }
                if (nowMs() - lastDataMs_ > 60000) { SERR("rtsp: no data for 60s, dropping"); return; }
                if (nowMs() - lastKeepalive > 25000 && !session_.empty()) {
                    lastKeepalive = nowMs();
                    int st = 0;
                    request("OPTIONS", url_, "Session: " + session_ + "\r\n", &st, nullptr, nullptr);
                }
            }
        }
    }
    void handleRtp(const uint8_t* p, size_t n) {
        if (n < 12 || (p[0] >> 6) != 2) return;
        int cc = p[0] & 0x0F;
        bool ext = p[0] & 0x10, pad = p[0] & 0x20;
        bool marker = p[1] & 0x80;
        size_t hdr = 12 + 4 * (size_t)cc;
        if (ext) {
            if (n < hdr + 4) return;
            size_t words = ((size_t)p[hdr + 2] << 8) | p[hdr + 3];
            hdr += 4 + 4 * words;
        }
        if (n <= hdr) return;
        size_t end = n;
        if (pad) { size_t padLen = p[n - 1]; if (padLen >= end - hdr) return; end -= padLen; }
        handleH264(p + hdr, end - hdr, marker);
    }
    void handleH264(const uint8_t* p, size_t n, bool marker) {
        if (n == 0) return;
        int type = p[0] & 0x1F;
        if (type >= 1 && type <= 23) {
            pump_.feedNal(p, n);
        } else if (type == 24) {  // STAP-A
            size_t off = 1;
            while (off + 2 <= n) {
                size_t len = ((size_t)p[off] << 8) | p[off + 1];
                off += 2;
                if (off + len > n) return;
                pump_.feedNal(p + off, len);
                off += len;
            }
        } else if (type == 28) {  // FU-A
            if (n < 2) return;
            bool s = p[1] & 0x80, e = p[1] & 0x40;
            if (s) { fu_.clear(); fu_.push_back((uint8_t)((p[0] & 0xE0) | (p[1] & 0x1F))); }
            if (!fu_.empty()) fu_.insert(fu_.end(), p + 2, p + n);
            if (e && !fu_.empty()) { pump_.feedNal(fu_.data(), fu_.size()); fu_.clear(); }
        }
        if (marker) { pump_.endAccessUnit(); dec_.drain(0); }
    }

    std::string url_;
    RtspUrl u_;
    std::atomic<bool>& stop_;
    H264Decoder& dec_;
    NalPump pump_;
    int fd_ = -1;
    int cseq_ = 0;
    std::string buf_, session_, authHeader_, lastWwwAuth_;
    std::vector<uint8_t> fu_;
    int64_t lastDataMs_ = 0;
};

static void rtspRun(const std::string& url, std::atomic<bool>& stop, H264Decoder& dec) {
    RtspUrl u;
    if (!parseRtspUrl(url, &u)) { SERR("rtsp: bad url %s", url.c_str()); return; }
    while (!stop.load()) {
        RtspSession sess(url, u, stop, dec);
        sess.run();
        if (stop.load()) break;
        SLOG("rtsp: session ended, reconnecting in 3s");
        for (int i = 0; i < 30 && !stop.load(); i++)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// ------------------------------------------------------------ StreamSource
struct StreamSource::Impl {
    std::mutex m;
    std::shared_ptr<const StreamFrame> latest;
    std::thread manager;
    bool started = false;
    void publish(std::shared_ptr<StreamFrame> f) {
        std::lock_guard<std::mutex> lk(m);
        latest = std::move(f);
    }
};

StreamSource& StreamSource::instance() {
    static StreamSource s;
    return s;
}

std::shared_ptr<const StreamFrame> StreamSource::snapshot() {
    if (!impl_) return nullptr;
    std::lock_guard<std::mutex> lk(impl_->m);
    auto f = impl_->latest;
    if (f && nowMs() - f->boottimeMs <= 3000) return f;
    return nullptr;
}

void StreamSource::ensureStarted() {
    if (!impl_) impl_ = std::make_unique<Impl>();
    if (impl_->started) return;
    impl_->started = true;
    Impl* impl = impl_.get();
    impl->manager = std::thread([impl]() {
        std::string current;
        std::thread worker;
        std::atomic<bool> stop{false};
        auto stopWorker = [&]() {
            if (worker.joinable()) { stop.store(true); worker.join(); }
            stop.store(false);
        };
        while (true) {
            char buf[1024];
            property_get("persist.l4.camera.source", buf, "");
            std::string want = buf;
            if (want != current) {
                stopWorker();
                current = want;
                if (current.empty()) {
                    SLOG("stream source cleared");
                } else {
                    std::string url = current;
                    worker = std::thread([impl, url, &stop]() {
                        H264Decoder dec;
                        dec.sink_ = [impl](std::shared_ptr<StreamFrame> f) { impl->publish(f); };
                        if (url.rfind("rtsp://", 0) == 0) {
                            SLOG("rtsp pipeline start: %s", url.c_str());
                            rtspRun(url, stop, dec);
                        } else if (url.find(".m3u8") != std::string::npos ||
                            url.rfind("http://", 0) == 0 || url.rfind("https://", 0) == 0) {
                            SLOG("hls pipeline start: %s", url.c_str());
                            hlsRun(url, stop, dec);
                        } else {
                            SERR("unsupported stream source: %s", url.c_str());
                            while (!stop.load()) std::this_thread::sleep_for(std::chrono::seconds(1));
                        }
                        SLOG("stream pipeline stopped");
                    });
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });
    impl->manager.detach();
}
