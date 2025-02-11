#ifndef PARSE_H
#define PARSE_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include "tokenise.h++"
#include "pneumonics.h++"

using namespace std;
//Datatype sizes (bytes)
#define SIZE_DATATYPE_INT 4
#define SIZE_DATATYPE_FLOAT 4
#define SIZE_DATATYPE_PTR 8
#define SIZE_DATATYPE_CHAR 1


typedef struct Variable {

    TOKEN_ENUM dataType; //Type of variable
    size_t stackOffset; //From bptr
    int registerIndex; //What register the variable is in
    size_t timesUsed; //How many times this variable has been retrieved
    bool isSaved; //If variable is saved in a register
} Variable;




bool parse(string &text);






#endif 
