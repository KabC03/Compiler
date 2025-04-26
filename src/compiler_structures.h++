
#ifndef COMPILER_STRUCTURES_H 
#define COMPILER_STRUCTURES_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include <tuple>
#include "architecture.h++"
#define HERE cout << "\n\nHERE\n\n" << endl;


typedef struct Token {

    TOKEN_ENUM tokenID; //ID of token (e.g while, for, if, etc)
    string tokenString; //For variable names, immediates, etc
    
} Token;


typedef struct VariableMetadata {

    TOKEN_ENUM dataType; //Type of variable
    long long int stackOffset; //From bptr
    size_t timesUsed; //How many times this variable has been retrieved
    bool isUpdated; //If variable is updated on stack (same as register)
} VariableMetadata;


typedef struct FunctionMetadata { //Information about the current function scope

    unordered_map<string, VariableMetadata> functionArguments;
    unordered_map<string, VariableMetadata> localVariables; //Known variables
    unordered_set<string> labels; //Known labels
    TOKEN_ENUM returnType; //Return type of function

} FunctionMetadata;

typedef struct RegisterItem {

    bool isFree;
    VariableMetadata variableMetadata; //Variable information

} RegisterItem;


#endif








