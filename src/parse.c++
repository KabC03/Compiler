#include "parse.h++"
#define HERE cout << "HERE" << endl;
bool declaringFunction = false;
size_t stackIndex = 0;
string text = "";

//Get the datasize of a datatype
size_t internal_get_variable_stack_size(Token &type) {

    size_t size = 0;
    switch (type.tokenID) {
        case TOK_KEYWORD_INT: {
            size = SIZE_DATATYPE_INT;
            break;
        } case TOK_KEYWORD_FLOAT: {
            size = SIZE_DATATYPE_FLOAT;
            break;
        } case TOK_KEYWORD_CHAR: {
            size = SIZE_DATATYPE_CHAR;
            break;
        } case TOK_KEYWORD_PTR: {
            size = SIZE_DATATYPE_PTR;
            break;
        } default: {
            size = 0;
            break;
        }
    }
    return size;
}


//Parse an expression
bool internal_parse_expression(FunctionScope &functionScope) {

    return true;
}




//Declare a new variable in the given scope
bool internal_parse_let(FunctionScope &functionScope) {


    Variable newVariable;
    newVariable.inRegister = false;
    newVariable.addressIndex = stackIndex++;
    newVariable.registerIndex = -1;

    //Get the variable type
    Token variableType = tokenise_request(text);
    switch(variableType.tokenID) {
        case TOK_KEYWORD_INT: {
            newVariable.type = TOK_KEYWORD_INT;
            break;
        } case TOK_KEYWORD_FLOAT: {
            newVariable.type = TOK_KEYWORD_FLOAT;
            break;
        } case TOK_KEYWORD_CHAR: {
            newVariable.type = TOK_KEYWORD_CHAR;
            break;
        } default: {
            cout << "Invalid type specified " << variableType.tokenString << endl;
            return false;
        }
    }

    //Get the variable name
    Token newVariableName = tokenise_request(text);
    //Check variable name type
    if(newVariableName.tokenID != TOK_STRING_IMM) {
        cout << "Cannot declare variable " << newVariableName.tokenString << endl;
        return false;
    }
    //Check if variable exists
    auto it = functionScope.variableMap.find(newVariableName.tokenString);
    if(it != functionScope.variableMap.end()) {
        //Found
        cout << "Cannot redeclare variable " << newVariableName.tokenString << endl;
        return false;
    }

    //Expect an equals
    Token equals = tokenise_request(text);
    if(equals.tokenID != TOK_SYMBOL_ASSIGNMENT) {
        cout << "Expected equals in assignment" << endl;
        return false;
    }

    //Parse an expression
    if(internal_parse_expression(functionScope) == false) {
        return false;
    }

    functionScope.variableMap[newVariableName.tokenString] = newVariable;

    return true;
}



//Declare fn
bool internal_parse_fn(void) {

    if(declaringFunction == true) {
        cout << "Cannot declare a function inside a function" << endl;
        return false;
    }
    declaringFunction = true;

    Token token = tokenise_request(text);
    FunctionScope functionScope; //Establish a new scope


    //Initialise a new function
    internal_macro_fn_init();

    switch(token.tokenID) {

        case TOK_KEYWORD_LET: {
            //Declare a new variable
            if(internal_parse_let(functionScope) == false) {
                return false;
            }

        } case TOK_BRACE_CLOSE_CURLEY: {
            //Finished parsing the function
            internal_macro_fn_exit();
            break;
        } default: {
            cout << "Unexpected token " << token.tokenID << endl;
            return false;
            break;
        }

    }

    return true;
}


//Parse expressions - call other functions recursively
bool parse(string &line) {
    text = line; //Make the information global

    Token token = tokenise_request(text);

    //cout << token.tokenID << " " << TOK_KEYWORD_LET << endl;
    //cout << token.tokenString << " " << tokens[token.tokenID] << endl;

    while (token.tokenID != TOK_INVALID) { //Parse all functions until an EOF is encountered
        switch(token.tokenID) {

            case TOK_KEYWORD_FN: { //Function declaration
                if(internal_parse_fn() == false) {
                    return false;
                }
                break;
            } default: {
                cout << "Unrecognised token " << token.tokenID << endl;
                return false;
                break;
            }
        }
    }

    return true;
}






























