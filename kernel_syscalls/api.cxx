#include "syscalls.h"
#include "syscalls.hxx"
#include <cstring>


namespace Corydale
{
    extern StatusCode Unknown() noexcept
    {
        return Syscalls::Invoke__Unknown();
    }

    extern StatusCode Retired() noexcept
    {
        return Syscalls::Invoke__Retired();
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


    extern funcattr_noinline StatusCode Barbaz(
        ArrayView<int const> x,
        ArrayView<int const> y,
        ArrayView<int> results) noexcept
    {
        return Syscalls::Invoke__Barbaz(
            { x.data(), x.size() },
            { y.data(), y.size() },
            { results.data(), results.size() });
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

    int posix_retired()
    {
        return Corydale::Syscalls::Invoke__Retired();
    }

    int posix_unknown()
    {
        using namespace Corydale::Syscalls;

        return Invoke__Unknown();
    }

    int posix_barbaz(int const* x, int const* y, int* results, size_t count)
    {
        using namespace Corydale::Syscalls;
        return Invoke__Barbaz(
            { x, count },
            { y, count },
            { results, count });
    }
}
