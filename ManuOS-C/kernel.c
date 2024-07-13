
#define NEWLINE 0x0d
#define VERSION "ManuOS 0.0.1-alpha, Puppy-kernel 0.0.1, C-edition"
#define HELP_MSG "Commands: version, help, wpp, dices"

extern void getchar();
extern void nl();
extern void cls();
extern void wpp_interpreter();


void sleepms(int ms) {
    int i = 0;
    while (i < ms) {
        i++;
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
        if (c != 0) {
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

unsigned long a = 1664525;
unsigned long c = 1013904223;
unsigned long m = 4294967290;

unsigned long seed; // Seed value

void initialize_seed(unsigned long initial_seed) {
    seed = initial_seed;
}

unsigned long lcg() {
    seed = (a * seed + c) % m;
    return seed;
}


unsigned long get_bios_time() {
    unsigned long time = 0;

    // BIOS interrupt 1Ah, function 00h to get the current clock count
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

void manu() {
    prints("Manu");
    nl();
    char manu[28][28] = {
        ",,,__,,,,,,",
        ",,/         "
    };

    for (int i = 0; i < 28; i++) {
        prints(manu[i]);
        nl();
    }
}

int diceroll() {
    return random(1, 6);
}
void rdice(){
    int dices[5] = {1};
    int initial_seed;
    int dicesToReRoll[5] = {0};
    for (int i = 0; i < 5; i++) {
            dices[i] = diceroll();
    }
    while(1){
        dice_loop:
        initial_seed = get_bios_time();
        initialize_seed(initial_seed);
        prints("Your dices are: ");
        for (int i = 0; i < 5; i++) {
            printc('[');
            printi(dices[i]);
            printc(']');
            printc(' ');
        }
        nl();
        prints("1 - reroll all");
        nl();
        prints("2 - reroll selected");
        nl();
        prints("3 - exit");
        nl();
        char c = getch();
        switch (c){
            case '1':
                for (int i = 0; i < 5; i++) {
                    dices[i] = diceroll();
                }
                break;
            case '2':
                prints("Select dices to reroll: ");
                int i = 0;
                while (1) {
                    dicesToReRoll[i] = getc();
                    printc(dicesToReRoll[i]);
                    if (dicesToReRoll[i] == NEWLINE) {

                        break;
                    }
                    i++;
                }
                for (int i = 0; i < 5; i++) {
                    switch (dicesToReRoll[i]) {
                        case '0':
                            break;
                        case '1':
                            dices[0] = diceroll();
                            break;
                        case '2':
                            dices[1] = diceroll();
                            break;
                        case '3':
                            dices[2] = diceroll();
                            break;
                        case '4':
                            dices[3] = diceroll();
                            break;
                        case '5':
                            dices[4] = diceroll();
                            break;
                    }
                }
                goto dice_loop;
            case '3':
                return;
            default:
                goto dice_loop;
        }
    }
}
void main(void) {
    char *prompt;
    int i = 0;
    prints("Welcome to ManuOS");
    nl();
    while (1){
        printc('>');
        i = 0;
        while (1) {
            prompt[i] = getc();
            printc(prompt[i]);
            if (prompt[i] == NEWLINE) {
                prompt[i] = '\0';
                nl(); 
                break;
            }
            if (prompt[i] == 0x08) {
                i--;
                printc(' ');
                printc(0x08);
                prompt[i] = '\0';
            }
            i++;
        }

        if (m_strcmp(prompt, "version") == 0) {
            prints("ManuOS " VERSION);
            nl();
        } else if (m_strcmp(prompt, "help") == 0) {
            prints(HELP_MSG);
            nl();
        } else if (m_strcmp(prompt, "wpp") == 0) {
            wpp_interpreter();
        } else if (m_strcmp(prompt, "dices") == 0) {
            rdice();
        } else if (m_strcmp(prompt, "cls") == 0) {
            cls();
        } else if (m_strcmp(prompt, "manu") == 0) {
            manu();
        }
    }
}