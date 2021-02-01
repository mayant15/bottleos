#!/usr/bin/env bash

rustup override set nightly
rustup component add rust-src
rustup component add llvm-tools-preview
