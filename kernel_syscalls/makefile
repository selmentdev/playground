CXXFLAGS := -fno-rtti -fno-exceptions -ftree-vectorize -fbuiltin -O3 -std=c++20 -mno-mmx -mno-sse -mno-sse2
CXX := clang++

CFLAGS := -ftree-vectorize -fbuiltin -O3 -mno-mmx -mno-sse -mno-sse2
CC := clang

ASFLAGS := -pipe -integrated-as
AS := clang

LD := clang

SOURCES := main.c syscalls.cxx api.cxx tablecall.S

OBJECTS := $(SOURCES:%=obj/%.o)

obj/%.cxx.o: %.cxx
	mkdir -p $(dir $(@))
	$(CXX) $(CXXFLAGS) -c $(<) -o $(@)

obj/%.c.o: %.c
	mkdir -p $(dir $(@))
	$(CC) $(CFLAGS) -c $(<) -o $(@)

obj/%.S.o: %.S
	mkdir -p $(dir $(@))
	$(AS) $(ASFLAGS) -c $(<) -o $(@)

main.elf: $(OBJECTS)
	$(LD) $(^) -o $(@)

all: main.elf

clean:
	rm -rf ./main.elf
	rm -rf ./obj

run:
	gdb -ex run ./main.elf
