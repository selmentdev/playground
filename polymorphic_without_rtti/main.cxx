#include <atomic>
#include <cstdint>
#include <cstddef>
#include <cstdio>

namespace corydale
{
    using InterfaceID = uint32_t;

    enum class Status {
        Success,
        NotFound,
        NotAllocated,
    };

    struct IUnknown {
        virtual int32_t AddRef() = 0;
        virtual int32_t Release() = 0;
        virtual Status Query(InterfaceID id, void** instance) = 0;
    };

    template <typename... Interfaces>
    class Component : public Interfaces...
    {
    private:
        static_assert(sizeof...(Interfaces) > 0);

    private:
        std::atomic<int32_t> m_ReferenceCount{1};

    public:
        virtual ~Component() { }

        virtual int32_t AddRef() override final {
            return ++this->m_ReferenceCount;
        }

        virtual int32_t Release() override final {
            int32_t const count = --this->m_ReferenceCount;

            if (count == 0) {
                delete this;
            }

            return count;
        }

        virtual Status Query(InterfaceID id, void** instance) override final {
            if (instance == nullptr) {
                return Status::NotAllocated;
            }

            auto ptr = Query<Interfaces...>(id);

            if (ptr != nullptr)
            {
                puts("succ");
                this->AddRef();
                (*instance) = ptr;
                return Status::Success;
            }
                puts("fail");

            (*instance) = nullptr;
            return Status::NotFound;
        }

    private:
        template <typename Interface, typename... Tail>
        void* Query(InterfaceID id) noexcept {
            printf("query...: %x == %x\n", id, Interface::ID);
            if (id == Interface::ID) {
                printf("query found: %x %p\n", id, this);
                return static_cast<Interface*>(this);
            }

            return Query<Tail...>(id);
        }

        template <int = 0>
        void* Query(InterfaceID) {
                puts("def");

            return nullptr;
        }
    };
}

struct ISomething1 : corydale::IUnknown
{
    static constexpr corydale::InterfaceID ID{ 0x1000'0001 };
    virtual bool Test1() = 0;
};

struct ISomething2 : corydale::IUnknown
{
    static constexpr corydale::InterfaceID ID{ 0x1000'0002 };
    virtual bool Test2() = 0;
};

struct IOther : corydale::IUnknown
{
    static constexpr corydale::InterfaceID ID{ 0x1000'0003 };
    virtual bool Boo() = 0;
};

class CSomething : public corydale::Component<ISomething1, ISomething2, IOther>
{
public:
    virtual ~CSomething() {
        std::puts(__PRETTY_FUNCTION__);
    }
    virtual bool Test1() override {
        std::puts(__PRETTY_FUNCTION__);
        return true;
    }
    
    virtual bool Test2() override {
        std::puts(__PRETTY_FUNCTION__);
        return true;
    }
    
    virtual bool Boo() override {
        std::puts(__PRETTY_FUNCTION__);
        return true;
    }
};

template <typename T, typename U>
corydale::Status Query(U* current, T** instance) noexcept {
    return current->Query(T::ID, (void**)instance);
}

void print_vtable(void* p, size_t count) {
    void** vptr = ((void***)p)[0];
    for (size_t i = 0; i < count; ++i) {
        printf("%p: %zu\n", vptr[i], i);
    }
}

int main() {
    CSomething* cc = new CSomething();
    ISomething1* i0{};
    ISomething2* i1{};
    IOther* i2{};

    corydale::Status s0 = Query<ISomething1>(cc, &i0);
    printf("status: %x : %p\n", s0, i0);
    corydale::Status s1 = Query<ISomething2>(cc, &i1);
    printf("status: %x : %p\n", s1, i1);
    corydale::Status s2 = Query<IOther>(cc, &i2);
    printf("status: %x : %p\n", s2, i2);

    print_vtable(i0, 4);
    print_vtable(i1, 4);
    print_vtable(i2, 4);
    print_vtable(cc, 4);

    int32_t const c0 = i0->Release();
    int32_t const c1 = i1->Release();
    int32_t const c3 = i2->Release();
    int32_t const c4 = cc->Release();

    printf("i0: %p %zu\n", i0, sizeof(*i0));
    printf("i1: %p %zu\n", i1, sizeof(*i1));
    printf("i2: %p %zu\n", i2, sizeof(*i2));
    printf("cc: %p %zu\n", cc, sizeof(*cc));
    return 0;
}
