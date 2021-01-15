#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "syscalls.h"

#define ASSERT(x) \
    do \
    { \
        if (!(x)) \
        { \
            printf("assertion failed:\n%s:%u\n%s\n", __FILE__, __LINE__, #x); \
            abort(); \
        } \
    } while (false)

#define STATUS_INVALID_SYSTEM_SERVICE 0xC000004C

int main()
{
    puts("start");
    char buffer[32];
    size_t buffer_size = sizeof(buffer);

    int numbers[4] = {
        1,
        2,
        3,
        4,
    };
    size_t numbers_count = 4;

    int sum    = 0;
    int result = posix_foobar("hello", numbers, numbers_count, &sum, buffer, &buffer_size);
    ASSERT(result == 0);
    ASSERT(sum == 10);
    ASSERT(buffer_size == 5);
    ASSERT(buffer[0] == 'H');
    ASSERT(buffer[1] == 'E');
    ASSERT(buffer[2] == 'L');
    ASSERT(buffer[3] == 'L');
    ASSERT(buffer[4] == 'O');
    ASSERT(buffer[5] == '\0');

    result = posix_unknown();
    ASSERT(result == STATUS_INVALID_SYSTEM_SERVICE);

    puts("stop");
    return 0;
}
