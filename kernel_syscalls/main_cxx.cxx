#include "syscalls.h"
#include "syscalls.hxx"

extern "C"
{
    void test_cxx_syscalls()
    {
        printf("%s:%d\n", __FILE__, __LINE__);
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
            int const result = Corydale::Unknown();
            ASSERT(result == STATUS_INVALID_SYSTEM_SERVICE);
        }
    }
}
