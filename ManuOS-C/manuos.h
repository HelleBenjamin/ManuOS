#ifndef MANUOS_H
#define MANUOS_H

#define OS_VERSION "ManuOS 0.0.2c-alpha"
#define TERMINAL_HELP_MSG "Commands: version, help, wpp, dices, clear, calculator"

void os_main();
void terminal();
void wpp_interpreter();
void dices();
short m_strcmp(char *str1, char *str2); 
void calculator();

#endif