/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "audio_hw_l4"
//#define LOG_NDEBUG 0

#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <log/log.h>
#include <math.h>
#include <sys/system_properties.h>

/* L4-M5 virtual microphone.
 * Input content is selected by system properties (read at stream open):
 *   persist.l4.mic.mode  sine | silence | wav      (default sine)
 *   persist.l4.mic.freq  sine frequency Hz          (default 1000)
 *   persist.l4.mic.gain  amplitude 0.0 - 1.0        (default 0.5)
 *   persist.l4.mic.wav   wav file path              (default /data/l4/mic.wav,
 *                          auto-fallback /data/misc/audioserver/l4mic.wav
 *                          for SELinux-enforcing guests)
 * Output streams discard samples (headless instances have no speaker);
 * pacing matches a real device so AudioFlinger timing stays sane. */

#include <hardware/audio.h>
#include <hardware/hardware.h>
#include <system/audio.h>

#define STUB_DEFAULT_SAMPLE_RATE   48000
#define STUB_DEFAULT_AUDIO_FORMAT  AUDIO_FORMAT_PCM_16_BIT

#define STUB_INPUT_BUFFER_MILLISECONDS  20
#define STUB_INPUT_DEFAULT_CHANNEL_MASK AUDIO_CHANNEL_IN_STEREO

#define STUB_OUTPUT_BUFFER_MILLISECONDS  10
#define STUB_OUTPUT_DEFAULT_CHANNEL_MASK AUDIO_CHANNEL_OUT_STEREO

struct stub_audio_device {
    struct audio_hw_device device;
};

struct stub_stream_out {
    struct audio_stream_out stream;
    int64_t last_write_time_us;
    uint32_t sample_rate;
    audio_channel_mask_t channel_mask;
    audio_format_t format;
    size_t frame_count;
};

struct stub_stream_in {
    struct audio_stream_in stream;
    int64_t last_read_time_us;
    uint32_t sample_rate;
    audio_channel_mask_t channel_mask;
    audio_format_t format;
    size_t frame_count;
    /* L4 mic generator state */
    int mode;                /* 0 sine, 1 silence, 2 wav */
    uint32_t phase;          /* sine phase accumulator (2^32 = 2*pi) */
    uint32_t phase_inc;
    float gain;              /* prop gain * framework in_set_gain */
    float fw_gain;
    int16_t lut[1024];       /* one sine period, peak = gain * 32767 */
    int16_t *wav;            /* interleaved PCM16, looped */
    size_t wav_frames;
    uint32_t wav_rate;
    size_t wav_channels;
    size_t wav_pos;          /* frame cursor */
};

static uint32_t out_get_sample_rate(const struct audio_stream *stream)
{
    const struct stub_stream_out *out = (const struct stub_stream_out *)stream;

    ALOGV("out_get_sample_rate: %u", out->sample_rate);
    return out->sample_rate;
}

static int out_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    struct stub_stream_out *out = (struct stub_stream_out *)stream;

    ALOGV("out_set_sample_rate: %d", rate);
    out->sample_rate = rate;
    return 0;
}

static size_t out_get_buffer_size(const struct audio_stream *stream)
{
    const struct stub_stream_out *out = (const struct stub_stream_out *)stream;
    size_t buffer_size = out->frame_count *
                         audio_stream_out_frame_size(&out->stream);

    ALOGV("out_get_buffer_size: %zu", buffer_size);
    return buffer_size;
}

static audio_channel_mask_t out_get_channels(const struct audio_stream *stream)
{
    const struct stub_stream_out *out = (const struct stub_stream_out *)stream;

    ALOGV("out_get_channels: %x", out->channel_mask);
    return out->channel_mask;
}

static audio_format_t out_get_format(const struct audio_stream *stream)
{
    const struct stub_stream_out *out = (const struct stub_stream_out *)stream;

    ALOGV("out_get_format: %d", out->format);
    return out->format;
}

static int out_set_format(struct audio_stream *stream, audio_format_t format)
{
    struct stub_stream_out *out = (struct stub_stream_out *)stream;

    ALOGV("out_set_format: %d", format);
    out->format = format;
    return 0;
}

