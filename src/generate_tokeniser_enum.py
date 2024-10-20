import sys;
import os;

fileName = "./src/tokens";
specifiers = [

    "TOK_FLOAT_IMM", "TOK_INT_IMM", "TOK_CHAR_IMM","TOK_STRING_IMM", "TOK_IDENTIFIER", "TOK_INVALID",
    #TOK_INVALID is used to indicate failure
];
tokens = {
    # Keywords
        #Types
    "char" : "TOK_KEYWORD_CHAR",
    "int" : "TOK_KEYWORD_INT", 
    "float" : "TOK_KEYWORD_FLOAT",
    "@" : "TOK_SYMBOL_REFERENCE",
    "let" : "TOK_KEYWORD_LET",
    "set" : "TOK_KEYWORD_SET",
    "=" : "TOK_SYMBOL_ASSIGNMENT",
        #Control flow
    "while" : "TOK_KEYWORD_WHILE", 
    "for" : "TOK_KEYWORD_FOR", 
    "if" : "TOK_KEYWORD_IF", 
    "elif" : "TOK_KEYWORD_ELIF", 
    "else" : "TOK_KEYWORD_ELSE", 
        #Functions
    "fn" : "TOK_KEYWORD_FN",
    "call" : "TOK_KEYWORD_CALL",
    "return" : "TOK_KEYWORD_RETURN",
    "->" : "TOK_KEYWORD_RETURN_SPECIFIER",

    # Arithmatic symbols
    "+" : "TOK_SYMBOL_PLUS",
    "-" : "TOK_SYMBOL_MINUS",
    "*" : "TOK_SYMBOL_MULTIPLY",
    "/" : "TOK_SYMBOL_DIVIDE",
    "&" : "TOK_SYMBOL_DEREFERENCE",
    "-" : "TOK_SYMBOL_MINUS",
    "==" : "TOK_SYMBOL_EQUALS",
    "!=" : "TOK_SYMBOL_NOT_EQUAL",

    # Braces
    "(" : "TOK_BRACE_OPEN_PAREN",
    ")" : "TOK_BRACE_CLOSE_PAREN",
};






def main() -> int:

    largestKeyLength = len(max(tokens.keys(), key=len));
    largestValueLength = len(max(tokens.values(), key=len));


    try:
        with open(str(fileName) + ".h++", 'w') as hFile, open(str(fileName) + ".c++", 'w') as cFile:

            cFile.write("//Generated by:" + str(os.path.basename(__file__) + "\n"));
            
            
            #cFile.write("#include \"" + str(fileName) + ".h++" + "\"\n\n");

            #Hard code this for now
            cFile.write("#include \"tokens.h++" + "\"\n\n");


            cFile.write("const string tokens[] = {\n");

            hFile.write("//Generated by:" + str(os.path.basename(__file__) + "\n"));
            hFile.write("#include <string>\n");
            hFile.write("#define NUM_TOKENS " + str(len(tokens)) + "\n");
            hFile.write("using namespace std;\n\n");
            hFile.write("extern const string tokens[];\n");
            hFile.write("typedef enum TOKEN_ENUM : int {\n");

            index = -1;
            for item in specifiers:
                hFile.write("\t" + str(item) + " = " + str(index) + ",\n");
                index -= 1;
            
            index = 0;
            for key, value in tokens.items():

                whiteSpace = (largestValueLength - len(value)) * " ";
                hFile.write("\t" + str(value) + ", " + whiteSpace + "//" + str(index) + " ::  " + str(key) + "\n");
        
                whiteSpace = ((largestKeyLength - len(key)) * " ");
                cFile.write("\t\"" + str(key) + "\", " + whiteSpace + "//" + str(index) + " :: " + str(value) + "\n");


                index += 1;

            hFile.write("} TOKEN_ENUM;\n");
            cFile.write("};\n");

            return 0;

    except:
        print("Unable to open .h++ or .c++ file\n");
        return 1;






if __name__ == "__main__":
    sys.exit(main());


