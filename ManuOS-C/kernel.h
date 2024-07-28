#ifndef KERNEL_H
#define KERNEL_H

#include "m_stdlib.h"

#define NEWLINE 0x0d
#define CARRIAGE_RETURN 0x0a
#define TAB 0x09
#define SPACE 0x20
#define DEL 0x7f
#define ESC 0x1b
#define KERNEL_VERSION "Puppy-kernel 0.0.4c-dev"

#define SECTOR_SIZE 512
#define FILENAME_SIZE 12
#define START_SECTOR 60
#define DIR_SIZE 1
#define DIR_SECTOR 59
#define END_SECTOR 120
#define MAX_SECTORS 4
#define DATA_SIZE 500 // 512 - 12

extern char currentDir;

void kernel_main();
void sleepms(unsigned long ms);
void printc(char c);
void prints(char *s);
void kernel_panic(char *msg);
void newline();
void cls();
char getc(); // does not wait for keypress
char getch(); //wait for keypress
int geti(); //does not wait for keypress
int getih(); //wait for keypress
short gets(char *s);
char numToAscii(int num);
short asciiToNum(char c);
void printi(int i);
unsigned long get_bios_time();
unsigned long random(unsigned long min, unsigned long max);
void initialize_seed(unsigned long initial_seed);
unsigned long lcg();
void WriteCharacter(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y);
void WriteGpixel(unsigned char backcolour, int x, int y);
short ifESC();
int disk_read(char *buffer, int sector, int num_sectors);
int disk_write(char *buffer, int sector, int num_sectors);
void restart();
int create_file(char* filename, char dir, char* data, int size);
int read_file(char *filename, char dir, char *buffer);
int find_file(char* filename, char dir);
int edit_file(char *filename, char dir, char *data, int size);
int list_files(char dir);
int list_dirs();
int mkdir(char dirname);
int find_dir(char dirname);

char getCurrentDir();

#endif