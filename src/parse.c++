#include "parse.h++"



//Variable declaration
bool internal_parse_let(string &line, unordered_map<string, TOKEN_ENUM> &tokenMap,
    unordered_map<string, Variable> &knownVariables) {
    //let char@ result = 0;
    //Check if variable is already defined
    //Call RPN parser to convert line expression to RPN

    cout << "HERE" << endl;



    return true;
}







//Parse expressions - call other functions recursively
bool parse(string &line, unordered_map<string, TOKEN_ENUM> &tokenMap) {
    //Automatically request tokens

    unordered_map<string, Variable> knownVariables; //Managing known variables in scope
    stack<Label> labels; //For managing labels


    Token token = tokenise_request(line, tokenMap);

    cout << token.tokenID << " " << TOK_KEYWORD_LET << endl;
    switch(token.tokenID) {

        case TOK_KEYWORD_LET: {
            return internal_parse_let(line, tokenMap, knownVariables);
            break;


        } default: {
            cout << "Unrecognised token " << token.tokenID << endl;
            return false;
            break;
        }
    }

    return true;
}






























