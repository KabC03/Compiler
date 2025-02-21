#ifndef PARSE_H
#define PARSE_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include "tokenise.h++"
#include "architecture.h++"

using namespace std;
//Datatype sizes (bytes)
#define SIZE_DATATYPE_INT 4
#define SIZE_DATATYPE_FLOAT 4
#define SIZE_DATATYPE_PTR 8
#define SIZE_DATATYPE_CHAR 1


typedef struct VariableMetadata {

    string name; //Name of the variable :: TODO: Remove this I dont think its needed
    TOKEN_ENUM dataType; //Type of variable
    size_t stackOffset; //From bptr
    size_t timesUsed; //How many times this variable has been retrieved
    bool updated; //If variable is updated on stack (same as register)
} VariableMetadata;


typedef struct FunctionMetadata {

    unordered_map<string, VariableMetadata> variableMap; //Known variables
    size_t stackTop; //Current stack pointer

} FunctionMetadata;

bool parse(string &text);






#endif 
