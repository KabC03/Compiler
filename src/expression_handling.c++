#include "expression_handling.h++"


//Handle expressions
//Handle both LR evaluation and also BODMAS
//Return register index where result is
//Functions are not allowed to be called in an expression



//Check if an operand is valid
tuple<bool, TOKEN_ENUM> internal_load_operand(size_t registerIndex, FunctionMetadata &functionMetadata, Token &token, TOKEN_ENUM expectedType) {

    if(token.tokenID == TOK_IDENTIFIER) {
    
        
        auto itV = functionMetadata.variableMap.find(token.tokenString);
        if(itV != functionMetadata.variableMap.end()) {
            //Found variable
            VariableMetadata variable = itV->second; 
            register_load_var_to_reg(registerIndex, variable, false);
            return make_tuple(true, variable.dataType);
        } else {
            cout << "Unrecognised variable" << endl;
            return make_tuple(false, TOK_INVALID);
        }
        
    } else if(token.tokenID == TOK_KEYWORD_INT) {
        ARCH_LOAD_INT_TO_REG(registerIndex, token.tokenString);
        return make_tuple(true, TOK_TYPE_INT);
    } else if(token.tokenID == TOK_TYPE_PTR_REF) {
        ARCH_LOAD_INT_TO_REG(registerIndex, token.tokenString);
        ARCH_ADD_BPTR(registerIndex);
        return make_tuple(true, TOK_TYPE_INT);
    } else if(token.tokenID == TOK_TYPE_PTR_DEREF) {
        if(expectedType == TOK_TYPE_INT) {
            ARCH_LOAD_INT_TO_REG(registerIndex, token.tokenString);
        } else if(expectedType == TOK_TYPE_FLOAT) {
            ARCH_LOAD_FLOAT_TO_REG(registerIndex, token.tokenString);
        } else {
            cout << "ERROR: Invalid compilation state" << endl;
            return make_tuple(false, TOK_INVALID);
        }
        return make_tuple(true, expectedType);
    } else if(token.tokenID == TOK_KEYWORD_FLOAT) {
        ARCH_LOAD_FLOAT_TO_REG(registerIndex, token.tokenString);
        return make_tuple(true, TOK_TYPE_FLOAT);
    } else {
        cout << "Unrecognised datatype" << endl;
        return make_tuple(false, TOK_INVALID);
    }
    return make_tuple(false, TOK_INVALID);
}



