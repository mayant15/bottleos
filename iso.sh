#!/usr/bin/env bash

set -e

ISO_IMAGE=target/kernel.iso
ISO_DIR=iso_root
KERNEL_BINARY_DIR=target/x86_64-cargo-target/debug
KERNEL_BINARY_NAME=bottleos

# Build the kernel binary
cargo build

# Copy files to temporary file structure
rm -rf $ISO_DIR
mkdir -p $ISO_DIR
cp  $KERNEL_BINARY_DIR/$KERNEL_BINARY_NAME \
    limine.cfg \
    limine/limine.sys \
    limine/limine-cd.bin \
    limine/limine-eltorito-efi.bin \
    $ISO_DIR/

mv -v $ISO_DIR/$KERNEL_BINARY_NAME $ISO_DIR/$KERNEL_BINARY_NAME.elf

# Generate an iso
xorriso -as mkisofs -b limine-cd.bin \
    -no-emul-boot -boot-load-size 4 -boot-info-table \
    --efi-boot limine-eltorito-efi.bin \
    -efi-boot-part --efi-boot-image --protective-msdos-label \
    $ISO_DIR -o $ISO_IMAGE

# Make it bootable
limine/limine-install $ISO_IMAGE

# Cleanup
rm -rf $ISO_DIR
