#include "tokenise.h++"
#include "parse.h++"

int main(void) {

    tokenise_init();

    string line = "let 0";

    parse(line);

    return 0;
}


