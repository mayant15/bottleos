#include "idt.h"
#include "isrs.h"

#include <string.h>

#define NUM_ISRS 256
#define IDT_SET_ENTRY(x) idt_set_entry(x, (uint32_t) _isr##x, 0x08, 0x8E)

struct idt_entry idt[NUM_ISRS];
struct idt_ptr idtp;

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

void idt_install()
{
    // Initialize idt_entry arr
    memset(idt, 0, sizeof (struct idt_entry) * NUM_ISRS);

    // Create idt_ptr
    idtp.size = sizeof (struct idt_entry) * NUM_ISRS - 1;
    idtp.offset = (uint32_t) idt;

    // Load entries
    IDT_SET_ENTRY(0);
    IDT_SET_ENTRY(1);
    IDT_SET_ENTRY(2);
    IDT_SET_ENTRY(3);
    IDT_SET_ENTRY(4);
    IDT_SET_ENTRY(5);
    IDT_SET_ENTRY(6);
    IDT_SET_ENTRY(7);
    IDT_SET_ENTRY(8);
    IDT_SET_ENTRY(9);
    IDT_SET_ENTRY(10);
    IDT_SET_ENTRY(11);
    IDT_SET_ENTRY(12);
    IDT_SET_ENTRY(13);
    IDT_SET_ENTRY(14);
    IDT_SET_ENTRY(15);
    IDT_SET_ENTRY(16);
    IDT_SET_ENTRY(17);
    IDT_SET_ENTRY(18);
    IDT_SET_ENTRY(19);
    IDT_SET_ENTRY(20);
    IDT_SET_ENTRY(21);
    IDT_SET_ENTRY(22);
    IDT_SET_ENTRY(23);
    IDT_SET_ENTRY(24);
    IDT_SET_ENTRY(25);
    IDT_SET_ENTRY(26);
    IDT_SET_ENTRY(27);
    IDT_SET_ENTRY(28);
    IDT_SET_ENTRY(29);
    IDT_SET_ENTRY(30);
    IDT_SET_ENTRY(31);

    // Call idt_load
    idt_load();
}
