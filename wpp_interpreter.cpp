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


/* Wuf++ interpreter

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
    & - jump to location pointed by pointer
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
    %[char] - compare main register with char, jump if equal to location pointed by pointer
    = - halt
*/

string filename;
ifstream source_file;

uint8_t bl = 0;
uint16_t cx = 0;
unsigned int pc = 0;
uint8_t stack[1000] = {0};
unsigned int sp = 1000;
bool halt = false;

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
    for(pc = 0; pc < program.size(); pc++) {
        if(halt) break;
        switch (program[pc]) {
            case '+':
                bl++;
                break;
            case '-':
                bl--;
                break;
            case '>':
                sp--;
                stack[sp] = bl;
                break;
            case '<':
                bl = stack[sp];
                sp++;
                break;
            case '.':
                cout << char(bl);
                break;
            case ',':
                cin >> bl;
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
                bl = ~bl;
                break;
            case '}':
                cx++;
                break;
            case '{':
                cx--;
                break;
            case '$':
                cout << dectohex(cx) << endl;
                break;
            case '#':
                bl = program[pc+1];
                pc++;
                break;
            case '(': 
                sp--;
                stack[sp] = pc & 0xFF;
                sp--;
                stack[sp] = pc >> 8;
                break;
            case ')':
                if (cx != 0) {
                    pc = (stack[sp] << 8) | stack[sp+1];
                    sp += 2;
                    cx--;
                } if (cx == 0) {
                    sp += 2;
                    break;
                }
                break;
            case '"':
                sp--;
                stack[sp] = bl;
                bl = (cx & 0xFF);
                cx = (cx >> 8) | stack[sp];
                sp++;
                break;
            case '%':
                if (bl == program[pc+1]) {
                    pc = cx;
                }
                break;
            case '=':
                halt = true;
                break;
            default:
                break;
        }
    }
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
            Interpreter();
        }
        if(string(argv[i]) == "-v") {
            cout << version << endl;
            cout << supportedArchitectures << endl;
        }
    }
    return 0;
}