static int out_standby(struct audio_stream *stream)
{
    ALOGV("out_standby");
    // out->last_write_time_us = 0; unnecessary as a stale write time has same effect
    return 0;
}

static int out_dump(const struct audio_stream *stream, int fd)
{
    ALOGV("out_dump");
    return 0;
}

static int out_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    ALOGV("out_set_parameters");
    return 0;
}

static char * out_get_parameters(const struct audio_stream *stream, const char *keys)
{
    ALOGV("out_get_parameters");
    return strdup("");
}

static uint32_t out_get_latency(const struct audio_stream_out *stream)
{
    ALOGV("out_get_latency");
    return STUB_OUTPUT_BUFFER_MILLISECONDS;
}

static int out_set_volume(struct audio_stream_out *stream, float left,
                          float right)
{
    ALOGV("out_set_volume: Left:%f Right:%f", left, right);
    return 0;
}

static ssize_t out_write(struct audio_stream_out *stream, const void* buffer,
                         size_t bytes)
{
    ALOGV("out_write: bytes: %zu", bytes);

    /* XXX: fake timing for audio output */
    struct stub_stream_out *out = (struct stub_stream_out *)stream;
    struct timespec t = { .tv_sec = 0, .tv_nsec = 0 };
    clock_gettime(CLOCK_MONOTONIC, &t);
    const int64_t now = (t.tv_sec * 1000000000LL + t.tv_nsec) / 1000;
    const int64_t elapsed_time_since_last_write = now - out->last_write_time_us;
    int64_t sleep_time = bytes * 1000000LL / audio_stream_out_frame_size(stream) /
               out_get_sample_rate(&stream->common) - elapsed_time_since_last_write;
    if (sleep_time > 0) {
        usleep(sleep_time);
    } else {
        // we don't sleep when we exit standby (this is typical for a real alsa buffer).
        sleep_time = 0;
    }
    out->last_write_time_us = now + sleep_time;
    // last_write_time_us is an approximation of when the (simulated) alsa
    // buffer is believed completely full. The usleep above waits for more space
    // in the buffer, but by the end of the sleep the buffer is considered
    // topped-off.
    //
    // On the subsequent out_write(), we measure the elapsed time spent in
    // the mixer. This is subtracted from the sleep estimate based on frames,
    // thereby accounting for drain in the alsa buffer during mixing.
    // This is a crude approximation; we don't handle underruns precisely.
    return bytes;
}

static int out_get_render_position(const struct audio_stream_out *stream,
                                   uint32_t *dsp_frames)
{
    *dsp_frames = 0;
    ALOGV("out_get_render_position: dsp_frames: %p", dsp_frames);
    return -EINVAL;
}

static int out_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    ALOGV("out_add_audio_effect: %p", effect);
    return 0;
}

static int out_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    ALOGV("out_remove_audio_effect: %p", effect);
    return 0;
}

static int out_get_next_write_timestamp(const struct audio_stream_out *stream,
                                        int64_t *timestamp)
{
    *timestamp = 0;
    ALOGV("out_get_next_write_timestamp: %ld", (long int)(*timestamp));
    return -EINVAL;
}

/** audio_stream_in implementation **/
static uint32_t in_get_sample_rate(const struct audio_stream *stream)
{
    const struct stub_stream_in *in = (const struct stub_stream_in *)stream;

    ALOGV("in_get_sample_rate: %u", in->sample_rate);
    return in->sample_rate;
}

static int in_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    struct stub_stream_in *in = (struct stub_stream_in *)stream;

    ALOGV("in_set_sample_rate: %u", rate);
    in->sample_rate = rate;
    return 0;
}

static size_t in_get_buffer_size(const struct audio_stream *stream)
{
    const struct stub_stream_in *in = (const struct stub_stream_in *)stream;
    size_t buffer_size = in->frame_count *
                         audio_stream_in_frame_size(&in->stream);

    ALOGV("in_get_buffer_size: %zu", buffer_size);
    return buffer_size;
}

static audio_channel_mask_t in_get_channels(const struct audio_stream *stream)
{
    const struct stub_stream_in *in = (const struct stub_stream_in *)stream;

    ALOGV("in_get_channels: %x", in->channel_mask);
    return in->channel_mask;
}

