all: lib/libc.a


lib/libc.a: lib/libc/string.o include/libc/string.h
	ar rc lib/libc.a lib/libc/string.o include/libc/string.h
	ranlib lib/libc.a

lib_clean:
	rm -f $(shell find lib/ -name *.o) $(shell find lib/ -name *.a)