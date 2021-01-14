#ifndef INCLUDED_HEADER_H
#define INCLUDED_HEADER_H

typedef int sys_result_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned long long uint64_t;
typedef long long int64_t;
typedef unsigned long long size_t;
typedef int boolean_t;
#define FALSE 0
#define UINT64_MAX 0xFFFFFFFFFFFFFFFFULL
#define rtl_char_is_space(x) ((x) == ' ')
#define E_INVALID_ARGUMENT      -1
#define E_INVALID_RANGE         -2
#define NULL 0
#define SYS_RESULT_SUCCESS(x) ((x) >= 0)
#define __c_predict_false(x) x
#define __c_predict_true(x) x
#define UINT32_MAX 0xFFFFFFFFU
#define S_OK 0

//
// https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/plain/Documentation/devicetree/booting-without-of.txt?id=HEAD
// http://lxr.free-electrons.com/source/Documentation/arm64/booting.txt
//
typedef struct arch_devicetree_boot_header_t {
    uint32_t    magic;
    uint32_t    total_size;
    uint32_t    offset_of_structure;
    uint32_t    offset_of_strings;
    uint32_t    offset_of_memory_map;
    uint32_t    version;
    uint32_t    version_compatible;
    uint32_t    boot_cpuid;                     // version == 2
    uint32_t    size_of_strings_block;          // version == 3
    uint32_t    size_of_structure_block;        // version == 17
} arch_devicetree_boot_header_t;

sys_result_t
rtl_string_from_uint64(
    uint64_t    value,
    char*       buffer,
    size_t      buffer_length,
    int         base
);


#endif // INCLUDED_HEADER_H