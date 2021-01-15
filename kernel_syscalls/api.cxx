#include "syscalls.h"
#include "syscalls.hxx"
#include <cstring>


namespace Corydale
{
    extern StatusCode Unknown() noexcept
    {
        return Syscalls::Invoke__Unknown();
    }

    extern StatusCode Foobar(
        StringView text,
        ArrayView<int> numbers,
        int& sum,
        ArrayView<char> chars,
        size_t& chars_count) noexcept
    {
        Syscalls::Syscall__FoobarParams params{
            .Text    = { text.data(), text.size() },
            .Numbers = { numbers.data(), numbers.size() },
            .Chars   = { chars.data(), chars.size() },
        };

        StatusCode const result = Syscalls::Invoke__Foobar(params);

        if (result == 0)
        {
            chars_count = params.Chars.Count;
            sum         = params.Sum;
        }

        return result;
    }
}


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
        if (sum == nullptr || chars_count == nullptr)
        {
            return -1;
        }

        using namespace Corydale::Syscalls;

        Syscall__FoobarParams params{
            .Text    = { text, __builtin_strlen(text) },
            .Numbers = { numbers, numbers_count },
            .Chars   = { chars, *chars_count },
        };

        int const result = Invoke__Foobar(params);

        if (result == 0)
        {
            *chars_count = params.Chars.Count;
            *sum         = params.Sum;
        }

        return result;
    }

    int posix_unknown()
    {
        using namespace Corydale::Syscalls;

        return Invoke__Unknown();
    }
}
