global _start
;wic v0.0.1
section .text
jp_cx:
     push cx
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
readc:
     mov edi, ecx
     mov eax, 0x3
     mov ebx, 0x0
     mov ecx, ebx
     mov edx, 1
     int 0x80
     cmp ebx, 0
     je readc
     mov ecx, edi
     ret
_start:
     mov ebx, 0
     mov ecx, 0
     mov edx, 0
     inc ecx
     inc ecx
     inc ecx
     mov bx, '0'
loop0:
     dec ecx
     call printc
     inc ebx
     inc ebx
     cmp ecx, 0
     jne loop0
     mov eax, 1
     mov ebx, 0
     int 0x80
