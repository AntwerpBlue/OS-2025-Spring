.globl start

/* Multiboot 头 */
.set MAGIC, 0x1BADB002
.set FLAGS, 0
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot_header
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.text
.code32

start:
    /* 屏幕输出 */
    movl $0x2f652f48, 0xB8000
    movl $0x2f6c2f6c, 0xB8004
    movl $0x2f6f, 0xB8008
    movl $0xce6fce77, 0xB800A
    movl $0xce6cce72, 0xB800E
    movl $0xce64, 0xB8012

    movl $0x3c423c50, 0xB80A0
    movl $0xfc30fc32, 0xB80A4
    movl $0xfc33fc30, 0xB80A8
    movl $0xfc37fc30, 0xB80AC
    movl $0xfc36fc33, 0xB80B0
    1:  hlt
    jmp 1b