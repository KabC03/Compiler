#ifndef PNEUMONICS_H
#define PNEUMONICS_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include "tokens.h++"

size_t architecture_get_datatype_size(TOKEN_ENUM dataType);

//Datatype sizes (bytes)
#define ARCH_SIZE_DATATYPE_INT 4
#define ARCH_SIZE_DATATYPE_FLOAT 4
#define ARCH_SIZE_DATATYPE_PTR 4
#define ARCH_RETURN_REGISTER_NUMBER 0 //Functions return to R0
#define PARSE_ENTRYPOINT "main" //Name of main function
#define PARSE_WHILE_START_PREFIX "while_start_"
#define PARSE_WHILE_END_PREFIX "while_end_"





//Architecture
#define ARCH_WORD_SIZE 4
#define ARCH_NUM_GP_REGISTERS 6 //DOES NOT include non-GPR

//Memory
#define ARCH_SAVE_VAR_TO_STACK(regSrc, stackDest) 1;
#define ARCH_LOAD_VAR_FROM_STACK(regDest, stackSrc) 1;
#define ARCH_LOAD_INT_TO_REG(regDest,const) 1;
#define ARCH_LOAD_FLOAT_TO_REG(regDest, const) 1;
#define ARCH_ADD_BPTR(regDest); //Add base pointer to this value and save it in the same place

#define ARCH_PUSH_STACK(src, offset) 1;
#define ARCH_POP_STACK(dest, offset) 1;

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
#define ARCH_LABEL(label) 1;

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

