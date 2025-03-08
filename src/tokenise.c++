#include "tokenise.h++"

unordered_map<string, TOKEN_ENUM> tokenMap;



void tokenise_print(Token &token) {

    cout << "Token ID: " << token.tokenID << " | Token String: " << token.tokenString << endl;


    return;
}





//Initialise tokeniser hashmap
void tokenise_init(void) {

    for(int i = 0; i < NUM_TOKENS; i++) { //Enum is strongly typed to hold int
        tokenMap[tokens[i]] = (TOKEN_ENUM)i;
    }

    return;
}





//Request a token from line -> token
Token tokenise_request(string &line) {

    static int index = 0; //Index into current line
    //Return the token immediatly upon finding it

    string buffer = "";
    TOKENISER_STATE state = STATE_START;
    Token token;
    token.tokenID = TOK_INVALID;

    TOKEN_ENUM last = TOK_INVALID;
    int saveIndex = index;
    while(index <= line.length()) {
        char currentChar = line[index];
        switch(state) {
            case STATE_START: {
                
                index++;
                if(currentChar == '\'') {

                    //state = STATE_CHAR_IMM;
                    cout << "ERROR: Chars are not yet implemented" << endl;
                    token.tokenID = TOK_INVALID;
                    return token;

                } else if(currentChar == '"') {
                    state = STATE_STRING_IMM;
                } else if(currentChar == '.') {
                    buffer.push_back('0');
                    state = STATE_FLOAT_IMM;
                } else if(isdigit(currentChar) == true) {
                    state = STATE_INT_IMM;
                } else if(isalpha(currentChar) == true) {
                    state = STATE_STRING;
                } else if(ispunct(currentChar) == true) {
                    state = STATE_SYMBOL;
                } else if(isspace(currentChar) == true) {
                    continue;
                } else if(currentChar == '\0') {
                    //cout << "EOF" << endl;
                    token.tokenID = TOK_EOF;
                    return token;
                } else {
                    //Unknown symbol
                    cout << "ERROR: Unrecognised symbol '" << buffer << "'"  << endl;
                    token.tokenID = TOK_INVALID;
                    return token;
                }
                buffer.push_back(currentChar);
                break;
            
            } case STATE_CHAR_IMM: {

                buffer.push_back(currentChar);
                if(currentChar == '\'') {
                    //Complete token
                    token.tokenID = TOK_CHAR_IMM;
                    token.tokenString = buffer;
                    //cout << "Char immediate found" << endl;
                    return token;
                    
                } else if(buffer.length() >= 3) {
                    cout << "ERROR: Char immediate " << buffer << "' may only contain one character" << endl;
                    token.tokenID = TOK_INVALID;
                    return token;
                }

                index++;
                break;
            } case STATE_STRING_IMM: {
                buffer.push_back(currentChar);
                if(currentChar == '"') {
                    //Complete token
                    token.tokenID = TOK_STRING_IMM;
                    token.tokenString = buffer;
                    //cout << "String immediate found" << endl;
                    return token;
                }
                index++;
                break;
            } case STATE_INT_IMM: {
                if(currentChar == '.') {
                    state = STATE_FLOAT_IMM;

                } else if(isdigit(currentChar) == false) {
                    //Complete token
                    token.tokenID = TOK_INT_IMM;
                    token.tokenString = buffer;
                    //cout << "Integer immediate found" << endl;
                    return token;
                }
                index++;
                buffer.push_back(currentChar);
                break;
            } case STATE_FLOAT_IMM: {
                if(isdigit(currentChar) == false) {
                    //Complete token
                    token.tokenID = TOK_FLOAT_IMM;
                    token.tokenString = buffer;
                    //cout << "Float immediate found" << endl;
                    return token;
                }
                index++;
                buffer.push_back(currentChar);
                break;
            } case STATE_STRING: {
                if(isdigit(currentChar) == false && isalpha(currentChar) == false) {
                    //Complete token
                    //Hash it to see if its a keyword - it not its a variable or function name

                    auto it = tokenMap.find(buffer);
                    if(it != tokenMap.end()) { //Key found - keyword
                        token.tokenID = it->second;
                        token.tokenString = "KEYWORD";
                        //cout << "Keyword" << endl;
                    } else { //Identifier
                        token.tokenString = buffer;
                        token.tokenID = TOK_IDENTIFIER;
                        //cout << "Identifier" << endl;
                    }
                    //cout << "String found" << endl;
                    return token;
                }
                index++;
                buffer.push_back(currentChar);
                break;
            } case STATE_SYMBOL: {

                if(ispunct(currentChar) == false) {
                    //Complete token
                    auto it = tokenMap.find(buffer);
                    if(it != tokenMap.end()) { //Key found - key symbol 
                        last = it->second;
                        saveIndex = index;
                    } else {
                        //Nothing found
                    }

                    if(last != TOK_INVALID) {
                        token.tokenID = last;
                        //cout << "Symbol found" << endl;

                        index = saveIndex;
                        return token;
                    } else { //No symbol found
                        cout << "ERROR: Invalid symbol '" << buffer << "'"  << endl;
                        token.tokenID = TOK_INVALID;
                        //ERROR
                        return token;
                    }
                } else {
                    auto it = tokenMap.find(buffer);
                    if(it != tokenMap.end()) { //Key found - key symbol 
                        saveIndex = index;
                        last = it->second;
                    } else {
                        //Nothing found
                    }
                }

                index++;
                buffer.push_back(currentChar);
                break;
            }



        }
    }
    //cout << "Nothing found" << endl;
    token.tokenID = TOK_INVALID;
    return token;
}
























