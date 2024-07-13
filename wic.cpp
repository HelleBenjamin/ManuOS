#include <iostream> // include all the necessary libraries
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>

#define helpMessage "-s <source file> -o <output file> -h help -v version -c compile -i interpret"
#define supportedArchitectures "Supported architectures: X86"
#define version "Wuf++ Interpreter Compiler v0.1"

using namespace std;

vector<char> program; // source program
vector<string> compiledProgram; // compiled program



/* Wuf++ Interpreter Compiler, WIC

Registers:

    bl - main register
    cx - pointer

Syntax:
    + - increment main register
    - - decrement main register
    } - push main register
    { - pop main register
    . - print main register
    , - read to the main register
    & - jump to location pointed by pointer
    [ - pc = pc - cx
    ] - pc = pc + cx
    ! - invert main register
    > - increment pointer
    < - decrement pointer
    $ - print pointer
    #[char] - load char to the main register
    ( - loop start, decrement pointer and loop until pointer = 0
    ) - loop end
    " - swap registers
    %[char] - compare main register with char, jump if equal to location pointed by pointer
    = - halt
    / - add main register and pointer, bx = bx + cx
    \ - sub main register and pointer, bx = bx - cx
    @ - load 0 to the main register
    ^- swap bl with bh, bh <- bl
*/

string filename;
ifstream source_file;
ofstream output_file; // output file

uint16_t bx = 0;
uint16_t cx,dx = 0;
unsigned int pc = 0;
uint8_t stack[1000] = {0};
unsigned int sp = 1000;
bool halt = false;

string source_name, output_name;

string dectohex(int num) {
    stringstream ss;
    ss << hex << num;
    return ss.str();
}

void Interpreter() {
    char c;
    while(source_file.get(c)) {
        program.push_back(c);
    }
    source_file.close();
    for(pc = 0; pc < program.size(); pc++) {
        if(halt) break;
        switch (program[pc]) {
            case '\n':
                break;
            case ' ':
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
                cout << char(bx);
                break;
            case ',':
                cin >> bx;
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
                cout << dectohex(cx) << endl;
                break;
            case '#':
                bx = program[pc+1];
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
                    break;
                }
            case '"':
                dx = bx;
                bx = cx;
                cx = dx;
                break;
            case '%':
                pc++;
                if (bx == program[pc]) {
                    pc = cx -1;
                    break;
                }
                break;
            case '=':
                halt = true;
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
                cout << "Error: Unknown command: '" << program[pc] << "' at position: " << pc << "" << endl;
                break;
        }
    }
}

