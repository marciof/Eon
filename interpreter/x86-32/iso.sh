#!/bin/sh
set -e -u

if [ $# -ne 1 ]; then
    echo "Usage: $(basename "$0") kernel-executable" >&2
    exit 1
fi

kernel_file="$1"
kernel_file_name="$(basename "$kernel_file")"
cd_image_file="$(mktemp -t "$kernel_file_name-grub-cd-XXXXX.iso")"
cd_contents_dir="$(mktemp -d)"

cp "$kernel_file" "$cd_contents_dir/"
mkdir -p "$cd_contents_dir/boot/grub"

cat <<CONFIG >"$cd_contents_dir/boot/grub/grub.cfg"
set timeout=0
menuentry "$kernel_file_name" {
    insmod multiboot
    multiboot /$kernel_file_name
}
CONFIG

echo "Creating CD ISO from: $cd_contents_dir" >&2
grub-mkrescue -o "$cd_image_file" "$cd_contents_dir"
rm -rf "$cd_contents_dir"

if [ ! -s "$cd_image_file" ]; then
    echo "Failed to create a GRUB boot CD ISO: $cd_image_file" >&2
    exit 1
fi

echo "$cd_image_file"
