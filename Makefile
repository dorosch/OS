include lib/Makefile


.PHONY: all kernel

NAME=kernel
BINARY=bin/$(NAME)
DEBUG=-g -Wall -pedantic
INCLUDE=-I include/ -I include/libc/
NO_STDLIB=-nostdlib -nostdinc -fno-builtin -fno-stack-protector
CFLAGS=-m32 -std=c89 $(NO_STDLIB) $(DEBUG) $(INCLUDE)
LDFLAGS=-T boot/link.ld -m elf_i386
ASFLAGS=-m32

OBJECTS=boot/loader.o kernel/kernel.o kernel/io.o kernel/interrupts.o kernel/drivers/tty/tty.o
LIBRARIES=lib/libc.a



all: $(OBJECTS) $(NAME)

$(NAME): $(LIBRARIES) $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $(BINARY)

test:
	qemu-system-i386 -kernel $(BINARY)

clean: lib_clean
	rm -f $(BINARY)
	rm -f $(shell find boot/ -name *.o)
	rm -f $(shell find kernel/ -name *.o)
