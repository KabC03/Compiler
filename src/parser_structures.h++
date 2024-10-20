#ifndef PARSER_STRUCTURES_H
#define PARSER_STRUCTURES_H 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include "tokenise.h++"

using namespace std;

typedef struct Label {
    Token type; //Parent type (e.g if/elif/while/etc)

    string loopExit; //For jumping out of a loop
    string loopEntry; //For jumping back into a loop (empty for if statements)

} Label;
typedef struct Variable {

    string name; //Should be the hashmap key but keep it here for debugging
    size_t stackOffset; //Stack offset from current base
    Token type; //Variable type (used to invoke propper instructions like float or int add)

} Variable;

/*
Scope:
    Manage a hashmap for the function of interest. Add and remove variables
    based on scope using {} brackets

Structure:
    A structure is the minimum amount of code that can be parsed independently
    of any other code.

    E.g while(a + c - 100 >= 2 && y != 0) {...}
    It doesnt matter whats in the {...} as the assembly for the while structure
    can be genrated immediatly.

    Use structs to encapsulate each structure and parse it once its filled

*/



//Structures

typedef struct StructureExpression {
    //1 + x + abc + def;
    //End of expression when a unmatched ')' is found or a ';'
    //Or conditional operators like &&, ||, etc
    //Spill onto stack if running out of registers when doing BODMAS 

    //Store expression as RPN
    stack<Token> rpn;

} StructureExpression;




#endif 
