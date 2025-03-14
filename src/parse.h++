#ifndef PARSE_H
#define PARSE_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include <tuple>
#include <algorithm>
#include "tokenise.h++"
#include "architecture.h++"
#include "registers.h++"
#include "compiler_structures.h++"
#include "expression_handling.h++"


using namespace std;




void parse_init(void);
bool parse_parse(string &text);






#endif 
