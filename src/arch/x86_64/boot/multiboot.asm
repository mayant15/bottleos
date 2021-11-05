; 24-byte header required to indicate our kernel follows multiboot 2

section .multiboot_header
header_start:
    ; Start the header with a u32 magic number
    dd 0xe85250d6

    ; Then give the architecture, 0 for i386
    dd 0

    ; Then comes the length of this header itself, a u32
    dd header_end - header_start

    ; Next comes a checksum, -(magic + architecture + header_length)
    ; Subtract from 0x100000000 to make it positive and fit in 32 bits
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; Multiboot 2 tags, if required

    ; End tag, (u16, u16, u32), (0, 0, 8)
    dw 0 ; type
    dw 0 ; flags
    dd 8 ; size

header_end:
