;==============================================================================
; Initialization and preparation
;
; We need to define and export a label that will be our entry point. We also
; need to reserve space for a stack.
;==============================================================================

; Make NASM export this symbol in the object file, so that the
; linker can see it.

global _start

; GRUB does not setup the stack. We need to reserve a stack for 
; this program, but we don't need to do it in the executable itself,
; that will just bloat it. Instead we can use an NASM pseudo-instruction
; called `res*`, to reserve memory when GRUB is loading this executable.
section .bss
stack_bottom:
    ; Reserve 64 bytes
    resb 64
stack_top:

;==============================================================================
; Main code
;
; This provides the entry point for the kernel and calls various helper
; functions to initialize the kernel and start it up. Try to keep this minimal
; and transfer control over to Rust as soon as possible.
;==============================================================================

; Start the text section, where we keep all the executable code
section .text

; GRUB sets the CPU to protected mode before loading our kernel,
; so we can only use 32-bit instructions. bits 32 makes it explicit
; that the following instructions are 32-bit
bits 32

; Entry point for the kernel
_start:
    ; Set the `esp` register to our stack, this will allow us to
    ; use push/pop instructions, and more importantly allow us to
    ; call functions
    mov dword esp, stack_top

    ; Check for errors before starting the kernel
    call check_multiboot
    call check_cpuid
    call check_long_mode

    ; print ASCII for OK to VGA memory directly
    mov dword [0xb8000], 0x2f4b2f4f

    ; Halt the CPU until the next interrupt is fired
    hlt

;==============================================================================
; Helper functions for validation
;
; Check if the platform supports required features. There functions print an
; error code and halt the booting process if something goes wrong.
;
; Legend:
; Error Code - Description
; 0          - Kernel was not loaded by a multiboot2 compliant bootloader
; 1          - The platform does not support CPUID instruction
; 2          - The platform does not support 64-bit long mode
;==============================================================================

; Print "ERR: <ERR-CODE>" to the screen by directly writing to VGA
; memory. The error code is passed into the `al` register, which is
; simply bits 0-8 of the `eax` 32-bit register.
error:
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt

; Check if the kernel was loaded by a multiboot compliant bootloader
; This can be done by checking the `eax` register. The bootloader
; is supposed to write a magic value to it.
check_multiboot:
    cmp eax, 0x36d76289
    jne .error_multiboot
    ret
.error_multiboot:
    mov byte al, 0
    jmp error

; Check if the CPU supports CPUID. This can be done by trying to
; flip the ID bit (bit 21) in the FLAGS register.
check_cpuid:
    ; Push the 32-bit EFLAGS register to stack and then pop it into
    ; `eax`. Only the last 8-bits of EFLAGS can be manipulated directly.
    ; If we want the entire thing then we must go through the stack.
    pushfd
    pop eax

    ; Copy EFLAGS to `ecx` as well
    mov ecx, eax

    ; Try to flip the 21st bit by taking a XOR with 1
    xor eax, 1 << 21

    ; Put this flipped value back into EFLAGS, then again pop into
    ; `eax`. If the flipped bit is retained, then CPUID is supported
    push eax
    popfd
    pushfd
    pop eax

    ; Restore EFLAGS with the initial value from ecx
    push ecx
    popfd

    ; Compare eax and ecx, if same then the flipped bit was restored
    ; which implies CPUID is not supported
    cmp eax, ecx
    je .error_cpuid
    ret
.error_cpuid:
    mov byte al, 0x1
    jmp error

; If CPUID is available, use it to check if long mode is available
check_long_mode:
    ; Check if extended processor info is available by passing
    ; arguments to CPUID through eax, and getting the return value
    ; via eax as well (returned value must be atleast 0x80000001)
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .error_long_mode

    ; Use extended info to check if long mode is available.
    ; Input through eax, output through ecx and edx
    ; 29th bit in edx must be set
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .error_long_mode
    ret
.error_long_mode:
    mov byte al, 0x2
    jmp error
