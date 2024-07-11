
#define NEWLINE 0x0d
#define VERSION "ManuOS 0.0.1-alpha, Puppy-kernel 0.0.1, C-edition"
#define HELP_MSG "Commands: version, help, wpp, yatzy"

extern void getchar();
extern void nl();
extern void cls();
extern void wpp_interpreter();



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



unsigned int random(int min, int max) {;
    int seed;
    //asm("push %ax\n\t");
    asm("mov %ax, %ax\n\t");
    asm(
        "nop\n\t"
        : "=ax"(seed)
        : 
    );
    //asm("pop %eax\n\t");
    return (seed % (max - min + 1)) + min;
}

int diceroll() {
    while (1) {
        int dice = random(1, 6);
        if (dice < 6 && dice > 1) {
            return dice;
        } else {
            continue;
        }       
    }

}

void yatzy() {
    cls();
    prints("YATZY");
    nl();
    int scoreboard[16] = {0}; 
    /* Score board
        0 - Ones
        1 - Twos
        2 - Threes
        3 - Fours
        4 - Fives
        5 - Sixes
        6 - Sum
        7 - Bonus
        8 - Three of a kind
        9 - Four of a kind
        10 - Full house
        11 - Small straight
        12 - Large straight
        13 - Chance
        14 - Yahtzee
        15 - Total
    */
    int dices[5] = {0};
    int rollsRemaining = 3;
    while (1) {
        prints("Press enter to roll");
        getch();
        prints("Rolling...");
        nl();
        for (int i = 0; i < 5; i++) {
            dices[i] = diceroll();
        }
        yatzy_loop:
        rollsRemaining--;
        prints("Rolls remaining: ");
        printi(rollsRemaining);
        nl();
        prints("Your dices are: ");
        for (int i = 0; i < 5; i++) {
            printc('[');
            printi(dices[i]);
            printc(']');
            printc(' ');
        }
        nl();
        prints("                 ^   ^   ^   ^   ^");
        nl();
        prints("Dice numbers:    1   2   3   4   5");
        nl();
        if (rollsRemaining == 0) {
            break;
        }
        prints("What do you want to do?");
        nl();
        prints("1 - Reroll");
        nl();
        prints("2 - Score");
        nl();
        char c = getch();
        char dicesToReRoll[5] = {0};
        int i = 0;
        if (c == '1') {
            prints("Which dices to reroll?");
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
            goto yatzy_loop;
            
        } else if (c == '2') {
            break;
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
            prints("ManuOS " VERSION "\n");
            nl();
        } else if (m_strcmp(prompt, "help") == 0) {
            prints(HELP_MSG);
            nl();
        } else if (m_strcmp(prompt, "wpp") == 0) {
            wpp_interpreter();
        } else if (m_strcmp(prompt, "yatzy") == 0) {
            yatzy();
        } else if (m_strcmp(prompt, "y") == 0) {
            yatzy();
        }
    }
}