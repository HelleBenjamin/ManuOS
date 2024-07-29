#include "kernel.h"
#include "m_stdlib.h"
#include "manuos.h"

extern void os_main(); // defined in manuos.c

/* Copyright (C) 2024 Benjamin H. All rights reserved. */

/** Kernel functions and syscalls ***/

/* ManuOS filesystem, SBFS-4 (Sector Based File System)
Starts at sector 60. Thing that must be defined: Sector size, number of files, filesystem entries and start sector
 - Status, 1 byte, 1 = Taken, 0 = Available
 - Filename, 12 bytes, example: text
 - Directory, 1 byte, example: A
 - Sector size, 1 byte, 1 = Single sector, 2 = Two sectors, 4 = Four sectors max
 - Data, remaining sector

Directory structure:

Root /
     |-- A
     |-- B
     |-- C
     ect..

*/

uint16_t nextSector;
char currentDir;

int init_fs() {
    char fsbuf[512]; // 0x0 - Next sector, 0x1 - Current directory
    if (disk_read(fsbuf, FS_SECTOR, 1) != 0) {
        kernel_panic("Failed to load filesystem");
    }
    nextSector = fsbuf[0];
    currentDir = fsbuf[1];
    return 0;
}

int find_free_sector() {
    char sectorbuf[512];
    int i = 0;
    while (i < END_SECTOR) {
        if (disk_read(sectorbuf, i + START_SECTOR, 1) != 0) {
            kernel_panic("Failed to read sector");
        }
        if (sectorbuf[0] == 0) {
            return i + START_SECTOR;
        }
        i++;
    }
}

int create_file(char *filename, char dir, char *data, int size) {
    char buf[SECTOR_SIZE * size];
    if (find_dir(dir) == 1) {
      return 2; // returns 2 if directory not found  
    }
    for (int i = 1; i < 12; i++) {
        buf[i] = filename[i - 1];
    }
    buf[0] = 1; // Taken
    buf[13] = dir;
    buf[14] = size;
    for (int i = 15; i < SECTOR_SIZE * size; i++) {
        buf[i] = data[i - 15];
    }
    int status = disk_write(buf, find_free_sector(), size);
    if (status != 0) {
        return 1;
    }
    return 0;

}

int find_file(char *filename, char dir) {
    char buf[SECTOR_SIZE];
    char fname[FILENAME_SIZE];
    if (find_dir(dir) == 1) {
      return 2; // returns 2 if directory not found  
    }
    for (int i = START_SECTOR; i < END_SECTOR; i++) {
        int status = disk_read(buf, i, 1);
        strncpy(fname, buf + 1, 12);
        if (status != 0) {
            return 1;
        }
        if (strcmp(fname, filename) == 0 && buf[13] == dir) {
            return i; // returns sector
        }
    }
    return 0;
}

int find_dir(char dir) {
    char buf[SECTOR_SIZE];
    char dir1;
    disk_read(buf, DIR_SECTOR, 1);
    for (int i = 1; i < 512; i++) {
        if (buf[i] == dir) {
            return 0; // returns 0 if found
        }
    }
    return 1; // returns 1 if not found
}

char getCurrentDir() {
    return currentDir;
}

int read_file(char *filename, char dir, char *buffer) {
    char buf[SECTOR_SIZE];
    int sector = find_file(filename, dir);
    if (sector == 0) {
        return 1;
    }
    int status = disk_read(buf, sector, 1);
    for (int i = 15; i < SECTOR_SIZE; i++) {
        buffer[i - 15] = buf[i];
    }
    return 0;

}

int edit_file(char *filename, char dir, char *data, int size) {
    char buf[SECTOR_SIZE * size];

    int sector = find_file(filename, dir);
    if (sector == 0) {
        return 1;
    }
    int status = disk_read(buf, sector, size);
    strncpy(buf, data, size);
    status = disk_write(buf, sector, size);
    if (status != 0) {
        return 1;
    }
    return 0;
}

int mkdir(char dirname){
    char sBuf[512]; //0x0 - dircount, 0x1 - 0x200 - dirnames 
    disk_read(sBuf, DIR_SECTOR, 1);
    sBuf[0] = sBuf[0] + 1;
    sBuf[sBuf[0]] = dirname;
    disk_write(sBuf, DIR_SECTOR, 1);
    return 0;
}

