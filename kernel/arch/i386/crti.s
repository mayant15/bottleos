// These sections must be provided so that gcc can 
// inject _init and _fini functions from its own .o files
// to enable global constructors.

.section .init
.global _init
.type _init, @function
_init:
    push %ebp
    movl %esp, %ebp
    // gcc will place crtbegin.o's .init section here

.section .fini
.global _fini
.type _fini, @function
_fini:
    push %ebp
    movl %esp, %ebp
    // gcc will place crtbegin.o's .fini section here
