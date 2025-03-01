#ifndef PNEUMONICS_H
#define PNEUMONICS_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>


#define ARCH_WORD_SIZE 4
#define ARCH_NUM_REGISTERS 6 //DOES NOT include non-GPR



#define ARCH_SAVE_VAR_STACK(regSrc, stackDest) 1;
#define ARCH_LOAD_VAR_STACK(regDest, stackSrc) 1;
#define ARCH_LOAD_INT_IMM(regDest,const) 1;
#define ARCH_LOAD_FLOAT_IMM(regDest, const) 1;


#endif

