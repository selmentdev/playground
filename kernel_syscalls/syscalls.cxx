#include "syscalls.hxx"
#include <algorithm>
#include <cstring>
#include <cctype>
#include <numeric>

extern "C"
{
    namespace Corydale::Syscalls
    {
        extern StatusCode Syscall__Foobar(Syscall__FoobarParams& params) noexcept
        {
            if (params.Chars.Array == nullptr || params.Text.Array == nullptr || params.Numbers.Array == nullptr)
            {
                return -1;
            }

            if (params.Text.Count >= params.Chars.Count)
            {
                return -1;
            }

            auto const text  = ToStringView(params.Text);
            auto const chars = ToArrayView(params.Chars);

            ASSERT(params.Chars.Count >= params.Text.Count);

            std::transform(
                text.begin(),
                text.end(),
                chars.begin(),
                toupper);

            params.Chars.Count                     = params.Text.Count;
            params.Chars.Array[params.Chars.Count] = '\0';

            auto const numbers = ToArrayView(params.Numbers);

            params.Sum = std::accumulate(
                numbers.begin(),
                numbers.end(),
                int{ 0 });

            return 0;
        }

        extern StatusCode Syscall__Barbaz(ImmutableArray<int> x, ImmutableArray<int> y, MutableArray<int> results) noexcept
        {
            if (x.Array == nullptr || y.Array == nullptr || results.Array == nullptr)
            {
                return -1;
            }

            if (x.Count == 0 || y.Count == 0 || results.Count == 0)
            {
                return -2;
            }

            for (size_t i = 0; i < results.Count; ++i)
            {
                results.Array[i] = x.Array[i] + y.Array[i];
            }

            return 0;
        }

    }
}
