# Declare constants for the multiboot header
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function # This here is a 'symbol attribute' that provides debug info
_start:
	movl $stack_top, %esp

	 /* 
       This is a good place to initialize crucial processor state before the
       high-level kernel is entered. It is best to minimize the early
       environment where crucial features are offline. Note that the
       processor is not fully initialized yet: Features such as floating
       point instructions and instruction set extensions are not initialized
       yet. The Global Descriptor Table should be loaded here. Paging should be 
       enabled here. C++ features such as global constructors and exceptions will 
       require runtime support to work as well.
    */
    

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# TODO: Hang if kernel_main unexpectedly returns?
	# cli
#1:	hlt
	# jmp 1b
1:
	jmp 1b

# Set size of the _start symbol to simplify debugging
.size _start, . - _start
