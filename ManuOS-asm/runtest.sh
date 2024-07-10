#!/bin/bash

nasm -f bin -o boot.bin boot.asm

nasm -f elf -o test_kernel.o test_kernel.asm

ld -m elf_i386 -T link.ld -o test_kernel.elf test_kernel.o

objcopy -O binary test_kernel.elf test_kernel.bin

cat boot.bin test_kernel.bin > test_manuos-image.bin

qemu-system-i386 -fda test_manuos-image.bin
