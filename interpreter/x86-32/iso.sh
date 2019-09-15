#!/bin/sh
set -e -u

if [ $# -ne 1 ]; then
    echo "Usage: $(basename "$0") kernel-executable" >&2
    exit 1
fi

kernel_file="$1"
cd_image="$(mktemp -t "$kernel_file-grub-cd-XXXXX.iso")"
cd_contents="$(mktemp -d)"

cp "$kernel_file" "$cd_contents"
mkdir -p "$cd_contents/boot/grub"

cat <<CONFIG >"$cd_contents/boot/grub/grub.cfg"
set timeout=0
menuentry "$(basename "$kernel_file")" {
    insmod multiboot
    multiboot /$kernel_file
}
CONFIG

echo "Creating CD ISO from: $cd_contents" >&2
grub-mkrescue -o "$cd_image" "$cd_contents"
rm -rf "$cd_contents"

if [ ! -s "$cd_image" ]; then
    echo "Failed to create a GRUB boot CD ISO: $cd_image" >&2
    exit 1
fi

echo "$cd_image"
