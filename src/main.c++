#include "tokenise.h++"

int main(void) {

    unordered_map<string, TOKEN_ENUM> tokenMap;
    tokenise_init(tokenMap);

    Token token;


    string line = "++--x";
    tokenise_request(token, line, tokenMap);


    cout << "New: \n\n" << endl;
    tokenise_request(token, line, tokenMap);

    cout << "\n\nTOKEN:" << endl;
    cout << tokens[token.tokenID] << endl;
    cout << token.tokenString << endl;
    cout << token.tokenID << endl;

    return 0;
}


