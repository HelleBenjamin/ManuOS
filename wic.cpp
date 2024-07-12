#include <iostream> // include all the necessary libraries
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>

#define helpMessage "-c <source file> -o <output file> -h help -v version -MODE=<mode>"
#define supportedArchitectures "Supported architectures: X86"
#define version "Wuf++ Interpreter Compiler v0.1"

using namespace std;

vector<char> program; // source program



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
                break;
            case ')':
                if (cx != 0) {
                    pc = dx;
                    cx--;
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