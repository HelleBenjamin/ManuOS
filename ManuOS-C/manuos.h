#ifndef MANUOS_H
#define MANUOS_H

#define OS_VERSION "ManuOS 0.0.4c-dev" 
#define TERMINAL_HELP_MSG "Commands: version, help, wpp, dices, clear, calculator, ball, echo, taskbar, username, restart, color, setup, txt, read <dir> <filename>, create, mkdir <dir>,  list <dir>, dir, cd <dir>, rmdir <dir>, ls, rm <filename>"

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHTGRAY 0x7
#define DARKGRAY 0x8
#define LIGHTBLUE 0x9
#define LIGHTGREEN 0xa
#define LIGHTCYAN 0xb
#define LIGHTRED 0xc
#define LIGHTMAGENTA 0xd
#define YELLOW 0xe
#define WHITE 0xf

void nl();
void os_main();
void terminal();
void wpp_interpreter(int op, char *program);
void dices();
void calculator();
void bouncing_ball();
void taskbar();
void update_taskbar();
void init_taskbar();
void clrs(); // clear screen, should be used in os environment
void clt(); // clear screen and initialize for terminal
void txt_editor();

#endif