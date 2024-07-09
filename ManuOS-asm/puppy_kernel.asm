
bits 16
section .data
    welcome db 'Welcome to ManuOS(kernel)', 0
    version dw 'ManuOS 0.0.1-puppy', 0
    help db 'Commands v(version), h(help), t(text editor)', 0
    msg db 'Hello, World!', 0
    manu db 'Manu', 0
    cm1 db 'version', 0
    cm2 db 'help', 0
section .text
    global start

start:
    mov bx, welcome
    call print_str
    call newline


terminal:
    call read
    cmp al, 'v'
    je version_command
    cmp al, 'h'
    je help_command
    cmp al, 't'
    je init_text_editor
    cmp al, 0x0d
    je newline
    call print_chr
    jmp terminal

version_command:
    mov al, 'v'
    call print_chr
    mov bx, version
    call print_str
    call newline
    jmp terminal

help_command:
    mov bx, help
    call print_str
    call newline
    jmp terminal

newline:
    mov al, 0x0a
    call print_chr
    mov al, 0x0d
    call print_chr
    ret

; TEXT EDITOR
init_text_editor:
    call clrscr
    txt_msg db 'Text editor', 0
    mov bx, txt_msg
    call print_str
    call newline
    jmp text_editor
text_editor:
    call read
    call print_chr
    call if_enter
    call if_backspace
    jmp text_editor

if_enter:
    cmp al, 0x0d
    jne text_editor
    mov al, 0x0a
    call print_chr
    mov al, 0x0d
    call print_chr
    ret

if_backspace:
    cmp al, 0x08
    jne text_editor
    mov al, 0x08
    call print_chr
    ret

read:
    mov ah, 0x00
    int 0x16
    mov bl, al
    ret

print_chr:
    mov ah, 0x0e
    int 0x10
    ret

print_str:
    mov ah, 0x0e
print_str_loop:
    mov al, [bx]
    cmp al, 0
    je end_print_str
    int 0x10
    inc bx
    jmp print_str_loop

end_print_str:
    ret

clrscr:
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    ret
