#ifndef REGISTERS_H
#define REGISTERS_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include "parse.h++"


typedef struct Register {

    bool isFree;
    union {
        size_t immediate; //Space for immediate value
        VariableMetadata variableMetadata; //Space for variable
    }

} Register;


size_t registers_load_variable(vector<variableMetadata> registers, FunctionMetadata functionMetadata, string varNameToLoad);
size_t registers_load_immediate(vector<variableMetadata> registers, FunctionMetadata functionMetadata, size_t immediate);


#endif 



