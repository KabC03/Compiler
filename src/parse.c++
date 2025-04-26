#include "parse.h++"

unordered_map<string, FunctionMetadata> knownFunctions;
bool mainIsDeclared = false;
bool internal_parse_call(string &text, FunctionMetadata &functionMetadata);
bool internal_parse_goto(string &text, FunctionMetadata &functionMetadata);
bool internal_parse_if(string &text, FunctionMetadata &functionMetadata);
bool internal_parse_assignment(string &text, FunctionMetadata &functionMetadata);
bool internal_parse_label_declaration(string &text, FunctionMetadata &functionMetadata);
bool internal_parse_while(string &text, FunctionMetadata &functionMetadata);
bool internal_parse_function_declaration(string &text);
bool internal_declare_variables(string &text, unordered_map<string, VariableMetadata> mapToAppend, unordered_map<string, VariableMetadata> mapWithClash);
bool internal_helper_call_parser_function(string &text, Token &token, FunctionMetadata &functionMetadata);



/* INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR(str, token)
 * @brief :: Print an unexpected token
 *
 * @param :: string &text :: Source code text
 *
 */
#define INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR(str, token) { \
    cout << "ERROR: " << str << ", but found '"; \
    tokenise_print(token); \
    cout << "'" << endl; \
}


/* INTERNAL_MACRO_ASSERT_TOKEN(token, exp)
 * @brief :: Assert the presence of a token, if not present print an error
 *
 * @param :: token :: Token encountered
 * @param :: exp :: Expected token
 *
 */
#define INTERNAL_MACRO_ASSERT_TOKEN(token, exp) { \
    if(token.tokenID != exp) { \
        cout << "ERROR: Expected '"; \
        tokens[exp]; \
        cout << "' (" << exp << ") but found '"; \
        tokenise_print(token); \
        cout << "'" << endl; \
    } \
}

/* INTERNAL_MACRO_IS_IN_MAP(item, map)
 * @brief :: Assess the presence of an item in an unordered_map
 *
 * @param :: item :: Item expected
 * @param :: map :: Map to search
 *
 */
#define INTERNAL_MACRO_IS_IN_MAP(item, map) \
    ((map.find(item) == map.end()) ? false : true) \





//Call the relevent parser function from a token
bool internal_helper_call_parser_function(string &text, Token &token, FunctionMetadata &functionMetadata) {
    switch(token.tokenID) {
        case TOK_KEYWORD_CALL: {
            return internal_parse_call(text, functionMetadata);
            break;
        } case TOK_KEYWORD_GOTO: {
            return internal_parse_goto(text, functionMetadata);
            break;
        } case TOK_KEYWORD_IF: {
            return internal_parse_if(text, functionMetadata);
            break;
        } case TOK_KEYWORD_INT: {
            return internal_parse_assignment(text, functionMetadata);
            break;
        } case TOK_KEYWORD_LABEL: {
            return internal_parse_label_declaration(text, functionMetadata);
            break;
        } case TOK_KEYWORD_RETURN: {
            return internal_parse_assignment(text, functionMetadata);
            break;
        } case TOK_KEYWORD_WHILE: {
            return internal_parse_while(text, functionMetadata);
            break;
        } default: {
            INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Unrecognised instruction", token);
            return false;
            break;
        }
    }
    return true;
}

//Declare a variable
bool internal_declare_variables(string &text, unordered_map<string, VariableMetadata> mapToAppend, unordered_map<string, VariableMetadata> mapWithClash) {

    Token token = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_BRACE_OPEN_SQUARE);

    token = tokenise_request(text);
    long long int stackOffset = 0;
    while(token.tokenID != TOK_BRACE_CLOSE_SQUARE) {
        VariableMetadata newVariable; newVariable.isUpdated = false; newVariable.timesUsed = 0;
        token = tokenise_request(text);
        if(token.tokenID == TOK_KEYWORD_INT) {
            newVariable.dataType = TOK_TYPE_INT;
        } else {
            INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Unrecognised type", token);
        }
        newVariable.stackOffset = (stackOffset += ARCH_SIZE_DATATYPE_INT);

        token = tokenise_request(text);
        INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_IDENTIFIER);
        if(INTERNAL_MACRO_IS_IN_MAP(token.tokenString, mapToAppend) != false || INTERNAL_MACRO_IS_IN_MAP(token.tokenString, mapWithClash) != false) {
            INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Duplicate variable", token);
        }

        mapToAppend[token.tokenString] = newVariable;
        token = tokenise_request(text);
        if(token.tokenID == TOK_BRACE_CLOSE_SQUARE) {
            break;
        } else if(token.tokenID == TOK_SYMBOL_COMMA) {
            INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_SYMBOL_COMMA);
            continue;
        } else {
            INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_BRACE_CLOSE_SQUARE);
        }
    }

    return true;
}


