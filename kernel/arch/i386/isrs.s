.section .text

# Load the IDT
.global idt_load
idt_load:
    lidt idtp
    ret

# Declare all ISRs
.global _isr0
.global _isr1
.global _isr2
.global _isr3
.global _isr4
.global _isr5
.global _isr6
.global _isr7
.global _isr8
.global _isr9
.global _isr10
.global _isr11
.global _isr12
.global _isr13
.global _isr14
.global _isr15
.global _isr16
.global _isr17
.global _isr18
.global _isr19
.global _isr20
.global _isr21
.global _isr22
.global _isr23
.global _isr24
.global _isr25
.global _isr26
.global _isr27
.global _isr28
.global _isr29
.global _isr30
.global _isr31

# ISR 0: Divide by zero exception
_isr0:
    cli
    pushl $0x00 # Push a dummy error code, to keep things uniform
    pushl $0x00 # Push the interrupt number
    jmp isr_common_stub

# ISR 1: Debug exception
_isr1:
    cli
    pushl $0x00
    pushl $0x01
    jmp isr_common_stub

# ISR 2: Non-maskable interrupt exception
_isr2:
    cli
    pushl $0x00
    pushl $0x02
    jmp isr_common_stub

# ISR 3: Breakpoint exception
_isr3:
    cli
    pushl $0x00
    pushl $0x03
    jmp isr_common_stub

# ISR 4: Into detected overflow exception
_isr4:
    cli
    pushl $0x00
    pushl $0x04
    jmp isr_common_stub

# ISR 5: Out of bounds exception
_isr5:
    cli
    pushl $0x00
    pushl $0x05
    jmp isr_common_stub

# ISR 6: Invalid opcode exception
_isr6:
    cli
    pushl $0x00
    pushl $0x06
    jmp isr_common_stub

# ISR 7: No coprocessor exception
_isr7:
    cli
    pushl $0x00
    pushl $0x07
    jmp isr_common_stub

# ISR 8: Double fault exception
_isr8:
    cli
    pushl $0x08 # This one pushes an error code, so just push the interrupt number
    jmp isr_common_stub

# ISR 9: Coprocessor segment overrun exception
_isr9:
    cli
    pushl $0x00
    pushl $0x09
    jmp isr_common_stub

# ISR 10: Bad TSS exception
_isr10:
    cli
    pushl $0x0A
    jmp isr_common_stub

# ISR 11: Segment not present exception
_isr11:
    cli
    pushl $0x0B
    jmp isr_common_stub

# ISR 12: Stack fault exception
_isr12:
    cli
    pushl $0x0C
    jmp isr_common_stub

# ISR 13: General protection fault exception
_isr13:
    cli
    pushl $0x0D
    jmp isr_common_stub

# ISR 14: Page fault exception
_isr14:
    cli
    pushl $0x0E
    jmp isr_common_stub

# ISR 15: Unknown interrupt exception
_isr15:
    cli
    pushl $0x00
    pushl $0x0F
    jmp isr_common_stub

# ISR 16: Coprocessor fault exception
_isr16:
    cli
    pushl $0x00
    pushl $0x10
    jmp isr_common_stub

# ISR 17: Alignment check exception
_isr17:
    cli
    pushl $0x00
    pushl $0x11
    jmp isr_common_stub

# ISR 18: Machine check exception
_isr18:
    cli
    pushl $0x00
    pushl $0x12
    jmp isr_common_stub

# ISRs 19 to 31 are reserved exceptions
_isr19:
    cli
    pushl $0x00
    pushl $0x13
    jmp isr_common_stub
_isr20:
    cli
    pushl $0x00
    pushl $0x14
    jmp isr_common_stub
_isr21:
    cli
    pushl $0x00
    pushl $0x15
    jmp isr_common_stub
_isr22:
    cli
    pushl $0x00
    pushl $0x16
    jmp isr_common_stub
_isr23:
    cli
    pushl $0x00
    pushl $0x17
    jmp isr_common_stub
_isr24:
    cli
    pushl $0x00
    pushl $0x18
    jmp isr_common_stub
_isr25:
    cli
    pushl $0x00
    pushl $0x19
    jmp isr_common_stub
_isr26:
    cli
    pushl $0x00
    pushl $0x1A
    jmp isr_common_stub
_isr27:
    cli
    pushl $0x00
    pushl $0x1B
    jmp isr_common_stub
_isr28:
    cli
    pushl $0x00
    pushl $0x1C
    jmp isr_common_stub
_isr29:
    cli
    pushl $0x00
    pushl $0x1D
    jmp isr_common_stub
_isr30:
    cli
    pushl $0x00
    pushl $0x1E
    jmp isr_common_stub
_isr31:
    cli
    pushl $0x00
    pushl $0x1F
    jmp isr_common_stub


# This is the common stub to call fault_handler() in C
# Save the state, handle the interrupt, then return to
# whatever the processor was doing
isr_common_stub:
    #call fault_handler
    pusha             # Save the current state
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    #movl $fault_handler, %eax
    #call %eax         # Calling it like this preserves the program counter (EIP register)
    call fault_handler
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
    add $0x08, %esp   # Advance to overwrite the error code and the ISR number
    iret
