#include "parse.h++"


#define INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR(str, token) { \
    cout << "ERROR: " << str << ", '"; \
    tokenise_print(token); \
    cout << "'" << endl; \
}
#define INTERNAL_MACRO_ASSERT_TOKEN(token, exp) { \
    if(token.tokenID != exp) { \
        cout << "ERROR: Expected '"; \
        tokens[exp]; \
        cout << "' (" << exp << ") but found '"; \
        tokenise_print(token); \
        cout << "'" << endl; \
    } \
}

#define INTERNAL_MACRO_IS_IN_MAP(item, map) \
    ((map.find(item) == map.end()) ? false : true) \


unordered_map<string, FunctionMetadata> knownFunctions;
bool mainIsDeclared = false;


bool internal_parse_function_declaration(string &text) {

    Token returnTypeToken = tokenise_request(text);
    FunctionMetadata newFunction;
    if(returnTypeToken.tokenID == TOK_KEYWORD_INT) {
        newFunction.returnType = TOK_TYPE_INT;
    } else if(returnTypeToken.tokenID == TOK_KEYWORD_BYTE) {
        newFunction.returnType = TOK_TYPE_BYTE;
    } else {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Expect valid function return type", returnTypeToken);
        return false;
    }
    Token functionNameToken = tokenise_request(text);
    if(INTERNAL_MACRO_IS_IN_MAP(functionNameToken.tokenString, knownFunctions) == true) {
        INTERNAL_MACRO_PRINT_UNEXPECTED_TOKEN_ERROR("Function redeclaration", functionNameToken);
        return false;
    }
    if(functionNameToken.tokenString == PARSE_ENTRYPOINT) {
        mainIsDeclared = true;
    }

    


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
        return false;
    }
    if(mainIsDeclared == false) {
        cout << "ERROR: Expect declaration of main function" << endl;
        return false;   
    }

    return true;
}








