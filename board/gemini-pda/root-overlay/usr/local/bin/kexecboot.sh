#!/bin/sh

cd $(mktemp -d)

# Receive Image.gz, gemini-pda.dtb, and initrd.img
dmesg -n 1
stty -echo
rz --binary --zmodem </dev/ttyS0 >/dev/ttyS0 2>/dev/null

for FILE in Image.gz gemini-pda.dtb rootfs.cpio.gz; do
  if [ ! -f "$FILE" ]; then
    echo "$FILE was not transferred.\n" >&2
    exit 1
  fi
done

# Delete memory and reserved-memory nodes
fdtput -r gemini-pda.dtb /memory /reserved-memory
# Convert to source, removing the terminating };
dtc -I dtb gemini-pda.dtb | grep -v '^};' > combined.dts

# Copy the currently running FDT and remove everything but /memory and
# /reserved-memory
cp /sys/firmware/fdt current.dtb
for ITEM in $(fdtget -l current.dtb /); do
  case "$ITEM" in
    memory@*)
      ;;
    reserved-memory)
      ;;
    *)
      fdtput -r current.dtb /$ITEM
      ;;
  esac
done
# Removed all nodes, now remove all properties
for ITEM in $(fdtget -p current.dtb /); do
  fdtput -d current.dtb / $ITEM
done

# Convert the currently running DTB to source, removing the top-level {};
# and the /dts-v1/; tag.
dtc -I dtb current.dtb | grep '^\s' >> combined.dts

echo "};" >> combined.dts
dtc -I dts -O dtb -o combined.dtb combined.dts

gunzip rootfs.cpio.gz

kexec --dtb=combined.dtb --initrd=rootfs.cpio --load Image.gz
kexec --force --exec
