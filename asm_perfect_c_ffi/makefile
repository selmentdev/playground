CXXFLAGS := -fno-rtti -fno-exceptions -ftree-vectorize -fbuiltin -O3 -std=c++20 -fno-omit-frame-pointer
CXX := clang++

elf-x86_64.asm: main.cxx
	$(CXX) $(CXXFLAGS) -S -c $(<) -o /dev/stdout | llvm-cxxfilt > $(@)
	
elf-aarch64.asm: main.cxx
	$(CXX) $(CXXFLAGS) -S --target=aarch64-arm-none-eabi -c $(<) -o /dev/stdout | llvm-cxxfilt > $(@)

elf-rv64gc.asm: main.cxx
	$(CXX) $(CXXFLAGS) -S --target=riscv64 -march=rv64gc -c $(<) -o /dev/stdout | llvm-cxxfilt > $(@)

OUTPUTS := elf-x86_64.asm elf-aarch64.asm elf-rv64gc.asm

all: $(OUTPUTS)
clean: $(OUTPUTS)
	-rm -rf $(^)
