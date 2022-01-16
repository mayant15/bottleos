#!/usr/bin/env bash

git submodule sync --recursive
git submodule update --recursive

make -C limine

