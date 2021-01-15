#include "syscalls.h"
#include "syscalls.hxx"
#include <cstring>

extern "C"
{
    int posix_foobar(
        const char* text,
        int const* numbers,
        size_t numbers_count,
        int* sum,
        char* chars,
        size_t* chars_count)
    {
        if (chars_count == nullptr)
        {
            return -2;
        }

        using namespace corydale::syscalls;

        syscall_foobar_params params{
            .in_text{ text, strlen(text) },
            .in_numbers{ numbers, numbers_count },
            .out_sum        = {},
            .out_chars      = { chars, *chars_count },
            .out_chars_size = 0,
        };

        int const result = call_syscall_foobar(&params);

        *sum         = params.out_sum;
        *chars_count = params.out_chars_size;

        return result;
    }

    int posix_unknown()
    {
        using namespace corydale::syscalls;

        return call_syscall_unknown();
    }
}
