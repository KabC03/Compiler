#ifndef PARSE_H
#define PARSE_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include "tokenise.h++"
#include "parser_structures.h++"

using namespace std;


bool parse(string &line, unordered_map<string, TOKEN_ENUM> &tokenMap);


#endif 
