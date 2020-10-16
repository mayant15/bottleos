/**
 * @file idt_impl.c
 * @brief Implements IDT installation
 */

#include "idt.h"
#include "isrs.h"

#include <string.h>

/** @brief Register a handler for software exceptions */
#define ISR_SET_IDT_ENTRY(x) idt_set_entry(x, (uint32_t)_isr##x, 0x08, 0x8E)

/** @brief Register a handler for hardware interrupts */
#define IRQ_SET_IDT_ENTRY(x) idt_set_entry(IRQ_OFFSET + x, (uint32_t)_irq##x, 0x08, 0x8E)

/** @brief C representation of the Interrupt Descriptor Table */
struct idt_entry idt[IDT_SIZE];

/** @brief C representation of the IDT handle */
struct idt_ptr idtp;

/**
 * @brief Set an entry in the Interrupt Descriptor Table
 * 
 * @param id        Interrupt index to set
 * @param address   Address of the handler function
 * @param selector  Selector for the kernel's code segment
 * @param type_attr Configuration flags for this entry
 */
void idt_set_entry(uint8_t id, uint32_t address, uint16_t selector, uint8_t type_attr)
{
    idt[id].zero = 0;
    idt[id].type_attr = type_attr;
    idt[id].selector = selector;

    uint16_t hi = (address & 0xFFFF0000) >> 16;
    uint16_t lo = (address & 0xFFFF);
    idt[id].offset_lo = lo;
    idt[id].offset_hi = hi;
}

/** @brief Sets up and installs the IDT with all required handlers */
void idt_install()
{
    // Initialize idt_entry arr
    memset(idt, 0, sizeof(struct idt_entry) * IDT_SIZE);

    // Create idt_ptr
    idtp.size = sizeof(struct idt_entry) * IDT_SIZE - 1;
    idtp.offset = (uint32_t)idt;

    // Load exception handlers
    ISR_SET_IDT_ENTRY(0);
    ISR_SET_IDT_ENTRY(1);
    ISR_SET_IDT_ENTRY(2);
    ISR_SET_IDT_ENTRY(3);
    ISR_SET_IDT_ENTRY(4);
    ISR_SET_IDT_ENTRY(5);
    ISR_SET_IDT_ENTRY(6);
    ISR_SET_IDT_ENTRY(7);
    ISR_SET_IDT_ENTRY(8);
    ISR_SET_IDT_ENTRY(9);
    ISR_SET_IDT_ENTRY(10);
    ISR_SET_IDT_ENTRY(11);
    ISR_SET_IDT_ENTRY(12);
    ISR_SET_IDT_ENTRY(13);
    ISR_SET_IDT_ENTRY(14);
    ISR_SET_IDT_ENTRY(15);
    ISR_SET_IDT_ENTRY(16);
    ISR_SET_IDT_ENTRY(17);
    ISR_SET_IDT_ENTRY(18);
    ISR_SET_IDT_ENTRY(19);
    ISR_SET_IDT_ENTRY(20);
    ISR_SET_IDT_ENTRY(21);
    ISR_SET_IDT_ENTRY(22);
    ISR_SET_IDT_ENTRY(23);
    ISR_SET_IDT_ENTRY(24);
    ISR_SET_IDT_ENTRY(25);
    ISR_SET_IDT_ENTRY(26);
    ISR_SET_IDT_ENTRY(27);
    ISR_SET_IDT_ENTRY(28);
    ISR_SET_IDT_ENTRY(29);
    ISR_SET_IDT_ENTRY(30);
    ISR_SET_IDT_ENTRY(31);

    // Load interrupt handlers
    irq_remap();
    IRQ_SET_IDT_ENTRY(0);
    IRQ_SET_IDT_ENTRY(1);
    IRQ_SET_IDT_ENTRY(2);
    IRQ_SET_IDT_ENTRY(3);
    IRQ_SET_IDT_ENTRY(4);
    IRQ_SET_IDT_ENTRY(5);
    IRQ_SET_IDT_ENTRY(6);
    IRQ_SET_IDT_ENTRY(7);
    IRQ_SET_IDT_ENTRY(8);
    IRQ_SET_IDT_ENTRY(9);
    IRQ_SET_IDT_ENTRY(10);
    IRQ_SET_IDT_ENTRY(11);
    IRQ_SET_IDT_ENTRY(12);
    IRQ_SET_IDT_ENTRY(13);
    IRQ_SET_IDT_ENTRY(14);
    IRQ_SET_IDT_ENTRY(15);

    // Call idt_load
    idt_load();
}
