extern void printchr();
extern void getchar();
extern void nl();

#define NEWLINE 0x0d


void printc(char c) {
    asm("mov %al, 0x95\n\t");
    printchr();
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
    char prompt[20];
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
        printc('O');

    }
}