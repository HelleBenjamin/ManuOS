bits 16

section .data
    version db 'ManuOS 0.0.2a, Puppy-kernel 0.0.2a, Asm-edition', 0
    help db 'Commands: m(manu), v(version), h(help), t(text editor), w(wuf++ interpreter), c(clear)', 0
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
    extern getchar 
    extern printc
    extern prints
    extern nl
    extern cls
    extern halt

main:
    jmp terminal


terminal:
    mov al, '>'
    call printc
    mov di, cmd_buffer
    .tloop:
        call getchar
        cmp al, 0
        je halt ; If no more input, stop the program
        call printc
        mov [di], al
        inc di
        cmp al, 0x08
        je .terminal_handle_backspace
        cmp al, 0x0d
        jne .tloop
    mov byte [di], 0 ; Null-terminate the command
    call handle_commands
    jmp terminal
    .terminal_handle_backspace: ; Handle backspace
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
    mov bl, 'c'
    cmp bl, [cmd_buffer]
    je .clear_command
    mov bx, not_found
    call prints
    mov bx, cmd_buffer
    call prints
    call nl
    ret

    ;Handle commands
    .manu_command:
        call nl
        mov bx, manumsg
        call prints
        call nl
        jmp terminal
    .version_command:
        call nl
        mov bx, version
        call prints
        call nl
        jmp terminal
    .help_command:
        call nl
        mov bx, help
        call prints
        call nl
        jmp terminal
    .clear_command:
        call cls
        jmp terminal
    .wpp_command:
        call wpp_interpreter
        jmp terminal

; TEXT EDITOR
init_text_editor:
    call cls
    mov bx, txt_msg
    call prints
    mov bx, escmsg
    call prints
    call nl
text_editor:
    call getchar
    call printc
    call check_txt_functions
    jmp text_editor

check_txt_functions:
    .if_esc:
        cmp al, 0x1b
        jne .if_enter
        call cls
        jmp terminal
    .if_enter:
        cmp al, 0x0d
        jne .no_backspace
        mov al, 0x0a
        call printc
        mov al, 0x0d
        call printc
        .no_backspace:
            ret
global wpp_interpreter
wpp_interpreter:
    .init_interpreter:
        push bp
        mov bp, sp
        sub sp, 0x200
        call cls
        mov bx, wppmsg
        call prints
        call nl
        mov di, wpp_buffer
        mov ecx, 0x100
        rep stosb 
        mov cx, 0x0000 ; Pointer
        mov bx, 0x0000 ; Main register
        mov dx, 0x0000 ; Temp register
    .interpreter_loop:
        call getchar
        mov [di], al
        inc di
        call printc
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
        call nl
        mov si, wpp_buffer
        call nl
    .interpret:
        mov al, [di]
        cmp di, 0
        je .end_interpreter
        inc di
        cmp al, ' '; skip spaces
        je .interpret
        cmp al, '+'
        je .if_plus
        cmp al, '-'
        je .if_minus
        cmp al, '}'
        je .if_push
        cmp al, '{'
        je .if_pop
        cmp al, '.'
        je .if_print
        cmp al, ','
        je .if_getchar
        cmp al, '&'
        je .if_jump
        cmp al, '['
        je .if_jump_back
        cmp al, ']'
        je .if_jump_forward
        cmp al, '!'
        je .if_invert
        cmp al, '>'
        je .if_increment_pointer
        cmp al, '<'
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
        cmp al, '%'
        je .if_compare
        cmp al, '='
        je .if_halt
        cmp al, '/'
        je .if_add
        cmp al, '\'
        je .if_sub
        cmp al, '@'
        je .if_ld_zero
        cmp al, '^'
        je .if_swp_bh_bl
        jne .interpret
        .if_getchar:
            .getchar_loop:
                call getchar
                cmp al, 0
                je .getchar_loop
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
            call printc
            jmp .interpret
        .if_jump:
            mov di, cx
            jmp .interpret
        .if_jump_back:
            sub di, cx
            jmp .interpret
        .if_jump_forward:
            add di, cx
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
            call printc
            jmp .interpret
        .if_load_char:
            mov bl, [di]
            inc di
            jmp .interpret
        .if_loop_start:
            mov dx, di
            ;dec cx
            jmp .interpret
        .if_loop_end:
            dec cx
            cmp cx, 0
            jle .interpret
            mov di, dx
            jmp .interpret
        .if_swap:
            xchg bl, cl
            jmp .interpret
        .if_compare:
            mov dl, [di]
            inc di
            cmp bl, dl
            jne .interpret
            lea di, [ecx + wpp_buffer]
            jmp .interpret
        .if_halt:
            jmp .end_interpreter
        .if_add:
            add bx, cx
            jmp .interpret
        .if_sub:
            sub bx, cx
            jmp .interpret
        .if_ld_zero:
            mov bx, 0x0000
            jmp .interpret
        .if_swp_bh_bl:
            xchg bh, bl
            jmp .interpret
    .end_interpreter:
        call nl
        mov bx, fmsg
        call prints
        .l1:
            call getchar
            cmp al, 0x0d
            jne .l1
        call cls
        mov sp, bp
        pop bp
        ret