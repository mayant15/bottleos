#ifndef ARCH_I386_IDT_H
#define ARCH_I386_IDT_H

#include <stdint.h>

struct idt_entry
{
    uint16_t offset_lo;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_hi;
}__attribute__((packed));


struct idt_ptr
{
    uint16_t size;
    uint32_t offset;
}__attribute__((packed));

#endif // ARCH_I386_IDT_H