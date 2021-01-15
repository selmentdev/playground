#pragma once
#include <cstdint>
#include <cstddef>
#include <string_view>
#include <span>
#include "base.h"

namespace corydale
{
    using std::string_view;

    template <typename T>
    using array_view = std::span<T>;

    using os_result = int;
}

namespace corydale::syscalls
{
    struct syscall_foobar_params
    {
        string_view in_text{};
        array_view<int const> in_numbers{};
        int out_sum{};
        array_view<char> out_chars;
        size_t out_chars_size;
    };

    extern "C"
    {
        extern funcattr_noinline os_result syscall_foobar(syscall_foobar_params* params) noexcept;
    }

    extern "C"
    {
        extern funcattr_noinline os_result call_syscall_foobar(syscall_foobar_params* params) noexcept;
        extern funcattr_noinline os_result call_syscall_unknown() noexcept;
    }
}
