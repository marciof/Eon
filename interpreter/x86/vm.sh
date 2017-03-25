#!/bin/sh
set -e -u

create_grub_cd_image() {
    local kernel_file=$1
    local cd_image="$(mktemp -t "$kernel_file.grub-cd.XXXXX.iso")"
    local cd_contents="$(mktemp -d)"

    cp "$kernel_file" "$cd_contents"
    mkdir -p "$cd_contents/boot/grub"

    cat <<CONFIG >"$cd_contents/boot/grub/grub.cfg"
set timeout=0
menuentry "$(basename "$kernel_file")" {
    insmod multiboot
    multiboot /$kernel_file
}
CONFIG

    grub-mkrescue -o "$cd_image" "$cd_contents"
    rm -rf "$cd_contents"
    echo "$cd_image"
    return 0
}

if [ $# -ne 1 ]; then
    echo "Usage: $(basename "$0") <kernel>" >&2
    exit 1
fi

kernel_file="$1"
vm_name="$kernel_file.$$"
storage_name=ide
kernel_cd="$(create_grub_cd_image "$kernel_file")"

trap 'rm "$kernel_cd"' EXIT

vboxmanage createvm --name "$vm_name" --ostype Other_64 --register
vboxmanage storagectl "$vm_name" --name "$storage_name" --add ide
vboxmanage storageattach "$vm_name" --storagectl "$storage_name" --port 0 --device 0 --type dvddrive --medium "$kernel_cd"
vboxmanage startvm "$vm_name" --type sdl

until vboxmanage showvminfo --machinereadable "$vm_name" | grep -Eq '^VMState="poweroff"$'; do
    sleep 1
done

sleep 1
vboxmanage storageattach "$vm_name" --storagectl "$storage_name" --port 0 --device 0 --type dvddrive --medium none
vboxmanage unregistervm --delete "$vm_name"
