bits 16
section .data
    welcome db 'Welcome to ManuOS(kernel mode)', 0
    version db 'ManuOS 0.0.1-puppy', 0
    help db 'Commands v(version), h(help), t(text editor)', 0
    not_found db 'Command not found', 0
    txt_msg db 'Text editor', 0
    msg db 'Hello, World!', 0
    manu db 'Manu', 0
    cm1 db 'version', 0
    cm2 db 'help', 0

section .bss
    cmd_buffer resb 0x50

section .text
    global start

start:
    call newline
    mov bx, welcome
    call print_str
    call newline
    jmp terminal

halt:
    nop
    jmp halt

terminal:
    mov al, '>'
    call print_chr
    mov di, cmd_buffer
    .tloop:
        call read
        cmp al, 0
        je halt ; If no more input, stop the program
        call print_chr
        mov [di], al
        inc di
        cmp al, 0x0d
        jne .tloop

    mov byte [di], 0 ; Null-terminate the command
    call handle_commands
    jmp terminal

handle_commands:
    mov bx, cmd_buffer
    mov dx, cm1
    call cmp_str
    jne .not_cm1 ; If not equal, check the next command
    call version_command
    ret
.not_cm1:
    mov bx, cmd_buffer
    mov dx, cm2
    call cmp_str
    jne .not_cm2 ; If not equal, check the next command
    call help_command
    ret
.not_cm2:
    mov bx, not_found
    call print_str
    call newline
    ret

version_command:
    call newline
    mov bx, version
    call print_str
    call newline
    ret

help_command:
    call newline
    mov bx, help
    call print_str
    call newline
    ret

newline:
    mov al, 0x0a
    call print_chr
    mov al, 0x0d
    call print_chr
    ret

; TEXT EDITOR
init_text_editor:
    call clrscr
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
    jne .no_enter
    mov al, 0x0a
    call print_chr
    mov al, 0x0d
    call print_chr
.no_enter:
    ret

if_backspace:
    cmp al, 0x08
    jne .no_backspace
    mov al, 0x08
    call print_chr
.no_backspace:
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

cmp_str: ; Parameters: bx = first pointer to string, dx = second pointer to string Returns: zf = 1 if equal
    cld
    mov si, bx
    mov di, dx
    mov cx, 0x50 ; Max length for comparison, adjust as necessary
    repe cmpsb
    ret
