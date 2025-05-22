#ifndef TOKENISE_HPP
#define TOKENISE_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <iostream>
using namespace std;

typedef struct Token {

	TOKEN_TYPE type;	
	string str;

} Token;



void tokenise_print_tokens(vector<Token> programTokens);
unordered_map<string, int> tokenise_generate_token_map(void);
vector<Token> tokenise_tokenise(string &tokenStream, unordered_map<string, int> tokenMap);













#endif

