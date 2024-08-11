BITS 16

section .data
    welcome db 'Welcome to ManuOS!', 0
section .bss

section .text
    global start
    global halt
    global nl
    global getchar
    global printc
    global prints
    global cls

    extern main

start:
    call nl
    mov bx, welcome
    call prints
    call nl
    jmp main

; System calls

halt: ; Parameters: none Returns: none
    nop
    jmp halt

nl: ; Parameters: none Returns: none
    mov al, 0x0a
    call printc
    mov al, 0x0d
    call printc
    ret

getchar: ; Parameters: none Returns: al = character
    mov ah, 0x00
    int 0x16
    ret

printc: ; Parameters: al = character Returns: none
    mov ah, 0x0e
    int 0x10
    ret

prints: ; Parameters: bx = pointer to string Returns: none
    mov ah, 0x0e
    .prints_loop:
        mov al, [bx]
        cmp al, 0
        je .end_prints
        int 0x10
        inc bx
        jmp .prints_loop

    .end_prints:
        ret

cls: ; Parameters: none Returns: none
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    ret
