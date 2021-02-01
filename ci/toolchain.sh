#!/usr/bin/env bash

sudo apt install -y qemu-system-x86

rustup override set nightly
rustup component add rust-src
rustup component add llvm-tools-preview
