#!/bin/bash

MNT="/mnt/os"
BASE_PATH="$(pwd)"
NAME='hard_disk.img'
IMAGE="$BASE_PATH/$NAME"



# exec modprobe -r loop
modprobe loop max_part=15

losetup -f "$IMAGE"

mount /dev/loop0p1 "$MNT"

rm "$MNT/boot/kernel"
rm "$MNT/boot/grub/grub.cfg"
cp "$BASE_PATH/bin/kernel" "$MNT/boot"
cp "$BASE_PATH/boot/grub.cfg" "$MNT/boot/grub"

umount "$MNT"


exit 0
