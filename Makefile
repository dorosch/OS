include lib/Makefile


.PHONY: all kernel

DEBUG=-g -Wall -pedantic
INCLUDE=-I stdc/include/ -I include/ -I include/libc/
NO_STDLIB=-nostdlib -nostdinc -fno-builtin -fno-stack-protector
CFLAGS=-m32 -std=c89 $(NO_STDLIB) $(DEBUG) $(INCLUDE)
LDFLAGS=-T boot/link.ld -m elf_i386
ASFLAGS=-m32

OBJECTS=boot/loader.o kernel/kernel.o kernel/io.o kernel/interrupts.o
LIBRARIES=lib/libc.a



all: $(OBJECTS) kernel

kernel: $(LIBRARIES) $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o bin/kernel

test:
	qemu-system-i386 -kernel bin/kernel

clean: lib_clean
	rm -f boot/*.o kernel/*.o bin/kernel