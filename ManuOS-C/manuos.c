#include "kernel.h"
#include "manuos.h"
#include "m_stdlib.h"

unsigned int cRow = 0;
uint8_t taskbarColor;
char cProgram[25];
char OS_Sector[0x200]; // 512 bytes for os settings, starting at sector 38
short OSS_ptr = 90;
char username[32];
/*OS Sector
0x00 - Taskbar color
0x0f- 0x2f username, 0x17 reading address
*/

void os_main() {
    if (disk_read(OS_Sector, OSS_ptr, 1) != 0) kernel_panic("Failed to load OS settings sector");
    taskbarColor = OS_Sector[0x00];
    for (int i = 0; i < 32; i++) {
        username[i] = OS_Sector[0xf + i];
    }
    terminal();
}

void nl() {
    newline();
    taskbar();
}

void terminal() {
    clt();
    char prompt[40];
    int i = 0;
    prints("Welcome to ManuOS, ");
    prints(username);
    nl();
    while (1){
        memset(prompt, 0, 40);
        printc(getCurrentDir());
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

        if (strcmp(prompt, "version") == 0) {
            prints("Copyright (C) 2024 Benjamin H. All rights reserved.");
            nl();
            prints("OS: " OS_VERSION);
            nl();
            prints("KERNEL: " KERNEL_VERSION);
            nl();
        } else if (strcmp(prompt, "help") == 0) {
            prints(TERMINAL_HELP_MSG);
            nl();
        } else if (strcmp(prompt, "wpp") == 0) {
            wpp_interpreter();
        } else if (strcmp(prompt, "dices") == 0) {
            dices();
        } else if (strcmp(prompt, "clear") == 0) {
            clt();
        } else if (strcmp(prompt, "calculator") == 0 || strcmp(prompt, "calc") == 0) {
            calculator();
        } else if (strcmp(prompt, "ball") == 0) {
            bouncing_ball();
        } else if (strcmp(prompt, "taskbar") == 0) {
            prints("Change taskbar color: ");
            taskbarColor = getih();
            OS_Sector[0x00] = taskbarColor;
            disk_write(OS_Sector, OSS_ptr, 1);
            init_taskbar();
        } else if (strcmp(prompt, "color") == 0) {
            prints("Colors: 0 - Black, 1 - Blue 2 - Green, 3 - Cyan, 4 - Red, 5 - Magenta, 6 - Brown, 7 - Light Gray, 8 - Dark Gray, 9 - Light Blue, 10 - Light Green, 11 - Light Cyan, 12 - Light Red, 13 - Light Magenta, 14 - Yellow, 15 - White");
            nl();
        } else if (strcmp(prompt, "username") == 0) {
            prints("Current username: ");
            for (int i = 0; i < strlen(username); i++) {
                printc(username[i]);
            }
            nl();
            prints("Change username: ");
            gets(username);
            for (int i = 0; i < 32; i++) {
                OS_Sector[0x0f + i] = username[i];
            }
            if (disk_write(OS_Sector, OSS_ptr, 1) != 0) prints("Failed to write sector");
            nl();

        } else if (strcmp(prompt, "restart") == 0) {
            restart();
            
        } else if (startsWith(prompt, "echo ") == 0) {
            for (int i = 5; i < strlen(prompt); i++) {
                printc(prompt[i]);
            }
            nl();
        } else if (strcmp(prompt, "setup") == 0) {
            prints("ManuOS Setup");
            nl();
            prints("Username: ");
            gets(username);
            for (int i = 0; i < 32; i++) {
                OS_Sector[0x0f + i] = username[i];
            }
            nl();
            OS_Sector[0x00] = BLUE;
            disk_write(OS_Sector, OSS_ptr, 1);
            prints("ManuOS Setup Complete");
            nl();
            prints("Rebooting...");
            sleepms(500);
            restart();
        } else if (strcmp(prompt, "test") == 0) {
            char tbuf[512] = {0};
            strcpy(tbuf, "This is a test file");
            if (create_file("Testfile", 'A', tbuf, 1) == 0){
                prints("File created");
            }
            char cbuf[512] = {0};
            read_file("Testfile", 'A', cbuf);
            prints(cbuf);
            strcpy(cbuf, "This is a second test file");
            create_file("Testfiles", 'B', cbuf, 1);
            read_file("Testfiles", 'B', tbuf);
            prints(tbuf);
        } else if (startsWith(prompt, "read ") == 0) {
            char filename[12] = {0};
            char dir = prompt[5];
            for (int i = 7; i < strlen(prompt); i++) {
                filename[i - 7] = prompt[i];
            }
            char cbuf[512] = {0};
            read_file(filename, dir, cbuf);
            prints(cbuf);
            nl();
        } else if (strcmp(prompt, "create") == 0) {
            char filename[12] = {0};
            char dir;
            char data[DATA_SIZE] = {0};
            prints("Enter Filename: ");
            gets(filename);
            nl();
            prints("Enter Directory: ");
            dir = getch();
            printc(dir);
            nl();
            prints("Enter Data: ");
            gets(data);
            nl();
            if (create_file(filename, dir, data, 1) == 0) prints("File created successfully");
            else prints("Failed to create file");
            nl();
        } else if (startsWith(prompt, "list ") == 0) {
            list_files(prompt[5]);
            nl();
        } else if (startsWith(prompt, "mkdir ") == 0){
            char dir = prompt[6];
            if (mkdir(dir) == 0) prints("Directory created");
            else prints("Failed to create directory");
            nl();
        } else if (strcmp(prompt, "dir") == 0) {
            list_dirs();
        }
        
    }
}

