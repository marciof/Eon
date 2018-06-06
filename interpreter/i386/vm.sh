#!/bin/sh
set -e -u

if [ $# -ne 1 ]; then
    echo "Usage: $(basename "$0") kernel-executable" >&2
    exit 1
fi

kernel_executable="$1"
bootable_iso="$("$(dirname "$0")/iso.sh" "$kernel_executable")"
vm_name="$kernel_executable.$$"
storage_name=ide

trap 'rm "$bootable_iso"' EXIT
echo "Creating VM and booting CD ISO: $bootable_iso" >&2

vboxmanage createvm --name "$vm_name" --ostype Other_64 --register
vboxmanage storagectl "$vm_name" --name "$storage_name" --add ide
vboxmanage storageattach "$vm_name" --storagectl "$storage_name" --port 0 --device 0 --type dvddrive --medium "$bootable_iso"
vboxmanage startvm "$vm_name" --type sdl

until vboxmanage showvminfo --machinereadable "$vm_name" | grep -Eq '^VMState="poweroff"$'; do
    sleep 1
done

sleep 1
vboxmanage storageattach "$vm_name" --storagectl "$storage_name" --port 0 --device 0 --type dvddrive --medium none
vboxmanage unregistervm --delete "$vm_name"
