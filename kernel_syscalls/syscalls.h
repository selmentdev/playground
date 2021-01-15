#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ASSERT(x) \
    do \
    { \
        if (!(x)) \
        { \
            printf("assertion failed:\n%s:%u\n%s\n", __FILE__, __LINE__, #x); \
            abort(); \
        } \
    } while (false)

#if defined(__cplusplus)
extern "C" {
#endif

int posix_foobar(
    const char* text,
    int const* numbers,
    size_t numbers_count,
    int* sum,
    char* chars,
    size_t* chars_count);

int posix_unknown();

int posix_barbaz(int const* x, int const* y, int* results, size_t count);

void test_cxx_syscalls();

#define STATUS_INVALID_SYSTEM_SERVICE 0xC000004C

#if defined(__cplusplus)
}
#endif

#endif // SYSCALLS_H
