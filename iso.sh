#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/bottleos.kernel isodir/boot/bottleos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "bottleos" {
	multiboot /boot/bottleos.kernel
}
EOF
grub-mkrescue -o bottleos.iso isodir