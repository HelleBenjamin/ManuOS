#ifndef MANUOS_H
#define MANUOS_H

#define OS_VERSION "ManuOS 0.0.3c-developer preview"
#define TERMINAL_HELP_MSG "Commands: version, help, wpp, dices, clear, calculator, ball"

void os_main();
void terminal();
void wpp_interpreter();
void dices();
short m_strcmp(char *str1, char *str2); //os included string tools
void m_strcpy(char *dest, char *src);
void m_strcat(char *dest, char *src);
void calculator();
void bouncing_ball();
void taskbar();
void update_taskbar();
void init_taskbar();
void clrs(); // clear screen, should be used in os environment
void clt(); // clear screen and initialize for terminal

#endif