static audio_format_t in_get_format(const struct audio_stream *stream)
{
    const struct stub_stream_in *in = (const struct stub_stream_in *)stream;

    ALOGV("in_get_format: %d", in->format);
    return in->format;
}

static int in_set_format(struct audio_stream *stream, audio_format_t format)
{
    struct stub_stream_in *in = (struct stub_stream_in *)stream;

    ALOGV("in_set_format: %d", format);
    in->format = format;
    return 0;
}

static int in_standby(struct audio_stream *stream)
{
    struct stub_stream_in *in = (struct stub_stream_in *)stream;
    in->last_read_time_us = 0;
    return 0;
}

static int in_dump(const struct audio_stream *stream, int fd)
{
    return 0;
}

static int in_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    return 0;
}

static char * in_get_parameters(const struct audio_stream *stream,
                                const char *keys)
{
    return strdup("");
}

static int in_set_gain(struct audio_stream_in *stream, float gain)
{
    struct stub_stream_in *in = (struct stub_stream_in *)stream;
    in->fw_gain = gain;
    return 0;
}

static int l4_prop_int(const char *key, int dflt) {
    char v[PROP_VALUE_MAX];
    if (__system_property_get(key, v) <= 0) return dflt;
    int n = atoi(v);
    return n > 0 ? n : dflt;
}
static float l4_prop_gain(void) {
    char v[PROP_VALUE_MAX];
    if (__system_property_get("persist.l4.mic.gain", v) <= 0) return 0.5f;
    float g = (float)atof(v);
    if (g < 0.0f) g = 0.0f;
    if (g > 1.0f) g = 1.0f;
    return g;
}
/* Load a PCM16 WAV (any rate/channels) fully into memory.
 * audioserver is confined by SELinux to audio data files, so the wav
 * must live somewhere it may read: default /data/l4/mic.wav only works
 * in permissive guests; the reliable home is the audio cache dir. */
