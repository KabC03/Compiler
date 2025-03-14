#include "parse.h++"


#define INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR(str, token) { \
    cout << "ERROR: " << str << ", '"; \
    tokenise_print(token); \
    cout << "'" << endl; \
    return false; \
}
#define INTERNAL_MACRO_ASSERT_TOKEN(token, exp) { \
    if(token.tokenID != exp) { \
        cout << "ERROR: Expected '"; \
        tokens[exp]; \
        cout << "' (" << exp << ") but found '"; \
        tokenise_print(token); \
        cout << "'" << endl; \
        return false; \
    } \
}

unordered_map<string, FunctionMetadata> knownFunctions;
bool mainIsDeclared = false;


//Call a function
bool internal_parse_call(string &text, FunctionMetadata &functionMetadata) {

    Token variableNameToken = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(variableNameToken, TOK_IDENTIFIER);
    INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Invalid variable name", variableNameToken);
    auto itV = functionMetadata.variableMap.find(variableNameToken.tokenString);
    if(itV == functionMetadata.variableMap.end()) {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Unrecognised variable", variableNameToken);
    }
    Token functionNameToken = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(functionNameToken, TOK_IDENTIFIER);
    //Push args to stack then call function
    auto itF = knownFunctions.find(functionNameToken.tokenString);
    if(itF == knownFunctions.end()) {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Unrecognised function", functionNameToken);
    }

    //Push args to stack
    Token currentToken = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(functionNameToken, TOK_BRACE_OPEN_PAREN);
    for(size_t argCount = 0; currentToken.tokenID != TOK_BRACE_CLOSE_PAREN; argCount++) {
        auto itV2 = functionMetadata.variableMap.find(variableNameToken.tokenString);
        if(itV2 == functionMetadata.variableMap.end()) {
            INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Unrecognised variable", variableNameToken);
        }
        ARCH_PUSH_STACK(register_load_variable(itV2->second, functionMetadata), -functionMetadata.argMap[argCount]->stackOffset); //Push to stack at address
        cout << "REMOVE THIS MESSAGE, it just stops the compiler complaining" << argCount << endl;
        currentToken = tokenise_request(text);
        INTERNAL_MACRO_ASSERT_TOKEN(functionNameToken, TOK_SYMBOL_COMMA);
    }

    INTERNAL_MACRO_ASSERT_TOKEN(functionNameToken, TOK_BRACE_CLOSE_PAREN);
    ARCH_CALL(functionNameToken.tokenString);
    //Bind register to variable
    itV->second.isUpdated = false;
    register_bind_variable(itV->second, ARCH_RETURN_REGISTER_NUMBER);

    return true;
}

//Update a variable
bool internal_parse_set(string &text, FunctionMetadata &functionMetadata) {

    Token variableNameToken = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(variableNameToken, TOK_IDENTIFIER);
    INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Invalid variable name", variableNameToken);
    auto itV = functionMetadata.variableMap.find(variableNameToken.tokenString);
    if(itV == functionMetadata.variableMap.end()) {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Unrecognised variable", variableNameToken);
    }
    tuple<bool, size_t> expressionResult = expression_handling_lr_evaluation(text, functionMetadata);
    if(get<0>(expressionResult) == false) {
        return false;
    }
    //Bind register to variable
    itV->second.isUpdated = false;
    register_bind_variable(itV->second, get<1>(expressionResult));

    return true;
}

//Goto a label
bool internal_parse_goto(string &text, FunctionMetadata &functionMetadata) {

    Token labelNameToken = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(labelNameToken, TOK_IDENTIFIER);
    INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Invalid label name", labelNameToken);
    auto itL = functionMetadata.knownLabels.find(labelNameToken.tokenString);
    if(itL == functionMetadata.knownLabels.end()) {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Unrecognised label", labelNameToken);
    }
    ARCH_GOTO(labelNameToken.tokenString);

    return true;
}

//Declare a label
bool internal_parse_label(string &text, FunctionMetadata &functionMetadata) {

    Token labelNameToken = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(labelNameToken, TOK_IDENTIFIER);
    INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Invalid label name", labelNameToken);
    auto itL = functionMetadata.knownLabels.find(labelNameToken.tokenString);
    if(itL != functionMetadata.knownLabels.end()) {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Redeclaration of label", labelNameToken);
    }
    functionMetadata.knownLabels.insert(labelNameToken.tokenString);
    ARCH_LABEL(labelNameToken.tokenString);

    return true;
}

