#include "tokenise.h++"
#include "tokens.h++"
#include "parse.h++"
using namespace std;


int main(void) {

	string str = "decl abc";
	auto vec = tokenise_tokenise(str, tokenise_generate_token_map());
	tokenise_print_tokens(vec);

	return 0;
}
















