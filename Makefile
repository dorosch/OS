# Исходные объектные модули
SOURCES=boot/loader.o kernel/kernel.o kernel/io.o

# Флаги компилятора языка C
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -g -pedantic -std=c89 -ansi -I stdlib/include/ -I inlcude/

# Флаги компоновщика
LDFLAGS=-T link.ld -m elf_i386

# Флаги ассемблера
ASFLAGS=-m32

# Правило сборки
all: $(SOURCES) link

# Правило очистки
clean:
	rm -f boot/*.o kernel/*.o bin/kernel

# Правило компоновки
link:
	ld $(LDFLAGS) $(SOURCES) -o bin/kernel

install:
	-sh install.sh

run:
	sudo qemu-system-x86_64 hard_disk.img

test:
	qemu-system-i386 -kernel bin/kernel