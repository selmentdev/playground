

.global _start
_start:
    b           arch_kernel_main2        // branch to arch-specific kernel main
    .long       0                       // reserved
    .quad       0x00040000  //le64sym     boot_kernel_offset      // kernel offset in address space, 0x00080000
    .quad       0x00010000  //le64sym     boot_kernel_size        // size of kernel image
    .quad       ((2 << 1) | (1 << 3))            //le64sym     boot_kernel_flags       // kernel flags for linux boot loader protocol
    .quad       0                       // reserved
    .quad       0                       // reserved
    .quad       0                       // reserved
    .long       0x644d5241              // 'ARM\x64'
    .long       0

hang:
	b hang

.extern c_entry

.global arch_kernel_main
arch_kernel_main:
    ldr x30, =stack_top	// setup stack
    mov sp, x30
    bl c_entry
1:
    wfe                                 // wait for event
    wfi                                 // wait for interrupt
    b       1b                          // loop until end of the hello world

.global arch_kernel_main2
arch_kernel_main2:
    ldr x30, =stack_top	// setup stack
    mov sp, x30
    adr x1, .
    mov x2, sp
    bl c_entry2
1:
    wfe                                 // wait for event
    wfi                                 // wait for interrupt
    b       1b                          // loop until end of the hello world
