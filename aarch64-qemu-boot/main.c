#include "header.h"

volatile unsigned int * const UART0DR = (unsigned int *) 0x09000000;
 
void print_uart0(const char *s) {
    while(*s != '\0') { 		/* Loop until end of string */
         *UART0DR = (unsigned int)(*s); /* Transmit char */
          s++;			        /* Next char */
    }
}

void c_entry() {
     print_uart0("Hello aarch64");
}

#define ENTRY(name, base)         do { \
    print_uart0(#name ": "); \
    rtl_string_from_uint64(__builtin_bswap64(((arch_devicetree_boot_header_t*)fdt)->name) >> 32, data, sizeof(data), base); \
    print_uart0(data); \
    print_uart0("\r\n"); \
} \
while (0)
 
void c_entry2(uint32_t* fdt, uint64_t pc, uint64_t sp) {
    char data[64];
    
    rtl_string_from_uint64(pc, data, sizeof(data), 0x10);
    print_uart0("program-counter: ");
    print_uart0(data);
    print_uart0("\r\n");
    rtl_string_from_uint64(sp, data, sizeof(data), 0x10);
    print_uart0("stack-pointer: ");
    print_uart0(data);
    print_uart0("\r\n");
    rtl_string_from_uint64((uint64_t)(void*)fdt, data, sizeof(data), 0x10);
    print_uart0("flat-device-tree-blob: ");
    print_uart0(data);
    print_uart0("\r\n");

    ENTRY(magic, 0x10);
    ENTRY(total_size, 10);
    ENTRY(offset_of_structure, 0x10);
    ENTRY(offset_of_strings, 0x10);
    ENTRY(offset_of_memory_map, 0x10);
    ENTRY(version, 10);
    ENTRY(version_compatible, 10);
    ENTRY(boot_cpuid, 10);
    ENTRY(size_of_strings_block, 10);
    ENTRY(size_of_structure_block, 10);
}