static const char *L4_WAV_CANDIDATES[] = {
    "/data/misc/audioserver/l4mic.wav",
    "/data/l4/mic.wav",
};
static int l4_load_wav(struct stub_stream_in *in, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f && strcmp(path, "/data/l4/mic.wav") == 0) {
        for (size_t i = 0; i < sizeof(L4_WAV_CANDIDATES) / sizeof(L4_WAV_CANDIDATES[0]) && !f; i++)
            f = fopen(L4_WAV_CANDIDATES[i], "rb");
    }
    if (!f) { ALOGW("l4mic: cannot open wav %s", path); return -1; }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size < 44 || size > 64 * 1024 * 1024) { fclose(f); return -1; }
    uint8_t *raw = malloc((size_t)size);
    if (!raw || fread(raw, 1, (size_t)size, f) != (size_t)size) {
        free(raw); fclose(f); return -1;
    }
    fclose(f);
    if (memcmp(raw, "RIFF", 4) != 0 || memcmp(raw + 8, "WAVE", 4) != 0) { free(raw); return -1; }
    uint32_t rate = 0; uint16_t channels = 0, bits = 0, audiofmt = 0;
    const uint8_t *data = NULL; uint32_t data_len = 0;
    for (size_t off = 12; off + 8 <= (size_t)size; ) {
        uint32_t clen = (uint32_t)raw[off + 4] | ((uint32_t)raw[off + 5] << 8) |
                        ((uint32_t)raw[off + 6] << 16) | ((uint32_t)raw[off + 7] << 24);
        if (off + 8 + clen > (size_t)size) break;
        if (memcmp(raw + off, "fmt ", 4) == 0 && clen >= 16) {
            audiofmt = (uint16_t)raw[off + 8] | ((uint16_t)raw[off + 9] << 8);
            channels = (uint16_t)raw[off + 10] | ((uint16_t)raw[off + 11] << 8);
            rate = (uint32_t)raw[off + 12] | ((uint32_t)raw[off + 13] << 8) |
                   ((uint32_t)raw[off + 14] << 16) | ((uint32_t)raw[off + 15] << 24);
            bits = (uint16_t)raw[off + 22] | ((uint16_t)raw[off + 23] << 8);
        } else if (memcmp(raw + off, "data", 4) == 0) {
            data = raw + off + 8; data_len = clen;
        }
        off += 8 + clen + (clen & 1);
    }
    if (!data || audiofmt != 1 || bits != 16 || channels < 1 || channels > 2 || rate == 0) {
        ALOGW("l4mic: unsupported wav (fmt=%u bits=%u ch=%u rate=%u)",
              audiofmt, bits, channels, rate);
        free(raw); return -1;
    }
    in->wav = malloc(data_len);
    if (!in->wav) { free(raw); return -1; }
    memcpy(in->wav, data, data_len);
    in->wav_frames = data_len / (2 * channels);
    in->wav_rate = rate;
    in->wav_channels = channels;
    in->wav_pos = 0;
    free(raw);
    ALOGI("l4mic: wav loaded %s: %zu frames @%uHz ch=%zu", path, in->wav_frames, rate, in->wav_channels);
    return 0;
}
static void l4_setup_source(struct stub_stream_in *in) {
    /* NB: __system_property_get clears the buffer when the property is
     * absent, so only trust the buffer when the return value is > 0. */
    char mode[PROP_VALUE_MAX] = "sine";
    char pv[PROP_VALUE_MAX];
    if (__system_property_get("persist.l4.mic.mode", pv) > 0 && pv[0])
        strncpy(mode, pv, sizeof(mode) - 1);
    in->fw_gain = 1.0f;
    in->gain = l4_prop_gain();
    in->mode = 0;
    if (strcmp(mode, "silence") == 0) {
        in->mode = 1;
    } else if (strcmp(mode, "wav") == 0) {
        char path[PROP_VALUE_MAX] = "/data/l4/mic.wav";
        if (__system_property_get("persist.l4.mic.wav", pv) > 0 && pv[0])
            strncpy(path, pv, sizeof(path) - 1);
        if (l4_load_wav(in, path) == 0) in->mode = 2;
        else ALOGW("l4mic: wav mode requested but load failed, falling back to sine");
    }
    if (in->mode == 0) {
        int freq = l4_prop_int("persist.l4.mic.freq", 1000);
        if (freq > (int)in->sample_rate / 2) freq = in->sample_rate / 4;
        in->phase = 0;
        in->phase_inc = (uint32_t)(((uint64_t)freq << 32) / in->sample_rate);
        float amp = in->gain * 32767.0f;
        for (int i = 0; i < 1024; i++)
            in->lut[i] = (int16_t)(sinf((float)i * 6.2831853f / 1024.0f) * amp);
        ALOGI("l4mic: sine %d Hz @%uHz gain=%.2f", freq, in->sample_rate, in->gain);
    } else if (in->mode == 1) {
        ALOGI("l4mic: silence @%uHz", in->sample_rate);
    }
}
/* Generate one frame's worth of samples into all channels. */
static int16_t l4_next_sample(struct stub_stream_in *in) {
    if (in->mode == 1) return 0;
    if (in->mode == 2 && in->wav) {
        /* nearest-neighbour rate conversion + channel fold-down */
        size_t src_frame = (size_t)((uint64_t)in->wav_pos * in->wav_rate / in->sample_rate) % in->wav_frames;
        const int16_t *s = in->wav + src_frame * in->wav_channels;
        int v = s[0];
        if (in->wav_channels == 2) v = (s[0] + s[1]) / 2;
        in->wav_pos++;
        return (int16_t)(v * in->gain * in->fw_gain);
    }
    in->phase += in->phase_inc;
    int16_t s = in->lut[(in->phase >> 22) & 1023];
    return (int16_t)(s * in->fw_gain);
}
static void l4_fill(struct stub_stream_in *in, void *buffer, size_t bytes) {
    size_t frame_size = audio_stream_in_frame_size(&in->stream);
    size_t frames = bytes / frame_size;
    size_t channels = audio_channel_count_from_in_mask(in->channel_mask);
    if (in->format == AUDIO_FORMAT_PCM_FLOAT) {
        float *out = (float *)buffer;
        for (size_t i = 0; i < frames; i++) {
            float v = l4_next_sample(in) / 32768.0f;
            for (size_t c = 0; c < channels; c++) *out++ = v;
        }
    } else if (in->format == AUDIO_FORMAT_PCM_8_24_BIT) {
        int32_t *out = (int32_t *)buffer;
        for (size_t i = 0; i < frames; i++) {
            int32_t v = (int32_t)l4_next_sample(in) << 8;
            for (size_t c = 0; c < channels; c++) *out++ = v;
        }
    } else if (in->format == AUDIO_FORMAT_PCM_16_BIT) {
        int16_t *out = (int16_t *)buffer;
        for (size_t i = 0; i < frames; i++) {
            int16_t v = l4_next_sample(in);
            for (size_t c = 0; c < channels; c++) *out++ = v;
        }
    } else {
        memset(buffer, 0, bytes);  /* unhandled format: paced silence */
    }
}

