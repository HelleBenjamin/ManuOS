
bits 16

section .data
    wppmsg db 'Welcome to Wuf++ interpreter, press enter to run the code', 0
    fmsg db 'Program finished, press enter to proceed', 0
section .bss
    wpp_buffer resb 0x100
section .text
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
    ;cmp al, 0x0d
    ;je nl
    ret
global nl
nl:
    mov al, 0x0a
    call printchr
    mov al, 0x0d
    call printchr
    mov al, 0x0d ;inform the kernel that a new line has been printed
    ret

global cls

cls:
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    ret

global printstr
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

; Wuf++ - Brainfuck like code interpreter
; Registers that are used:
; bl - main register
; cx - pointer, not the program counter
; Example: #H.#e.#l.#l.#o.
;Syntax:
; + - increment main register
; - - decrement main register
; } - push main register
; { - pop main register
; . - print main register
; , - read to the main register
; & - jump to location pointed by pointer
; [ - pc = pc - cx
; ] - pc = pc + cx
; ! - invert main register
; > - increment pointer
; < - decrement pointer
; $ - print pointer
; #<char> - load char to main register
; ( - loop start, decrement pointer and loop until pointer = 0
; ) - loop end
; " - swap registers
; %<char> - compare main register with char, jump if equal to location pointed by pointer
; = - halt
; / - add bx and cx, bx = bx + cx
; \ - sub bx and cx, bx = bx - cx
; @ - load zero to bx, bx = 0
; ^ - swap bl with bh, bh <-> bl
global wpp_interpreter
wpp_interpreter:
    .init_interpreter:
        call cls
        mov bx, wppmsg
        call print_str
        call nl
        mov di, wpp_buffer
        mov ecx, 0x100 ; Length of wpp_buffer
        rep stosb 
        mov cx, 0x0000 ; Pointer
        mov bx, 0x0000 ; Main register
    .interpreter_loop:
        call getchar
        mov [di], al
        inc di
        call printchr
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
        je .if_read
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
        .if_read:
            .read_loop:
                call getchar
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
            call printchr
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
            call printchr
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
            ; Comparison successful, jump to address in cx
            mov di, cx
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
        call print_str
        .l1:
            call getchar
            cmp al, 0x0d
            jne .l1
        call cls
        ret