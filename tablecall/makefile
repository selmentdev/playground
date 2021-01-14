CXXFLAGS := -fno-rtti -fno-exceptions -ftree-vectorize -fbuiltin -DNEW_DELETE_OPERATORS -O3
CXX := clang++

ASFLAGS := -pipe -integrated-as
AS := clang

LD := clang

SOURCES := tablecall.S tablecall.cxx main.cxx

OBJECTS := $(SOURCES:%=obj/%.o)

obj/%.cxx.o: %.cxx
	mkdir -p $(dir $(@))
	$(CXX) $(CXXFLAGS) -c $(<) -o $(@)

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
