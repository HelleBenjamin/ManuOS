bits 16

section .data
    version db 'ManuOS 0.0.1-alpha, Puppy-kernel 0.0.1', 0
    help db 'Commands: m(manu), v(version), h(help), t(text editor), w(wuf++ interpreter)', 0
    not_found db 'Command not found: ', 0
    txt_msg db 'Text editor v1.2 ', 0
    escmsg db 'Press ESC to exit', 0
    manumsg db 'Manu', 0
    wppmsg db 'Welcome to Wuf++ interpreter, press enter to run the code', 0
    fmsg db 'Program finished, press enter to proceed', 0

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
        cmp al, 0x08
        je .terminal_handle_backspace
        cmp al, 0x0d
        jne .tloop
    mov byte [di], 0 ; Null-terminate the command
    call handle_commands
    jmp terminal
    .terminal_handle_backspace:
        dec di
        dec di
        mov byte [di], 0
        jmp .tloop

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
    je .wpp_command
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
        jmp terminal
    .version_command:
        call newline
        mov bx, version
        call print_str
        call newline
        jmp terminal
    .help_command:
        call newline
        mov bx, help
        call print_str
        call newline
        jmp terminal

    .wpp_command:
        call wpp_interpreter
        jmp terminal

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
; bl - main register
; cx - pointer, not the program counter
; Example: #H.#e.#l.#l.#o.
;Syntax:
; + - increment main register
; - - decrement main register
; > - push main register
; < - pop main register
; . - print main register
; , - read to the main register
; [ - pc = pc - cx
; ] - pc = pc + cx
; ! - invert main register
; } - increment pointer
; { - decrement pointer
; $ - print pointer
; #[char] - load char to main register
; ( - loop start, decrement pointer and loop until pointer = 0
; ) - loop end
; " - swap registers
wpp_interpreter:
    .init_interpreter:
        call clrscr
        mov bx, wppmsg
        call print_str
        call newline
        mov di, wpp_buffer
        mov cx, 0x0000 ; Pointer
        mov bx, 0x0000 ; Main register
    .interpreter_loop:
        call read
        mov [di], al
        inc di
        call print_chr
        cmp al, 0x0d
        je .handle_enter
        cmp al, 0x08
        je .handle_backspace
        jne .interpreter_loop
    .handle_backspace:
        dec di
        dec di
        mov byte [di], 0
        jmp .interpreter_loop
    .handle_enter:
        mov byte [di], 0
        mov di, wpp_buffer
        call newline
    .interpret:
        mov al, [di]
        cmp di, 0
        je .end_interpreter
        inc di
        cmp al, '+'
        je .if_plus
        cmp al, '-'
        je .if_minus
        cmp al, '>'
        je .if_push
        cmp al, '<'
        je .if_pop
        cmp al, '.'
        je .if_print
        cmp al, ','
        je .if_read
        cmp al, '['
        je .if_jump_forward
        cmp al, ']'
        je .if_jump_back
        cmp al, '!'
        je .if_invert
        cmp al, '}'
        je .if_increment_pointer
        cmp al, '{'
        je .if_decrement_pointer
        cmp al, '$'
        je .if_print_pointer
        cmp al, '#'
        je .if_load_char
        cmp al, '('
        je .if_loop_start
        cmp al, ')'
        je .if_loop_end
        cmp al, '"'
        je .if_swap
        jne .interpret
        .if_read:
            .read_loop:
                call read
                cmp al, 0
                je .read_loop
            mov bl, al
            jmp .interpret
        .if_plus:
            inc bl
            jmp .interpret
        .if_minus:
            dec bl
            jmp .interpret
        .if_push:
            push bx
            jmp .interpret
        .if_pop:
            pop bx
            jmp .interpret
        .if_print:
            mov al, bl
            call print_chr
            jmp .interpret
        .if_jump_forward:
            add di, cx
            jmp .interpret
        .if_jump_back:
            sub di, cx
            jmp .interpret
        .if_invert:
            not bl
            jmp .interpret
        .if_increment_pointer:
            inc cx
            jmp .interpret
        .if_decrement_pointer:
            dec cx
            jmp .interpret
        .if_print_pointer:
            mov al, cl
            call print_chr
            jmp .interpret
        .if_load_char:
            mov bl, [di]
            inc di
            jmp .interpret
        .if_loop_start:
            mov dx, di
            jmp .interpret
        .if_loop_end:
            cmp cx, 0
            je .interpret
            dec cx
            mov di, dx
            jmp .interpret
        .if_swap:
            xchg bl, cl
            jmp .interpret
    .end_interpreter:
        call newline
        mov bx, fmsg
        call print_str
        .l1:
            call read
            cmp al, 0x0d
            jne .l1
        call clrscr
        jmp terminal