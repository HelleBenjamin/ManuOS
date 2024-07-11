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

    bl - main register
    cx - pointer

Syntax:
    + - increment main register
    - - decrement main register
    > - push main register
    < - pop main register
    . - print main register
    , - read to the main register
    [ - pc = pc - cx
    ] - pc = pc + cx
    ! - invert main register
    } - increment pointer
    { - decrement pointer
    $ - print pointer
    #[char] - load char to the main register
    ( - loop start, decrement pointer and loop until pointer = 0
    ) - loop end
    " - swap registers
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
    while(source_file.get(c)) {
        program.push_back(c);
    }

    compiledProgram.push_back("global _start");
    compiledProgram.push_back(";wpp v0.1");
    compiledProgram.push_back("section .text");
    compiledProgram.push_back("_start:");
    compiledProgram.push_back("mov ecx, 0");
    compiledProgram.push_back("mov ebx, 0");
    for(int i = 0; i < program.size(); i++) {
        switch (program[i]) {
            case '+':
                compiledProgram.push_back("inc ebx");
                break;
            case '-':
                compiledProgram.push_back("dec ebx");
                break;
            case '>':
                compiledProgram.push_back("push ebx");
                break;
            case '<':
                compiledProgram.push_back("pop ebx");
                break;
            case '.':
                compiledProgram.push_back("mov ecx, bl");
                compiledProgram.push_back("mov eax, 4");
                compiledProgram.push_back("mov ebx, 1");
                compiledProgram.push_back("mov edx, 1");
                compiledProgram.push_back("int 80h");
                break;
            case ',':
                compiledProgram.push_back("mov ah, 1");
                compiledProgram.push_back("int 21h");
                break;
            case '[':
                compiledProgram.push_back("sub pc, ecx");
                break;
            case ']':
                compiledProgram.push_back("add pc, ecx");
                break;
            case '!':
                compiledProgram.push_back("not ebx");
                break;
            case '}':
                compiledProgram.push_back("inc ecx");
                break;
            case '{':
                compiledProgram.push_back("dec ecx");
                break;
            case '$':
                compiledProgram.push_back("mov ecx, cx");
                compiledProgram.push_back("mov eax, 4");
                compiledProgram.push_back("mov ebx, 1");
                compiledProgram.push_back("mov edx, 1");
                compiledProgram.push_back("int 80h");
                break;
            case '#':
                compiledProgram.push_back("mov ebx, '" + std::string(1, program[i+1]) + "'");
                break;
            case '(': 
                compiledProgram.push_back("loop:");
                compiledProgram.push_back("dec ecx");
                break;
            case ')':
                compiledProgram.push_back("cmp ecx, 0");
                compiledProgram.push_back("jne loop");
                break;
            case '"':
                compiledProgram.push_back("xchg ebx, ecx");
                break;
            default:
                break;
        }
    }
    compiledProgram.push_back("mov eax, 1");
    compiledProgram.push_back("mov ebx, 0");
    compiledProgram.push_back("int 80h");
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