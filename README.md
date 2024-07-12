# ManuOS
A hobby os written in C and asm.
## Features
- Two editions, C and asm
- C edition is written in C and asm, full version
- Asm edition is written only in asm, minimalist
- 16-bit operating system
- Real Mode
## Programs
- Wuf++ interpreter
- Text editor

## Wuf++ language
**Wuf++**(wuf plus plus) is a low-level programming language
### Registers:
- **bx** - main register, bl mainly used
- **cx** - main pointer
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
