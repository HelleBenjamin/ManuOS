bits 16
section .data
    welcome db 'Welcome to ManuOS 0.0.1-alpha', 0
section .bss
section .text
    global start
    global halt
    global newline
    global read
    global print_chr
    global print_str
    global clrscr

    extern main

start:
    call newline
    mov bx, welcome
    call print_str
    call newline
    jmp main

; System calls

halt: ; Parameters: none Returns: none
    nop
    jmp halt

newline: ; Parameters: none Returns: none
    mov al, 0x0a
    call print_chr
    mov al, 0x0d
    call print_chr
    ret

read: ; Parameters: none Returns: al = character
    mov ah, 0x00
    int 0x16
    ret

print_chr: ; Parameters: al = character Returns: none
    mov ah, 0x0e
    int 0x10
    ret

print_str: ; Parameters: bx = pointer to string Returns: none
    mov ah, 0x0e
    .print_str_loop:
        mov al, [bx]
        cmp al, 0
        je .end_print_str
        int 0x10
        inc bx
        jmp .print_str_loop

    .end_print_str:
        ret

clrscr: ; Parameters: none Returns: none
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    ret
