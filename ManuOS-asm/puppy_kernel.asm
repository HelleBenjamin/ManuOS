BITS 16

section .data
    welcome db 'Welcome to ManuOS 0.0.1-alpha', 0

section .text
    global start
    global halt
    global newline
    global read
    global print_chr
    global print_str
    global clrscr
    global save_byte_to_disk
    global read_byte_from_disk

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

save_byte_to_disk: ; Parameters: al = byte, bx = address on disk Returns: none
    pusha                   ; Save all general-purpose registers
    push es                 ; Save ES register

    ; Write one sector (512 bytes) from memory address 0x0600
    mov ax, 0x0600
    mov es, ax
    mov di, bx              ; Destination address in ES:DI
    stosb                   ; Store byte in AL to [ES:DI]

    ; BIOS disk write parameters
    mov bx, 0x0600          ; Data buffer address in memory
    mov ah, 0x03            ; Write sector function
    mov al, 1               ; Number of sectors to write
    mov ch, 0               ; Cylinder number
    mov cl, 2               ; Sector number (2 since 1 is typically used by the boot sector)
    mov dh, 0               ; Head number
    mov dl, 0               ; Drive number (0 for the first floppy drive)
    int 0x13                ; Call BIOS interrupt

    jc write_error          ; Jump if carry flag is set (indicating an error)
    jmp write_success

write_error:
    ; Handle the error
    call print_str
    db 'Disk write error', 0
    jmp halt

write_success:
    ; Successfully written to disk
    call print_str
    db 'Disk write successful', 0

    pop es                  ; Restore ES register
    popa                    ; Restore all general-purpose registers
    ret

read_byte_from_disk: ; Parameters: bx = address on disk Returns: al = byte
    pusha                   ; Save all general-purpose registers
    push es                 ; Save ES register

    ; BIOS disk read parameters
    mov bx, 0x0600          ; Data buffer address in memory
    mov ah, 0x02            ; Read sector function
    mov al, 1               ; Number of sectors to read
    mov ch, 0               ; Cylinder number
    mov cl, 2               ; Sector number (2 since 1 is typically used by the boot sector)
    mov dh, 0               ; Head number
    mov dl, 0               ; Drive number (0 for the first floppy drive)
    int 0x13                ; Call BIOS interrupt

    jc read_error           ; Jump if carry flag is set (indicating an error)

    ; Load the byte from memory address 0x0600 + offset
    mov ax, 0x0600
    mov es, ax
    mov di, bx              ; Source address in ES:DI
    lodsb                   ; Load byte from [ES:DI] to AL

    jmp read_success

read_error:
    ; Handle the error
    call print_str
    db 'Disk read error', 0
    jmp halt

read_success:
    ; Successfully read from disk
    call print_str
    db 'Disk read successful', 0

    pop es                  ; Restore ES register
    popa                    ; Restore all general-purpose registers
    ret
