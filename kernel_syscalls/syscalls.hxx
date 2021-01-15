#pragma once
#include <cstdint>
#include <cstddef>
#include <string_view>
#include <span>
#include "base.h"
#include "syscalls.h"

namespace Corydale
{
    using StatusCode = int;

    using StringView = std::string_view;

    template <typename T>
    using ArrayView = std::span<T>;
}

namespace Corydale::Syscalls
{
    template <typename T>
    struct MutableArray final
    {
        T* Array;
        size_t Count;
    };

    template <typename T>
    struct ImmutableArray final
    {
        T const* Array;
        size_t Count;
    };

    struct MutableString final
    {
        char* Array;
        size_t Count;
    };

    struct ImmutableString final
    {
        const char* Array;
        size_t Count;
    };

    constexpr StringView ToStringView(MutableString value) noexcept
    {
        return StringView{ value.Array, value.Count };
    }

    constexpr StringView ToStringView(ImmutableString value) noexcept
    {
        return StringView{ value.Array, value.Count };
    }

    template <typename T>
    constexpr ArrayView<T> ToArrayView(MutableArray<T> value) noexcept
    {
        return ArrayView<T>{ value.Array, value.Count };
    }

    template <typename T>
    constexpr ArrayView<T const> ToArrayView(ImmutableArray<T> value) noexcept
    {
        return ArrayView<T const>{ value.Array, value.Count };
    }

    constexpr ArrayView<char> ToArrayView(MutableString value) noexcept
    {
        return ArrayView<char>{ value.Array, value.Count };
    }
}

namespace Corydale::Syscalls
{
    struct Syscall__FoobarParams final
    {
        ImmutableString Text;
        ImmutableArray<int> Numbers;
        MutableString Chars;
        int Sum;
    };

    // Actual syscall implementation function.
    // Must be visible in assembly, thus C FFI.
    extern "C"
    {
        extern funcattr_noinline StatusCode Syscall__Foobar(Syscall__FoobarParams& params) noexcept;
        extern funcattr_noinline StatusCode Syscall__Barbaz(ImmutableArray<int> x, ImmutableArray<int> y, MutableArray<int> results) noexcept;
    }

    // Stubs for invoking syscalls from FFI and C++ wrappers
    extern "C"
    {
        extern funcattr_noinline StatusCode Invoke__Foobar(Syscall__FoobarParams& params) noexcept;
        extern funcattr_noinline StatusCode Invoke__Unknown() noexcept;
        extern funcattr_noinline StatusCode Invoke__Retired() noexcept;
        extern funcattr_noinline StatusCode Invoke__Barbaz(ImmutableArray<int> x, ImmutableArray<int> y, MutableArray<int> results) noexcept;
    }
}

namespace Corydale
{
    // Actual C++ functions providing APIs
    extern funcattr_noinline StatusCode Unknown() noexcept;

    extern funcattr_noinline StatusCode Retired() noexcept;

    extern funcattr_noinline StatusCode Foobar(
        StringView text,
        ArrayView<int> numbers,
        int& sum,
        ArrayView<char> chars,
        size_t& chars_count) noexcept;

    extern funcattr_noinline StatusCode Barbaz(
        ArrayView<int const> x,
        ArrayView<int const> y,
        ArrayView<int> results) noexcept;
}
