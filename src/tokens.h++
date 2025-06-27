#ifndef TOKENS_HPP
#define TOKENS_HPP

typedef enum TOKENS : int {

	//Internal tokens
	TOK_INVALID = -1,                    //'TOKEN_INVALID'

	//Specifier tokens
	SPECIFIER_IMMEDIATE = -2,            //'SPECIFIER_IMMEDIATE'
	SPECIFIER_IDENTIFIER = -3,           //'SPECIFIER_IDENTIFIER'

	//Reserved tokens
	KEYWORD_FN = 0,                     //'fn'
	KEYWORD_CALL = 1,                   //'call'
	KEYWORD_RETURN = 2,                 //'return'
	KEYWORD_IF = 3,                     //'if'
	KEYWORD_ELIF = 4,                   //'elif'
	KEYWORD_WHILE = 5,                  //'while'
	KEYWORD_DECL = 6,                   //'decl'
	DELIMITER_COMMA = 7,                //','
	DEMIMITER_SEMICOLON = 8,            //';'
	DELIMETER_OPEN_BRACE = 9,           //'('
	DELIMETER_CLOSE_BRACE = 10,          //')'
	DELIMETER_OPEN_CURLEY_BRACE = 11,    //'{'
	DELIMETER_CLOSE_CURLEY_BRACE = 12,   //'}'
	DELIMETER_OPEN_SQUARE_BRACE = 13,    //'['
	DELIMETER_CLOSE_SQUARE_BRACE = 14,   //']'
	OPERATOR_INDIRECTION = 15,           //'@'
	OPERATOR_ADDRESS_OF = 16,            //'#'
	OPERATOR_ASSIGNMENT = 17,            //'='
	OPERATOR_PLUS = 18,                  //'+'
	OPERATOR_SUBTRACT = 19,              //'-'
	OPERATOR_MULTIPLY = 20,              //'*'
	OPERATOR_DIVIDE = 21,                //'/'
	OPERATOR_EQUAL_TO = 22,              //'=='
	OPERATOR_GREATER_EQUAL_TO = 23,      //'>='


} TOKENS;

#endif

