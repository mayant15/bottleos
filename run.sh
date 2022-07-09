#!/usr/bin/env bash

./iso.sh

qemu-system-x86_64 -cdrom target/kernel.iso -monitor stdio

