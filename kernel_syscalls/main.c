#include "syscalls.h"

int main()
{
    puts("start");

    test_cxx_syscalls();

    {
        puts("posix_foobar");
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
        puts("posix_unknown");
        int const result = posix_unknown();
        ASSERT(result == STATUS_INVALID_SYSTEM_SERVICE);
    }
    {
        int const count = 4;
        int x[count]    = {
            1,
            2,
            3,
            4,
        };
        int y[count] = {
            10,
            20,
            30,
            40,
        };
        int results[count];

        puts("posix_barbaz");
        int const result = posix_barbaz(x, y, results, count);

        ASSERT(result == 0);
        ASSERT(results[0] == 11);
        ASSERT(results[1] == 22);
        ASSERT(results[2] == 33);
        ASSERT(results[3] == 44);
    }

    puts("stop");
    return 0;
}
