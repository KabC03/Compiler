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


void register_init(void);
size_t register_request(void);
void register_mark_used(size_t index);
void register_mark_free(size_t index);
void register_load_var_to_reg(size_t registerIndex, VariableMetadata &variable, bool isUpdated);
tuple<bool, size_t> register_var_is_in_register(VariableMetadata &variable);
void register_init_return_register(VariableMetadata &variable);
#endif 



