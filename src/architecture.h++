#ifndef PNEUMONICS_H
#define PNEUMONICS_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>


//Architecture
#define ARCH_WORD_SIZE 4
#define ARCH_NUM_GP_REGISTERS 6 //DOES NOT include non-GPR


//Memory
#define ARCH_SAVE_VAR_TO_STACK(regSrc, stackDest) 1;
#define ARCH_LOAD_VAR_FROM_STACK(regDest, stackSrc) 1;
#define ARCH_LOAD_INT_TO_REG(regDest,const) 1;
#define ARCH_LOAD_FLOAT_TO_REG(regDest, const) 1;


//ALU
#define ARCH_MOV(dest, src) 1;

#define ARCH_ADD_INT(dest, src1, src2) 1;
#define ARCH_ADD_FLOAT(dest, src1, src2) 1;

#define ARCH_SUB_INT(dest, src1, src2) 1;
#define ARCH_SUB_FLOAT(dest, src1, src2);

#define ARCH_MUL_INT(dest, src1, src2) 1;
#define ARCH_MUL_FLOAT(dest, src1, src2) 1;

#define ARCH_DIV_INT(dest, src1, src2) 1;
#define ARCH_DIV_FLOAT(dest, src1, src2) 1;


//Branching
#define ARCH_GOTO(label) 1;

#define ARCH_EQ_INT(src1, src2, label) 1;
#define ARCH_EQ_FLOAT(src1, src2, label) 1;

#define ARCH_NEQ_INT(src1, src2, label) 1;
#define ARCH_NEQ_FLOAT(src1, src2, label) 1;

#define ARCH_GR_INT(src1, src2, label) 1;
#define ARCH_GR_FLOAT(src1, src2, label) 1;

#define ARCH_GRE_INT(src1, src2, label) 1;
#define ARCH_GRE_INT(src1, src2, label) 1;

#define ARCH_LT_FLOAT(src1, src2, label) 1;
#define ARCH_LT_FLOAT(src1, src2, label) 1;

#define ARCH_LTE_FLOAT(src1, src2, label) 1;
#define ARCH_LTE_FLOAT(src1, src2, label) 1;


//Procedure calls
#define ARCH_CALL(label);
#define ARCH_RETURN();


#endif

