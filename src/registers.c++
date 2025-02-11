#include "registers.h++"





//Load a variable to a register and return the index - VARIABLE ASSUMED TO EXIST
size_t registers_load_variable(vector<variableMetadata> registers, FunctionMetadata functionMetadata, string varNameToLoad) {

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

    //Check if index is saved - if not save it
    if(registers[leastUsedRegisterIndex].variableMetadata.timesUsed == false) {
        //TODO: PUT MACRO HERE TO SAVE
        cout << "UNIMPLEMENTED - SAVE REGISTER TO STACK" << endl;
    }

    //TODO: LOAD VAR TO REGISTER FROM STACK

    return leastUsedRegisterIndex;
}





//Load a immediate to a register and return the index
size_t registers_load_immediate(vector<variableMetadata> registers, FunctionMetadata functionMetadata, size_t immediate) {

    //Is variable in register? Yes - Return index | No - Go below
    //Find any free spaces in the register space
    //Find least used variable in register and mark
    //Is least used variable saved? Yes - Overwrite and return index | No - Save and return index

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

    //Check if index is saved - if not save it
    if(registers[leastUsedRegisterIndex].variableMetadata.timesUsed == false) {
        //TODO: PUT MACRO HERE TO SAVE
        cout << "UNIMPLEMENTED - SAVE REGISTER TO STACK" << endl;
    }

    //TODO: LOAD CONSTANT INTO REGISTER HERE


    return leastUsedRegisterIndex;
}








