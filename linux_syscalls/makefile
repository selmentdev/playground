CFLAGS := -ffreestanding -fno-rtti -fno-exceptions -nostdlib -ftree-vectorize -fbuiltin -DNEW_DELETE_OPERATORS -O3
CC := clang

all:
	$(CC) main.cxx $(CFLAGS) -o main.elf

clean:
	-rm ./main.elf

run:
	gdb -ex run ./main.elf
