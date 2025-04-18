#ifndef TOKENISE_H
#define TOKENISE_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "compiler_structures.h++"


using namespace std;

//Tokens delimeterd via:
//Symbol next to non-symbol
//Alphanumeric next to space or symbol
//String literals enclosed via ""
//Brackets, comma

typedef enum TOKENISER_STATE {

    STATE_START,

    STATE_STRING, //Variable name or keyword
    STATE_INT_IMM,
    STATE_FLOAT_IMM,
    STATE_CHAR_IMM,
    STATE_STRING_IMM,
    STATE_SYMBOL,
    STATE_COMMENT,

} TOKENISER_STATE;




void tokenise_print(Token &token);
void tokenise_init(void);
Token tokenise_request(string &line);



#endif 



      
      
      
      
