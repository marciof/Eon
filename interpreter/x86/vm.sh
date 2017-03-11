#!/bin/sh

set -e

create_grub_cd_image() {
    local KERNEL_FILE=$1
    local CD_IMAGE=`mktemp -t "$KERNEL_FILE.grub-cd.XXXXX.iso"`
    local CD_CONTENTS=`mktemp -d`

    cp "$KERNEL_FILE" "$CD_CONTENTS"
    mkdir -p "$CD_CONTENTS/boot/grub"

    cat << CONFIG > "$CD_CONTENTS/boot/grub/grub.cfg"
set timeout=0
menuentry "`basename "$KERNEL_FILE"`" {
    insmod multiboot
    multiboot /$KERNEL_FILE
}
CONFIG

    grub-mkrescue -o "$CD_IMAGE" "$CD_CONTENTS"
    rm -rf "$CD_CONTENTS"
    echo "$CD_IMAGE"
    return 0
}

KERNEL_FILE=$1

if [ -z "$KERNEL_FILE" ]; then
    echo "Usage: `basename $0` <kernel>"
    exit 1
fi

VM_NAME=$KERNEL_FILE.$$
KERNEL_CD=`create_grub_cd_image "$KERNEL_FILE"`

vboxmanage createvm --name "$VM_NAME" --ostype Other_64 --register
vboxmanage storagectl "$VM_NAME" --name IDE --add ide
vboxmanage storageattach "$VM_NAME" --storagectl IDE --port 0 --device 0 --type dvddrive --medium "$KERNEL_CD"
vboxmanage startvm "$VM_NAME" --type sdl

until `vboxmanage showvminfo --machinereadable "$VM_NAME" | grep -Eq '^VMState="poweroff"$'`; do
    sleep 1
done

sleep 1
vboxmanage unregistervm --delete "$VM_NAME"
rm -vrf "$KERNEL_CD"
