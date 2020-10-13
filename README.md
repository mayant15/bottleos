# BottleOS

Teaching myself OS internals by building a kernel.

## Build

- **Requirements**
    - A cross-compiler toolchain on your path that does not use pre-installed  libc and builds i686-elf binaries. See [here](https://wiki.osdev.org/GCC_Cross-Compiler).
    - I'm working on Ubuntu-20.04 and testing on qemu

- **Build**
```
# Clean previously built objects
./clean.sh

# Build
./build.sh

# Create an ISO
./iso.sh
```

- **Run**
```
qemu-system-i386 -kernel sysroot/boot/bottleos.kernel
```

## References
- [OSDev](https://wiki.osdev.org/Main_Page)