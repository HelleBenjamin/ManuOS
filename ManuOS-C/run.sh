#!/bin/bash

# Assemble the bootloader
nasm -f bin -o boot.bin boot.asm

# Assemble the kernel assembly file
nasm -f elf -o kernel_asm.o kernel_asm.asm

# Compile the C kernel file
gcc -m16 -ffreestanding -c -o kernel.o kernel.c -fno-pic -nostdlib

# Link the kernel object files with the linker script
ld -m elf_i386 -T link.ld -o kernel.bin kernel_asm.o kernel.o --oformat binary -nostdlib

# Combine the bootloader and the kernel into a single binary
cat boot.bin kernel.bin > os-image.bin

# Run the OS image in QEMU
qemu-system-i386 -fda os-image.bin