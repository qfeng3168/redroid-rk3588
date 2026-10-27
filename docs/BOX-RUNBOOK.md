# 盒上运行手册（G98 / RK3588，2026-10-27 实测跑通）

全链：CI 建 host 包 → CI 打容器镜像 → GHCR → 盒子经 1ms 镜像拉取 → docker run → launch_cvd。
宿主机（fnOS）不装任何包、不动网络配置；CVD 网络建在容器自己的 netns 里。

## 1. 拉镜像（盒子直连 Google/ghcr 都慢或超时，必须走 1ms）

```bash
docker pull ghcr.1ms.run/qfeng3168/cuttlefish-orchestration:rk3588        # 1.97GB ≈ 83s
docker tag ghcr.1ms.run/qfeng3168/cuttlefish-orchestration:rk3588 cuttlefish-orchestration:rk3588
docker pull ghcr.1ms.run/qfeng3168/cuttlefish-guest-images:16644040        # guest 镜像包（scratch 镜像）
docker create --name gi-tmp ghcr.1ms.run/qfeng3168/cuttlefish-guest-images:16644040 /bin/true
mkdir -p /vol2/cuttlefish/images && docker cp gi-tmp:/images/. /vol2/cuttlefish/images/ && docker rm gi-tmp
cd /vol2/cuttlefish/images && sha256sum -c SHA256SUMS
mkdir -p /vol2/cuttlefish/work && cd /vol2/cuttlefish/work
tar xzf ../images/cvd-host_package.tar.gz
unzip -o ../images/aosp_cf_arm64_only_phone-img-16644040.zip
```

## 2. 起 HO 容器

**`--ulimit nofile` 是生死线**：默认软限额 1024 会让 Android 的 crosvm 在 virtio_blk 建 async tube 时 EMFILE panic（exit 后不按 code 32 重启，实例假死、kernel.log 停在 U-Boot）。

```bash
docker run -d --name cvd-ho --privileged --ulimit nofile=524288:524288 \
  -v /vol2/cuttlefish:/cvd \
  -p 127.0.0.1:2080:2080 -p 127.0.0.1:2443:2443 \
  -p 127.0.0.1:1080:1080 -p 127.0.0.1:1443:1443 \
  cuttlefish-orchestration:rk3588
# HO 就绪判据：curl http://127.0.0.1:2080/ → 200（约 20s 内）
```

注：实例数据放 /vol2（NVMe，383/694 MB/s）；Docker 数据根在 /vol1（SATA，196/251 MB/s），别把实例放默认 overlay 里。

## 3. 拉实例（容器内，软件渲染基线）

```bash
docker exec cvd-ho sh -c 'cd /cvd/work && HOME=/cvd/work ./bin/launch_cvd -daemon \
  -report_anonymous_usage_stats=n -gpu_mode=guest_swiftshader \
  -memory_mb=4096 -cpus=4 -resume=false'
# 验证 + 计时：轮询 ./bin/adb -s localhost:6520 shell getprop sys.boot_completed → 1
# 实测冷启动（-resume=false）47s 到 boot_completed（Android 17，CP2A.260605.016）
docker exec cvd-ho sh -c 'cd /cvd/work && HOME=/cvd/work ./bin/stop_cvd'   # 停实例
```

## 已知现象

- 图形探测在容器内报 EGL/Vulkan 不可用属正常：软件渲染走 guest_swiftshader，与宿主 Mali 无关；gfxstream 硬件渲染是 M4 探索项。
- `docker exec` 断开不会杀掉 -daemon 的实例进程组（实测 SSH 会话被掐后实例继续启动）。
- webRTC/vsock 的 connect 报错刷 launcher.log = guest 没起来时的连锁噪音，先查 crosvm 自己的日志行（`grep "^crosvm " logs/launcher.log`）。

## Optimized launch profile (2026-10-27, measured)
Baseline 4G/full-peripherals: 4.3 GiB steady, 47 s boot. Optimized: **2.68 GiB steady, 35 s boot**.
- `-memory_mb=2048` (A17 practical floor: guest MemAvailable ~0.7 GiB at 2G)
- Trims that WORK via flags: `-enable_host_bluetooth=false -enable_host_nfc=false -enable_host_uwb=false -enable_modem_simulator=false -record_screen=false` (casimir/modem/screen_recording processes disappear; saves ~50 MiB fleet RSS)
- netsimd (~26 MiB) CANNOT be disabled by flags in this build: generated config has `start_netsim: true` + `has_bluetooth: true` from the phone device config; `-enable_host_bluetooth=false` only sets `enable_host_bluetooth_connector: false`; `-netsim=false` is a no-op for this. Do not hand-edit the generated cuttlefish_config.json.
- Fleet accounting (RSS): Android crosvm = guest RAM; OpenWrt crosvm ~230 MiB is a second VM (guest router/Wi-Fi AP); all other ~50 host processes ≈ 355 MiB total, HO itself only ~6 MiB.

## M4 verdict: gfxstream HW rendering NOT viable on stock G98 stack (2026-10-27, measured)
Explored all three gfxstream routes against the Mali-G610 (ARM g24p0 blob, kbase /dev/mali0 only):
- **Vulkan plumbing WORKS**: staging the host Mali Vulkan stack (libMaliVulkan.so.1 + libmali.so.1.9.0 + libmali-hook.so.1.9.0 + libxcb-dri2.so.0 + mali.json ICD) into the container's default paths (/usr/share/vulkan/icd.d + /usr/lib/aarch64-linux-gnu + ldconfig) makes graphics_detector enumerate Mali-G610 with NO env vars. Staging dir kept at /vol2/cuttlefish/mali-stack.
- **Wall 1 (vhost-user GPU)**: `-gpu_mode=gfxstream_guest_angle` defaults to vhost-user GPU on arm64, which hard-requires VK_EXT_external_memory_host — absent on g24p0 → assemble_cvd aborts. Flag to disable is `-gpu_vhost_user_mode=off` (NOT --enable_gpu_vhost_user, which launch_cvd rejects).
- **Wall 2 (pure gfxstream)**: crosvm renderer init fails — host EGL cannot initialize a display headless. Proven twice: env-based (LD_LIBRARY_PATH/VK_DRIVER_FILES) and full default-path install of Mali EGL/GLES/GBM stubs in a privileged container with /dev/dri present.
- **Wall 3 (guest_angle in-process)**: renderer init HANGS — v_gpu thread parked in futex, crosvm never opens /dev/mali0, guest kernel log stays 0 bytes (35 min). OpenWrt sidecar boots fine.
- **No mesa escape**: the GPU has NO DRM node (card0=rockchip-drm display, card1/renderD128=RKNPU). Panfrost/PanVK would need a kernel swap — out of scope on the production NAS.
- Reopen conditions: ARM driver gaining VK_EXT_external_memory_host, a BSP kernel exposing a panfrost DRM GPU, or gfxstream dropping its host-EGL dependency.
- Production baseline stays guest_swiftshader (36 s boot, 2.33 GiB at the optimized 2G profile).
