#!/bin/bash
# 在盒子上拉官方 Cuttlefish 镜像（build 由 versions.env 钉死）。
# 经验参数（2026-10-26 实测）：GCS 单连接 ~1.6MB/min 不可用；12 路分片 ~50MB/min。
# ci.android.com /raw/ 接口有分钟级配额（429），resolve 失败自动等待重试。
set -eu
cd "$(dirname "$0")/.."
# shellcheck disable=SC1091
. ./versions.env
DEST=${DEST:-/vol2/cuttlefish/images}
mkdir -p "$DEST"
cd "$DEST"

resolve() { # $1=raw url -> signed url
  curl -s -D - -o /dev/null "$1" | grep -i '^location:' | tr -d '\r' | cut -d' ' -f2
}

chunkget() { # $1=raw url  $2=out  $3=min bytes  $4=file-type pattern
  local raw=$1 out=$2 min=$3 pat=$4 parts=12 signed total chunk i s e t
  for attempt in 1 2 3 4 5 6; do
    signed=$(resolve "$raw")
    [ -n "$signed" ] && break
    echo "resolve failed (quota?), wait 60s (attempt $attempt)"
    sleep 60
  done
  [ -n "$signed" ] || { echo "RESOLVE_FAIL $out"; return 1; }
  total=$(curl -sI "$signed" | grep -i '^content-length:' | tr -d '\r' | awk '{print $2}')
  echo "GET $out total=$total parts=$parts"
  chunk=$(( (total + parts - 1) / parts ))
  rm -f "$out".p*
  for i in $(seq 0 $((parts-1))); do
    s=$(( i * chunk )); e=$(( (i+1) * chunk - 1 ))
    if [ $e -ge $total ]; then e=$(( total - 1 )); fi
    ( for t in 1 2 3 4 5; do curl -s --fail -r $s-$e -o "$out.p$i" "$signed" && break; sleep 20; done ) &
  done
  wait
  cat $(ls "$out".p* | sort -t p -k2 -n) > "$out"
  rm -f "$out".p*
  local sz
  sz=$(stat -c%s "$out")
  echo "DONE $out size=$sz"
  [ "$sz" -ge "$min" ] && file "$out" | grep -qi "$pat"
}

BASE="https://ci.android.com/builds/submitted/${CF_IMAGE_BUILD_ID}/${CF_IMAGE_TARGET}/latest/raw"
chunkget "$BASE/cvd-host_package.tar.gz" cvd-host_package.tar.gz 700000000 gzip
chunkget "$BASE/aosp_cf_arm64_only_phone-img-${CF_IMAGE_BUILD_ID}.zip" "aosp_cf_arm64_only_phone-img-${CF_IMAGE_BUILD_ID}.zip" 950000000 'zip archive'
sha256sum cvd-host_package.tar.gz "aosp_cf_arm64_only_phone-img-${CF_IMAGE_BUILD_ID}.zip" > SHA256SUMS
echo "FETCH COMPLETE"
