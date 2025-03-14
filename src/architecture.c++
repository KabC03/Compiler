#include "architecture.h++"


size_t architecture_get_datatype_size(TOKEN_ENUM dataType) {

    if(dataType == TOK_TYPE_INT) {
        return ARCH_SIZE_DATATYPE_INT;
    } else if(dataType == TOK_TYPE_FLOAT) {
        return ARCH_SIZE_DATATYPE_FLOAT;
    } else if(dataType == TOK_TYPE_PTR) {
        return ARCH_SIZE_DATATYPE_PTR;
    } else {
        cout << "INVALID COMPILATION STATE" << endl;
        exit(1);
    }

    return -1;
}





