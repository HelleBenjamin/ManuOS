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

vector<string> program; // source program
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
    string line;
    while(getline(source_file, line)) {
        program.push_back(line);
    }
    for(int i = 0; i < program.size(); i++) {
        switch (program[i][0]) {
            case 
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
        }
        if((string(argv[i])).find("-o") == 0) {
            filename = argv[i+1];
            output_file.open(filename);
        }
        if(string(argv[i]) == "-v") {
            cout << version << endl;
            cout << supportedArchitectures << endl;
        }
        if(string(argv[i]) == "-BIN") {
            format = 0;
        }
        if(string(argv[i]) == "-HEX") {
            format = 1;
        }
    }
    if (source_file.is_open() && output_file.is_open()) {
        p4();
        source_file.close();
        output_file.close();
    }
    return 0;
}