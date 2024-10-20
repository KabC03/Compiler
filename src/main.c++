#include "tokenise.h++"
#include "parse.h++"

int main(void) {

    unordered_map<string, TOKEN_ENUM> tokenMap = tokenise_init();

    string line = "let 0";

    parse(line, tokenMap);

    return 0;
}


