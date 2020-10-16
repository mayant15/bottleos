#ifndef ARCH_I386_IDT_H
#define ARCH_I386_IDT_H

#include <stdint.h>

/** Maximum number of entries in the Interrupt Descriptor Table */
#define IDT_SIZE 256

/** A single entry of the Interrupt Descriptor Table */
struct idt_entry
{
    /** Bits 0..15 of the registered handler's address. */
    uint16_t offset_lo;

    /** Selector for the kernel's code segment that the handler should be executed from. Must be ring 0. */
    uint16_t selector;

    /** 8 bits that always have to be zero. */
    uint8_t zero;

    /** Attribute flags for this entry. Use this for reference https://wiki.osdev.org/IDT#Structure_IA-32 */
    uint8_t type_attr;

    /** Bits 16..31 of the registered handler's address. */
    uint16_t offset_hi;
} __attribute__((packed));

/** Handle to an IDT */
struct idt_ptr
{
    /** Size if the IDT */
    uint16_t size;

    /** Address of the IDT */
    uint32_t offset;
} __attribute__((packed));

#endif // ARCH_I386_IDT_H