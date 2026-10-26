# Cuttlefish RK3588 适配设计（定稿 v1，2026-10-26）

## 0. 目标与非目标

**目标**：在 RK3588 宿主机（首台：G98 / fnOS，内核 6.18.18.c1145-trim）上跑通 Google Cuttlefish 虚拟 Android 设备，产出可复现的"RK3588 专用"交付物：host 包 + 启动配置 + 部署/验证脚本，全部在 GitHub CI 构建，宿主机只做运行时验证。

**非目标**：
- 不 fork AOSP 全量源码、不在免费 CI 构建 Android 整机镜像（已核实：免费 runner 资源不足，larger runner 计费；且无必要）。
- 不承诺 GPU 硬件渲染（gfxstream+Mali 全网零先例，见勘察）；基线为软件渲染。
- 不动 G98 上现有 redroid 生产实例与 NAS 服务。

## 1. 基线（Baseline）

| 组件 | 基线 | 说明 |
|---|---|---|
| Guest 镜像 | 官方 A17 `aosp_cf_arm64_only_phone` build **16644040**（aosp-android-latest-release） | ci.android.com 官方产物；A15/A16 官方预构建已下线/删除，此为唯一存活基线 |
| Host 工具 | google/android-cuttlefish 源码自建 .deb（cuttlefish-base / cuttlefish-user） | 钉死版本（见 §3），不直接用官方预编译 deb 以便打 RK3588 补丁 |
| 宿主机 | G98：RK3588 / 16GB / fnOS(Debian 12) / 内核 6.18.18.c1145-trim | 实测见勘察记录（DESIGN 勘察节） |

## 2. 差异面与适配策略（源自 2026-10-26 勘察）

| # | 差异面 | 实测/调研结论 | 适配策略 |
|---|---|---|---|
| D1 | 宿主机内核 vhost | /dev/kvm、vhost-vsock、vhost-net、tun 全在，KVM=y | **零适配**。preflight 脚本守门，缺失即停 |
| D2 | GPU 渲染 | Host Vulkan 真实可用（Mali-G610 官方驱动 1.3.276）；但 gfxstream 硬件路径在 Mali 上无先例 | 基线 `--gpu_mode=guest_swiftshader` + WebRTC；gfxstream+Mali 为探索分支，独立开关、失败不阻塞主线 |
| D3 | Host 包安装 | 官方仅 Debian .deb 体系；fnOS=Debian 12 衍生 | 走自建 .deb；安装后 usermod kvm/cvdnetwork/render + 重启触发模块/udev |
| D4 | 宿主机网络共存 | cuttlefish-base 预建 cvd tap/桥与 host-resources 服务，与现有 redroid/docker 桥共存风险 | **部署前快照**（ip/iptables/docker network 全量存档）；实例数 num_cvd_accounts 先设 1；装后逐项 diff 验证 NAS/redroid 网络无损；预置回滚脚本 |
| D5 | 镜像分发 | ci.android.com /raw/ 直链；GCS 单连接实测 ~1.6MB/min，12 路分片 ~50MB/min；接口有分钟级 429 配额 | 盒上脚本分片+重试拉取（scripts/fetch-images.sh）；可选后续镜像到 GitHub Release 做二级源 |
| D6 | 页大小 | pgagnostic 与 4KB 宿主机无关 | 用标准 aosp_cf_arm64_only_phone，不碰 pgagnostic |

## 3. 构建管线（GitHub CI）

仓库：`redroid-rk3588`（本仓库）。

| Job | Runner | 内容 | 产物 |
|---|---|---|---|
| build-host-packages | ubuntu-24.04-arm | 拉 google/android-cuttlefish 钉死 ref → tools/buildutils/build_packages.sh 构建 .deb → 应用 patches/ 下 RK3588 补丁（初期可为空集） | cuttlefish-base/user .deb（artifact） |
| bundle | ubuntu-24.04-arm | 汇总 .deb + scripts/ + 配置模板，生成版本清单（上游 ref、镜像 build id、校验和） | release bundle（artifact / Release） |
| validate | ubuntu-latest | shellcheck 脚本、校验 workflow 与配置模板语法 | — |

版本钉死策略：android-cuttlefish 的 ref、官方镜像 build id 都写在 `versions.env`，升级只改这一处并走 CI 全量重验。

## 4. 盒上验证协议（运行时，唯一在盒子上做的事）

1. `scripts/box-preflight.sh` 只读检查：设备节点、内核 config、Vulkan 设备、内存/磁盘余量、现有网络快照存在性。全过才继续。
2. 装 host 包（dpkg -i 本仓库 bundle）→ 重启 → 复查模块/udev/用户组。
3. `scripts/fetch-images.sh` 拉官方镜像（分片+重试）→ 解包到独立目录（不覆盖既有 redroid 目录）。
4. 首启：`launch_cvd --gpu_mode=guest_swiftshader --num_instances=1`，判据：adb 可连、`sys.boot_completed=1`、WebRTC 8443 可达。
5. 回归检查：NAS 服务、redroid 实例 5555、Docker 桥逐一探活；任一异常执行回滚（停 cvd、卸 host 包、恢复网络快照）。
6. 探索分支（主线通过后）：`--gpu_mode=gfxstream` 对照启动，记录成功/失败日志，不设通过预期。

## 5. 里程碑

- M0 设计定稿 + 仓库/CI 骨架（本文档）✅
- M1 CI 首次产出 host .deb bundle
- M2 盒上 preflight + 网络快照 + host 包安装与回滚演练（不启 guest）
- M3 首次 launch_cvd 软件渲染跑通 boot_completed（CV 轨成立判据）
- M4 gfxstream+Mali 探索（可选，不阻塞）
- M5 与管理层衔接（实例编排进 P0/P1 的管理器与控制台）

## 6. 风险与回滚

- 最大风险：host 包动宿主机网络 → 以快照+回滚脚本对冲；M2 阶段专门演练回滚后再进 M3。
- G98 是生产 NAS：所有盒上动作限定在明确目录与 cvd 专用资源内；禁止顺手改 fnOS 系统配置。
- 官方镜像 build 会滚动下线（保留策略）：bundle 里记录 build id 与 sha256；必要时把镜像 zip 转存 GitHub Release 固化基线。