//Uses two accumulator registers <success, resultRegister> NOTE: RESULT REGISTER MUSE BE EXPLICITLY MARKED AS FREE AFTER BEING USED
tuple<bool, size_t> expression_handling_lr_evaluation(string &text, FunctionMetadata &functionMetadata) {

    size_t resultReg = register_request(); //Request src register
    register_mark_used(resultReg);

    //Move first argument into register (overwrite it)
    Token firstOperandToken = tokenise_request(text);


    TOKEN_ENUM expected = TOK_INVALID;
    if(firstOperandToken.tokenID == TOK_SYMBOL_REFERENCE) { //Take address
        Token firstOperandToken = tokenise_request(text);
        //Get address and convert variable token to an immediate of its address
        VariableMetadata variable;
        auto itV = functionMetadata.variableMap.find(firstOperandToken.tokenString);
        if(itV != functionMetadata.variableMap.end()) {
            //Found variable
            variable = itV->second; 
            return make_tuple(true, variable.dataType);
        } else {
            cout << "Unrecognised variable" << endl;
            return make_tuple(false, TOK_INVALID);
        }
        firstOperandToken.tokenID = TOK_TYPE_PTR_REF;
        firstOperandToken.tokenString = variable.stackOffset; //MUST ADD BASE POINTER

    } else if(firstOperandToken.tokenID == TOK_SYMBOL_DEREFERENCE) { //Read address
        Token firstOperandToken = tokenise_request(text);
        firstOperandToken.tokenID = TOK_TYPE_PTR_DEREF;


        VariableMetadata variable;
        auto itV = functionMetadata.variableMap.find(firstOperandToken.tokenString);
        if(itV != functionMetadata.variableMap.end()) {
            //Found variable
            variable = itV->second; 
            return make_tuple(true, variable.dataType);
        } else {
            cout << "Unrecognised variable" << endl;
            return make_tuple(false, TOK_INVALID);
        }
        if(variable.dataType == TOK_TYPE_INT) {
            expected = TOK_INT_IMM;
        } else if(variable.dataType == TOK_TYPE_FLOAT) {
            expected = TOK_FLOAT_IMM;
        } else {
            cout << "ERROR: Invalid compilation state" << endl;
            return make_tuple(false, TOK_INVALID);
        }

        //Load memory to store register
    }

    tuple<bool, TOKEN_ENUM> operandResult = internal_load_operand(resultReg, functionMetadata, firstOperandToken, expected);
    if(get<0>(operandResult) == false) {
        return make_tuple(false, 0);
    }  

    Token nextToken = tokenise_request(text); //Either a operator or a terminal ']'
    if(nextToken.tokenID == TOK_BRACE_CLOSE_SQUARE) {
        return make_tuple(true, resultReg); 
    }

    //If more than 2 operands, request a second register
    bool expectOperator = true;
    TOKEN_ENUM expectedType = get<1>(operandResult); //This is for type checking
    size_t storeReg = register_request();
    register_mark_used(storeReg);
    while(1) {

        if(expectOperator == true) {

            if(nextToken.tokenID == TOK_SYMBOL_PLUS) {
               if(expectedType == TOK_TYPE_INT) {
                    ARCH_ADD_INT(resultReg, resultReg, storeReg);
               } else if(expectedType == TOK_TYPE_FLOAT) {
                    ARCH_ADD_FLOAT(resultReg, resultReg, storeReg);
               } else {
                   cout << "ERROR: Invalid compilation state" << endl;
                   return make_tuple(false, 0);
               }

            } else if(nextToken.tokenID == TOK_SYMBOL_MINUS) {
               if(expectedType == TOK_TYPE_INT) {
                    ARCH_SUB_INT(resultReg, resultReg, storeReg);
               } else if(expectedType == TOK_TYPE_FLOAT) {
                    ARCH_SUB_FLOAT(resultReg, resultReg, storeReg);
               } else {
                   cout << "ERROR: Invalid compilation state" << endl;
                   return make_tuple(false, 0);
               }

            } else if(nextToken.tokenID == TOK_SYMBOL_MUL) {
               if(expectedType == TOK_TYPE_INT) {
                    ARCH_MUL_INT(resultReg, resultReg, storeReg);
               } else if(expectedType == TOK_TYPE_FLOAT) {
                    ARCH_MUL_FLOAT(resultReg, resultReg, storeReg);
               } else {
                   cout << "ERROR: Invalid compilation state" << endl;
                   return make_tuple(false, 0);
               }

            } else if(nextToken.tokenID == TOK_SYMBOL_DIV) {
               if(expectedType == TOK_TYPE_INT) {
                    ARCH_DIV_INT(resultReg, resultReg, storeReg);
               } else if(expectedType == TOK_TYPE_FLOAT) {
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
            if(token.tokenID == TOK_SYMBOL_REFERENCE) { //Take address
                Token token = tokenise_request(text);
                //Get address and convert variable token to an immediate of its address
                VariableMetadata variable;
                auto itV = functionMetadata.variableMap.find(token.tokenString);
                if(itV != functionMetadata.variableMap.end()) {
                    //Found variable
                    variable = itV->second; 
                    return make_tuple(true, variable.dataType);
                } else {
                    cout << "Unrecognised variable" << endl;
                    return make_tuple(false, TOK_INVALID);
                }
                token.tokenID = TOK_TYPE_PTR_REF;
                token.tokenString = variable.stackOffset; //MUST ADD BASE POINTER

            } else if(token.tokenID == TOK_SYMBOL_DEREFERENCE) { //Read address
                Token token = tokenise_request(text);
                token.tokenID = TOK_TYPE_PTR_DEREF;
        
        
                VariableMetadata variable;
                auto itV = functionMetadata.variableMap.find(token.tokenString);
                if(itV != functionMetadata.variableMap.end()) {
                    //Found variable
                    variable = itV->second; 
                    return make_tuple(true, variable.dataType);
                } else {
                    cout << "Unrecognised variable" << endl;
                    return make_tuple(false, TOK_INVALID);
                }
                if(variable.dataType == TOK_TYPE_INT) {
                    expected = TOK_INT_IMM;
                } else if(variable.dataType == TOK_TYPE_FLOAT) {
                    expected = TOK_FLOAT_IMM;
                } else {
                    cout << "ERROR: Invalid compilation state" << endl;
                    return make_tuple(false, TOK_INVALID);
                }
        
                //Load memory to store register
            }
            tuple<bool, TOKEN_ENUM> operandResult = internal_load_operand(resultReg, functionMetadata, token, expectedType);
            if(get<0>(operandResult) == false) {
                return make_tuple(false, 0);
            }
            
            if(get<1>(operandResult) != expectedType) {
                return make_tuple(false, 0);
            }
        }
        expectOperator = !expectOperator;
    }
    register_mark_free(storeReg);

    return make_tuple(true, resultReg);
}


/*
//Uses intertwined stack to handle BODMAS
tuple<bool, size_t> expression_handling_ordered_evaluation(string &text) {

    size_t resultReg = register_request();

    //Use SYA



    return resultReg;
}
*/






