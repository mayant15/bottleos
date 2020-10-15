#include <stdio.h>
#include <kernel/tty.h>
#include <stdint.h>


/**
 * @brief Entry point for the BottleOS kernel.
 * 
 * This function is called when the bootloader passed control to the kernel.
 * 
 */
void kernel_main(void)
{
    terminal_initialize();
    printf("Hello, kernel world!\n");
    uint8_t d = 5 / 0;
    printf("%d", d);
}

