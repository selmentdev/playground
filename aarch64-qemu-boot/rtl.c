#include "header.h"

sys_result_t
rtl_internal_string_from_uint_validate(
    const char* buffer,
    size_t      buffer_length,
    int         base,
    boolean_t   is_negative
)
{
    if (buffer == NULL)
    {
        return E_INVALID_ARGUMENT;
    }

    if (buffer_length == 0)
    {
        return E_INVALID_ARGUMENT;
    }

    if (buffer_length <= (is_negative ? 2 : 1))
    {
        return E_INVALID_RANGE;
    }

    if (!(2 <= base && base <= 36))
    {
        return E_INVALID_RANGE;
    }

    return S_OK;
}
sys_result_t
rtl_internal_string_from_uint64(
    uint64_t    value,
    char*       buffer,
    size_t      buffer_length,
    int         base,
    boolean_t   is_negative
)
{
    sys_result_t status = rtl_internal_string_from_uint_validate(buffer, buffer_length, base, is_negative);
    if (SYS_RESULT_SUCCESS(status))
    {
        uint64_t remaining = value;
        char* buf = buffer;

        size_t length = 0;
        if (is_negative)
        {
            (*buf++) = '-';
            ++length;

            remaining = (uint64_t)-((int64_t)remaining);
        }

        char* first_digit = buffer;

        do
        {
            const unsigned int digit = (unsigned int)(remaining % base);
            remaining /= base;

            if (digit > 9)
            {
                (*buffer++) = (char)(digit - 10 + 'a');
            }
            else
            {
                (*buffer++) = (char)(digit + '0');
            }

            ++length;
        } while (remaining > 0 && length < buffer_length);

        if (length >= buffer_length)
        {
            buffer[0] = '\0';
            return E_INVALID_RANGE;
        }

        (*buffer--) = '\0';

        do
        {
            char t = (*buffer);
            (*buffer) = (*first_digit);
            (*first_digit) = t;
            --buffer;
            ++first_digit;
        } while (first_digit < buffer);
    }

    return status;
}

sys_result_t
rtl_string_from_uint64(
    uint64_t    value,
    char*       buffer,
    size_t      buffer_length,
    int         base
)
{
    return rtl_internal_string_from_uint64(
        (uint64_t)value,
        buffer,
        buffer_length,
        base,
        FALSE
    );
}