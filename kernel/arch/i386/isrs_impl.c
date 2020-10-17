/**
 * @file isrs_impl.c
 * @brief Implements routines that handle interrupts
 */

#include "isrs.h"

#include <stdio.h>
#include <stdlib.h>

#define PIC_MASTER_COMMAND     0x20                     /** @brief Base and command port for the master PIC */
#define PIC_MASTER_DATA        PIC_MASTER_COMMAND + 1   /** @brief Data port for the master PIC */
#define PIC_MASTER_LINES       8                        /** @brief Number of interrupts that the master PIC can handle */

#define PIC_SLAVE_COMMAND      0xA0                     /** @brief Base and command port for the slave PIC */
#define PIC_SLAVE_DATA         PIC_SLAVE_COMMAND + 1    /** @brief Data port for the slave PIC */
#define PIC_SLAVE_LINES        8                        /** @brief Number of interrupts that the slave PIC can handle */

#define PIC_INIT               0x10                     /** @brief Initialize the PIC chip */
#define PIC_INIT_FLAG_USE_ICW4 0x01                     /** @brief Use fourth initialization word for environment configuration */
#define PIC_ICW4_FLAG_8086     0x01                     /** @brief Use 8086/8088 mode as opposed to MCS-80/85 mode */

#define PIC_EOI                0x20                     /** @brief Indicate that we're done handling the instruction */


/** @brief Brief error messages printed out when an exception occurs */
static const char *exception_msg[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"};

/** @internal Print the state of the stack when an exception was called */
static void dump_stack(struct isr_state *state)
{
    printf("Stack:\nGS: %X, FS: %X, ES: %X, DS: %X\nEDI: %X, ESI: %X, EBP: %X, ESP: %X\nEBX: %X, EDX: %X, ECX: %X, EAX: %X\nEIP: %X, CS: %X, EFLAGS: %X, USRESP: %X, SS: %X\n",
           state->gs,
           state->fs,
           state->es,
           state->ds,
           state->edi,
           state->esi,
           state->ebp,
           state->esp,
           state->ebx,
           state->edx,
           state->ecx,
           state->eax,
           state->eip,
           state->cs,
           state->eflags,
           state->useresp,
           state->ss);
}

/**
 * @brief Handles software exceptions
 * 
 * @param state State of the stack on exception
 */
void fault_handler(struct isr_state state)
{
    printf("Exception [AT %X][ID %X][ERROR CODE %X]: ", state.eip, state.id, state.err_code);
    if (state.id < 32)
    {
        puts(exception_msg[state.id]);
    }
    else
    {
        puts("Unknown");
    }
    dump_stack(&state);
    abort();
}

/**
 * @brief Handles hardware interrupts
 * 
 * @param state State of the stack on interrupt
 */
void irq_handler(struct isr_state state)
{
    printf("IRQ Handled.");

    // id >= 40 implies this was from the slave PIC
    if (state.id >= 40)
    {
        outb(PIC_SLAVE_COMMAND, PIC_EOI);
    }
    outb(PIC_MASTER_COMMAND, PIC_EOI);
}

void irq_remap()
{
    // Need to send some bytes to the PIC
    // https://wiki.osdev.org/PIC#Programming_the_PIC_chips

    // ICW1: Initialize both chips
    outb(PIC_MASTER_COMMAND, PIC_INIT | PIC_INIT_FLAG_USE_ICW4);
    outb(PIC_SLAVE_COMMAND, PIC_INIT | PIC_INIT_FLAG_USE_ICW4);

    // ICW2: Set IRQ offsets
    outb(PIC_MASTER_DATA, IRQ_OFFSET);
    outb(PIC_SLAVE_DATA, IRQ_OFFSET + PIC_MASTER_LINES);

    // ICW3: Configure them as master/slave
    outb(PIC_MASTER_DATA, 0x04);
    outb(PIC_SLAVE_DATA, 0x02);

    // ICW4: Run in x86 mode
    outb(PIC_MASTER_DATA, PIC_ICW4_FLAG_8086);
    outb(PIC_SLAVE_DATA, PIC_ICW4_FLAG_8086);

    // Unmask all interrupts
    outb(PIC_MASTER_DATA, 0x0);
    outb(PIC_SLAVE_DATA, 0x0);
}
