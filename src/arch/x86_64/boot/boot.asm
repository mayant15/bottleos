; Make NASM export this symbol in the object file, so that the
; linker can see it.

global _start

; Start the text section, where we keep all the executable code
section .text

; GRUB sets the CPU to protected mode before loading our kernel,
; so we can only use 32-bit instructions. bits 32 makes it explicit
; that the following instructions are 32-bit
bits 32

; Entry point for the kernel
_start:
    ; print ASCII for OK to VGA memory directly
    mov dword [0xb8000], 0x2f4b2f4f

    ; Halt the CPU until the next interrupt is fired
    hlt
