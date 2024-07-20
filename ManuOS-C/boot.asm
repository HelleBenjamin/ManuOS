BITS 16
ORG 0x7C00 ; Don't modify this, necessary for the bootloader

start:
    extern kernel_main
    ; Setup segment registers
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    ; Load the kernel from disk
    mov ah, 0x02
    mov al, 20
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, 0x8000
    int 0x13
    jc disk_error

    ; Jump to the loaded kernel
    push ax
    mov al, 'O'
    mov ah, 0x0e
    int 0x10
    mov al, 'K'
    int 0x10
    pop ax
    jmp 0x0000:0x8000

disk_error: ;Error
    mov al, 'E'
    mov ah, 0x0e
    int 0x10
    hlt

times 510 - ($ - $$) db 0 ; Don't remove this, necessary for the bootloader
dw 0xAA55
