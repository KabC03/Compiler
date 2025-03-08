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


tuple<bool, size_t> expression_handling_lr_evaluation(string &text, FunctionMetadata &functionMetadata);


#endif




