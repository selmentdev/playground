#include "syscalls.h"
#include "syscalls.hxx"

extern "C"
{
    void test_cxx_syscalls()
    {
        {
            int numbers[4] = {
                1,
                2,
                3,
                4,
            };
            char buffer[32];
            size_t processed;
            int sum;

            puts("Corydale::Foobar");
            int const result = Corydale::Foobar(
                "hello",
                numbers,
                sum,
                buffer,
                processed);
            ASSERT(result == 0);
            ASSERT(sum == 10);
            ASSERT(processed == 5);
            ASSERT(buffer[0] == 'H');
            ASSERT(buffer[1] == 'E');
            ASSERT(buffer[2] == 'L');
            ASSERT(buffer[3] == 'L');
            ASSERT(buffer[4] == 'O');
            ASSERT(buffer[5] == '\0');
        }
        {
            puts("Corydale::Unknown");
            int const result = Corydale::Unknown();
            ASSERT(result == STATUS_INVALID_SYSTEM_SERVICE);
        }
        {
            int x[]{
                1,
                2,
                3,
                4,
            };
            int y[]{
                10,
                20,
                30,
                40,
            };
            int results[4];

            puts("Corydale::Barbaz");
            int const result = Corydale::Barbaz(x, y, results);

            ASSERT(result == 0);
            ASSERT(results[0] == 11);
            ASSERT(results[1] == 22);
            ASSERT(results[2] == 33);
            ASSERT(results[3] == 44);
        }
    }
}
