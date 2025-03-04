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


size_t register_request(vector<RegisterItem> registerFile);
void register_mark_used(vector<RegisterItem> registerFile, size_t index);
void register_mark_free(vector<RegisterItem> registerFile, size_t index);
#endif 



