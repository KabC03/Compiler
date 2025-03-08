#ifndef PARSE_H
#define PARSE_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include <tuple>
#include "tokenise.h++"
#include "architecture.h++"
#include "compiler_structures.h++"


using namespace std;
//Datatype sizes (bytes)
#define SIZE_DATATYPE_INT 4
#define SIZE_DATATYPE_FLOAT 4
#define SIZE_DATATYPE_PTR 8
#define SIZE_DATATYPE_CHAR 1



bool parse(string &text);






#endif 
