import sys;
import os;

fileName = "./src/tokens";
specifiers = [

	"TOK_INV", "TOK_IMM", "TOK_IDEN",
];
tokens = [
	"FN", "RETURN", "CALL", "IF", "ELIF", "ELSE", "WHILE", "DECL", ",", ";", "@", "#", "=", "+", "-", "*", "/", "(", ")", "{", "}", "[", "]", "==", ">=",
];





"""
    @brief :: Generate tokens.c++ and tokens.h++ for tokeniser structure
              based on supplied tokens[] and specifiers[] in this file
"""
def main() -> int:

    try:
        with open(str(fileName) + ".h++", 'w') as hFile, open(str(fileName) + ".c++", 'w') as cFile:

            cFile.write("#include \"tokens.h++" + "\"\n\n");


            cFile.write("const vector<string>tokens = {\n");


            hFile.write("#ifndef TOKENS_H\n");
            hFile.write("#define TOKENS_H\n");
            hFile.write("#include <string>\n");
            hFile.write("#include <vector>\n");


	
            hFile.write("using namespace std;\n");
            hFile.write("#define NUM_TOKENS " + str(len(tokens)) + "\n");
            hFile.write("using namespace std;\n\n");
            hFile.write("extern const vector<string>tokens\n");
            hFile.write("typedef enum TOKEN_TYPE: int {\n");

            index = -1;
            for item in specifiers:
                hFile.write("\t" + str(item) + " = " + str(index) + ",\n");
                index -= 1;
            
            index = 0;
            for item in tokens:

                hFile.write("\t" + str("TOK_" + item) + " = " + str(index) + ", //" + str(index) + " ::  " + str(item) + "\n");
                cFile.write("\t\"" + str(item) + "\", //" + str(index) + " :: " + str("TOK_" + item) + "\n");


                index += 1;

            hFile.write("} TOKEN_TYPE;\n");
            cFile.write("};\n");

            hFile.write("#endif\n");
            return 0;

    except OSError:
        print("Unable to open .h++ or .c++ file\n");
        return 1;






if __name__ == "__main__":
    sys.exit(main());


