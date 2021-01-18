#pragma once
#include <cstdlib>
#include <cstdint>
#include <cstdio>

#define ASSERT(x) \
    do \
    { \
        if (!(x)) \
        { \
            printf("\033[36;01massertion failed: %s\n%s:%d\033[0m\n", #x, __FILE__, __LINE__); \
        } \
    } while (false)

namespace corydale::kernel::memory
{
    enum class memory_pool : uint32_t
    {
        kernel     = 0xdeadbeef,
        user       = 0xbabecafe,
        hypervisor = 0xbaca1337,
    };

    struct pool_header final
    {
        memory_pool pool;
        size_t size;
    };

    template <memory_pool Pool>
    class pooled_object
    {
    public:
        static void* operator new(size_t size) noexcept
        {
            char* buffer        = reinterpret_cast<char*>(::malloc(size + sizeof(pool_header)));
            pool_header* header = reinterpret_cast<pool_header*>(buffer);
            header->pool        = Pool;
            header->size        = size;

            void* result = (buffer + sizeof(pool_header));
            printf("\033[34;01mnew (pool: %u, size: %zu, ptr: %p)\033[0m\n", Pool, size, result);
            return result;
        }

        static void operator delete(void* ptr) noexcept
        {
            char* buffer        = reinterpret_cast<char*>(ptr);
            pool_header* header = reinterpret_cast<pool_header*>(buffer - sizeof(pool_header));
            printf("\033[35;01mdel (pool: %u, size: %zu, ptr: %p)\033[0m\n", header->pool, header->size, header);
            ASSERT(header->pool == Pool);
            ::free(header);
        }
    };
}