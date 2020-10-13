// These sections must be provided so that gcc can 
// inject _init and _fini functions from its own .o files
// to enable global constructors.

.section .init
    // gcc will place crtend.o's .init section here
    popl %ebp
    ret

.section .fini
    // gcc will place crtend.o's .fini section here
    popl %ebp
    ret
