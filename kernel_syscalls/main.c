#include "syscalls.h"

int main()
{
    puts("start");

    test_cxx_syscalls();
    printf("%s:%d\n", __FILE__, __LINE__);

    {
        char buffer[32];
        size_t buffer_size = sizeof(buffer);

        int numbers[4] = {
            1,
            2,
            3,
            4,
        };
        size_t numbers_count = 4;

        int sum          = 0;
        int const result = posix_foobar("hello", numbers, numbers_count, &sum, buffer, &buffer_size);
        ASSERT(result == 0);
        ASSERT(sum == 10);
        ASSERT(buffer_size == 5);
        ASSERT(buffer[0] == 'H');
        ASSERT(buffer[1] == 'E');
        ASSERT(buffer[2] == 'L');
        ASSERT(buffer[3] == 'L');
        ASSERT(buffer[4] == 'O');
        ASSERT(buffer[5] == '\0');
    }

    {
        int const result = posix_unknown();
        ASSERT(result == STATUS_INVALID_SYSTEM_SERVICE);
    }

    puts("stop");
    return 0;
}