static ssize_t in_read(struct audio_stream_in *stream, void* buffer,
                       size_t bytes)
{
    ALOGV("in_read: bytes %zu", bytes);

    /* XXX: fake timing for audio input */
    struct stub_stream_in *in = (struct stub_stream_in *)stream;
    struct timespec t = { .tv_sec = 0, .tv_nsec = 0 };
    clock_gettime(CLOCK_MONOTONIC, &t);
    const int64_t now = (t.tv_sec * 1000000000LL + t.tv_nsec) / 1000;

    // we do a full sleep when exiting standby.
    const bool standby = in->last_read_time_us == 0;
    const int64_t elapsed_time_since_last_read = standby ?
            0 : now - in->last_read_time_us;
    int64_t sleep_time = bytes * 1000000LL / audio_stream_in_frame_size(stream) /
            in_get_sample_rate(&stream->common) - elapsed_time_since_last_read;
    if (sleep_time > 0) {
        usleep(sleep_time);
    } else {
        sleep_time = 0;
    }
    in->last_read_time_us = now + sleep_time;
    l4_fill(in, buffer, bytes);
    return bytes;
    // last_read_time_us is an approximation of when the (simulated) alsa
    // buffer is drained by the read, and is empty.
}

static uint32_t in_get_input_frames_lost(struct audio_stream_in *stream)
{
    return 0;
}

static int in_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    return 0;
}

static int in_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    return 0;
}

static size_t samples_per_milliseconds(size_t milliseconds,
                                       uint32_t sample_rate,
                                       size_t channel_count)
{
    return milliseconds * sample_rate * channel_count / 1000;
}

static int adev_open_output_stream(struct audio_hw_device *dev,
                                   audio_io_handle_t handle,
                                   audio_devices_t devices,
                                   audio_output_flags_t flags,
                                   struct audio_config *config,
                                   struct audio_stream_out **stream_out,
                                   const char *address __unused)
{
    ALOGV("adev_open_output_stream...");

    *stream_out = NULL;
    struct stub_stream_out *out =
            (struct stub_stream_out *)calloc(1, sizeof(struct stub_stream_out));
    if (!out)
        return -ENOMEM;

    out->stream.common.get_sample_rate = out_get_sample_rate;
    out->stream.common.set_sample_rate = out_set_sample_rate;
    out->stream.common.get_buffer_size = out_get_buffer_size;
    out->stream.common.get_channels = out_get_channels;
    out->stream.common.get_format = out_get_format;
    out->stream.common.set_format = out_set_format;
    out->stream.common.standby = out_standby;
    out->stream.common.dump = out_dump;
    out->stream.common.set_parameters = out_set_parameters;
    out->stream.common.get_parameters = out_get_parameters;
    out->stream.common.add_audio_effect = out_add_audio_effect;
    out->stream.common.remove_audio_effect = out_remove_audio_effect;
    out->stream.get_latency = out_get_latency;
    out->stream.set_volume = out_set_volume;
    out->stream.write = out_write;
    out->stream.get_render_position = out_get_render_position;
    out->stream.get_next_write_timestamp = out_get_next_write_timestamp;
    out->sample_rate = config->sample_rate;
    if (out->sample_rate == 0)
        out->sample_rate = STUB_DEFAULT_SAMPLE_RATE;
    out->channel_mask = config->channel_mask;
    if (out->channel_mask == AUDIO_CHANNEL_NONE)
        out->channel_mask = STUB_OUTPUT_DEFAULT_CHANNEL_MASK;
    out->format = config->format;
    if (out->format == AUDIO_FORMAT_DEFAULT)
        out->format = STUB_DEFAULT_AUDIO_FORMAT;
    out->frame_count = samples_per_milliseconds(
                           STUB_OUTPUT_BUFFER_MILLISECONDS,
                           out->sample_rate, 1);

    ALOGV("adev_open_output_stream: sample_rate: %u, channels: %x, format: %d,"
          " frames: %zu", out->sample_rate, out->channel_mask, out->format,
          out->frame_count);
    *stream_out = &out->stream;
    return 0;
}

