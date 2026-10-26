#!/bin/bash
# G98 / RK3588 宿主机只读预检：Cuttlefish 运行前置条件。不改任何系统状态。
# 退出码 0 = 全部通过；1 = 有硬性不满足项。
set -u
fail=0
say() { echo "[preflight] $*"; }
bad() { say "FAIL: $*"; fail=1; }

# 1) 设备节点（勘察 D1：生死线）
for d in /dev/kvm /dev/vhost-vsock /dev/vhost-net /dev/net/tun /dev/mali0; do
  [ -e "$d" ] && say "ok device $d" || bad "missing device $d"
done

# 2) 内核 config（有 /boot/config-* 或 /proc/config.gz 任一可查即可）
CFG=""
for f in /proc/config.gz "/boot/config-$(uname -r)"; do
  if [ -r "$f" ]; then CFG="$f"; break; fi
done
if [ -n "$CFG" ]; then
  if [ "${CFG##*.}" = "gz" ]; then zcat "$CFG" > /tmp/kcfg.$$; CFG=/tmp/kcfg.$$; fi
  for c in CONFIG_KVM CONFIG_BRIDGE; do
    grep -q "^$c=y" "$CFG" && say "ok $c=y" || bad "$c not =y in $CFG"
  done
  rm -f /tmp/kcfg.$$
else
  say "warn: no kernel config readable; device nodes already checked"
fi

# 3) Vulkan：至少能枚举出 Mali 设备或软件渲染
if command -v vulkaninfo >/dev/null 2>&1; then
  timeout 30 vulkaninfo --summary 2>/dev/null | grep -q "Mali-G610" \
    && say "ok vulkan Mali-G610 present" \
    || say "warn: Mali-G610 not enumerated by vulkaninfo (software rendering still possible)"
else
  say "warn: vulkaninfo not installed"
fi

# 4) 资源：可用内存 >= 6G（单实例基线），目标盘可用 >= 30G
avail_kb=$(awk '/MemAvailable/ {print $2}' /proc/meminfo)
[ "${avail_kb:-0}" -ge 6291456 ] && say "ok MemAvailable ${avail_kb}kB" || bad "MemAvailable too low: ${avail_kb:-?}kB"
target=${1:-/vol2}
free_gb=$(df --output=avail -BG "$target" 2>/dev/null | tail -1 | tr -dc '0-9')
[ "${free_gb:-0}" -ge 30 ] && say "ok $target free ${free_gb}G" || bad "$target free space low: ${free_gb:-?}G"

# 5) 网络快照存在性（D4 共存守门：无快照不许装 host 包）
snap_dir=${SNAP_DIR:-/vol2/cuttlefish/net-snapshots}
if [ -d "$snap_dir" ] && ls "$snap_dir"/* >/dev/null 2>&1; then
  say "ok network snapshot present in $snap_dir"
else
  say "warn: no network snapshot in $snap_dir (required before host package install)"
fi

[ "$fail" -eq 0 ] && say "ALL PASS" || say "PREFLIGHT FAILED"
exit "$fail"
