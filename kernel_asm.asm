
bits 16

global _start
extern main

_start:
    call nl
    call main
    hlt

global printchr
printchr:
    mov ah, 0x0e
    int 0x10
    ret

global getchar
getchar:
    mov ah, 0x00
    int 0x16
    ret
global nl
nl:
    mov al, 0x0a
    call printchr
    mov al, 0x0d
    call printchr
    ret
section .text
section .bss