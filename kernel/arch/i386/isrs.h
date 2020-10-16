/**
 * @file isrs.h
 * @brief Constructs for interrupt handlers
 */

#ifndef _ARCH_I386_ISRS_H
#define _ARCH_I386_ISRS_H

#include <stdint.h>

/** @brief Index in the IDT where IRQs start */
#define IRQ_OFFSET 32

extern void idt_load();

// Exceptions
extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

// Hardware Interrupts
extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();

/** @brief State of the stack when an interrupt is triggered */
struct isr_state
{
    /** @brief Segment registers */
    uint32_t gs, fs, es, ds;

    /** @brief General purpose registers */
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;

    /** @brief IDT row that this interrupt corresponds to */
    uint32_t id;

    /** @brief Error code pushed by the interrupt. Zero if no error code was pushed. */
    uint32_t err_code;

    /** @brief Program state registers, pushed by the processor */
    uint32_t eip, cs, eflags, useresp, ss;
};

/** @brief Remaps IRQs to ids 32 to 47 in the IDT */
void irq_remap();

/** @brief Send a byte to the specified port */
static inline void outb(uint16_t port, uint8_t data)
{
    asm("outb %0, %1"
        :
        : "r"(data), "Nd"(port));
}

#endif // _ARCH_I386_ISRS_H