int cd(char dirname){
    if (find_dir(dirname) == 1) {
        return 1;
    }
    if (dirname == '/') {
        currentDir = '/';
        return 0;
    }
    currentDir = dirname;
    return 0;
}

int ls(){
    list_files(currentDir);
}

int list_files(char dirname){
    if (find_dir(dirname) == 1) {
        return 1;
    }
    prints("File list:");
    nl();
    for (int i = START_SECTOR; i < END_SECTOR; i++){
        char sBuf[512];
        char filename[FILENAME_SIZE];
        disk_read(sBuf, i, 1);
        if (sBuf[13] == dirname){
            strncpy(filename, sBuf + 1, 12);
            prints(filename);
            nl();
        }  
    }
}

int list_dirs(){
    char dBuf[512];
    disk_read(dBuf, DIR_SECTOR, 1);
    prints("/");
    nl();
    for (int i = 1; i < dBuf[0]; i++){
        prints(" |-- ");
        printc(dBuf[i+1]);
        nl();
    }
}

int rmdir(char dirname){
    if (find_dir(dirname) == 1) {
        return 1;
    }
    char sBuf[512];
    disk_read(sBuf, DIR_SECTOR, 1);
    sBuf[sBuf[0]] = 0;
    sBuf[0] = sBuf[0] - 1;
    disk_write(sBuf, DIR_SECTOR, 1);
    return 0; 
}

int rm(char *filename, char dir){
    int sector = find_file(filename, dir);
    char sBuf[512];
    disk_read(sBuf, sector, 1); 
    for (int i = 0; i < 512; i++){
        sBuf[i] = 0;
    }
    disk_write(sBuf, sector, 1);
    return 0;
}

int poke(int *addr, int value) {
    *addr = value;
    return 0;
}

void newline() {
    asm(
        "mov $0x0a, %al\n\t"
        "call printchr\n\t"
        "mov $0x0d, %al\n\t"
        "call printchr\n\t"
        "mov $0x0d, %al\n\t"
        "call printchr\n\t"
    );
}

asm(
    "printchr: \n\t"
    "   mov $0x0e, %ah\n\t"
    "   int $0x10\n\t"
    "   ret\n\t"
);
int disk_read(char *buffer, int sector, int num_sectors) {
    int status;
    int heads_per_cyl = 2;
    int sectors_per_track = 18;
    int cylinder = sector / (heads_per_cyl * sectors_per_track);
    int temp = sector % (heads_per_cyl * sectors_per_track);
    int head = temp / sectors_per_track;
    int sec = temp % sectors_per_track + 1;
    int ch = cylinder & 0xFF;
    int cl = (sec & 0x3F) | ((cylinder >> 2) & 0xC0);

    asm volatile (
        "int $0x13"
        : "=a" (status)
        : "a" ((0x02 << 8) | num_sectors),
          "c" ((ch << 8) | cl),
          "d" ((head << 8) | 0x00),
          "b" (buffer)
        : "cc", "memory"
    );
    return (status & 0xFF00) == 0 ? 0 : (status >> 8);
}

int disk_write(char *buffer, int sector, int num_sectors) {
    if (sector == 0) {
        return -3; // Prevent writing to boot sector
    }

    int status;
    int heads_per_cyl = 2;
    int sectors_per_track = 18;
    int cylinder = sector / (heads_per_cyl * sectors_per_track);
    int temp = sector % (heads_per_cyl * sectors_per_track);
    int head = temp / sectors_per_track;
    int sec = temp % sectors_per_track + 1;
    int ch = cylinder & 0xFF;
    int cl = (sec & 0x3F) | ((cylinder >> 2) & 0xC0);

    asm volatile (
        "int $0x13"
        : "=a" (status)
        : "a" ((0x03 << 8) | num_sectors),
          "c" ((ch << 8) | cl),
          "d" ((head << 8) | 0x00),
          "b" (buffer)
        : "cc", "memory"
    );
    return (status & 0xFF00) == 0 ? 0 : (status >> 8);
}


