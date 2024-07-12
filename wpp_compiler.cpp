#include <iostream> // include all the necessary libraries
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>

#define helpMessage "-c <source file> -o <output file> -h help -v version"
#define supportedArchitectures "Supported architectures: X86"
#define version "Wuf++ compiler v0.1"

using namespace std;

vector<char> program; // source program
vector<string> compiledProgram; // compiled program


/* Architectures:
    - X86
    - ARM(not supported yet)

Registers:

    bx - main register
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
ofstream output_file;

string dectohex(int num) {
    stringstream ss;
    ss << hex << num;
    return ss.str();
}

void compileX86() {
    char c;
    int loopLabel = 0;
    while(source_file.get(c)) {
        program.push_back(c);
    }

    compiledProgram.push_back("global _start");
    compiledProgram.push_back(";wic v0.0.1");
    compiledProgram.push_back("section .text");

    compiledProgram.push_back("jp_cx:");
    compiledProgram.push_back("     push cx");
    compiledProgram.push_back("     ret");

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

    compiledProgram.push_back("readc:");
    compiledProgram.push_back("     mov edi, ecx");
    compiledProgram.push_back("     mov eax, 0x3");
    compiledProgram.push_back("     mov ebx, 0x0");
    compiledProgram.push_back("     mov ecx, ebx");
    compiledProgram.push_back("     mov edx, 1");
    compiledProgram.push_back("     int 0x80");
    compiledProgram.push_back("     cmp ebx, 0");
    compiledProgram.push_back("     je readc");
    compiledProgram.push_back("     mov ecx, edi");
    compiledProgram.push_back("     ret");

    compiledProgram.push_back("_start:");
    compiledProgram.push_back("     mov ebx, 0");
    compiledProgram.push_back("     mov ecx, 0");
    compiledProgram.push_back("     mov edx, 0");
    for(int i = 0; i < program.size(); i++) {
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
                break;
            case '(': 
                compiledProgram.push_back("loop" + std::to_string(loopLabel) + ":");
                compiledProgram.push_back("     dec ecx");
                loopLabel++;
                break;
            case ')':
                compiledProgram.push_back("     cmp ecx, 0");
                compiledProgram.push_back("     jne loop" + std::to_string(loopLabel-1));
                break;
            case '"':
                compiledProgram.push_back("     xchg ebx, ecx");
                break;
            case '%':
                compiledProgram.push_back("     cmp ebx, '" + std::to_string(program[i+1]) + "'");
                compiledProgram.push_back("     je jp_cx");
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
                break;
        }
    }
    for(int i = 0; i < compiledProgram.size(); i++) {
        output_file << compiledProgram[i] << endl;
        cout << compiledProgram[i] << endl;
    }
    output_file.close();
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
        if((string(argv[i])).find("-c") == 0) {
            filename = argv[i+1];
            source_file.open(filename);
        }
        if((string(argv[i])).find("-o") == 0) {
            filename = argv[i+1];
            output_file.open(filename);
        }
        if(string(argv[i]) == "-v") {
            cout << version << endl;
            cout << supportedArchitectures << endl;
        }
    }
    if (source_file.is_open() && output_file.is_open()) {
        compileX86();
        source_file.close();
        output_file.close();
    }
    return 0;
}