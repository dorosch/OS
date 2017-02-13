DEBUG=-g
INCLUDE=-I stdc/include/ -I include/
NO_STDLIB=-nostdlib -nostdinc
CFLAGS= $(NO_STDLIB) -fno-builtin -fno-stack-protector -m32 -pedantic -std=c89 -ansi $(DEBUG) $(INCLUDE)
LDFLAGS=-T link.ld -m elf_i386
ASFLAGS=-m32
SOURCES=boot/loader.o kernel/kernel.o kernel/io.o



all: $(SOURCES) link

link:
	ld $(INCLUDE) $(LDFLAGS) $(SOURCES) -o bin/kernel

install:
	-sh install.sh

run:
	sudo qemu-system-x86_64 hard_disk.img

test:
	qemu-system-i386 -kernel bin/kernel

clean:
	rm -f boot/*.o kernel/*.o bin/kernel