#!/bin/bash

nasm -f bin -o boot.bin boot.asm

nasm -f elf -o puppy_kernel.o puppy_kernel.asm
nasm -f elf -o manuos.o manuos.asm

ld -m elf_i386 -T link.ld -o kernel.elf puppy_kernel.o manuos.o

objcopy -O binary kernel.elf kernel.bin

cat boot.bin kernel.bin > manuos-image.bin

qemu-system-i386 -fda manusos-image.bin
