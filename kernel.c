extern void printchr();
extern void getchar();
extern void nl();


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
        while(prompt[i] != '\n') {
            prompt[i] = getc();
            printchr(prompt[i]);
            i++;
        }
        prompt[i] = '\n'; // Add newline character at the end
        printc('\n');
    }
}