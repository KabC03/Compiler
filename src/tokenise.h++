#ifndef TOKENISE_H
#define TOKENISE_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "tokens.h++"

using namespace std;

//Tokens delimeterd via:
//Symbol next to non-symbol
//Alphanumeric next to space or symbol
//String literals enclosed via ""
//Brackets, comma

typedef struct Token {

    TOKEN_ENUM tokenID; //ID of token (e.g while, for, if, etc)
    string tokenString; //For variable names, immediates, etc
    
} Token;

typedef enum TOKENISER_STATE {

    STATE_START,

    STATE_STRING, //Variable name or keyword
    STATE_INT_IMM,
    STATE_FLOAT_IMM,
    STATE_CHAR_IMM,
    STATE_STRING_IMM,
    STATE_SYMBOL,

} TOKENISER_STATE;




void tokenise_init(unordered_map<string, TOKEN_ENUM> &tokenSet);
bool tokenise_request(Token &token,string &line, unordered_map<string, TOKEN_ENUM> &tokenMap);



#endif 



      
      
      
      