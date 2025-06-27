#include "tokenise.h++"



//Print token vector
void tokenise_print_tokens(vector<Token> programTokens) {

	for(int i = 0; i < programTokens.size(); i++) {
		cout << "Token: " << global_reservedTokens[programTokens[i].type] << " || String: " << programTokens[i].str << endl;
	}

	return;
}

//Generate the token map
unordered_map<string, TOKENS> tokenise_generate_token_map(void) {
	unordered_map<string, TOKENS> tokenMap;

	for(long long int i = 0; i < global_reservedTokens.size(); i++) {
		tokenMap[global_reservedTokens[i]] = (TOKENS)i;
	}

	return tokenMap;
}

//Tokenise a string, return a vector of tokens for the entire program
vector<Token> tokenise_tokenise(string &tokenStream, unordered_map<string, TOKENS> tokenMap) {
	vector<Token> programTokens;

	//If token contains symbols - stop upon encountering non-symbol
	//If token contains no symbols - stop upon encountering symbol

	for(long long int i = 0; i < tokenStream.length(); i++) {
		Token currentToken;
		string buffer = "";

	}

	return programTokens;
}














