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
    for(size_t i = 0; i < registerFile.size(); i++) {
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



    //Load variable
    registerFile[registerIndex].variableMetadata = variable; 
    if(isUpdated == false) { //If doing a reassignment and this is the destination (where its not just read)
        registerFile[registerIndex].variableMetadata.isUpdated = false;
    }


    return; 
}

tuple<bool, size_t> register_var_is_in_register(VariableMetadata &variable) {
    //Check if variable is already in register
    for(size_t i = 0; i < registerFile.size(); i++) {
        if(registerFile[i].variableMetadata.stackOffset == variable.stackOffset && registerFile[i].isFree == false) { 
            //If they have the same stack offset they are the same var
            return make_tuple(true, i);
        }
    }

    return make_tuple(false, 0);
}


bool register_bind_variable(VariableMetadata &variable, size_t registerIndex) {

    //If variable is already in register then remove it
    for(size_t i = 0; i < registerFile.size(); i++) {
        if(registerFile[i].variableMetadata.stackOffset == variable.stackOffset && registerFile[i].isFree == false) {
            registerFile[i].isFree = true;
        }
    }

    registerFile[registerIndex].variableMetadata = variable;
    return true;
}



//Load a variable to a register (if it doesnt exist return false)
size_t register_load_variable(VariableMetadata &variable, FunctionMetadata &FunctionMetadata) {
    //TODO
    return true;
}


//Prepare R0 for a return value
void register_init_return_register(VariableMetadata &variable) {

    tuple<bool, size_t> isInRegisterTuple = register_var_is_in_register(variable);
    if(get<0>(isInRegisterTuple) == true) { //If variable is in register remove it
        //Copy R0 -> variable Register
        registerFile[get<1>(isInRegisterTuple)].isFree = true;
        registerFile[get<1>(isInRegisterTuple)].variableMetadata.isUpdated = false; //No longer matches stack value
    }
    registerFile[ARCH_RETURN_REGISTER_NUMBER].variableMetadata = variable;

    return;
}