static void adev_close_output_stream(struct audio_hw_device *dev,
                                     struct audio_stream_out *stream)
{
    ALOGV("adev_close_output_stream...");
    free(stream);
}

static int adev_set_parameters(struct audio_hw_device *dev, const char *kvpairs)
{
    ALOGV("adev_set_parameters");
    return -ENOSYS;
}

static char * adev_get_parameters(const struct audio_hw_device *dev,
                                  const char *keys)
{
    ALOGV("adev_get_parameters");
    return strdup("");
}

static int adev_init_check(const struct audio_hw_device *dev)
{
    ALOGV("adev_init_check");
    return 0;
}

static int adev_set_voice_volume(struct audio_hw_device *dev, float volume)
{
    ALOGV("adev_set_voice_volume: %f", volume);
    return -ENOSYS;
}

static int adev_set_master_volume(struct audio_hw_device *dev, float volume)
{
    ALOGV("adev_set_master_volume: %f", volume);
    return -ENOSYS;
}

static int adev_get_master_volume(struct audio_hw_device *dev, float *volume)
{
    ALOGV("adev_get_master_volume: %f", *volume);
    return -ENOSYS;
}

static int adev_set_master_mute(struct audio_hw_device *dev, bool muted)
{
    ALOGV("adev_set_master_mute: %d", muted);
    return -ENOSYS;
}

static int adev_get_master_mute(struct audio_hw_device *dev, bool *muted)
{
    ALOGV("adev_get_master_mute: %d", *muted);
    return -ENOSYS;
}

static int adev_set_mode(struct audio_hw_device *dev, audio_mode_t mode)
{
    ALOGV("adev_set_mode: %d", mode);
    return 0;
}

static int adev_set_mic_mute(struct audio_hw_device *dev, bool state)
{
    ALOGV("adev_set_mic_mute: %d",state);
    return -ENOSYS;
}

static int adev_get_mic_mute(const struct audio_hw_device *dev, bool *state)
{
    ALOGV("adev_get_mic_mute");
    return -ENOSYS;
}

static size_t adev_get_input_buffer_size(const struct audio_hw_device *dev,
                                         const struct audio_config *config)
{
    size_t buffer_size = samples_per_milliseconds(
                             STUB_INPUT_BUFFER_MILLISECONDS,
                             config->sample_rate,
                             audio_channel_count_from_in_mask(
                                 config->channel_mask));

    if (!audio_has_proportional_frames(config->format)) {
        // Since the audio data is not proportional choose an arbitrary size for
        // the buffer.
        buffer_size *= 4;
    } else {
        buffer_size *= audio_bytes_per_sample(config->format);
    }
    ALOGV("adev_get_input_buffer_size: %zu", buffer_size);
    return buffer_size;
}

