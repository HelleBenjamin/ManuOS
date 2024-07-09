
#define NEWLINE 0x0d
#define VERSION "ManuOS 0.0.1-puppy"
#define HELP_MSG "Commands: version, help"

extern void getchar();
extern void nl();

void printc(char c) {
    asm volatile(
        "movb %b0, %%al\n\t"
        "jmp 1f\n\t"
        ".byte 0x9c\n\t"
        "1:\n\t"
        "movb $0x0e, %%ah\n\t"
        "int $0x10"
        :
        : "a"(c)
        : "cc"
    );
}

void prints(char *s) {
    int len = 0;
    __asm__ volatile(
        "1:\n\t"
        "lodsb\n\t"
        "testb %%al, %%al\n\t"
        "jz 2f\n\t"
        "movb $0x0e, %%ah\n\t"
        "int $0x10\n\t"
        "incl %0\n\t"
        "jmp 1b\n\t"
        "2:\n\t"
        : "=S"(s), "=c"(len)
        : "0"(s)
        : "cc"
    );
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
            printc(prompt[i]);
            i++;
        }

        if (m_strcmp(prompt, "version") == 0) {
            prints("ManuOS " VERSION "\n");
            nl();
        } else if (m_strcmp(prompt, "help") == 0) {
            prints(HELP_MSG);
            nl();
        }
    }
}