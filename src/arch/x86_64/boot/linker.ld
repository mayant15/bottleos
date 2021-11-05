/* Specify the label that is to be used as the entry point */
ENTRY(_start)

SECTIONS {
    /* 
     * Load the first section at 1MB. Memory before that may
     * be reserved for other uses (eg. VGA buffer)
     */
    . = 1M;

    /* Place the multiboot_header at the top */
    .boot :
    {
        *(.multiboot_header)
    }

    /* Then place our text section */
    .text :
    {
        *(.text)
    }
}
