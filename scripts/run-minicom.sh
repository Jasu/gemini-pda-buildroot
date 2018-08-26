#!/bin/sh

NAME=$(basename "$0")
ROOTDIR="$(dirname "$0")/../"
CAPTUREFILE="$ROOTDIR/logs/terminal/log_$(date "+%Y-%m-%d_%H:%M:%S")"

if [ ! -c "/dev/$1" ]; then
  echo "$NAME: File /dev/$1 does not exist or is not a character device." >&2
  echo >&2
  echo "USAGE: $NAME TTY" >&2
  echo -e "\tE.g. $NAME ttyUSB0 (without /dev/)." >&2
  exit 1
fi

mkdir -p "$ROOTDIR/logs/terminal"

echo "Capturing to $CAPTUREFILE." >&2
echo >&2
echo "If the script exists without output, it is likely that you" >&2
echo "do not have permissions to write to /dev/$1." >&2
exec minicom \
  --wrap \
  --color=on \
  --device="/dev/$1" \
  --capturefile="$CAPTUREFILE" \
  --8bit \
  --baudrate=921600 \
  --noinit
