# BottleOS
![build](https://github.com/mayant15/bottleos/workflows/build/badge.svg)
![clippy](https://github.com/mayant15/bottleos/workflows/clippy/badge.svg)

Teaching myself OS internals by building a kernel.

## Build

Get build requirements
```sh
# Compile the limine submodule
./setup.sh

# Use Rust nightly for experimental features
rustup override set nightly

# Recompile core libraries
rustup component add rust-src

# For using the bootloader package
rustup component add llvm-tools-preview
```

And build with `cargo`
```sh
cargo build
```

The repo also contains a few helper scripts to help build a bootable ISO (`iso.sh`) and for running it with QEMU
(`run.sh`).

## Documentation
The complete documentation can be found [here](https://mayantmukul.com/bottleos/)

## References
- https://wiki.osdev.org/Main_Page
- http://www.osdever.net/tutorials
- https://os.phil-opp.com/
- https://www.os-book.com/OS9/

