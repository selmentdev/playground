#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stddef.h>

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

#if defined(__cplusplus)
}
#endif

#endif // SYSCALLS_H
