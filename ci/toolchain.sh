#!/usr/bin/env bash

sudo apt install -y qemu-system-x86

cargo install bootimage

rustup override set nightly
rustup component add rust-src llvm-tools-preview
