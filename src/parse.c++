#include "parse.h++"

unordered_map<string, FunctionMetadata> knownFunctions;
bool mainIsDeclared = false;




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









/* bool internal_parse_function_declaration(string &text)
 * @brief :: Parse a function declaration
 *
 * @param :: string &text :: Source code text
 *
 * @return :: bool :: Indication of success/failure in parsing
 */
bool internal_parse_function_declaration(string &text) {

    

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








