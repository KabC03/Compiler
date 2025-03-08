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
#include "compiler_structures.h++"


vector<RegisterItem> register_init(void);
size_t register_request(vector<RegisterItem> registerFile);
void register_mark_used(vector<RegisterItem> registerFile, size_t index);
void register_mark_free(vector<RegisterItem> registerFile, size_t index);
void register_load_var_to_reg(vector<RegisterItem> &registerFile, size_t registerIndex, VariableMetadata &variable, bool isUpdated);
#endif 