//Declare a variable
bool internal_declare_variables(string &text, FunctionMetadata &FunctionMetadata, bool declaringLocalVars) {
    //[int x = 10, int y = 0, reg float y = 0];

    Token currentToken = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(currentToken, TOK_BRACE_OPEN_SQUARE);
    long int stackTop = 0;
    vector<VariableMetadata*> variableStackVector;
    currentToken = tokenise_request(text);
    size_t argCount = 0;
    while(currentToken.tokenID != TOK_BRACE_CLOSE_SQUARE) {

        VariableMetadata newVariable;
        if(currentToken.tokenID == TOK_KEYWORD_INT) {
            newVariable.dataType = TOK_TYPE_INT;
        } else if(currentToken.tokenID == TOK_KEYWORD_FLOAT) {
            newVariable.dataType = TOK_TYPE_FLOAT;
        } else if(currentToken.tokenID == TOK_KEYWORD_PTR) {
            newVariable.dataType = TOK_TYPE_PTR;
        } else {
            INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Invalid variable type", currentToken);
        }
        newVariable.isUpdated = false;
        newVariable.timesUsed = 0;
        Token variableNameToken = tokenise_request(text);
        auto itV = FunctionMetadata.variableMap.find(variableNameToken.tokenString);
        if(itV != FunctionMetadata.variableMap.end()) {
            INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Redeclaration of variable", variableNameToken);
        }
        FunctionMetadata.variableMap[variableNameToken.tokenString] = newVariable;
        variableStackVector.push_back(&FunctionMetadata.variableMap[variableNameToken.tokenString]);
        currentToken = tokenise_request(text);
        if(currentToken.tokenID == TOK_BRACE_CLOSE_SQUARE) {
            return true;
        }
        INTERNAL_MACRO_ASSERT_TOKEN(currentToken, TOK_SYMBOL_COMMA);
        currentToken = tokenise_request(text);
        FunctionMetadata.argMap[argCount] = &FunctionMetadata.variableMap[variableNameToken.tokenString];
        argCount++;
    }
    //Stack variables efficiently by sorting the vector then writing stack addresses
    std::sort(variableStackVector.begin(), variableStackVector.end(), [](const VariableMetadata* lhs, const VariableMetadata* rhs) {
        return architecture_get_datatype_size(lhs->dataType) < architecture_get_datatype_size(rhs->dataType);
    });
    for(size_t i = 0; i < variableStackVector.size(); i++) { //Update stack offset in variable map
        if(declaringLocalVars == true) {
            stackTop += architecture_get_datatype_size(variableStackVector[i]->dataType) % stackTop; //Pad the stack pointer
        } else {
            stackTop -= architecture_get_datatype_size(variableStackVector[i]->dataType) % stackTop; //Pad the stack pointer
        }
        variableStackVector[i]->stackOffset = stackTop; //Store the stack offset
    }
    return true;
}



bool internal_parse_function_declaration(string &text) {
    //fn int foo[reg int arg1, int arg2]
    FunctionMetadata newFunction;
    //Expect return type
    Token currentToken = tokenise_request(text);
    if(currentToken.tokenID == TOK_KEYWORD_INT) {
        newFunction.returnType = TOK_TYPE_INT;
    } else if(currentToken.tokenID == TOK_KEYWORD_FLOAT) {
        newFunction.returnType = TOK_TYPE_FLOAT;
    } else if(currentToken.tokenID == TOK_KEYWORD_PTR) {
        newFunction.returnType = TOK_TYPE_PTR;
    } else {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Invalid function return type", currentToken);
    }

    //Function name
    Token functionNameToken = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(functionNameToken, TOK_IDENTIFIER);
    auto itF = knownFunctions.find(functionNameToken.tokenString);
    if(itF != knownFunctions.end()) {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Redeclaration of function", functionNameToken);
    }
    internal_declare_variables(text, newFunction, true); //Arguments
    internal_declare_variables(text, newFunction, false); //Local variables

    currentToken = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(currentToken, TOK_BRACE_OPEN_CURLEY);
    currentToken = tokenise_request(text);
    if(currentToken.tokenID == TOK_KEYWORD_IF) {
        //if(x == 1) {...}
    } else if(currentToken.tokenID == TOK_KEYWORD_WHILE) {
        //while(x == 1) {...}
    } else if(currentToken.tokenID == TOK_KEYWORD_CALL) {
        //call foo[x,y,z];
    } else if(currentToken.tokenID == TOK_KEYWORD_SET) {
        //set x = &[x + 1];
        if(internal_parse_set(text, newFunction) == false) {
            return false;
        }
    } else if(currentToken.tokenID == TOK_KEYWORD_GOTO) {
        //goto label;
        if(internal_parse_goto(text, newFunction) == false) {
            return false;
        }
    } else if(currentToken.tokenID == TOK_KEYWORD_LABEL) {
        //label something;
        if(internal_parse_label(text, newFunction) == false) {
            return false;
        }
    }
    currentToken = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(currentToken, TOK_BRACE_CLOSE_CURLEY);
    knownFunctions[functionNameToken.tokenString] = newFunction;
    return true;
}



void parse_init(void) {
    return;
}


bool parse_parse(string &text) {

    Token startToken = tokenise_request(text);
    if(startToken.tokenID == TOK_KEYWORD_FN) {
        if(internal_parse_function_declaration(text) == false) {
            return false;
        }

    } else if(startToken.tokenID == TOK_EOF && mainIsDeclared == true) {
        return true;

    } else {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Expect function declaration", startToken);
    }

    return true;
}








