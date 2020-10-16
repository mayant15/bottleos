/**
 * @file idt.h
 * @brief Constructs for declaring an Interrupt Descriptor Table (IDT)
 */

#ifndef _ARCH_I386_IDT_H
#define _ARCH_I386_IDT_H

#include <stdint.h>

/** @brief Maximum number of entries in the Interrupt Descriptor Table */
#define IDT_SIZE 256

/** @brief A single entry of the Interrupt Descriptor Table */
struct idt_entry
{
    /** @brief Bits 0..15 of the registered handler's address. */
    uint16_t offset_lo;

    /** @brief Selector for the kernel's code segment that the handler should be executed from. Must be ring 0. */
    uint16_t selector;

    /** @brief 8 bits that always have to be zero. */
    uint8_t zero;

    /** @brief Attribute flags for this entry. Use this for reference https://wiki.osdev.org/IDT#Structure_IA-32 */
    uint8_t type_attr;

    /** @brief Bits 16..31 of the registered handler's address. */
    uint16_t offset_hi;
} __attribute__((packed));

/** @brief Handle to an IDT */
struct idt_ptr
{
    /** @brief Size if the IDT */
    uint16_t size;

    /** @brief Address of the IDT */
    uint32_t offset;
} __attribute__((packed));

#endif // _ARCH_I386_IDT_H