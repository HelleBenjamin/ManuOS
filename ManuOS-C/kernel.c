
#define NEWLINE 0x0d
#define VERSION "ManuOS 0.0.1-alpha, Puppy-kernel 0.0.1, C-edition"
#define HELP_MSG "Commands: version, help, wpp"

extern void getchar();
extern void nl();
extern void cls();
extern void wpp_interpreter();



void ascii_to_hex(char *str) {
    while (*str) {
        *str = *str - 48;
        *str = *str << 4;
        str++;
    }
};
void printc(char c) {
    asm("mov %al, 0x95\n\t");
    asm("call printchr\n\t");
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

char getch() {
    char c = 0;
    while (1) {
        c = getc();
        if (c != NEWLINE) {
            break;
        }
    }
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
        } else if (m_strcmp(prompt, "wpp") == 0) {
            wpp_interpreter();
        }
    }
}