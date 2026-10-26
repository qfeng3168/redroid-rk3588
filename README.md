# redroid-rk3588

RK3588 云手机双轨项目的适配仓库。本阶段内容：把 Google Cuttlefish 跑在 RK3588 上——RK3588 专用 host 包与启动配置，GitHub CI 构建，盒子只做运行时验证。

**设计**：[docs/DESIGN.md](docs/DESIGN.md)（定稿 v1，含勘察结论与差异面）

**现状**：M0 设计定稿 + 仓库/CI 骨架。基线为官方 A17 Cuttlefish 镜像（build 16644040）+ google/android-cuttlefish 源码自建 host 包。

**路线要点**：
- G98（首台 RK3588 宿主机）实测 vhost/KVM 齐备，不用重编内核
- 基线软件渲染（guest SwiftShader）+ WebRTC；gfxstream+Mali 硬件渲染为探索项（全网无先例）
- 最大风险是 host 包与现有 NAS/redroid 网络共存，部署带快照与回滚

**目录**：
- `docs/` 设计与勘察
- `scripts/` 盒上脚本（preflight / 拉镜像 / 回滚）
- `patches/` 对 android-cuttlefish 的 RK3588 补丁集（初期为空）
- `versions.env` 钉死的版本清单（上游 ref + 镜像 build id）
