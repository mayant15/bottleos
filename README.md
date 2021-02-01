# BottleOS
![build](https://github.com/mayant15/bottleos/workflows/build/badge.svg)
![clippy](https://github.com/mayant15/bottleos/workflows/clippy/badge.svg)

Teaching myself OS internals by building a kernel.

## Build

Get build requirements
```sh
# Use Rust nightly for experimental features
rustup override set nightly

# Recompile core libraries
rustup component add rust-src

# For using the bootloader package
rustup component add llvm-tools-preview
```

Build with `cargo`
```sh
# Build the kernel itself
cargo build

# Or build a bootimage
cargo bootimage
```

## Documentation
The complete documentation can be found [here](https://mayantmukul.me/bottleos/)

## References
- https://wiki.osdev.org/Main_Page
- http://www.osdever.net/tutorials
- https://os.phil-opp.com/
