#!/bin/sh

# USAGE:
# This command must be run in the output/images directory of the buildroot
# build. The directory must contain files Image (kernel image),
# rootfs.cpio.gz (gzipped # initrd) image, and gemini.dtb (the compiled device
# tree blob).

set -euo pipefail

ROOT_DIR=$(realpath "$(dirname $0)/..")
MKBOOTIMG_DIR="$ROOT_DIR/ext/mkbootimg"

cd "$BINARIES_DIR"

if [ ! -f Image ] && [ ! -f Image.gz ]; then
  echo "$0: Neither Image nor Image.gz exists in the current directory ($PWD)." >&2
  exit 1
fi

for FILE in gemini-pda.dtb rootfs.cpio.gz; do
  if [ ! -f "$FILE" ]; then
    echo "$0: File $FILE does not exist in the current directory ($PWD)." >&2
    exit 1
  fi
done

# MediaTek LK adds its properties in the empty padding of the DTB. We need to
# make sure that everything fits. Likely, a few kilobytes would be enough, but
# better safe than sorry...
dtc --in-format dtb \
    --out-format dtb \
    --out gemini.padded.dtb \
    --pad 16384 \
    gemini-pda.dtb

gzip --keep --force Image

# The MediaTek bootloader expects the device tree to be concatenated with the
# boot image in a non-standard way (arm64 has no support for appended DTB like
# 32-bit ARM, so append it manually)
cat Image.gz gemini.padded.dtb > Image-With-DTB

# NOTE: Kernel CMDLINE is overridden in kernel configuration, so cmdline here
#       is only read by the bootloader.
"$MKBOOTIMG_DIR/mkbootimg" \
  --kernel         Image-With-DTB \
  --ramdisk        rootfs.cpio.gz \
  --base           0x40078000 \
  --cmdline        "bootopt=64S3,32N2,64N2" \
  --kernel_offset  0x00008000 \
  --tags_offset    0x03F88000 \
  --ramdisk_offset 0x04F88000 \
  --pagesize       2048 \
  --output         boot_linux.img
