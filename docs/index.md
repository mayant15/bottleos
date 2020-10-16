BottleOS is a bare-bones kernel that I'm making to teach myself OS internals.

## Build

A cross-compiler toolchain on your path that does not use pre-installed libc and builds i686-elf binaries is required. See [here](https://wiki.osdev.org/GCC_Cross-Compiler). I'm working on Ubuntu-20.04 and testing on qemu.

To build the kernel, run these scripts
```
# Clean previously built objects
./clean.sh

# Build
./build.sh

# Create an ISO
./iso.sh
```

To run the build kernel with qemu, use
```
qemu-system-i386 -kernel sysroot/boot/bottleos.kernel
```

## References
- https://wiki.osdev.org/Main_Page
- http://www.osdever.net/tutorials
