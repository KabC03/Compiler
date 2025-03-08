#include "expression_handling.h++"


//Handle expressions
//Handle both LR evaluation and also BODMAS
//Return register index where result is
//Functions are not allowed to be called in an expression



//Check if an operand is valid
tuple<bool, TOKEN_ENUM> internal_load_operand(vector<RegisterItem> &registerFile, size_t registerIndex, FunctionMetadata &functionMetadata, Token &token) {

    if(token.tokenID == TOK_IDENTIFIER) {
    
        VariableMetadata variable;
        auto itV = functionMetadata.variableMap.find(token.tokenString);
        if(itV != functionMetadata.variableMap.end()) {
            //Found variable
            variable = itV->second; 
        } else {
            return make_tuple(false, TOK_INVALID);
        }
        register_load_var_to_reg(registerFile, registerIndex, variable, false);
        return make_tuple(true, variable.dataType);
    } else if(token.tokenID == TOK_INT_IMM) {
        ARCH_LOAD_INT_TO_REG(registerIndex, token.tokenString);
        return make_tuple(true, TOK_INT_IMM);
    } else if(token.tokenID == TOK_FLOAT_IMM) {
        ARCH_LOAD_FLOAT_TO_REG(registerIndex, token.tokenString);
        return make_tuple(true, TOK_FLOAT_IMM);
    } else {
        return make_tuple(false, TOK_INVALID);
    }
    return make_tuple(false, TOK_INVALID);
}



//Uses two accumulator registers <success, resultRegister> NOTE: RESULT REGISTER MUSE BE EXPLICITLY MARKED AS FREE AFTER BEING USED
tuple<bool, size_t> expression_handling_lr_evaluation(string &text, FunctionMetadata &functionMetadata, vector<RegisterItem> &registerFile) {

    size_t resultReg = register_request(registerFile); //Request src register
    register_mark_used(registerFile, resultReg);

    //Move first argument into register (overwrite it)
    Token firstOperandToken = tokenise_request(text);
    tuple<bool, TOKEN_ENUM> operandResult = internal_load_operand(registerFile, resultReg, functionMetadata, firstOperandToken);
    if(get<0>(operandResult) == false) {
        return make_tuple(false, 0);
    }  
    
    Token nextToken = tokenise_request(text); //Either a operator or a terminal ']'
    if(nextToken.tokenID == TOK_BRACE_CLOSE_SQUARE) {
        return make_tuple(true, resultReg); 
    }

    //If more than 2 operands, request a second register
    bool expectOperator = true;
    TOKEN_ENUM expectedType = get<1>operandResult; //This is for type checking
    size_t storeReg = register_request(registerFile);
    register_mark_used(registerFile, storeReg);
    while(1) {

        if(expectOperator == true) {

            if(nextToken.tokenID == TOK_SYMBOL_PLUS) {
               if(expectedType == TOK_INT_IMM) {
                    ARCH_ADD_INT(resultReg, resultReg, storeReg);
               } else if(expectedType == TOK_FLOAT_IMM) {
                    ARCH_ADD_FLOAT(resultReg, resultReg, storeReg);
               } else {
                   cout << "ERROR: Invalid compilation state" << endl;
                   return make_tuple(false, 0);
               }

            } else if(nextToken.tokenID == TOK_SYMBOL_MINUS) {
               if(expectedType == TOK_INT_IMM) {
                    ARCH_SUB_INT(resultReg, resultReg, storeReg);
               } else if(expectedType == TOK_FLOAT_IMM) {
                    ARCH_SUB_FLOAT(resultReg, resultReg, storeReg);
               } else {
                   cout << "ERROR: Invalid compilation state" << endl;
                   return make_tuple(false, 0);
               }

            } else if(nextToken.tokenID == TOK_SYMBOL_MUL) {
               if(expectedType == TOK_INT_IMM) {
                    ARCH_MUL_INT(resultReg, resultReg, storeReg);
               } else if(expectedType == TOK_FLOAT_IMM) {
                    ARCH_MUL_FLOAT(resultReg, resultReg, storeReg);
               } else {
                   cout << "ERROR: Invalid compilation state" << endl;
                   return make_tuple(false, 0);
               }

            } else if(nextToken.tokenID == TOK_SYMBOL_DIV) {
               if(expectedType == TOK_INT_IMM) {
                    ARCH_DIV_INT(resultReg, resultReg, storeReg);
               } else if(expectedType == TOK_FLOAT_IMM) {
                    ARCH_DIV_FLOAT(resultReg, resultReg, storeReg);
               } else {
                   cout << "ERROR: Invalid compilation state" << endl;
                   return make_tuple(false, 0);
               }

            } else if(nextToken.tokenID == TOK_BRACE_CLOSE_SQUARE) {
                return make_tuple(true, resultReg);
            } else {
                cout << "ERROR: Invalid operator" << endl;
                return make_tuple(false, 0);

            }
        } else {
            Token token = tokenise_request(text);
            tuple<bool, TOKEN_ENUM> operandResult = internal_load_operand(registerFile, resultReg, functionMetadata, token);
            if(get<0>operandResult == false) {
                return make_tuple(false, 0);
            }
            
            if(get<1>operandResult != expectedType) {
                return make_tuple(false, 0);
            }
        }
        expectOperator = !expectOperator;
    }
    register_mark_free(registerFile, storeReg);

    return make_tuple(true, resultReg);
}


/*
//Uses intertwined stack to handle BODMAS
tuple<bool, size_t> expression_handling_ordered_evaluation(string &text) {

    size_t resultReg = register_request(registerFile);

    //Use SYA



    return resultReg;
}
*/






