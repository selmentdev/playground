OUTPUT_ARCH(aarch64)
ENTRY(_start)

SECTIONS
{
	. = 0x40000000;

	.startup . : { startup64.o(.text) }
	.text : { *(.text) }
	.data : { *(.data) }
	.bss : { *(.bss COMMON) }
	. = ALIGN(8);
	. = . + 0x1000; /* 4kB of stack memory */
	stack_top = .;
    
	/DISCARD/ : {
		*(.discard)
		*(.discard.*)
		*(.interp .dynamic)
		*(.dynsym .dynstr .hash)
        *(.note.*)
	}
}
