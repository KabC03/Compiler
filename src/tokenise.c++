#include "tokenise.h++"



//Print token vector
void tokenise_print_tokens(vector<Token> programTokens) {

	for(int i = 0; i < programTokens.size(); i++) {
		cout << "Token: " << global_reservedTokens[programTokens[i].type] << " || String: " << programTokens[i].str << endl;
	}

	return;
}

//Generate the token map
unordered_map<string, int> tokenise_generate_token_map(void) {
	unordered_map<string, int> tokenMap;

	for(int i = 0; i < global_reservedTokens.size(); i++) {
		tokenMap[global_reservedTokens[i]] = i;
	}

	return tokenMap;
}

//Tokenise a string, return a vector of tokens for the entire program
vector<Token> tokenise_tokenise(string &tokenStream, unordered_map<string, int> tokenMap) {
	vector<Token> programTokens;


	for(size_t i = 0; i < tokenStream.length(); i++) {
		char currentChar = tokenStream[i];
		bool firstCharIsPunct = ispunct(currentChar);
		
		bool containsLetters = false;
		bool containsNumbers = false;

		Token currentToken;
	
		string tokenBuffer;
		for(int j = i; i < tokenStream.length(); j++) {
			currentChar = tokenStream[j];

			containsLetters ||= isalpha(currentChar); 
			containsNumbers ||= isdigit(currentChar);

			if(ispunct(currentChar) != firstCharIsPunct) {
				break; //End of token
			} else {
				tokenBuffer += currentChar;
			}
		}

		auto it = tokenMap.find(tokenBuffer);
		if(it == tokenMap.end()) { 
			currentToken.type = it->second; //Keyword found
		} else {
			if(containsNumbers == true && containsLetters == false) {
				programTokens.type = TOK_IMM; //Immediate
			} else if(containsNumbers == true || containsLetters == true) {
				programTokens.type = TOK_IDEN; //Identifier
			} else {
				programTokens.type = TOK_INV;//Invalid
			}
			programTokens.str = tokenBuffer;
		}

		i = j;
		programTokens.push_back(currentToken);
	}

	return tokens;
}














