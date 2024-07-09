
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

short m_strcmp(char *str1, char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void main(void) {
    char *prompt;
    int i = 0;
    while (1){
        printc('>');
        i = 0;
        while (1) {
            prompt[i] = getc();
            if (prompt[i] == NEWLINE) {
                prompt[i] = '\0';
                break;
            }
            printchr(prompt[i]);
            i++;
        }

        if (m_strcmp(prompt, "version") == 0) {
            prints(VERSION);
        }
    }
}