static int adev_open_input_stream(struct audio_hw_device *dev,
                                  audio_io_handle_t handle,
                                  audio_devices_t devices,
                                  struct audio_config *config,
                                  struct audio_stream_in **stream_in,
                                  audio_input_flags_t flags __unused,
                                  const char *address __unused,
                                  audio_source_t source __unused)
{
    ALOGV("adev_open_input_stream...");

    *stream_in = NULL;
    struct stub_stream_in *in = (struct stub_stream_in *)calloc(1, sizeof(struct stub_stream_in));
    if (!in)
        return -ENOMEM;

    in->stream.common.get_sample_rate = in_get_sample_rate;
    in->stream.common.set_sample_rate = in_set_sample_rate;
    in->stream.common.get_buffer_size = in_get_buffer_size;
    in->stream.common.get_channels = in_get_channels;
    in->stream.common.get_format = in_get_format;
    in->stream.common.set_format = in_set_format;
    in->stream.common.standby = in_standby;
    in->stream.common.dump = in_dump;
    in->stream.common.set_parameters = in_set_parameters;
    in->stream.common.get_parameters = in_get_parameters;
    in->stream.common.add_audio_effect = in_add_audio_effect;
    in->stream.common.remove_audio_effect = in_remove_audio_effect;
    in->stream.set_gain = in_set_gain;
    in->stream.read = in_read;
    in->stream.get_input_frames_lost = in_get_input_frames_lost;
    in->sample_rate = config->sample_rate;
    if (in->sample_rate == 0)
        in->sample_rate = STUB_DEFAULT_SAMPLE_RATE;
    in->channel_mask = config->channel_mask;
    if (in->channel_mask == AUDIO_CHANNEL_NONE)
        in->channel_mask = STUB_INPUT_DEFAULT_CHANNEL_MASK;
    in->format = config->format;
    if (in->format == AUDIO_FORMAT_DEFAULT)
        in->format = STUB_DEFAULT_AUDIO_FORMAT;
    in->frame_count = samples_per_milliseconds(
                          STUB_INPUT_BUFFER_MILLISECONDS, in->sample_rate, 1);
    l4_setup_source(in);

    ALOGV("adev_open_input_stream: sample_rate: %u, channels: %x, format: %d,"
          "frames: %zu", in->sample_rate, in->channel_mask, in->format,
          in->frame_count);
    *stream_in = &in->stream;
    return 0;
}

static void adev_close_input_stream(struct audio_hw_device *dev,
                                   struct audio_stream_in *stream_in)
{
    struct stub_stream_in *in = (struct stub_stream_in *)stream_in;
    ALOGV("adev_close_input_stream...");
    if (in) { free(in->wav); free(in); }
    return;
}

static int adev_dump(const audio_hw_device_t *device, int fd)
{
    ALOGV("adev_dump");
    return 0;
}

static int adev_close(hw_device_t *device)
{
    ALOGV("adev_close");
    free(device);
    return 0;
}

static int adev_open(const hw_module_t* module, const char* name,
                     hw_device_t** device)
{
    ALOGV("adev_open: %s", name);

    struct stub_audio_device *adev;

    if (strcmp(name, AUDIO_HARDWARE_INTERFACE) != 0)
        return -EINVAL;

    adev = calloc(1, sizeof(struct stub_audio_device));
    if (!adev)
        return -ENOMEM;

    adev->device.common.tag = HARDWARE_DEVICE_TAG;
    adev->device.common.version = AUDIO_DEVICE_API_VERSION_2_0;
    adev->device.common.module = (struct hw_module_t *) module;
    adev->device.common.close = adev_close;

    adev->device.init_check = adev_init_check;
    adev->device.set_voice_volume = adev_set_voice_volume;
    adev->device.set_master_volume = adev_set_master_volume;
    adev->device.get_master_volume = adev_get_master_volume;
    adev->device.set_master_mute = adev_set_master_mute;
    adev->device.get_master_mute = adev_get_master_mute;
    adev->device.set_mode = adev_set_mode;
    adev->device.set_mic_mute = adev_set_mic_mute;
    adev->device.get_mic_mute = adev_get_mic_mute;
    adev->device.set_parameters = adev_set_parameters;
    adev->device.get_parameters = adev_get_parameters;
    adev->device.get_input_buffer_size = adev_get_input_buffer_size;
    adev->device.open_output_stream = adev_open_output_stream;
    adev->device.close_output_stream = adev_close_output_stream;
    adev->device.open_input_stream = adev_open_input_stream;
    adev->device.close_input_stream = adev_close_input_stream;
    adev->device.dump = adev_dump;

    *device = &adev->device.common;

    return 0;
}

static struct hw_module_methods_t hal_module_methods = {
    .open = adev_open,
};

struct audio_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = AUDIO_MODULE_API_VERSION_0_1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = AUDIO_HARDWARE_MODULE_ID,
        .name = "L4 virtual audio HAL (redroid-l4)",
        .author = "The Android Open Source Project",
        .methods = &hal_module_methods,
    },
};
