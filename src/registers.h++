#ifndef REGISTERS_H
#define REGISTERS_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include <cstdlib>
#include "parse.h++"


typedef struct RegisterItem {

    bool isFree;
    VariableMetadata variableMetadata; //Variable information

} RegisterItem;


size_t registers_load_variable(vector<RegisterItem> registers, FunctionMetadata functionMetadata, string varNameToLoad);
size_t registers_load_immediate(vector<RegisterItem> registers, FunctionMetadata functionMetadata, size_t immediate, TOKEN_ENUM type);


#endif 



