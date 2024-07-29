#!/bin/bash

mkdir -p build

nasm -f bin -o build/boot.bin boot.asm

gcc -m16 -ffreestanding -c -o build/kernel.o kernel.c -fno-pic -nostdlib
gcc -m16 -ffreestanding -c -o build/manuos.o manuos.c -fno-pic -nostdlib
gcc -m16 -ffreestanding -c -o build/m_stdlib.o m_stdlib.c -fno-pic -nostdlib

ld -m elf_i386 -T link.ld -o build/oskernel.bin build/manuos.o build/kernel.o build/m_stdlib.o --oformat binary -nostdlib

cat build/boot.bin build/oskernel.bin > build/os-image.bin

dd if=/dev/zero of=build/floppy.img bs=512 count=2880

dd if=build/os-image.bin of=build/floppy.img bs=512 conv=notrunc

mv build/floppy.img build/manuos.img

qemu-system-i386 -fda build/manuos.img
