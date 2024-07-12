# ManuOS
A hobby os written in C and asm.
## Features
- Two editions, C and asm
- C edition is written in C and asm, full version
- Asm edition is written only in asm, minimal version
- 16-bit operating system
- Real Mode
## Programs
- Wuf++ interpreter
- Text editor

## Wuf++ language
**Wuf++**(wuf plus plus) is a low-level programming language. Can be interpreted or compiled. It is possible to run wpp programs on any cpu architecture, for example x86 and Z80. Custom compilers are also possible.
### Registers:
- **bx** - main register, bl mainly used
- **cx** - main pointer
- **sp** - stack pointer
- **dx** - temp register
- **pc** - program counter, instruction pointer
### Syntax:
- **+** - increment main register, *bx = bx + 1*
- **-** - decrement main register, *bx = bx - 1*
- **}** - push main register to stack, *[sp+2] = bx*
- **{** - pop main register from stack, *bx = [sp-2]*
- **.** - print main register as ascii character
- **,** - read ascii character to main register
- **&** - jump to location pointed by pointer, *pc = cx*
- **]** - jump to location pointed by instruction pointer + main pointer, *pc = pc + cx*
- **[** - jump to location pointed by instruction pointer - main pointer, *pc = pc - cx*
- **!** - invert main register, *bx = ~bx*
- **>** - increment pointer, *cx = cx + 1*
- **<** - decrement pointer, *cx = cx - 1*
- **$** - print pointer as ascii character
- **#[char]** - load char to main register
- **(** - loop start, loads dx with loop start address, *dx = pc*
- **)** - loop end, decrement pointer and loop until pointer = 0, *cx = cx - 1, if cx != 0 jump to dx*
- **"** - swap registers, *bx = dx, dx = bx*
- **%[char]** - compare main register with char, jump if equal to location pointed by pointer, *if bx == char jump to cx*
- **=** - halt program, *halt = 1*
- **/** - add main register and pointer, *bx = bx + cx*
- **\\** - sub main register and pointer, *bx = bx - cx*
- **@** - load zero to main register, *bx = 0*
- **^** - swap bl with bh, *bx = bh, bh = bl*

### Code examples:
#### Hello World
```wpp
#H.#e.#l.#l.#o.# .#W.#o.#r.#l.#d.=
```
#### Hello World printed 2x times
```wpp
>(#H.#e.#l.#l.#o.# .#W.#o.#r.#l.#d.)=
```
In assembly:
```asm
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
loop0:
     dec ecx
     mov bx, 'H'
     call printc
     mov bx, 'e'
     call printc
     mov bx, 'l'
     call printc
     mov bx, 'l'
     call printc
     mov bx, 'o'
     call printc
     mov bx, ' '
     call printc
     mov bx, 'W'
     call printc
     mov bx, 'o'
     call printc
     mov bx, 'r'
     call printc
     mov bx, 'l'
     call printc
     mov bx, 'd'
     call printc
     cmp ecx, 0
     jne loop0
     mov eax, 1
     mov ebx, 0
     int 0x80
```

## WIC
**WIC**(wuf++ interpreter compiler) is a compiler and interpreter for the Wuf++ language. A file can be compiled or interpreted. Nasm is used for compilation. C++ is used for interpretation.
### Command line arguments:
- **-s** - source file
- **-o** - output file
- **-c** - compile
- **-i** - interpret
- **-h** - help
- **-v** - version

An example of using the compiler:
```bash
wic -c -s example.wpp -o example
```
An example of using the interpreter:
```bash
wic -i -s example.wpp
```
