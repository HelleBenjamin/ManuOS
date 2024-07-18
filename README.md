# ManuOS
A hobby os written in C and asm.
## Features
- Two editions, C and asm
- C edition is written in C and asm, full version
- Asm edition is written only in asm, minimal version
- 16-bit operating system, real mode
- Kernel and OS in one file in C edition, will change in the future
- Kernel and OS in different files in asm edition
## Programs
### C-edition
- Wuf++ interpreter
- Dices
### Asm-edition
- Wuf++ interpreter
- Text editor

## How to use
### Requirements
- Linux, if you use Windows you can use Cygwin or Linux Subsystem for Windows
- gcc
- NASM
- QEMU

### How to build
1. Change directory to the edition you want to build, for example: ```cd ManuOS-asm```
2. Build the edition: ```./run.sh```, it should launch the QEMU after building. If you encounter permission error, run ```chmod +x run.sh```


## Wuf++ language
ManuOS comes with a Wuf++ interpreter. You can find it [here](https://github.com/Pepe-57/wpp)

# Changelog
## C-edition
### ManuOS 0.0.1-alpha
- Initial release
- Kernel and OS in one file
## Asm-edition
### ManuOS 0.0.1-alpha
- Initial release
- Kernel and OS in different files
# Versions
Legacy or alpha versions are not maintained.
## C-edition
- v0.0.1-alpha
## Asm-edition
- v0.0.1-alpha
## Puppy Kernel
- v0.0.1