void text_editor() {
    strcpy(cProgram, "Text Editor");
    clrs();
    while (1) {
        clrs();
        nl();
    }
}

int diceroll() {
    return random(1, 6);
}
void dices(){
    strcpy(cProgram, "Dices");
    clrs();
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
        update_taskbar();
        prints("Select an action: ");
        nl();
        update_taskbar();
        prints("1 - reroll all");
        nl();
        update_taskbar();
        prints("2 - reroll selected");
        nl();
        update_taskbar();
        prints("3 - exit");
        update_taskbar();
        char c = getch();
        nl();
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
                clt();
                return;
            default:
                goto dice_loop;
        }
    }
}

void wpp_interpreter() {
    strcpy(cProgram, "Wuf++ Interpreter");
    clrs();
    prints("Press ESC to exit, enter to execute the code");
    nl();
    int i = 0;
    int halt, pc = 0;
    unsigned int stack[0xff] = {0};
    short sp, bx, cx, dx;
    char InterpretedProgram[0x200] = {0};
    loop:
    for (i = 0; i < 0x200; i++) InterpretedProgram[i] = 0;
    i = 0;
    prints("> ");
    while(1) {
        InterpretedProgram[i] = getch();
        printc(InterpretedProgram[i]);
        if (InterpretedProgram[i] == NEWLINE){
            break;
        } 
        if (InterpretedProgram[i] == 0x08) {
            i--;
            printc(' ');
            printc(0x08);
            InterpretedProgram[i] = '\0';
            i--;
        }
        if (InterpretedProgram[i] == ESC) {
            clt();
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
    interpret:
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
    strcpy(cProgram, "Calculator");
    clrs();
    int a, b, c, sum;
    cloop:
    prints("Operations: 1.ADD 2.SUBTRACT 3.MULTIPLY 4.DIVIDE 5.EXIT ");
    update_taskbar();
    c = geti();
    if (c == 5){
        clt();
        return;
    }
    nl();
    update_taskbar();
    prints("Enter first number: ");
    a = geti();
    nl();
    update_taskbar();
    prints("Enter second number: ");
    b = geti();
    nl();
    update_taskbar();
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
        default:
            goto cloop;
    }
    prints("Result: ");
    printi(sum);
    nl();
    update_taskbar();
    goto cloop;
}

void bouncing_ball(){
    cls();
    int x = 0, y = 1;
    int dx = 1, dy = 1;
    int ballX = 0, ballY = 0;
    int color = 0xf;
    while (1) {
        sleepms(100);
        if(ifESC()) {
            clt();
            return;
        }
        if (ballX < 0 || ballX > 79) {
            dx *= -1;
        }
        if (ballY < 0 || ballY > 24) {
            dy *= -1;
        }
        if (color > 0xf) {
            color = 1;
        }
        ballX += dx;
        ballY += dy;
        WriteGpixel(0xf, ballX, ballY);
        WriteGpixel(0, x, y);
        x = ballX;
        y = ballY;
        color++;
    }
}

void clrs() { //clear screen and update taskbar
    cls();
    init_taskbar();
}

void clt(){ //clear screen for terminal, use for when exiting to terminal
    strcpy(cProgram, "Terminal");
    clrs();
}

void taskbar() { //simple taskbar, not required in custom programs
    char tskbr[80] = {0};
    strcpy(tskbr, username);
    strcat(tskbr, " | ");
    strcat(tskbr, cProgram);	
    strcat(tskbr, " | ");
    strcat(tskbr, OS_VERSION);
    int i = 0;
    for (int i = 0; i < 80; i++) {
        WriteCharacter(tskbr[i], 0xf, taskbarColor, i, 0);
    }
}

void update_taskbar() {
    cRow++;
    if (cRow > 23) {
        taskbar();
    }
}

void init_taskbar() {
    cRow = 0;
    taskbar();
    nl();
}