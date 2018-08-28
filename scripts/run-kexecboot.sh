#/bin/sh

if [ ! -c "/dev/$1" ]; then
  echo "$NAME: File /dev/$1 does not exist or is not a character device." >&2
  echo >&2
  echo "USAGE: $NAME TTY" >&2
  echo -e "\tE.g. $NAME ttyUSB0 (without /dev/)." >&2
  exit 1
fi

DEVICE="/dev/$1"

ROOT_DIR=$(realpath "$(dirname $0)/..")
cd "$ROOT_DIR"

echo "Attempting to start kexec-boot.sh on the PDA." >&2
echo "/usr/local/bin/kexecboot.sh" >$DEVICE

sleep 1

echo "Transferring files..." >&2
sz --binary --zmodem \
  ext/buildroot/output/images/Image.gz \
  ext/buildroot/output/images/gemini-pda.dtb \
  ext/buildroot/output/images/rootfs.cpio.gz \
  >$DEVICE <$DEVICE

echo "All done." >&2
