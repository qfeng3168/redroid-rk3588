// L4-M4 virtual camera: network stream source (HLS now, RTSP later).
// When persist.l4.camera.source holds an .m3u8 / rtsp URL, a pipeline
// thread pulls the stream, soft-decodes H.264 via AMediaCodec and keeps
// the latest frame as RGB888. fillStreamBuffer samples it when fresh;
// otherwise the synthetic pattern is used (fallback).
#pragma once
#include <cstdint>
#include <memory>
#include <vector>

struct StreamFrame {
    int width = 0, height = 0;
    std::vector<uint8_t> rgb;  // width*height*3
    int64_t boottimeMs = 0;
};

class StreamSource {
  public:
    static StreamSource& instance();
    // Latest decoded frame, or nullptr if none / stale (>3s old).
    std::shared_ptr<const StreamFrame> snapshot();
    // Start the manager thread (idempotent).
    void ensureStarted();

  private:
    StreamSource() = default;
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
