#include "parse.h++"



//Parse fn statement
bool internal_parse_fn(string &text, unordered_set<string> &knownFunctions) {
    //fn name(int x, ptr y) {...}

    //Expect function name
    Token functionNameToken = tokenise_request(text);
    if(functionNameToken.tokenID != TOK_STRING_IMM) {
        cout << "ERROR: Function cannot have name: '" << functionNameToken.tokenString << "'" << endl;
        return false;
    } else if(knownFunctions.find(functionNameToken.tokenString) != knownFunctions.end()) {
        cout << "ERROR: Redeclaration of function: '" << functionNameToken.tokenString << "'" << endl;
        return false;
    } else {
        knownFunctions.insert(functionName);
    }


    //Expect open brace 
    Token openBraceToken = tokenise_request(text);
    if(openBraceToken.tokenID != TOK_BRACE_OPEN_PAREN) {
        cout << "ERROR: Expect open parenthesis preceding function arguments" << endl;
        return false;
    }


    //Expect arguments
    while(1) {

    }





    return true;
}

//Starting call
bool parse(string &text) {

    Token currentToken;
    currentToken.tokenID = TOK_INVALID;

    unordered_set<string> knownFunctions;


    while(1) {
        currentToken = tokenise_request(text);

        //Use if instead of switch - compiler will optimise it but it means I can break out of while loop
        if(currentToken.tokenID == TOK_EOF) {
            break;
        } else if(currentToken.tokenID == TOK_KEYWORD_FN) {
            //Function declaration    
            if(internal_parse_fn(text, knownFunctions) == false) {
                return false;
            }

        } else {
            cout << "Expected function declaration" << endl;
            return false;
        }
    }


    return true;
}












