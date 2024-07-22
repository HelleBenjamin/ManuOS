#ifndef MANUOS_H
#define MANUOS_H

#define OS_VERSION "ManuOS 0.0.3c-dev preview 1" 
#define TERMINAL_HELP_MSG "Commands: version, help, wpp, dices, clear, calculator, ball, echo"

void os_main();
void terminal();
void wpp_interpreter();
void dices();
void calculator();
void bouncing_ball();
void taskbar();
void update_taskbar();
void init_taskbar();
void clrs(); // clear screen, should be used in os environment
void clt(); // clear screen and initialize for terminal

#endif