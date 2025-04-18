#include <fstream>
#include <sstream>
#include "tokenise.h++"
#include "parse.h++"
#include "registers.h++"


int main(void) {

    tokenise_init();
    register_init();


    string fileName = "./src/example.txt";
    ifstream file(fileName);

    if(file.is_open() == false) {
        cout << "Cannot open file" << endl;
        return 1;
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();

    if(parse_parse(text) == false) {
        cout << "Parser error" << endl;
        return 1;
    }


    cout << "Compilation complete" << endl;

    return 0;
}


