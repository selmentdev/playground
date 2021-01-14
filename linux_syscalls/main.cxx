#include <asm/unistd.h>
#include <inttypes.h>
#include <sys/types.h>

extern "C" void* memset(void* p, int c, size_t s) {
	return __builtin_memset(p, c, s);
}


__attribute__((__noinline__))
ssize_t std_write(int fd, void const* buffer, size_t size) {
	ssize_t result;

	__asm__ __volatile__("syscall" : "=a"(result) : "0"(__NR_write), "D"(fd), "S"(buffer), "d"(size) : "cc", "rcx", "r11", "memory");
	return result;
}

__attribute__((__noinline__))
ssize_t std_exit(int status) {
	ssize_t result;

	__asm__ __volatile__("syscall" : "=a"(result) : "0"(__NR_exit), "D"(status) : "cc", "rcx", "r11", "memory");
	return result;
}


extern "C" void __cxa_pure_virtual()
{
	std_write(2, "pure function called\n", 4 + 1 + 8 + 1 + 6 + 1);
	std_exit(1);
}


struct base {
	virtual ~base();
	virtual void action() = 0;
};

__attribute__((__noinline__))
base::~base() {
	std_write(1, "~base\n", 6);
}

struct derived : base {
	virtual ~derived();
	virtual void action() override;

#if defined(NEW_DELETE_OPERATORS)
    void* operator new(size_t);
    void operator delete(void*p);
#endif
};

__attribute__((__noinline__))
derived::~derived() {
	std_write(1, "~derived\n", 9);
}

#if defined(NEW_DELETE_OPERATORS)
alignas(derived) static char buffer[sizeof(derived)];

__attribute__((__noinline__))
void* derived::operator new(size_t) {
    std_write(1, "operator new\n", 13);
    return buffer;
}
__attribute__((__noinline__))
void derived::operator delete(void*) {
    std_write(1, "operator delete\n", 16);
}
#endif

__attribute__((__noinline__))
void derived::action() {
	std_write(1, "action\n", 7);
}

extern "C" void _start() {
	std_write(1, "start\n", 6);
	
	{
		derived d{};
		d.action();
	}

	std_write(1, "stop\n", 5);
	std_exit(0);
}
