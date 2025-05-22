#ifndef TOKENS_H
#define TOKENS_H
#include <string>
#include <vector>
using namespace std;
#define NUM_TOKENS 20
using namespace std;

extern const vector<string>tokens
typedef enum TOKEN_TYPE: int {
	TOK_INV = -1,
	TOK_IMM = -2,
	TOK_IDEN = -3,
	TOK_FN = 0, //0 ::  FN
	TOK_CALL = 1, //1 ::  CALL
	TOK_IF = 2, //2 ::  IF
	TOK_ELIF = 3, //3 ::  ELIF
	TOK_ELSE = 4, //4 ::  ELSE
	TOK_WHILE = 5, //5 ::  WHILE
	TOK_DECL = 6, //6 ::  DECL
	TOK_= = 7, //7 ::  =
	TOK_+ = 8, //8 ::  +
	TOK_- = 9, //9 ::  -
	TOK_* = 10, //10 ::  *
	TOK_/ = 11, //11 ::  /
	TOK_( = 12, //12 ::  (
	TOK_) = 13, //13 ::  )
	TOK_{ = 14, //14 ::  {
	TOK_} = 15, //15 ::  }
	TOK_[ = 16, //16 ::  [
	TOK_] = 17, //17 ::  ]
	TOK_== = 18, //18 ::  ==
	TOK_>= = 19, //19 ::  >=
} TOKEN_TYPE;
#endif
