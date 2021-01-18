#include "pool.hxx"

#define corydale_noinline __attribute__((__noinline__))

namespace corydale::kernel
{
    class user_object : public memory::pooled_object<memory::memory_pool::user>
    {
    public:
        user_object() noexcept;
        virtual ~user_object() noexcept;
        virtual bool wait() noexcept = 0;
    };

    corydale_noinline user_object::user_object() noexcept
    {
        printf("\033[31;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline user_object::~user_object() noexcept
    {
        printf("\033[32;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    class kernel_object : public memory::pooled_object<memory::memory_pool::kernel>
    {
    public:
        kernel_object() noexcept;
        virtual ~kernel_object() noexcept;
        virtual bool wait() noexcept = 0;
    };

    corydale_noinline kernel_object::kernel_object() noexcept
    {
        printf("\033[31;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline kernel_object::~kernel_object() noexcept
    {
        printf("\033[32;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    class semaphore : public kernel_object
    {
    private:
        int32_t data[4]{};

    public:
        semaphore() noexcept;
        virtual ~semaphore() noexcept;
        virtual bool wait() noexcept override;
    };

    corydale_noinline semaphore::semaphore() noexcept
    {
        printf("\033[31;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline semaphore::~semaphore() noexcept
    {
        printf("\033[32;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline bool semaphore::wait() noexcept
    {
        printf("\033[33;01m%s\033[0m\n", __PRETTY_FUNCTION__);
        return true;
    }

    class mutex : public user_object
    {
    private:
        char buffer[128]{};

    public:
        mutex() noexcept;
        virtual ~mutex() noexcept;
        virtual bool wait() noexcept override;
    };

    corydale_noinline mutex::mutex() noexcept
    {
        printf("\033[31;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline mutex::~mutex() noexcept
    {
        printf("\033[32;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline bool mutex::wait() noexcept
    {
        printf("\033[33;01m%s\033[0m\n", __PRETTY_FUNCTION__);
        return true;
    }
}

void test_delete_object_by_reinterpret_cast_from_related_type()
{
    corydale::kernel::mutex* m     = new corydale::kernel::mutex();
    corydale::kernel::semaphore* s = reinterpret_cast<corydale::kernel::semaphore*>(m);
    delete s;
}

void test_regular_case()
{
    corydale::kernel::semaphore* s0 = new corydale::kernel::semaphore();
    corydale::kernel::semaphore* s1 = new corydale::kernel::semaphore();
    s0->wait();
    delete s0;
    corydale::kernel::mutex* m0 = new corydale::kernel::mutex();
    s1->wait();
    m0->wait();
    delete s1;
    delete m0;
}

namespace corydale::kernel
{
    class unrelated_first final : public corydale::kernel::memory::pooled_object<corydale::kernel::memory::memory_pool::kernel>
    {
    private:
        uint32_t array[16];
        
    public:
        unrelated_first() noexcept;
        ~unrelated_first() noexcept;
    };

    corydale_noinline unrelated_first::unrelated_first() noexcept
    {
        printf("\033[31;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline unrelated_first::~unrelated_first() noexcept
    {
        printf("\033[33;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    class unrelated_second final : public corydale::kernel::memory::pooled_object<corydale::kernel::memory::memory_pool::hypervisor>
    {
    private:
        uint32_t array[4];

    public:
        unrelated_second() noexcept;
        ~unrelated_second() noexcept;
    };

    corydale_noinline unrelated_second::unrelated_second() noexcept
    {
        printf("\033[31;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline unrelated_second::~unrelated_second() noexcept
    {
        printf("\033[33;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }
}

void test_non_virtual_unrelated()
{
    corydale::kernel::unrelated_first* f  = new corydale::kernel::unrelated_first();
    corydale::kernel::unrelated_second* s = reinterpret_cast<corydale::kernel::unrelated_second*>(f);
    delete s;
}

int main()
{
    test_non_virtual_unrelated();

    test_regular_case();
    test_delete_object_by_reinterpret_cast_from_related_type();
    return 0;
}
