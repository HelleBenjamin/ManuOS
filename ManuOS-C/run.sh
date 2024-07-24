#!/bin/bash

nasm -f bin -o boot.bin boot.asm

#nasm -f elf -o kernel_asm.o kernel_asm.asm

gcc -m16 -ffreestanding -c -o kernel.o kernel.c -fno-pic -nostdlib
gcc -m16 -ffreestanding -c -o manuos.o manuos.c -fno-pic -nostdlib
gcc -m16 -ffreestanding -c -o m_stdlib.o m_stdlib.c -fno-pic -nostdlib

ld -m elf_i386 -T link.ld -o kernel.bin manuos.o kernel.o m_stdlib.o --oformat binary -nostdlib

cat boot.bin kernel.bin > os-image.bin

dd if=/dev/zero of=floppy.img bs=512 count=2880
dd if=os-image.bin of=osfloppy.img bs=512 count=2880

cat osfloppy.img floppy.img > manuos.img

qemu-system-i386 -fda manuos.img #floppy

# Todo:
# - Cleanup
# - Windows bat version
# - Consider using makefile