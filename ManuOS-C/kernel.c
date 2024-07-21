#include "kernel.h"

extern void os_main(); // defined in manuos.c
/* Copyright (C) 2024 Benjamin H. All rights reserved. */

/** Kernel functions and syscalls ***/

void nl() { // new line
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
    cls();
    prints("KERNEL PANIC: ");
    prints(msg);
    nl();
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

void kernel_main(void) {
    // Add here functions that should be called at the start of the kernel
    os_main(); // Don't remove this line
}