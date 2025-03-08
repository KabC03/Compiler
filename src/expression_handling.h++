#ifndef EXPRESSION_HANDLING_H
#define EXPRESSION_HANDLING_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include <tuple>
#include "tokenise.h++"
#include "architecture.h++"
#include "registers.h++"
#include "compiler_structures.h++"
typedef struct VariableMetadata {

    string name; //Name of the variable :: TODO: Remove this I dont think its needed
    TOKEN_ENUM dataType; //Type of variable
    size_t stackOffset; //From bptr
    size_t timesUsed; //How many times this variable has been retrieved
    bool isUpdated; //If variable is updated on stack (same as register)
} VariableMetadata;


typedef struct FunctionMetadata { //Information about the current function scope

    unordered_map<string, VariableMetadata> variableMap; //Known variables
    size_t stackTop; //Current stack pointer

} FunctionMetadata;

tuple<bool, size_t> expression_handling_lr_evaluation(string &text, FunctionMetadata &functionMetadata, vector<RegisterItem> &registerFile);


#endif




