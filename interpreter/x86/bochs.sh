#!/bin/sh


create_cd_image() {
    local CD=$1
    local KERNEL=$2
    local KERNEL_NAME=$(basename $KERNEL)
    local DEVICE=$(mktemp -d)
    
    cp $KERNEL $DEVICE || return 1
    mkdir -p $DEVICE/boot/grub || return 1
    
    cat << CONFIG > $DEVICE/boot/grub/grub.cfg || return 1
set timeout=0
menuentry "$KERNEL_NAME" {
    insmod multiboot
    multiboot /$KERNEL_NAME
}
CONFIG
    
    grub-mkrescue --output=$CD $DEVICE || return 1
    rm -rf $DEVICE || return 1
    return 0
}


start_bochs() {
    local IMAGE=$1
    local CONFIG=$(mktemp)
    local BIOS=/usr/share/vgabios/vgabios.bin
    
    cat << EOT > $CONFIG || return 1
boot: cdrom, floppy
vgaromimage: file="$BIOS"
floppya: 1_44="$IMAGE", status=inserted
ata0-master: type=cdrom, path="$IMAGE", status=inserted
# Avoid Ubuntu/Bochs issue 980167.
# https://bugs.launchpad.net/ubuntu/+source/bochs/+bug/980167
display_library: sdl
EOT
    
    bochs -f $CONFIG || return 1
    rm -f $CONFIG || return 1
    return 0
}


KERNEL=$1

if [ -z "$KERNEL" ]; then
    echo "Boot a kernel via GRUB using Bochs."
    echo "Usage: <file>"
    exit 1
fi

IMAGE=$(mktemp)
create_cd_image "$IMAGE" "$KERNEL"

[ $? -eq 0 ] && start_bochs "$IMAGE"
rm "$IMAGE"
