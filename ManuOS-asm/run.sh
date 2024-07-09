#!/bin/bash

# Assemble the bootloader
nasm -f bin -o boot.bin boot.asm

# Assemble the kernel assembly file
nasm -f elf -o puppy_kernel.o puppy_kernel.asm

# Link the kernel object file with the linker script
ld -m elf_i386 -T link.ld -o kernel.elf puppy_kernel.o

# Convert the ELF kernel to a binary format
objcopy -O binary kernel.elf kernel.bin

# Create the OS image by concatenating the bootloader and the kernel
cat boot.bin kernel.bin > os-image.bin

# Run the OS image in QEMU
qemu-system-i386 -fda os-image.bin
