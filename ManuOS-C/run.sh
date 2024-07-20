#!/bin/bash

nasm -f bin -o boot.bin boot.asm

#nasm -f elf -o kernel_asm.o kernel_asm.asm

gcc -m16 -ffreestanding -c -o kernel.o kernel.c -fno-pic -nostdlib
gcc -m16 -ffreestanding -c -o manuos.o manuos.c -fno-pic -nostdlib


ld -m elf_i386 -T link.ld -o kernel.bin manuos.o kernel.o --oformat binary -nostdlib

cat boot.bin kernel.bin > os-image.bin

dd if=os-image.bin of=osfloppy.img bs=512 count=2880

qemu-system-i386 -fda osfloppy.img #floppy

# Todo:
# - Cleanup
# - Windows bat version
# - Consider using makefile