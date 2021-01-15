#include <cstdint>
#include <cstdio>
#include <cstdlib>

#define ASSERT(x) \
    do \
    { \
        if (!(x)) \
        { \
            printf("assertion failed:\n%s:%u\n%s\n", __FILE__, __LINE__, #x); \
            abort(); \
        } \
    } while (false)

#define STATUS_INVALID_SYSTEM_SERVICE 0xC000004C

extern "C"
{
    extern int call_function_1(uint64_t* result, uint64_t a, uint64_t b);
    extern int call_function_2(float* result, float a, float b, float c);
    extern int call_function_3(uint8_t* result);
    extern int call_function_4(float* result);
    extern int call_function_5(uint32_t* result, float x, float y);
    extern int call_function_6(uintptr_t* result, uintptr_t x, const char* ptr);
    extern int call_check_all_abi_registers(uintptr_t* result, uintptr_t a, uintptr_t b, uintptr_t c, uintptr_t d, uintptr_t e, uintptr_t f, uintptr_t g, uintptr_t h, uintptr_t i, uintptr_t j, uintptr_t k);

    extern int call_function_0x2137(void);
}

int main()
{
    int status;

    {
        uint64_t result = 0;

        status = call_function_1(&result, 1, 2);
        ASSERT(status == 0);
        ASSERT(result == 3);
    }

    {
        float result = 0.0F;

        status = call_function_2(&result, 1.0F, 2.0F, 3.0F);

        ASSERT(status == 0);
        ASSERT(result >= 4.99999F);
        ASSERT(result <= 5.00001F);
    }

    {
        uint8_t result = 0;
        status         = call_function_3(&result);

        ASSERT(status == 0);
        ASSERT(result == 0x42);
    }

    {
        float result = 0.0F;
        status       = call_function_4(&result);

        ASSERT(status == 0);
    }

    {
        uint32_t result = 0;
        status          = call_function_5(&result, 1.0F, 2.0F);

        ASSERT(status == 0);
        ASSERT(result == 0x7f800000);
    }

    {
        uintptr_t result = 0;
        const char* ptr  = (const char*)-1;
        status           = call_function_6(&result, 0x1, ptr);

        ASSERT(status == 0);
        ASSERT(result == (uintptr_t)-2);
    }

    {
        const char* ptr = (const char*)-1;
        status          = call_function_6(nullptr, 0x1, ptr);

        ASSERT(status == -1);
    }

    {
        status = call_function_0x2137();

        ASSERT(status == STATUS_INVALID_SYSTEM_SERVICE);
    }

    {
        uintptr_t result = 0;
        status           = call_check_all_abi_registers(&result, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

        ASSERT(status == 0);
        ASSERT(result == 11);
    }

    {
        status = call_check_all_abi_registers(nullptr, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

        ASSERT(status == -1);
    }

    return 0;
}
