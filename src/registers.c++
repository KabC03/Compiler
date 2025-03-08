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

vector<RegisterItem> registerFile;


void register_init(void) {

    vector<RegisterItem> registers;
    registers.resize(ARCH_NUM_GP_REGISTERS);

    return;
}

size_t register_request(void) {

    //Check for unused space
    for(size_t i = 1; i < registerFile.size(); i++) {
        if(registerFile[i].isFree == true) {
            return i;
        }
    }


    //Find least used register
    size_t lrrIndex = 0;
    for(size_t i = 0; i < registerFile.size(); i++) {
        if(registerFile[lrrIndex].variableMetadata.timesUsed > registerFile[i].variableMetadata.timesUsed) {
            lrrIndex = i;
        }
    }

    //Save LRR if not updated
    if(registerFile[lrrIndex].variableMetadata.isUpdated == false) {
        ARCH_SAVE_VAR_TO_STACK(lrrIndex, registerFile[lrrIndex].variableMetadata.stackOffset);
    }
    return lrrIndex;
}

void register_mark_used(size_t index) {
    registerFile[index].isFree = false;
    return;
}
void register_mark_free(size_t index) {
    registerFile[index].isFree = true;
    return;
}

void register_load_var_to_reg(size_t registerIndex, VariableMetadata &variable, bool isUpdated) {

    registerFile[registerIndex].variableMetadata = variable; 
    if(isUpdated == false) { //If doing a reassignment and this is the destination (where its not just read)
        registerFile[registerIndex].variableMetadata.isUpdated = false;
    }


    return; 
}


















