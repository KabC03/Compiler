#include "registers.h++"

//TODO: Refactor this so that its broken up into:
//registers_request_free -> int
//register_load_var -> int
//register_load_imm -> int



//Load a variable to a register and return the index - VARIABLE ASSUMED TO EXIST
size_t registers_load_variable(vector<RegisterItem> registers, FunctionMetadata functionMetadata, string varNameToLoad) {

    //Is variable in register? Yes - Return index | No - Go below
    //Find any free spaces in the register space
    //Find least used variable in register and mark
    //Is least used variable saved? Yes - Overwrite and return index | No - Save and return index

    //Check if variable is already in register
    for(size_t i = 0; i < registers.size(); i++) {
        if(registers[i].variableMetadata.name == varNameToLoad) {
            return i;
        }
    }

    //Check for free registers 
    for(size_t i = 0; i < registers.size(); i++) {
        if(registers[i].isFree == true) {
            return i;
        }
    }

    //Find least used register
    size_t leastUsedRegisterIndex = 0; 
    for(size_t i = 0; i < registers.size(); i++) {
        if(registers[leastUsedRegisterIndex].variableMetadata.timesUsed > registers[i].variableMetadata.timesUsed) {
            leastUsedRegisterIndex = i;
        }
    }

    //Check if index is saved - if not save it (sometimes var may have just been read no need to save it)
    if(registers[leastUsedRegisterIndex].variableMetadata.updated == false) {

        ARCH_SAVE_VAR_STACK(leastUsedRegisterIndex, registers[leastUsedRegisterIndex].variableMetadata.stackOffset);
    }


    //Load new variable to register from stack
    registers[leastUsedRegisterIndex].variableMetadata = functionMetadata.variableMap[varNameToLoad];
    ARCH_LOAD_VAR_STACK(leastUsedRegisterIndex, functionMetadata.variableMap[varNameToLoad].stackOffset);

    return leastUsedRegisterIndex;
}



//Load an immediate to a register
size_t registers_load_immediate(vector<RegisterItem> registers, FunctionMetadata functionMetadata, size_t immediate, TOKEN_ENUM type) {

    //Find any free spaces in the register space
    //Find least used variable in register and mark
    //Is least used variable saved? Yes - Overwrite and return index | No - Save and return index


    //Check for free registers 
    for(size_t i = 0; i < registers.size(); i++) {
        if(registers[i].isFree == true) {
            switch(type) {
                case TOK_INT_IMM: {
                    ARCH_LOAD_INT_IMM(i, immediate);
                    break;
                } case TOK_FLOAT_IMM: {
                    ARCH_LOAD_FLOAT_IMM(i, immediate);
                    break;
                } default: {
                    cout << "ERROR: register.c++ expects INT or FLOAT immediate" << endl;
                    exit(1);
                }
            }
            return i;
        }
    }

    //Find least used register
    size_t leastUsedRegisterIndex = 0; 
    for(size_t i = 0; i < registers.size(); i++) {
        if(registers[leastUsedRegisterIndex].variableMetadata.timesUsed > registers[i].variableMetadata.timesUsed) {
            leastUsedRegisterIndex = i;;
        }
    }

    //Check if index is saved - if not save it (sometimes var may have just been read no need to save it)
    if(registers[leastUsedRegisterIndex].variableMetadata.updated == false) {

        ARCH_SAVE_VAR_STACK(leastUsedRegisterIndex, registers[leastUsedRegisterIndex].variableMetadata.stackOffset);
    }


    //Load new variable to register from stack

    switch(type) {
        case TOK_INT_IMM: {
            ARCH_LOAD_INT_IMM(leastUsedRegisterIndex, immediate);
            break;
        } case TOK_FLOAT_IMM: {
            ARCH_LOAD_FLOAT_IMM(leastUsedRegisterIndex, immediate);
            break;
        } default: {
            cout << "ERROR: register.c++ expects INT or FLOAT immediate" << endl;
            exit(1);
        }
    }

    return leastUsedRegisterIndex;
}