void compileX86() {
    char c;
    int pc = 0;
    int loopLabel = 0;
    while(source_file.get(c)) {
        program.push_back(c);
    }

    compiledProgram.push_back("global _start");
    compiledProgram.push_back(";wic v0.0.1");
    compiledProgram.push_back("section .text");

    compiledProgram.push_back("jp_cx:");
    compiledProgram.push_back("     jmp edx");
    if (program[pc] == 'i') {
        compiledProgram.push_back("readc:");
        compiledProgram.push_back("     mov edi, ecx");
        compiledProgram.push_back("     mov eax, 0x3");
        compiledProgram.push_back("     mov ebx, 0x0");
        compiledProgram.push_back("     mov ecx, ebx");
        compiledProgram.push_back("     mov edx, 1");
        compiledProgram.push_back("     int 0x80");
        compiledProgram.push_back("     mov ecx, edi");
        compiledProgram.push_back("     ret");        
        pc++;
    }
    if (program[pc] == 'o') {
        compiledProgram.push_back("printc:");
        compiledProgram.push_back("     mov edi, ecx");
        compiledProgram.push_back("     push ebx");   
        compiledProgram.push_back("     mov eax, 0x4");
        compiledProgram.push_back("     mov ebx, 0x1");
        compiledProgram.push_back("     mov ecx, esp");
        compiledProgram.push_back("     mov edx, 1");
        compiledProgram.push_back("     int 0x80");
        compiledProgram.push_back("     pop ebx");
        compiledProgram.push_back("     mov ecx, edi");
        compiledProgram.push_back("     ret");
        pc++;
    }


    compiledProgram.push_back("_start:");
    compiledProgram.push_back("     mov ebx, 0");
    compiledProgram.push_back("     mov ecx, 0");
    compiledProgram.push_back("     mov edx, 0");
    compiledProgram.push_back("main:");
    int lineLabel = 0;
    for(int i = pc; i < program.size(); i++) {
        switch (program[i]) {
            case '\n':
                break;
            case ' ':
                break;
            case '+':
                compiledProgram.push_back("     inc ebx");
                break;
            case '-':
                compiledProgram.push_back("     dec ebx");
                break;
            case '}':
                compiledProgram.push_back("     push ebx");
                break;
            case '{':
                compiledProgram.push_back("     pop ebx");
                break;
            case '.':
                compiledProgram.push_back("     call printc");
                break;
            case ',':
                compiledProgram.push_back("     call readc");
                break;
            case '[':
                compiledProgram.push_back("     sub pc, ecx");
                break;
            case ']':
                compiledProgram.push_back("     add pc, ecx");
                break;
            case '!':
                compiledProgram.push_back("     not ebx");
                break;
            case '>':
                compiledProgram.push_back("     inc ecx");
                break;
            case '<':
                compiledProgram.push_back("     dec ecx");
                break;
            case '$':
                compiledProgram.push_back("     push bx");
                compiledProgram.push_back("     mov bx, cx");
                compiledProgram.push_back("     call printc");
                compiledProgram.push_back("     pop bx");
                break;
            case '#':
                compiledProgram.push_back("     mov bx, '" + std::string(1, program[i+1]) + "'");
                i++;
                break;
            case '(': 
                compiledProgram.push_back("loop" + std::to_string(loopLabel) + ":");
                loopLabel++;
                break;
            case ')':
                compiledProgram.push_back("     cmp ecx, 0");
                compiledProgram.push_back("     dec ecx");
                compiledProgram.push_back("     jne loop" + std::to_string(loopLabel-1));
                compiledProgram.push_back("     .loop" + std::to_string(loopLabel-1) + "_end:");
                break;
            case '"':
                compiledProgram.push_back("     xchg ebx, ecx");
                break;
            case '%':
                compiledProgram.push_back("     cmp ebx, " + std::to_string(program[i+1]));
                compiledProgram.push_back("     lea edx, [ecx + main]");
                compiledProgram.push_back("     je jp_cx");
                i++;
                break;
            case '=':
                compiledProgram.push_back("     mov eax, 1");
                compiledProgram.push_back("     mov ebx, 0");
                compiledProgram.push_back("     int 0x80");
                break;
            case '/':
                compiledProgram.push_back("     add ebx, ecx");
                break;
            case '\\':
                compiledProgram.push_back("     sub ebx, ecx");
                break;
            case '@':
                compiledProgram.push_back("     mov ebx, 0");
                break;
            case '^':
                compiledProgram.push_back("     xchg bl, bh");
                break;
            default:
                cout << "Error: " << program[i] << " at position " << i << endl;
                break;
        }
    }
    for(int i = 0; i < compiledProgram.size(); i++) {
        output_file << compiledProgram[i] << endl;
        //cout << compiledProgram[i] << endl;
    }
    cout << "Compiled" << endl;
    output_file.close();
    source_file.close();
}

int main(int argc, char *argv[]) {
    for(int i = 0; i < argc; i++) {
        if (argc == 1) {
            cout << "Error: No arguments" << endl;
            cout << "Usage: ";
            cout << helpMessage << endl;
            return 1;
        }   
        if(string(argv[i]) == "-h") {
            cout << helpMessage << endl;
        }
        if((string(argv[i])).find("-s") == 0) {
            filename = argv[i+1];
            int len = filename.length();
            source_name = filename;
            source_name.erase(len-4, 4); // remove .wpp
            source_file.open(filename);
        }
        if((string(argv[i])).find("-o") == 0) {
            filename = argv[i+1];
            output_name = filename;
            filename = filename + ".asm";
            output_file.open(filename);
        }
        if(string(argv[i]) == "-v") {
            cout << version << endl;
            cout << supportedArchitectures << endl;
        }
        if(string(argv[i]) == "-c") {
            compileX86();
            //system(("./wic -s " + source_name + " -o " + output_name + ".asm").c_str());
            system(("nasm -f elf32 -o " + output_name + ".o " + source_name + ".asm").c_str());
            system(("ld -m elf_i386 -o " + output_name + " -static -nostdlib " + output_name + ".o").c_str());
            system(("rm " + output_name + ".o").c_str());
        }
        if(string(argv[i]) == "-i") {
            Interpreter();
        }
    }
    return 0;
}