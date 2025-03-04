#include "registers.h++"

//TODO: Refactor this so that its broken up into:
//registers_request_free -> int
//register_load_var -> int
//register_load_imm -> int

//Functions:
//register_request -> request a register, marked as used
//register_free -> mark a register as unused
//register_load -> load an item from the stack to a register:


//NOTE: Should use macro to load immediate to register, mark as unused first


//Request register and save data
size_t register_request(vector<RegisterItem> registerFile) {

    //Check for unmarked register
    for(size_t i = 0; i < registerFile.size(); i++) {
        if(registerFile[i].isFree == true) {
            return i;
        }
    }

    //Get LRU
    size_t lruIndex = 0;
    for(size_t i = 0; i < registerFile.size(); i++) {
        if(registerFile[lruIndex].timesUsed > registerFile[i].timesUsed) {
            lruIndex = i;
        }
    }

    if(registerFile[index].isFree == true) {
        registerFile[index].isFree = false;
    } else if(registerFile[index].variableMetadata.updated == false) { //Check if variable is not updated in stack
        //Save variable from stack
        ARCH_SAVE_VAR_STACK(registerFile[index].variableMetadata.stackOffset, index); //Save register -> stack
    }
    return index;
}

//Mark a register as free
void register_mark_used(vector<RegisterItem> registerFile, size_t index) {

    registerFile[index].isFree = false;

    return;
}

//Mark a register as free
void register_mark_free(vector<RegisterItem> registerFile, size_t index) {

    registerFile[index].isFree = true;

    return;
}








