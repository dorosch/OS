/*.set MBOOT_HEADER_MAGIC, 0x1BADB002
.set MBOOT_HEADER_FLAGS, 0x00000001
.set MBOOT_CHECKSUM, -(INIT_MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)
*/

.set ALIGN,        1<<0
.set MEMINFO,      1<<1
.set HEADER_FLAGS, ALIGN | MEMINFO
.set HEADER_MAGIC, 0x1BADB002
.set CHECKSUM,     -(HEADER_MAGIC + HEADER_FLAGS)


.extern kernel_main

.section .mboot

.int HEADER_MAGIC
.int HEADER_FLAGS
.int CHECKSUM

.section    .text
.global      init

init:
        cli
	push    %ebx
	call    kernel_main

	hlt

loop:
	jmp    loop