void cls() { // clear screen
    asm(
        "mov $0x00, %ah\n\t"
        "mov $0x03, %al\n\t"
        "int $0x10\n\t"
    );
}
void sleepms(unsigned long ms) { // sleep milliseconds
   for (unsigned long i = 0; i < ms * 2000; i++) {
       asm("nop\n\t");
   }
}
char numToAscii(int num) {
    return '0' + num;
}
short asciiToNum(char c) {
    return c - 48;
}
void printc(char c) {
    asm(
        "nop\n\t"
        :
        : "al"(c)
    );
    asm("call printchr\n\t");
}

void prints(char *s) {
    while (*s) {
        printc(*s);
        s++;
    }
}

void printi(int i) {
    char buf[10];
    int j = 0;
    if (i < 0) {
        printc('-');
        i *= -1;
    }
    while (i > 0) {
        buf[j++] = i % 10 + '0';
        i /= 10;
    }
    while (j > 0) {
        printc(buf[--j]);
    }
}

void kernel_panic(char *msg) {
    prints("KERNEL PANIC: ");
    prints(msg);
    newline();
    while (1) {
        sleepms(100);
    }
}

char getc() {
    char c = 0;
    asm(
        "mov $0x00, %%ah\n\t"
        "int $0x16\n\t"
        : "=al"(c)
        :
    );
    return c;
}

short ifESC() {
    char c;
        asm(
        "mov $0x01, %%ah\n\t"
        "int $0x16\n\t"
        : "=al"(c)
        :
    );
    if (c == 0x1b) {
        return 1;
    }
    return 0;
}
char getch() {
    char c = 0;
    while (1) {
        c = getc();
        if (c != 0) {
            break;
        }
    }
    return c;
}

int geti() {
    char c = 0;
    int i = 0;
    while (1) {
        c = getc();
        printc(c);
        if (c >= '0' && c <= '9') {
            i = i * 10 + (c - '0');
        } else if (c == '-') {
            i *= -1;
        } else {
            break;
        }
    }
    return i;
}

short gets(char *s) { //retuns length
    int i = 0;
    while (1) {
        s[i] = getc();
        printc(s[i]);
        if (s[i] == NEWLINE) {
            s[i] = 0;
            break;
        }
        if (s[i] == 0x08) {
            i--;
            printc(' ');
            printc(0x08);
            s[i] = '\0';
            i--;
        }
        i++;
    }
    return i;
    
}
int getih() {
    int i = 0;
    while (1) {
        i = geti();
        if (i != 0) {
            break;
        }
    }
    return i;
}

unsigned long a = 1664525;
unsigned long c = 1013904223;
unsigned long m = 4294967290;

unsigned long seed;

void initialize_seed(unsigned long initial_seed) {
    seed = initial_seed;
}

unsigned long lcg() {
    seed = (a * seed + c) % m;
    return seed;
}


unsigned long get_bios_time() {
    unsigned long time = 0;
    __asm__ __volatile__ (
        "int $0x1A"
        : "=c" (((unsigned char *)&time)[1]),
          "=d" (((unsigned char *)&time)[0]),
          "=b" (((unsigned char *)&time)[2]),
          "=a" (((unsigned char *)&time)[3])
        : "a" (0x0000)
    );

    return time;
}
unsigned long random(unsigned long min, unsigned long max) {
    unsigned long range = max - min + 1;
    unsigned long random_value = lcg() % range;
    return min + random_value;
}

void WriteCharacter(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y){
    short attrib = (backcolour << 4) | (forecolour & 0x0F);
    volatile short * where;
    where = (volatile short *)0xB8000 + (y * 80 + x) ;
    *where = c | (attrib << 8);
}

void WriteGpixel(unsigned char backcolour, int x, int y){
    WriteCharacter(' ', 0xf, backcolour, x, y);
}

void restart() {
    __asm__ __volatile__ (
        "cli\n\t"
        "movw $0x1234, %ax\n\t"
        "movw %ax, %ds \n\t"
        "movw %ax, %es \n\t"
        "movw %ax, %fs \n\t"
        "movw %ax, %gs \n\t"
        "movw %ax, %ss \n\t"
        "ljmp $0xF000, $0xE05B \n\t"
    );
}

void kernel_main(void) {
    os_main(); // Call any other required initialization functions
}

