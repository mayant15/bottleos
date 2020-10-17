#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int putchar(int ic)
{
#if defined(__is_libk)
    // If this is called as a freestanding library, then use the kernel's tty utilities
    terminal_putchar((char) ic);
#else
    // TODO: Implement stdio and the write system call.
#endif
    return ic;
}
