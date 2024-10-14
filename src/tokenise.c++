#include "tokenise.h++"




//Initialise tokeniser hashmap
void tokenise_init(unordered_map<string, TOKEN_ENUM> &tokenMap) {

    for(int i = 0; i < NUM_TOKENS; i++) { //Enum is strongly typed to hold int
        tokenMap[tokens[i]] = (TOKEN_ENUM)i;
    }

    return;
}





//Request a token from line -> token
bool tokenise_request(Token &token,string &line, unordered_map<string, TOKEN_ENUM> &tokenMap) {

    static int index = 0; //Index into current line
    //Return the token immediatly upon finding it

    string buffer = "";
    TOKENISER_STATE state = STATE_START;

    TOKEN_ENUM last = TOK_INVALID;
    int saveIndex = index;
    while(index <= line.length()) {
        char currentChar = line[index];

        switch(state) {
            case STATE_START: {
                index++;
                if(currentChar == '\'') {
                    state = STATE_CHAR_IMM;
                } else if(currentChar == '"') {
                    state = STATE_STRING_IMM;
                } else if(isdigit(currentChar) == true) {
                    state = STATE_INT_IMM;
                } else if(isalpha(currentChar) == true) {
                    state = STATE_STRING;
                } else if(ispunct(currentChar) == true) {
                    state = STATE_SYMBOL;
                } else if(isspace(currentChar) == true) {
                    continue;
                } else {
                    //Unknown symbol
                    cout << "Unrecognised symbol" << endl;
                    return false;
                }
                buffer.push_back(currentChar);
                break;
            
            } case STATE_CHAR_IMM: {

                index++;
                buffer.push_back(currentChar);
                if(currentChar == '\'') {
                    //Complete token
                    token.tokenID = TOK_CHAR_IMM;
                    token.tokenString = buffer;
                    cout << "Char immediate found" << endl;
                    return true;
                }

                break;
            } case STATE_STRING_IMM: {
                index++;
                buffer.push_back(currentChar);
                if(currentChar == '"') {
                    //Complete token
                    token.tokenID = TOK_STRING_IMM;
                    token.tokenString = buffer;
                    cout << "String immediate found" << endl;
                    return true;
                }
                break;
            } case STATE_INT_IMM: {
                index++;
                if(currentChar == '.') {
                    state = STATE_FLOAT_IMM;

                } else if(isdigit(currentChar) == false) {
                    //Complete token
                    token.tokenID = TOK_INT_IMM;
                    token.tokenString = buffer;
                    cout << "Integer immediate found" << endl;
                    return true;
                }
                buffer.push_back(currentChar);
                break;
            } case STATE_FLOAT_IMM: {
                index++;
                if(isdigit(currentChar) == false) {
                    //Complete token
                    token.tokenID = TOK_FLOAT_IMM;
                    token.tokenString = buffer;
                    cout << "Float immediate found" << endl;
                    return true;
                }

                buffer.push_back(currentChar);
                break;
            } case STATE_STRING: {
                index++;
                if(isdigit(currentChar) == false && isalpha(currentChar) == false) {
                    //Complete token
                    //Hash it to see if its a keyword - it not its a variable or function name

                    auto it = tokenMap.find(buffer);
                    if(it != tokenMap.end()) { //Key found - keyword
                        token.tokenID = it->second;
                        cout << "Keyword" << endl;
                    } else { //Identifier
                        token.tokenString = buffer;
                        token.tokenID = TOK_IDENTIFIER;
                        cout << "Identifier" << endl;
                    }
                    cout << "String found" << endl;
                    return true;
                }
                buffer.push_back(currentChar);
                break;
            } case STATE_SYMBOL: {
                index++;
                saveIndex = index;
                if(ispunct(currentChar) == false) {
                    //Complete token

                    auto it = tokenMap.find(buffer);
                    if(it != tokenMap.end()) { //Key found - key symbol 
                        last = it->second;
                    } else {
                        //Nothing found
                    }

                    if(last != TOK_INVALID) {
                        token.tokenID = last;
                        cout << "Symbol found" << endl;
                        index = saveIndex;
                        return true;
                    } else { //No symbol found
                        cout << "Invalid symbol" << endl;
                        return false;
                    }
                } else {
                    auto it = tokenMap.find(buffer);
                    if(it != tokenMap.end()) { //Key found - key symbol 
                        last = it->second;
                    } else {
                        //Nothing found
                    }
                }

                buffer.push_back(currentChar);
                break;
            }



        }
    }
    cout << "Nothing found" << endl;
    return false;
}
























