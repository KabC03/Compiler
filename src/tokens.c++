#include "./src/tokens.h++"

extern std::vector<std::string> global_reservedTokens = {
	"fn",        //KEYWORD_FN
	"call",      //KEYWORD_CALL
	"return",    //KEYWORD_RETURN
	"if",        //KEYWORD_IF
	"elif",      //KEYWORD_ELIF
	"while",     //KEYWORD_WHILE
	"decl",      //KEYWORD_DECL
	",",         //DELIMITER_COMMA
	";",         //DEMIMITER_SEMICOLON
	"(",         //DELIMETER_OPEN_BRACE
	")",         //DELIMETER_CLOSE_BRACE
	"{",         //DELIMETER_OPEN_CURLEY_BRACE
	"}",         //DELIMETER_CLOSE_CURLEY_BRACE
	"[",         //DELIMETER_OPEN_SQUARE_BRACE
	"]",         //DELIMETER_CLOSE_SQUARE_BRACE
	"@",         //OPERATOR_INDIRECTION
	"#",         //OPERATOR_ADDRESS_OF
	"=",         //OPERATOR_ASSIGNMENT
	"+",         //OPERATOR_PLUS
	"-",         //OPERATOR_SUBTRACT
	"*",         //OPERATOR_MULTIPLY
	"/",         //OPERATOR_DIVIDE
	"==",        //OPERATOR_EQUAL_TO
	">=",        //OPERATOR_GREATER_EQUAL_TO
};

