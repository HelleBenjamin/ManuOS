bits 16

section .data
    version db 'ManuOS 0.0.1-puppy, Puppy-kernel 0.0.1', 0
    help db 'Commands: m(manu), v(version), h(help), t(text editor)', 0
    not_found db 'Command not found: ', 0
    txt_msg db 'Text editor v1.2 ', 0
    escmsg db 'Press ESC to exit', 0
    manumsg db 'Manu', 0
    wppmsg db 'Welcome to Wuf++ interpreter, press enter to run the code', 0

section .bss
    cmd_buffer resb 0x20
    wpp_buffer resb 0x100

section .text
    global main
    extern read
    extern print_chr
    extern print_str
    extern newline
    extern clrscr
    extern halt

main:
    jmp terminal


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
    mov bl, 'm'
    cmp bl, [cmd_buffer]
    je .manu_command
    mov bl, 'v'
    cmp bl, [cmd_buffer]
    je .version_command
    mov bl, 'h'
    cmp bl, [cmd_buffer]
    je .help_command
    mov bl, 't'
    cmp bl, [cmd_buffer]
    je init_text_editor
    mov bl, 'w'
    cmp bl, [cmd_buffer]
    je wufpp_interpreter
    mov bx, not_found
    call print_str
    mov bx, cmd_buffer
    call print_str
    call newline
    ret

    .manu_command:
        call newline
        mov bx, manumsg
        call print_str
        call newline
        ret
    .version_command:
        call newline
        mov bx, version
        call print_str
        call newline
        ret
    .help_command:
        call newline
        mov bx, help
        call print_str
        call newline
        ret

; TEXT EDITOR
init_text_editor:
    call clrscr
    mov bx, txt_msg
    call print_str
    mov bx, escmsg
    call print_str
    call newline
text_editor:
    call read
    call print_chr
    call check_txt_functions
    jmp text_editor

check_txt_functions:
    .if_esc:
        cmp al, 0x1b
        jne .if_enter
        call clrscr
        jmp terminal
    .if_enter:
        cmp al, 0x0d
        jne .no_backspace
        mov al, 0x0a
        call print_chr
        mov al, 0x0d
        call print_chr
        .no_backspace:
            ret
; Wuf++ - Brainfuck like code interpreter
; Registers that are used:
; al - main register
; b
; + - increment register
; - - decrement register
; > - push register
; < - pop register
; . - print register
; , - read register
; [ - jump forward
; ] - jump back
wufpp_interpreter:
    .init_interpreter:
        call clrscr
        mov bx, wppmsg
        call print_str
        call newline
        mov di, wpp_buffer
    .interpreter_loop:
        call read
        mov [di], al
        inc di
        call print_chr
        jmp .interpreter_loop
    .if_enter:
        cmp al, 0x0d

    interpret:
        
    ret