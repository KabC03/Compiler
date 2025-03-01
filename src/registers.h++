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




#endif 



