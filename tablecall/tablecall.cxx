#include <cstdint>

extern "C"
{

    extern int svc_function_1(uint64_t* result, uint64_t a, uint64_t b)
    {
        if (result == nullptr)
        {
            return -1;
        }

        *result = a ^ b;

        return 0;
    }

    extern int svc_function_2(float* result, float a, float b, float c)
    {
        if (result == nullptr)
        {
            return -1;
        }

        *result = a * b + c;

        return 0;
    }

    extern int svc_function_3(uint8_t* result)
    {
        if (result == nullptr)
        {
            return -1;
        }

        *result = 0x42;

        return 0;
    }

    extern int svc_function_4(float* result)
    {
        if (result == nullptr)
        {
            return -1;
        }

        *result = 3.14159F;

        return 0;
    }

    extern int svc_function_5(uint32_t* result, float x, float y)
    {
        union
        {
            float f;
            uint32_t u;
        } uf;

        uf.f = x;

        uint32_t r = uf.u;

        uf.f = y;
        r ^= uf.u;

        *result = r;

        return 0;
    }

    extern int svc_function_6(uintptr_t* result, uintptr_t x, const char* ptr)
    {
        if (result == nullptr)
        {
            return -1;
        }

        *result = x ^ (uintptr_t)ptr;

        return 0;
    }

    extern int svc_check_all_abi_registers(uintptr_t* result, uintptr_t a, uintptr_t b, uintptr_t c, uintptr_t d, uintptr_t e, uintptr_t f, uintptr_t g, uintptr_t h, uintptr_t i, uintptr_t j, uintptr_t k)
    {
        if (result == nullptr)
        {
            return -1;
        }

        *result = a + b + c + d + e + f + g + h + i + j + k;

        return 0;
    }
}
