
#define NEWLINE 0x0d
#define VERSION "ManuOS 0.0.1-puppy"
#define HELP_MSG "Commands: version, help, wpp"

extern void getchar();
extern void nl();
extern void cls();

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
/* Wuf++ - Brainfuck like code interpreter
; Registers that are used:
; bl - main register
; cx - pointer, not the program counter
; + - increment main register
; - - decrement main register
; > - push main register
; < - pop main register
; . - print main register
; , - read to the main register
; [ - jump forward, by cx
; ] - jump back, by cx
; ! - invert main register
; } - increment pointer
; { - decrement pointer
; ? - print pointer
*/

void wpp_interpreter(void) {
    start:
    cls();
    char *wpp_buffer;
    char bl, cx = 0;
    unsigned int i = 0;
    prints("Welcome to Wuf++ interpreter, press enter to run the code");
    nl();
    while (1) {
        i = 0;
        while (1) {
            wpp_buffer[i] = getc();
            if (wpp_buffer[i] == NEWLINE) {
                wpp_buffer[i] = '\0';
                break;
            }
            printc(wpp_buffer[i]);
            i++;
        }
        for (i = 0; wpp_buffer[i] != '\0'; i++) {
            switch (wpp_buffer[i])
            {
            case '+':
                bl++;
                break;
            case '-':
                bl--;
                break;
            case '>':
                asm(
                    "nop"
                    : 
                    : "bl"(bl)
                );
                asm("push %bx");
                break;
            case '<':
                asm("pop %bx");
                asm(
                    "nop"
                    : "=bl"(bl)
                    :
                );
                break;
            case '.':
                printc(bl);
                break;
            case ',':
                bl = getch();
                break;
            case '[':
                i = i - cx;
                break;
            case ']':
                i = i + cx;
                break;
            default:
                break;
            }
        }
        nl();
        prints("Code finished, press enter to run the code again");
        getch();
        break;
    }
    goto start;
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