#ifndef KERNEL_H
#define KERNEL_H

#define NEWLINE 0x0d
#define CARRIAGE_RETURN 0x0a
#define TAB 0x09
#define SPACE 0x20
#define DEL 0x7f
#define ESC 0x1b
#define KERNEL_VERSION "Puppy-kernel 0.0.2c"

void kernel_main();
void sleepms(unsigned long ms);
void printc(char c);
void prints(char *s);
void nl();
void cls();
char getc(); // does not wait for keypress
char getch(); //wait for keypress
int geti(); //does not wait for keypress
int getih(); //wait for keypress
char numToAscii(int num);
short asciiToNum(char c);
void printi(int i);
unsigned long get_bios_time();
unsigned long random(unsigned long min, unsigned long max);
void initialize_seed(unsigned long initial_seed);
unsigned long lcg();

#endif