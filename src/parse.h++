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
#define PARSE_SIZE_DATATYPE_INT 4
#define PARSE_SIZE_DATATYPE_FLOAT 4
#define PARSE_ENTRYPOINT "main" //Name of main function
#define PARSE_RETURN_REGISTER_NUMBER 0 //Functions return to R0

void parse_init(void);
bool parse_parse(string &text);






#endif 
