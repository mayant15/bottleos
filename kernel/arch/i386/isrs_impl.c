#include "isrs.h"

#include <stdio.h>
#include <stdlib.h>

const char* exception_msg[] = {
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
    "Reserved"
};

void print_stack(struct isr_state *state)
{
    printf("Stack: gs: %d, fs: %d, es: %d, ds: %d, edi: %d, esi: %d, ebp: %d, esp: %d, ebx: %d, edx: %d, ecx: %d, eax: %d, id: %d, err: %d, eip: %d, cs: %d, eflags: %d, usresp: %d, ss: %d",
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
        state->id, 
        state->err_code,
        state->eip,
        state->cs,
        state->eflags, 
        state->useresp, 
        state->ss
    );
}

void fault_handler(struct isr_state state)
{
    if (state.id < 32)
    {
        puts(exception_msg[state.id]);
    }
    abort();
}