/* bool internal_parse_if(string &text)
 * @brief :: Parse an if statement
 *
 * @param :: string &text :: Source code text
 * @param :: FunctionMetadata &functionMetadata :: Function metadata
 *
 * @return :: bool :: Indication of success/failure in parsing
 */
bool internal_parse_if(string &text, FunctionMetadata &functionMetadata) {
    //if(a == b) {...}
    

    return true;
}

/* bool internal_parse_while(string &text)
 * @brief :: Parse a while loop
 *
 * @param :: string &text :: Source code text
 * @param :: FunctionMetadata &functionMetadata :: Function metadata
 *
 * @return :: bool :: Indication of success/failure in parsing
 */
bool internal_parse_while(string &text, FunctionMetadata &functionMetadata) {
    //while(a == b) {...}
    

    return true;
}

/* bool internal_parse_label_declaration(string &text)
 * @brief :: Parse a label declaration
 *
 * @param :: string &text :: Source code text
 * @param :: FunctionMetadata &functionMetadata :: Function metadata
 *
 * @return :: bool :: Indication of success/failure in parsing
 */
bool internal_parse_label_declaration(string &text, FunctionMetadata &functionMetadata) {
    //label x;
    Token token = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_IDENTIFIER);
    if(INTERNAL_MACRO_IS_IN_MAP(token.tokenString, functionMetadata.labels) == true) {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Duplicate label", token);
        return false;
    }
    functionMetadata.labels.insert(token.tokenString);

    token = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_SYMBOL_SEMICOLON);

    return true;
}

/* bool internal_parse_goto(string &text)
 * @brief :: Parse a goto statement
 *
 * @param :: string &text :: Source code text
 * @param :: FunctionMetadata &functionMetadata :: Function metadata
 *
 * @return :: bool :: Indication of success/failure in parsing
 */
bool internal_parse_goto(string &text, FunctionMetadata &functionMetadata) {
    //goto x;
    Token token = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_IDENTIFIER);
    if(INTERNAL_MACRO_IS_IN_MAP(token.tokenString, functionMetadata.labels) == false) {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Unrecognised label", token);
        return false;
    }
    ARCH_GOTO(token.tokenString);

    token = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_SYMBOL_SEMICOLON);

    return true;
}

/* bool internal_parse_function_declaration(string &text)
 * @brief :: Parse a function declaration
 *
 * @param :: string &text :: Source code text
 *
 * @return :: bool :: Indication of success/failure in parsing
 */
bool internal_parse_function_declaration(string &text) {

    FunctionMetadata newFunction;
    Token functionNameToken = tokenise_request(text);
    if(INTERNAL_MACRO_IS_IN_MAP(functionNameToken.tokenString, knownFunctions) == true) { //Check for function redefinition
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Duplicate function", functionNameToken);
        return false;
    }
    if(functionNameToken.tokenString == PARSE_ENTRYPOINT) { //Main function
        mainIsDeclared = true;
    }

    internal_declare_variables(text, newFunction.functionArguments, newFunction.localVariables);
    internal_declare_variables(text, newFunction.localVariables, newFunction.functionArguments);

    Token token = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_SYMBOL_RETURN_TYPE);

    token = tokenise_request(text);
    if(INTERNAL_MACRO_IS_IN_MAP(token.tokenString, newFunction.localVariables) == false) {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Unrecognised retuen", token);
    }

    token = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_BRACE_OPEN_CURLEY);

    token = tokenise_request(text);
    internal_helper_call_parser_function(text, token, newFunction);

    token = tokenise_request(text);
    INTERNAL_MACRO_ASSERT_TOKEN(token, TOK_BRACE_CLOSE_CURLEY);
    knownFunctions[functionNameToken.tokenString] = newFunction;
    return true;
}




/* bool internal_parse_call(string &text)
 * @brief :: Parse an call statement
 *
 * @param :: string &text :: Source code text
 * @param :: FunctionMetadata &functionMetadata :: Function metadata
 *
 * @return :: bool :: Indication of success/failure in parsing
 */
bool internal_parse_call(string &text, FunctionMetadata &functionMetadata) {
    //call foo(args) -> x
    

    return true;
}

/* bool internal_parse_assignment(string &text)
 * @brief :: Parse an assignment
 *
 * @param :: string &text :: Source code text
 * @param :: FunctionMetadata &functionMetadata :: Function metadata
 *
 * @return :: bool :: Indication of success/failure in parsing
 */
bool internal_parse_assignment(string &text, FunctionMetadata &functionMetadata) {
    //call foo(args) -> x
    





    return true;
}



/* bool parse_parse(string &text)
 * @brief :: Initialise parsing stage of compilation
 *
 * @param :: string &text :: Source code text
 *
 * @return :: bool :: Indication of success/failure in parsing
 */
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
        return false;
    }
    if(mainIsDeclared == false) {
        cout << "ERROR: Expect declaration of main function" << endl;
        return false;   
    }

    return true;
}








