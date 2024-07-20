#include "kernel.h"
#include "manuos.h"

void os_main() {
    terminal();
}

short m_strcmp(char *str1, char *str2) { // string compare
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void terminal() {
    char *prompt;
    int i = 0;
    nl();
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
                i--;
            }
            i++;
        }

        if (m_strcmp(prompt, "version") == 0) {
            prints("OS: " OS_VERSION);
            nl();
            prints("KERNEL: " KERNEL_VERSION);
            nl();
        } else if (m_strcmp(prompt, "help") == 0) {
            prints(TERMINAL_HELP_MSG);
            nl();
        } else if (m_strcmp(prompt, "wpp") == 0) {
            wpp_interpreter();
        } else if (m_strcmp(prompt, "dices") == 0) {
            dices();
        } else if (m_strcmp(prompt, "clear") == 0) {
            cls();
        } else if (m_strcmp(prompt, "calculator") == 0 || m_strcmp(prompt, "calc") == 0) {
            calculator();
        }
    }
}

int diceroll() {
    return random(1, 6);
}
void dices(){
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

void wpp_interpreter() {
    cls();
    prints("--Wuf++ interpreter--");
    nl();
    prints("Press ESC to exit, enter to execute");
    nl();
    int i = 0;
    int halt, pc = 0;
    unsigned int stack[0xff] = {0};
    short sp, bx, cx, dx;
    char InterpretedProgram[0xff] = {0};
    loop:
    for (i = 0; i < 0xff; i++) InterpretedProgram[i] = 0;
    i = 0;
    prints("> ");
    while(1) {
        InterpretedProgram[i] = getch();
        printc(InterpretedProgram[i]);
        if (InterpretedProgram[i] == NEWLINE) break;
        if (InterpretedProgram[i] == 0x08) {
            i--;
            printc(' ');
            printc(0x08);
            InterpretedProgram[i] = '\0';
            i--;
        }
        if (InterpretedProgram[i] == ESC) {
            cls();
            return;
        };
        i++;
    }
    InterpretedProgram[i] = '=';
    bx = 0;
    dx = 0;
    cx = 0;
    sp = 0xff;
    pc = 0;
    halt = 0;
    nl();
    unsigned len = i;
    while (pc < len) {
        if(halt) break;
        switch (InterpretedProgram[pc]) {
            case '\n':
                break;
            case ' ':
                break;
            case 'i':
                break;
            case 'o':
                break;
            case '+':
                bx++;
                break;
            case '-':
                bx--;
                break;
            case '}':
                sp--;
                stack[sp] = bx & 0xFF;
                sp --;
                stack[sp] = (bx & 0xFF00) >> 8;
                break;
            case '{':
                bx = (stack[sp] << 8) | stack[sp+1];
                sp += 2;
                break;
            case '.':
                printc(bx);
                break;
            case ',':
                bx = getch();
                break;
            case '&':
                pc = cx;
                break;
            case '[':
                pc = pc - cx;
                break;
            case ']':
                pc = pc + cx;
                break;
            case '!':
                bx = ~bx;
                break;
            case '>':
                cx++;
                break;
            case '<':
                cx--;
                break;
            case '$':
                printc(cx);
                break;
            case '#':
                bx = InterpretedProgram[pc+1];
                pc++;
                break;
            case '(': 
                dx = pc;
                cx--;
                break;
            case ')':
                if (cx != 0) {
                    cx--;
                    pc = dx;
                    break;
                } if (cx == 0) {
                    printc(NEWLINE);
                    break;
                }
            case '"':
                dx = bx;
                bx = cx;
                cx = dx;
                break;
            case '%':
                pc++;
                if (bx == InterpretedProgram[pc]) {
                    pc = cx -1;
                    break;
                }
                break;
            case '=':
                halt = 1;
                break;
            case '/':
                bx = bx + cx;
                break;
            case '\\':
                bx = bx - cx;
                break;
            case '@':
                bx = 0;
                break;
            case '^':
                dx = bx;
                bx = (dx & 0xFF00);
                bx = (dx & 0xFF00) >> 8;
                break;
            default:
                
                prints("Error: Unknown command: '");
                printc(InterpretedProgram[pc]);
                prints("' at position: ");
                printi(pc);
                nl();
                break;
        }
        pc++;
    }
    nl();
    goto loop;
}

void calculator() {
    cls();
    prints("--Calculator--");
    nl();
    int a, b, c, sum;
    cloop:
    prints("Operations: 1.ADD 2.SUBTRACT 3.MULTIPLY 4.DIVIDE 5.EXIT ");
    c = geti();
    if (c == 5){
        cls();
        return;
    }
    nl();
    prints("Enter first number: ");
    a = geti();
    nl();
    prints("Enter second number: ");
    b = geti();
    nl();
    switch(c) {
        case 1:
            sum = a + b;
            break;
        case 2:
            sum = a - b;
            break;
        case 3:
            sum = a * b;
            break;
        case 4:
            sum = a / b;
            break;
        case 5:
            terminal();
        default:
            goto cloop;
    }
    prints("Result: ");
    printi(sum);
    nl();
    goto cloop;
}