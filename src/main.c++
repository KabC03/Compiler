#include <fstream>
#include <sstream>
#include "tokenise.h++"
#include "parse.h++"

int main(void) {

    tokenise_init();
    string fileName = "./src/example.txt";
    ifstream file(fileName);

    if(file.is_open() == false) {
        cout << "Cannot open file" << endl;
        return 1;
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();


    Token token = tokenise_request(text);
    tokenise_print(token);


    //parse(text);

    return 0;
}


