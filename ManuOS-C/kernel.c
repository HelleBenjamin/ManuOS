
#define NEWLINE 0x0d
#define VERSION "ManuOS 0.0.1-alpha, Puppy-kernel 0.0.1, C-edition"
#define HELP_MSG "Commands: version, help, wpp, yatzy, mazec"

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

int diceroll() {
    return random(1, 6);
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
    unsigned long initial_seed = get_bios_time();
    initialize_seed(initial_seed);
    unsigned int dicesone = 0; // how many dices are equal to 1
    unsigned int dicestwo = 0;
    unsigned int dicesthree = 0;
    unsigned int dicesfour = 0;
    unsigned int dicesfive = 0;
    unsigned int dicessix = 0;
    while (1) {
        prints("Press enter to roll");
        getch();
        prints("Rolling...");
        nl();
        for (int i = 0; i < 5; i++) {
            dices[i] = diceroll();
        }
        yatzy_loop:
        for (int i = 0; i < 5; i++) {
            switch(dices[i]) {
                case 1:
                    dicesone++;
                    break;
                case 2:
                    dicestwo += 2;
                    break;
                case 3:
                    dicesthree += 3;
                    break;
                case 4:
                    dicesfour += 4;
                    break;
                case 5:
                    dicesfive += 5;
                    break;
                case 6:
                    dicessix += 6;
                    break;
            }
        }
        nl();
        printi(dicesone);
        printc(' ');
        printi(dicestwo);
        printc(' ');
        printi(dicesthree);
        printc(' ');
        printi(dicesfour);
        printc(' ');
        printi(dicesfive);
        printc(' ');
        printi(dicessix);
        nl();
        rollsRemaining--;
        initial_seed = get_bios_time();
        initialize_seed(initial_seed);
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
        prints("3 - See scoreboard");
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
                        dicesone--;
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
            
        } else if (c == '2') { // score
            prints("Where do you want to score?");
            nl();
            char sel[10] = {0};
            i = 0;
            while (1) {
                sel[i] = getc();
                printc(sel[i]);
                if (sel[i] == NEWLINE) {
                    sel[i] = '\0';
                    break;
                }
                i++;
            }
            if (m_strcmp(sel, "ones") == 0) {
                scoreboard[0] = dicesone;
            }
            if (m_strcmp(sel, "twos") == 0) {
                scoreboard[1] = dicestwo;
            }
            if (m_strcmp(sel, "threes") == 0) {
                scoreboard[2] = dicesthree;
            }
            if (m_strcmp(sel, "fours") == 0) {
                scoreboard[3] = dicesfour;
            }
            if (m_strcmp(sel, "fives") == 0) {
                scoreboard[4] = dicesfive;
            }
            if (m_strcmp(sel, "sixes") == 0) {
                scoreboard[5] = dicessix;
            }

            
        } else if (c == '3') {
                       prints("--Scoreboard--");
            nl();
            prints("Ones: ");
            printi(scoreboard[0]);
            nl();
            prints("Twos: ");
            printi(scoreboard[1]);
            nl();
            prints("Threes: ");
            printi(scoreboard[2]);
            nl();
            prints("Fours: ");
            printi(scoreboard[3]);
            nl();
            prints("Fives: ");
            printi(scoreboard[4]);
            nl();
            prints("Sixes: ");
            printi(scoreboard[5]);
            nl();
            prints("Sum: ");
            for (int i = 0; i < 5; i++) {
                scoreboard[6] = scoreboard[0] + scoreboard[1] + scoreboard[2] + scoreboard[3] + scoreboard[4] + scoreboard[5];
            }
            printi(scoreboard[6]);
            nl();
            prints("Three of a kind: ");
            printi(scoreboard[8]);
            nl();
            prints("Four of a kind: ");
            printi(scoreboard[9]);
            nl();
            prints("Full house: ");
            printi(scoreboard[10]);
            nl();
            prints("Small straight: ");
            printi(scoreboard[11]);
            nl();
            prints("Large straight: ");
            printi(scoreboard[12]);
            nl();
            prints("Chance: ");
            printi(scoreboard[13]);
            nl();
            prints("Yahtzee: ");
            printi(scoreboard[14]);
            nl();
            prints("Total: ");
            printi(scoreboard[15]);
            nl();
            prints("--------------");
            nl();
            prints("Press any key to continue");
            getch();
        }
    }

}
#define NULL 0
#define DEFAULT_X 1 //player start position
#define DEFAULT_Y 1
#define WIDTH 30
#define HEIGHT 20

#define WALL '#'
#define PATH ' '
#define PLAYER 'P'
#define DOOR 'D'


static char* maze0[HEIGHT] = {
    "#############################",
    "# #   #      #              #",
    "# ## ### # # #              #",
    "#        # # #              #",
    "#### ## ## ### #            #",
    "#  #  #  # # #D###          #",
    "#  #  #  # # ### #          #",
    "#     #  # #     #          #",
    "# ######## # ### #          #",
    "#      #     #   #          #",
    "#### # #### ###  #          #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#############################"
};

int currentX = 1;
int currentY = 1;
char** currentMaze = NULL;
int currentMazeNum = 0;

void renderMaze(char** maze) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printc(maze[i][j]);
        }
        nl();
    }
    prints("Input: ");
}

void movePlayer(char** maze) {
    char input = getch();
    switch (input){
        case 'w':
            //up
            if (maze[currentY - 1][currentX] != WALL) {
                maze[currentY][currentX] = PATH;
                currentY--;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        case 'a':
            //left
            if (maze[currentY][currentX - 1] != WALL) {
                maze[currentY][currentX] = PATH;
                currentX--;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        case 's':
            //down
            if (maze[currentY + 1][currentX] != WALL) {
                maze[currentY][currentX] = PATH;
                currentY++;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        case 'd':
            //right
            if (maze[currentY][currentX + 1] != WALL) {
                maze[currentY][currentX] = PATH;
                currentX++;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        default:
            break;
    }
}

void load_new_level() {
    currentMaze = maze0;
    currentMazeNum++;
    currentMaze[currentY][currentX] = PATH;
    currentX = DEFAULT_X;
    currentY = DEFAULT_Y;
    currentMaze[currentY][currentX] = PLAYER;
}

void game_loop() {
    while (1) {
        if (currentMaze[currentY + 1][currentX] == DOOR || currentMaze[currentY - 1][currentX] == DOOR || currentMaze[currentY][currentX + 1] == DOOR || currentMaze[currentY][currentX - 1] == DOOR) {
            load_new_level();
        }
        cls();
        prints("Current level: ");
        printi(currentMazeNum);
        renderMaze(currentMaze);
        movePlayer(currentMaze);
    }
}

void mazec_start_menu() {
    char start_menu_msg[] = "MazeC 0.1\n 1. Start\n 2. Keyboard controls\n 3. Exit\n";
    prints(start_menu_msg);
    nl();
    while (1) {
        char input = getch();
        if (input == '1') {
            load_new_level();
            game_loop();
        } else if (input == '2') {
            prints("Keyboard controls: ");
            prints("w = up, a = left, s = down, d = right, press enter after pressing a key\n");
        } else if (input == '3') {
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
        } else if (m_strcmp(prompt, "mazec") == 0) {
            mazec_start_menu();
        }
    }
}