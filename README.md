![Terminal](manuos1.png)
# DEV BRANCH!
# ManuOS
ManuOS is a hobby os written in C and X86 assembly. Its main goal is to be simple and easy to use. It currently supports only X86 architecture. Arm support is planned in the future. 
## Features
- Two editions, C and asm
- Open source
- C edition is written in C and asm, full version, recommended
- Asm edition is written only in asm, minimal version
- Currently runs in real mode, planned to run in protected mode in the future
- OS uses kernel system calls to interact with the hardware
- Kernel can be customized for different architectures
## Programs
### C-edition, recommended
- Wuf++ interpreter
- Dices
- Calculator
- Bouncing ball
### Asm-edition
- Wuf++ interpreter
- Text editor

## Requirements
- Linux, if you use Windows you can use Cygwin or Linux Subsystem for Windows
- gcc
- NASM
- QEMU or other emulator

## How to build
1. Change directory to the edition you want to build, for example: ```cd ManuOS-C```
2. Build the edition: ```./run.sh```, it should launch the QEMU after building. If you encounter a permission error, run ```chmod +x run.sh```
3. In the OS terminal, type ```setup``` and follow the instructions, this needs to be done only once.

## Colors
- **Black** - 0
- **Blue** - 1
- **Green** - 2
- **Cyan** - 3
- **Red** - 4
- **Magenta** - 5
- **Brown** - 6
- **Light Gray** - 7
- **Dark Gray** - 8
- **Light Blue** - 9
- **Light Green** - 10
- **Light Cyan** - 11
- **Light Red** - 12
- **Light Magenta** - 13
- **Yellow** - 14
- **White** - 15

## Wuf++ language
ManuOS comes with a Wuf++ interpreter. See more on [here](https://github.com/Pepe-57/wpp). 
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

# Changelog
### ManuOS 0.0.4c-dev
- Major change: Added a simple file system
- Small changes/bugfixes
### ManuOS 0.0.3c-release
- Stable release
- Small changes/bugfixes
### ManuOS 0.0.3c-dev preview 2
- Added disk management to the kernel
- General improvements
- Small changes/bugfixes
### ManuOS 0.0.3c-dev preview 1
- Added simple taskbar
- Added more kernel syscalls
- Small changes/bugfixes
- Added simple bouncing ball
### ManuOS 0.0.2c-alpha
- Kernel and OS now in different files
- Small changes/bugfixes
- Added simple calculator
### ManuOS 0.0.1c-alpha
- Initial release
- Kernel and OS in one file
### ManuOS 0.0.1a-alpha
- Initial release
- Kernel and OS in different files
# Versions
Legacy, alpha or dev versions are not maintained. 'c' stands for C edition and 'a' for asm edition
- v0.0.3c-release (latest)
- v0.0.3c-dev preview 2
- v0.0.3c-dev preview 1
- v0.0.2c-alpha
- v0.0.1c-alpha
- v0.0.1a-alpha (latest, asm-edition)
## Puppy Kernel
- v0.0.3c-release (latest)
- v0.0.3c-dev2
- v0.0.3c-dev1
- v0.0.2c
- v0.0.1c
- v0.0.1a (latest, asm-edition)
