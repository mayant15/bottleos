# Declare constants for the multiboot header
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as per the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Create a 16KiB stack for the initial thread
# .section .bss
# .align 16
# stack_bottom:
# .skip 163843
# stack_top:

.section .data
gdt:
gdt_null: # Null segment, required by the specification
	.long 0
	.long 0
gdt_code: # Code segment starts at zero and covers the entire 4GB address space
	.short 0xFFFF       # 4GB limit
	.short 0			# Starts at 0
	.byte  0			# Bits 16-23 in the base address, required by the specification
	.byte  0b10011010   # Configuration flags for the code segment. This is a readable executable non-conforming segment
	.byte  0b11001111   # Configure to use 4KiB granularity and 32-bit protected mode, as opposed to 16-bit
	.byte  0			# Bits 24-31 in the base address, required by the specification
gdt_data: # Data segment starts at zero and covers the entire 4GB address space
	.short 0xFFFF       # 4GB limit
	.short 0			# Starts at 0
	.byte  0			# Bits 16-23 in the base address, required by the specification
	.byte  0b10010010   # Configuration flags for the data segment. This is a readable non-executable non-conforming segment
	.byte  0b11001111   # Configure to use 4KiB granularity and 32-bit protected mode, as opposed to 16-bit
	.byte  0			# Bits 24-31 in the base address, required by the specification
gdt_end:
gdt_desc:
	.short gdt_end - gdt - 1  # Size of the GDT declaration
	.long  gdt                # Address of the GDT

# The kernel entry point.
.section .text
.global _start
.type _start, @function # This here is a 'symbol attribute' that provides debug info
_start:
	 /* 
       This is a good place to initialize crucial processor state before the
       high-level kernel is entered. It is best to minimize the early
       environment where crucial features are offline. Note that the
       processor is not fully initialized yet: Features such as floating
       point instructions and instruction set extensions are not initialized
       yet.
    */

	# Load the GDT
	cli
	xor %ax, %ax
	mov %ax, %ds
	lgdt gdt_desc

	# Enter 32-bit protected mode (set bit 0 in CR0 to 1)
	mov %cr0, %eax
	or $1, %eax
	mov %eax, %cr0

	ljmp $0x08, $pmode_main # This sets up the CS register too

pmode_main:
	# Set the remaining registers
	mov $0x10, %eax
	mov %eax, %ds
	mov %eax, %ss
	mov %eax, %es
	mov %eax, %fs
	mov %eax, %gs

	# Set the stack
	mov $0x8000, %esp

	# TODO: Enable paging
	sti

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# TODO: Hang if kernel_main unexpectedly returns?
	cli
hang:
	jmp hang

# Set size of the _start symbol to simplify debugging
.size _start, . - _start
