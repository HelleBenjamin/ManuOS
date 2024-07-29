#!/bin/bash

mkdir -p build

nasm -f bin -o build/boot.bin boot.asm

#nasm -f elf -o kernel_asm.o kernel_asm.asm

gcc -Ilibs -m16 -ffreestanding -c -o build/kernel.o kernel/kernel.c -fno-pic -nostdlib
gcc -Ilibs -m16 -ffreestanding -c -o build/manuos.o os/manuos.c -fno-pic -nostdlib
gcc -Ilibs -m16 -ffreestanding -c -o build/m_stdlib.o libs/m_stdlib.c -fno-pic -nostdlib

ld -m elf_i386 -T link.ld -o build/oskernel.bin build/manuos.o build/kernel.o build/m_stdlib.o --oformat binary -nostdlib

cat build/boot.bin build/oskernel.bin > obuild/s-image.bin

dd if=/dev/zero of=build/floppy.img bs=512 count=2880
#mkfs.fat -F 12 -n "MANUOS" floppy.img
dd if=os-build/image.bin of=build/osfloppy.img bs=512 count=2880 conv=notrunc

cat build/osfloppy.img build/floppy.img > build/manuos.img

qemu-system-i386 -fda build/manuos.img #floppy

# Todo:
# - Cleanup
# - Windows bat version
# - Consider using makefile