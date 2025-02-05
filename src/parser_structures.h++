#ifndef PARSER_STRUCTURES_H
#define PARSER_STRUCTURES_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include "tokenise.h++"

using namespace std;

//Datatype sizes (bytes)
#define SIZE_DATATYPE_INT 4
#define SIZE_DATATYPE_FLOAT 4
#define SIZE_DATATYPE_PTR 8
#define SIZE_DATATYPE_CHAR 1



typedef struct Variable {

    TOKEN_ENUM type; //Type of the variable (int, float, char)

    size_t addressIndex; //Stack memory address of the variable

    int registerIndex; //Register number for the variable (-1 if not in register)

} Variable;

typedef struct FunctionScope {

    unordered_map<string, Variable> variableMap; //Known variables to the function
    TOKEN_ENUM returnType; //Return type of the function


} FunctionScope;


#endif 
