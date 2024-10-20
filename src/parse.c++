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



//Variable declaration
bool internal_parse_let(size_t stackOffset, string &line, unordered_map<string, TOKEN_ENUM> &tokenMap,
    unordered_map<string, Variable> &knownVariables) {
    //let char@ result = 0;
    //Check if variable is already defined

    StructureLet structure;
    Token token = tokenise_request(line, tokenMap);
    if(token.tokenID == TOK_INVALID) return false;
    structure.variable.type = token;
    //Grab variable name
    token = tokenise_request(line, tokenMap);
    if(token.tokenID == TOK_INVALID) return false;
    structure.variable.name = token.tokenString;
    structure.variable.stackOffset = stackOffset;
    stackOffset += internal_get_variable_stack_size(structure.variable.type);
    //Convert to RPN

    return true;
}







//Parse expressions - call other functions recursively
bool parse(string &line, unordered_map<string, TOKEN_ENUM> &tokenMap) {
    //Automatically request tokens

    static size_t stackOffset = 0;
    unordered_map<string, Variable> knownVariables; //Managing known variables in scope
    stack<Label> labels; //For managing labels
    Token token = tokenise_request(line, tokenMap);

    //cout << token.tokenID << " " << TOK_KEYWORD_LET << endl;
    //cout << token.tokenString << " " << tokens[token.tokenID] << endl;
    switch(token.tokenID) {

        case TOK_KEYWORD_LET: {
            return internal_parse_let(stackOffset, line, tokenMap, knownVariables);
            break;


        } default: {
            cout << "Unrecognised token " << token.tokenID << endl;
            return false;
            break;
        }
    }

    return true;
}






























