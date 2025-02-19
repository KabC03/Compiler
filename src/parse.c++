#include "parse.h++"



//Parse fn statement
bool internal_parse_fn(string &text, unordered_map<string, TOKEN_ENUM> &knownFunctions, TOKEN_ENUM functionReturnType) {
    //int name(int x, ptr y) {...}

    //NOTE: Passing functionReturnType from caller since name is not known then
    //Combine the two pieces of the puzzle

    //Expect function name
    Token functionNameToken = tokenise_request(text);
    if(functionNameToken.tokenID != TOK_IDENTIFIER) {
        cout << "ERROR: Function cannot have name: '" << functionNameToken.tokenString << "'" << endl;
        return false;
    } else if(knownFunctions.find(functionNameToken.tokenString) != knownFunctions.end()) {
        cout << "ERROR: Redeclaration of function: '" << functionNameToken.tokenString << "'" << endl;
        return false;
    } else {
        knownFunctions[functionNameToken.tokenString] = functionReturnType;
    }


    //Expect open brace 
    Token openBraceToken = tokenise_request(text);
    if(openBraceToken.tokenID != TOK_BRACE_OPEN_PAREN) {
        cout << "ERROR: Expect open parenthesis preceding function arguments" << endl;
        return false;
    }


    //Expect arguments
    FunctionMetadata functionMetadata;
    functionMetadata.stackTop = ARCH_WORD_SIZE; //Below this is the return address
    bool declaringFnArgs = true;
    while(declaringFnArgs == true) {
        //Expect type - name - comma || close paren
        Token variableTypeToken = tokenise_request(text);
        Token variableNameToken = tokenise_request(text);
        VariableMetadata newVariable;


        if(variableNameToken.tokenID != TOK_IDENTIFIER) {
            cout << "ERROR: Invalid variable name" << endl;
            return false;
        }
        //Check variable name does not clash
        if(knownFunctions.find(variableNameToken.tokenString) != knownFunctions.end()) {
            cout << "ERROR: Variable name clashes with function: '" << functionNameToken.tokenString << "'" << endl;
            return false;
        } else if(functionMetadata.variableMap.find(variableNameToken.tokenString) != functionMetadata.variableMap.end()) {
            cout << "ERROR: Variable name clash for : '" << variableNameToken.tokenString << "'" << endl;
            return false;
        } 

        if(variableTypeToken.tokenID != TOK_KEYWORD_INT && 
           variableTypeToken.tokenID != TOK_KEYWORD_FLOAT &&
           variableTypeToken.tokenID != TOK_KEYWORD_CHAR &&
           variableTypeToken.tokenID != TOK_KEYWORD_PTR ) {

            cout << "ERROR: Unrecognised datatype for variable: '" << variableNameToken.tokenString << "'" << endl;
            return false;
        } else {
            newVariable.dataType = variableTypeToken.tokenID;
        }
        
        newVariable.name = variableNameToken.tokenString;
        newVariable.stackOffset = functionMetadata.stackTop+=4;
        newVariable.timesUsed = 0;
        functionMetadata.variableMap[variableNameToken.tokenString] = newVariable;


        //Expect a comma or brace
        Token argumentSeperator = tokenise_request(text); 
        if(argumentSeperator.tokenID == TOK_BRACE_CLOSE_PAREN) {
            declaringFnArgs = false;
        } else if(argumentSeperator.tokenID == TOK_SYMBOL_COMMA) {
            declaringFnArgs = true;
        } else {
            cout << "ERROR: Invalid function argument seperator" << endl;
        }
    }


    //Expect a open curley brace
    Token openCurleyToken = tokenise_request(text);
    if(openCurleyToken.tokenID != TOK_BRACE_OPEN_CURLEY) {
        cout << "ERROR: Expect open curley parenthesis preceding function body" << endl;
        return false;
    }

    //UP TO HERE - GO THROUGH INT, FLOAT, FOR, WHILE, RECURSIVELY HERE
    Token instructionToken = tokenise_request(text);
    if(instructionToken.tokenID == TOK_KEYWORD_INT) {

    } else if(instructionToken.tokenID == TOK_KEYWORD_FLOAT 
            || instructionToken.tokenID == TOK_KEYWORD_CHAR 
            || instructionToken.tokenID == TOK_KEYWORD_CHAR 
            || instructionToken.tokenID == TOK_KEYWORD_PTR) {
    //Variable declarations

    } else if(instructionToken.tokenID == TOK_KEYWORD_WHILE) {

    } else if(instructionToken.tokenID == TOK_KEYWORD_IF) {

    } else if(instructionToken.tokenID == TOK_KEYWORD_ELIF) {

    } else if(instructionToken.tokenID == TOK_KEYWORD_ELSE) {

    } else if(instructionToken.tokenID == TOK_IDENTIFIER) { //Function calls and variable renaming
        //Check if its a variable or a function
        if(knownFunctions.find(instructionToken.tokenString) != knownFunctions.end()) {
            //Call function call function (not recursion is allowed)

        } else if(functionMetadata.variableMap.find(instructionToken.tokenString) != functionMetadata.variableMap.end()) {
            //Call variable redeclaration function

        } else {
            cout << "ERROR: Unrecognised identifier: " << instructionToken.tokenString << endl;
            return false;
        }
    } else {
        cout << "ERROR: Expect valid instruction" << endl;
        return false;
    }

    //Expect a close curley brace
    Token closeCurleyToken = tokenise_request(text);
    if(closeCurleyToken.tokenID != TOK_BRACE_CLOSE_CURLEY) {
        cout << "ERROR: Expect closing curley parenthesis succeeding function body" << endl;
        return false;
    }

    return true;
}

//Starting call
bool parse(string &text) {

    Token currentToken;
    currentToken.tokenID = TOK_INVALID;

    unordered_map<string, TOKEN_ENUM> knownFunctions; //Name -> return type


    while(1) {
        currentToken = tokenise_request(text);

        //Use if instead of switch - compiler will optimise it but it means I can break out of while loop
        if(currentToken.tokenID == TOK_EOF) {
            break;
        } else if(currentToken.tokenID == TOK_KEYWORD_INT ||
                  currentToken.tokenID == TOK_KEYWORD_FLOAT ||
                  currentToken.tokenID == TOK_KEYWORD_CHAR ||
                  currentToken.tokenID == TOK_KEYWORD_PTR) {
            //Function declaration    
            if(internal_parse_fn(text, knownFunctions, currentToken.tokenID) == false) {
                return false;
            }

        } else {
            cout << "Expected function declaration" << endl;
            return false;
        }
    }


    return true;
}












