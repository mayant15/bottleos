#include <stdio.h>
#include <kernel/tty.h>
#include <stdint.h>

/** Entry point for the BottleOS kernel */
void kernel_main(void)
{
    terminal_initialize();
    printf("Hello, kernel world!\n");

    // NOTE: I tried doing a simple 5 / 0 here but GCC generated a `ud2`
    // instruction here while optimizing it.
    // https://stackoverflow.com/questions/26309300/c-code-with-undefined-results-compiler-generates-invalid-code-with-o3
    volatile int x = 0;
    x = 1 / x;
}
