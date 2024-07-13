org 0x7c00
BITS 16
global _start
;wic v0.0.1
section .text
jmp _start
jp_cx:
     jmp edx
readc:
    mov ah, 0x00
    int 0x16
    cmp al, 0x0
    je readc
    mov bl, al
    ret
printc:
    mov al, bl
    mov ah, 0x0e
    int 0x10
    ret
_start:
     mov bx, 0
     mov cx, 0
     mov dx, 0
     mov sp, 0x7b00
main:
     mov bl, 'O'
     call printc
     mov bl, 'k'
     call printc
     inc cx
     inc cx
loop0:
     call readc
     call printc
     inc cx
     cmp cx, 0
     dec cx
     jne loop0
     .loop0_end:

times 510 - ($ - $$) db 0
dw 0xAA55