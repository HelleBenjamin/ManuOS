global _start
;wic v0.0.1
section .text
jp_cx:
     jmp edx
readc:
     mov edi, ecx
     mov eax, 0x3
     mov ebx, 0x0
     mov ecx, ebx
     mov edx, 1
     int 0x80
     mov ecx, edi
     ret
printc:
     mov edi, ecx
     push ebx
     mov eax, 0x4
     mov ebx, 0x1
     mov ecx, esp
     mov edx, 1
     int 0x80
     pop ebx
     mov ecx, edi
     ret
_start:
     mov ebx, 0
     mov ecx, 0
     mov edx, 0
main:
     mov bx, 'O'
     call printc
     mov bx, 'k'
     call printc
     inc ecx
     inc ecx
loop0:
     call readc
     call printc
     inc ecx
     cmp ecx, 0
     dec ecx
     jne loop0
     .loop0_end:
