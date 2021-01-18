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

    corydale_noinline
    user_object::user_object() noexcept
    {
        printf("\033[31;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline
        user_object::~user_object() noexcept
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

    corydale_noinline
    kernel_object::kernel_object() noexcept
    {
        printf("\033[31;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline
        kernel_object::~kernel_object() noexcept
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

    corydale_noinline
    semaphore::semaphore() noexcept
    {
        printf("\033[31;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline
        semaphore::~semaphore() noexcept
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

    corydale_noinline
    mutex::mutex() noexcept
    {
        printf("\033[31;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline
        mutex::~mutex() noexcept
    {
        printf("\033[32;01m%s\033[0m\n", __PRETTY_FUNCTION__);
    }

    corydale_noinline bool mutex::wait() noexcept
    {
        printf("\033[33;01m%s\033[0m\n", __PRETTY_FUNCTION__);
        return true;
    }
}

int main()
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
    return 0;
}
