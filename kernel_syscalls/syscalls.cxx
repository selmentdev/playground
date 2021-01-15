#include "syscalls.hxx"
#include <algorithm>
#include <cstring>
#include <cctype>

extern "C"
{
    namespace corydale::syscalls
    {
        extern os_result syscall_foobar(syscall_foobar_params* params) noexcept
        {
            params->out_chars_size = params->in_text.size();

            if (params->in_text.size() > params->out_chars.size())
            {
                return -1;
            }
            else
            {
                std::transform(params->in_text.begin(), params->in_text.end(), params->out_chars.begin(), toupper);
            }

            int sum{};
            for (int i : params->in_numbers)
            {
                sum += i;
            }

            params->out_sum = sum;

            return 0;
        }
    }
}
