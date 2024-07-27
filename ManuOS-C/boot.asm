BITS 16
ORG 0x7C00 ; Don't modify this, necessary for the bootloader

boot:
    jmp start
    TIMES 3-($-$$) DB 0x90
    OEMname:           db    "ManuOS"
    bytesPerSector:    dw    512
    sectPerCluster:    db    1
    reservedSectors:   dw    1
    numFAT:            db    2
    numRootDirEntries: dw    224
    numSectors:        dw    2880
    mediaType:         db    0xf0
    numFATsectors:     dw    9
    sectorsPerTrack:   dw    18
    numHeads:          dw    2
    numHiddenSectors:  dd    0
    numSectorsHuge:    dd    0
    driveNum:          db    0
    reserved:          db    0
    signature:         db    0x29
    volumeID:          dd    0x2d7e5a1a
    volumeLabel:       db    "A       "
    fileSysType:       db    "FAT12   "

start:
    extern kernel_main
    ; Setup segment registers
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    ; Load the kernel from disk
    mov ah, 0x02
    mov al, 42
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, 0x8000
    int 0x13
    jc disk_error

    ; Jump to the loaded kernel
    push ax
    mov al, 'O'
    mov ah, 0x0e
    int 0x10
    mov al, 'K'
    int 0x10
    pop ax
    jmp 0x0000:0x8000

disk_error: ;Error
    mov bx, errmsg
    call print_str
    hlt

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

errmsg: db 'Error loading kernel', 0
times 510 - ($ - $$) db 0 ; Don't remove this, necessary for the bootloader
dw 0xAA55
