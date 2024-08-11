NASM = nasm
GCC = gcc
LD = ld
DD = dd
CAT = cat
QEMU = qemu-system-i386
MKDIR = mkdir -p
BUILDDIR = build/

ASMFLAGS = -f bin
GCCFLAGS = -m16 -ffreestanding -c -fno-pic -nostdlib
LDFLAGS = -m elf_i386 -T link.ld --oformat binary -nostdlib
BOOT_BIN = build/boot.bin
OS_KERNEL_BIN = build/oskernel.bin
MANUOS_IMG = build/manuos.img
FLOPPY_IMG = build/floppy.img
OS_FLOPPY_IMG = build/osfloppy.img
KERNEL_O = build/kernel.o
MANUOS_O = build/manuos.o
SIMPLEGL_O = build/simplegl.o
M_STDLIB_O = build/m_stdlib.o
S_IMAGE_BIN = build/s-image.bin

.PHONY: all clean run

all: $(MANUOS_IMG)

$(BOOT_BIN): boot.asm
	$(MKDIR) build
	$(NASM) $(ASMFLAGS) -o $(BOOT_BIN) boot.asm

$(KERNEL_O): kernel.c
	$(GCC) $(GCCFLAGS) -o $(KERNEL_O) kernel.c

$(MANUOS_O): manuos.c
	$(GCC) $(GCCFLAGS) -o $(MANUOS_O) manuos.c

$(M_STDLIB_O): m_stdlib.c
	$(GCC) $(GCCFLAGS) -o $(M_STDLIB_O) m_stdlib.c

$(SIMPLEGL_O): simplegl.c
	$(GCC) $(GCCFLAGS) -o $(SIMPLEGL_O) simplegl.c

$(OS_KERNEL_BIN): $(KERNEL_O) $(MANUOS_O) $(M_STDLIB_O) $(SIMPLEGL_O)
	$(LD) $(LDFLAGS) -o $(OS_KERNEL_BIN) $(MANUOS_O) $(KERNEL_O) $(M_STDLIB_O) $(SIMPLEGL_O)

$(S_IMAGE_BIN): $(BOOT_BIN) $(OS_KERNEL_BIN)
	$(CAT) $(BOOT_BIN) $(OS_KERNEL_BIN) > $(S_IMAGE_BIN)

$(FLOPPY_IMG):
	$(DD) if=/dev/zero of=$(FLOPPY_IMG) bs=512 count=2880

$(OS_FLOPPY_IMG): $(S_IMAGE_BIN)
	$(DD) if=$(S_IMAGE_BIN) of=$(OS_FLOPPY_IMG) bs=512 count=2880 conv=notrunc

$(MANUOS_IMG): $(FLOPPY_IMG) $(OS_FLOPPY_IMG)
	$(CAT) $(OS_FLOPPY_IMG) $(FLOPPY_IMG) > $(MANUOS_IMG)

clean:
	rm -rf build

run: $(MANUOS_IMG)
	$(QEMU) -fda $(BUILDDIR)$(MANUOS_IMG)
