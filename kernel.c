
#define NEWLINE 0x0d
#define VERSION "ManuOS 0.0.1-puppy"

extern void printchr();
extern void getchar();
extern void nl();

void printc(char c) {
    asm("mov %al, 0x95\n\t");
    printchr();
}

void prints(char *s) {
    while (*s) {
        printc(*s);
        s++;
    }
}

char getc() {
    char c = 0;
    getchar();
    asm(
        "nop"
        : "=al"(c)
        :
    );
}


void main(void) {
    char *prompt;
    int i = 0;
    while (1){
        printc('>');
        i = 0;
        while (1) {
            prompt[i] = getc();
            printchr(prompt[i]);
            if (prompt[i] == NEWLINE) break;
            i++;
        }
        prompt[i] = 0;
        for (i = 0; prompt[i] != 0; i++) {
            printc(prompt[i]);
        }
        if (prompt == "version") {
            prints(VERSION);
        }
        nl();
    }
}