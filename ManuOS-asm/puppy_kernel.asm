
bits 16
section .data
    welcome db 'Welcome to ManuOS(kernel mode)', 0
    version dw 'ManuOS 0.0.1-puppy', 0
    help db 'Commands v(version), h(help), t(text editor)', 0
    msg db 'Hello, World!', 0
    manu db 'Manu', 0
    cm1 db 'version', 0
    cm2 db 'help', 0
section .text
    global start

start:
    call newline
    mov bx, welcome
    call print_str
    call newline
    mov bx, cm1
    mov dx, cm1
    call cmp_str
    je l2
    jne l1

l1:
    mov al, '1'
    call print_chr
    jmp halt
l2:
    mov al, '2'
    call print_chr
    jmp halt

halt:
    nop
    jmp halt

terminal:
    mov al, '>'
    call print_chr
    .tloop:
        call read
        call print_chr
        cmp al, 0x0d
        je handle_commands
        jmp .tloop
handle_commands:


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

read: ;Parameters: none Returns: al = character
    mov ah, 0x00
    int 0x16
    mov bl, al
    ret

print_chr: ; Parameters: al = character Returns: none
    mov ah, 0x0e
    int 0x10
    ret

print_str: ; Parameters: bx = pointer to string Returns: none
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

clrscr: ; Parameters: none Returns: none
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    ret

cmp_str: ; Parameters: bx = first pointer to string, dx = second pointer to string, cx = length Returns: zf = 1 if equal
    mov si, bx
    mov di, dx
    mov bx, cx
    repe cmpsb
    ret