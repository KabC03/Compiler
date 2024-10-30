#include "parse.h++"

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


//Handle expressions
bool internal_handle_expression(string &line) {
    //E.g [x + 3 + y]
    //Wrap expression in []
    //Expect operand, operator, operand, operator 

    Token token = tokenise_request(line);
    // [ should already be consumed by caller

    bool expectOperand = true;
    while(token.tokenID != TOK_BRACE_CLOSE_SQUARE) {

        if(expectOperand == true) {
            //Number, variable or function call




        } else {
            //Arithmatic operators


        }

        expectOperand = !expectOperand;
    }


    return true;
}




//Parse expressions - call other functions recursively
bool parse(string &line) {
    //Automatically request tokens

    static size_t stackOffset = 0;
    unordered_map<string, Variable> knownVariables; //Managing known variables in scope
    stack<Label> labels; //For managing labels
    Token token = tokenise_request(line);

    //cout << token.tokenID << " " << TOK_KEYWORD_LET << endl;
    //cout << token.tokenString << " " << tokens[token.tokenID] << endl;
    switch(token.tokenID) {

        case TOK_KEYWORD_SET: {



            break;


        } default: {
            cout << "Unrecognised token " << token.tokenID << endl;
            return false;
            break;
        }
    }

    return true;
}






























