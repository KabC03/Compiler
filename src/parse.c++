#include "parse.h++"
#define HERE cout << "HERE" << endl;

#define INTERNAL_MACRO_EXPECT_TOKEN(tok)\
    { Token token = tokenise_request(text);\
    if(token.tokenID != tok) {\
        cout << "Expected " << token.tokenID << endl;\
        return false;\
    }}

//TODO: Bit rough around the edges, better errors, make sure var name cannot duplicate a function



bool declaringFunction = false;
size_t stackIndex = 0;
string text = "";
unordered_set<string> knownFunctions; //Known functions, used for function call in asm


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









//Declare fn
bool internal_parse_fn(void) {
    //fn int foo(int x, char y) {...}
    if(declaringFunction == true) {
        cout << "Cannot declare a function inside a function" << endl;
        return false;
    }
    declaringFunction = true;
    FunctionScope functionScope; //Establish a new scope

    //Initialise a new function
    internal_macro_fn_init();

    //Return type
    Token token = tokenise_request(text);
    if(token.tokenID != TOK_KEYWORD_INT 
            && token.tokenID != TOK_KEYWORD_FLOAT 
            && token.tokenID != TOK_KEYWORD_CHAR 
            && token.tokenID != TOK_KEYWORD_PTR) {
    
        cout << "Unrecognised function return type " << token.tokenID << endl;
        return false;
    } else {
        functionScope.returnType = token.tokenID;        
    }
    //Function name
    token = tokenise_request(text);
    //Check for redeclaration and if not there then add to known functions 
    if(knownFunctions.find(token.tokenString) != knownFunctions.end()) {
        cout << "Redeclaration of function" << endl; 
        return false;
    } else { //Insert into set
        knownFunctions.insert(text);
    }
    //Expect opening brace
    INTERNAL_MACRO_EXPECT_TOKEN(TOK_BRACE_OPEN_PAREN);
    //Input parameters

    bool expectName = false;
    while(token.tokenID != TOK_BRACE_CLOSE_PAREN) {
        //Expecting type name, type name, type name until a )
        //Each variable should have an associated stack offset
        Variable newVariable;
        string newVariableName = "";

        if(expectName == true) {
            newVariableName = tokenise_request(text);     
        } else { //Declare variable type
            if(token.tokenID != TOK_KEYWORD_INT 
                    && token.tokenID != TOK_KEYWORD_FLOAT 
                    && token.tokenID != TOK_KEYWORD_CHAR 
                    && token.tokenID != TOK_KEYWORD_PTR) {
            
                cout << "Unrecognised function return type " << token.tokenID << endl;
                return false;
            } else {
                newVariable.type = token.tokenID;
            }
        }

        functionScope.variableMap[newVariableName] = newVariable;

        INTERNAL_MACRO_EXPECT_TOKEN(TOK_SYMBOL_COMMA);
        token = tokenise_request(text);
        expectName = !expectName;
    }
    
    //Expect {
    INTERNAL_MACRO_EXPECT_TOKEN(TOK_BRACE_OPEN_CURLEY);

    //Loop until a } is found 
    token = tokenise_request(text);
    while(token.tokenID != TOK_BRACE_CLOSE_CURLEY) {
        switch(token.tokenID) {

            case TOK_KEYWORD_INT: {
                break;
            } case TOK_KEYWORD_FLOAT: {
                break;
            } case TOK_KEYWORD_CHAR: {
                break;
            } case TOK_KEYWORD_PTR: {
                break;
            } case TOK_KEYWORD_IF: { //This function should also handle elif/else
                break;
            } case TOK_KEYWORD_WHILE: { 
                break;
            } case TOK_KEYWORD_FOR: {
                break;
            } case TOK_KEYWORD_RETURN: {
                break;

            } default: {

                //Check variable map and function map then call assignment functions here

                if(knownFunctions.find(token.tokenString) != knownFunctions.end()) {
                    //Call function call
                } else if(functionScope.variableMap.find(token.tokenString) != functionScope.variableMap.end()) { 
                    //Call variable assignment
                } else {
                    //Unrecognised
                    cout << "Unrecognised operation" << endl;
                    return false;
                }
            }
        }
        token = tokenise_request(text);
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
                declaringFunction = false;
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






























