#include "parse.h++"
//NOTE: AS OF NOW, VARIABLES ARE NOT ALIGNED, SHOULD IMPLEMENT A STACKING ALGORITHM TO ENSURE ALIGNMENT
unordered_map<string, FunctionMetadata> knownFunctions;
bool mainDeclared = false;


bool internal_declare_variable(string &text, Token currentToken, TOKEN_ENUM terminalToken, FunctionMetadata &functionMetadata) {
    while(currentToken.tokenID != terminalToken) {
        VariableMetadata currentVariable; //Datatype of variable
        currentVariable.dataType = currentToken.tokenID;
        currentVariable.timesUsed = 0;
        if(currentToken.tokenID == TOK_KEYWORD_INT) {
            currentVariable.stackOffset = (functionMetadata.stackTop += PARSE_SIZE_DATATYPE_INT);
        } else if(currentToken.tokenID == TOK_KEYWORD_FLOAT) {
            currentVariable.stackOffset = (functionMetadata.stackTop += PARSE_SIZE_DATATYPE_FLOAT);
        } else {
            cout << "ERROR: Invalid type for argument" << endl;
            return false;
        }
        currentToken = tokenise_request(text); //Name of variable
        auto itF = knownFunctions.find(currentToken.tokenString);
        auto itV = functionMetadata.variableMap.find(currentToken.tokenString);
        if(itF != knownFunctions.end()) {
            cout << "ERROR: Clash of variable name with function name" << endl;
            return false;
        } else if(itV != functionMetadata.variableMap.end()) {
            cout << "ERROR: Clash of variable name with variable name" << endl;
            return false;
        }
        functionMetadata.variableMap[currentToken.tokenString] = currentVariable;
        currentToken = tokenise_request(text); //Expect a comma to seperate types
        if(currentToken.tokenID == TOK_SYMBOL_COMMA) {
        } else if(currentToken.tokenID == terminalToken) {
            return true;
        } else {
            return false;
        }
        currentToken = tokenise_request(text);
    }
    return true;
}



bool internal_parse_function_declaration(string &text) {
    //fn int foo(int x, float y) [vars] {logic}
    FunctionMetadata functionMetadata;
    functionMetadata.stackTop = 0;

    Token currentToken = tokenise_request(text); //Expect a data type
    if(currentToken.tokenID != TOK_KEYWORD_INT && currentToken.tokenID != TOK_KEYWORD_FLOAT) {
        cout << "ERROR: Invalid datatype for function return" << endl;
        return false;
    }
    functionMetadata.returnType = currentToken.tokenID;

    currentToken = tokenise_request(text); //Expect function name and check it doesnt clash with a variable name or function name
    if(currentToken.tokenID != TOK_IDENTIFIER) {
        cout << "ERROR: Invalid function name" << endl;
        return false;
    }
    auto itF = knownFunctions.find(currentToken.tokenString);
    if(itF != knownFunctions.end()) {
        cout << "ERROR: Redeclaration of function" << endl;
        return false;
    }
    string functionName = currentToken.tokenString;

    currentToken = tokenise_request(text); //Expect a '('
    if(currentToken.tokenID != TOK_BRACE_OPEN_PAREN) {
        cout << "ERROR: Expect opening brace" << endl;
        return false;
    }
    currentToken = tokenise_request(text); //Handle args
    if(internal_declare_variable(text, currentToken, TOK_BRACE_CLOSE_PAREN, functionMetadata) == false) {
        return false;
    }

    currentToken = tokenise_request(text); //Expect a '['
    if(currentToken.tokenID != TOK_BRACE_OPEN_SQUARE) {
        cout << "ERROR: Expect opening brace" << endl;
        return false;
    }
    currentToken = tokenise_request(text); //Handle variable declarations
    if(internal_declare_variable(text, currentToken, TOK_BRACE_CLOSE_SQUARE, functionMetadata) == false) {
        return false;
    }

    currentToken = tokenise_request(text); //Expect a '{'
    if(currentToken.tokenID != TOK_BRACE_OPEN_CURLEY) {
        cout << "ERROR: Expect opening brace" << endl;
        return false;
    }
    while(currentToken.tokenID != TOK_BRACE_CLOSE_CURLEY) {
        if(currentToken.tokenID == TOK_KEYWORD_IF) { //elif/else should be also handled by this function
            //TODO: IMPLEMENT
        } else if(currentToken.tokenID == TOK_KEYWORD_WHILE) {
            //TODO: IMPLEMENT
        } else if(currentToken.tokenID == TOK_KEYWORD_CALL) {
            //TODO: IMPLEMENT
        } else if(currentToken.tokenID == TOK_KEYWORD_INT || currentToken.tokenID == TOK_KEYWORD_FLOAT) {
            //TODO: IMPLEMENT
        } else if(currentToken.tokenID == TOK_KEYWORD_RETURN) {
            //TODO: IMPLEMENT
        } else {
            cout << "ERROR: Invalid instruction" << endl;
            return false;
        }
    }

    knownFunctions[functionName] = functionMetadata;     //Add functions to known functions

    return true;
}



void parse_init(void) {
    //Nothing here so far
    return;
}


bool parse_parse(string &text) {

    Token startToken = tokenise_request(text);

    if(startToken.tokenID == TOK_KEYWORD_FN) {
        if(internal_parse_function_declaration(text) == false) {
            return false;
        }

    } else if(startToken.tokenID == TOK_EOF && mainDeclared == true) {
        return true;

    } else {
        cout << "ERROR: Expect function declaration" << endl;
        return false;
    }

    return true;
}








