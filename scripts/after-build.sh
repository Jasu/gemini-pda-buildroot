#!/bin/sh

set -euo pipefail

ROOT_DIR=$(realpath "$(dirname $0)/..")
BUILDROOT_DIR="$ROOT_DIR/ext/buildroot"

cd "$BUILDROOT_DIR/output/images/" && "$ROOT_DIR/scripts/create-boot-image.sh"

mkdir -p "$ROOT_DIR/output"
mv "$BUILDROOT_DIR/output/images/boot_linux.img" "$ROOT_DIR/output/boot_linux.img"

echo "The build image is available in output/boot_linux.img." >&2

if [ -x "$ROOT_DIR/scripts/custom-after-build.sh" ]; then
  echo "Running custom-after-build.sh (PWD=$PWD)..." >&2
  cd "$ROOT_DIR" && scripts/custom-after-build.sh
else
  echo "No scripts/custom-after-build.sh or it is not executable." >&2
fi
