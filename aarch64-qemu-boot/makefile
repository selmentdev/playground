TOOLCHAIN := /home/selmentdev/selment/selment-sysroot/bin/aarch64-elf-

CC = $(TOOLCHAIN)gcc
OBJCOPY := $(TOOLCHAIN)objcopy
OBJDUMP := $(TOOLCHAIN)objdump
CFLAGS := -O3 -nostdlib

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.S
	$(CC) -c $< -o $@

SOURCES := \
	main.c \
	rtl.c \
	startup64.S

SOURCES_C := $(filter %.c,$(SOURCES))
SOURCES_S := $(filter %.S,$(SOURCES))

OBJECTS_C := $(SOURCES_C:%.c=%.o)
OBJECTS_S := $(SOURCES_S:%.S=%.o)

OBJECTS := $(OBJECTS_C) $(OBJECTS_S)

kernel.elf: $(OBJECTS)
	$(CC) $(OBJECTS) -o kernel.elf -T linker.lds $(CFLAGS)

kernel.img: kernel.elf
	$(OBJCOPY) kernel.elf -O binary kernel.img

kernel.src: kernel.elf
	$(OBJDUMP) -S kernel.elf > kernel.src

run: clean kernel.img kernel.src
	qemu-system-aarch64 \
		-machine virt \
		-cpu cortex-a57 \
		-machine type=virt \
		-smp 4 \
		-m 128 \
		-kernel kernel.img \
		-D qemu.log \
		-d cpu_reset,int,guest_errors \
		-smp 4 \
		-serial file:selment.log \
		-nographic

clean:
	-rm kernel.img
	-rm kernel.elf
	-rm *.o
	-rm kernel.src
