import sys;
import os;

fileName = "./src/tokens";
specifiers = [

    "TOK_FLOAT_IMM", "TOK_INT_IMM", "TOK_CHAR_IMM","TOK_STRING_IMM", "TOK_IDENTIFIER", "TOK_INVALID", "TOK_EOF",
    #TOK_INVALID is used to indicate failure
];
tokens = {
    # Keywords
        #Types
    "char" : "TOK_KEYWORD_CHAR",
    "int" : "TOK_KEYWORD_INT", 
    "float" : "TOK_KEYWORD_FLOAT",
    "=" : "TOK_SYMBOL_ASSIGNMENT",

        #Control flow
    "while" : "TOK_KEYWORD_WHILE", 
    "if" : "TOK_KEYWORD_IF", 
    "elif" : "TOK_KEYWORD_ELIF", 
    "else" : "TOK_KEYWORD_ELSE", 

        #Functions
    "return" : "TOK_KEYWORD_RETURN",

    # Symbols
    "+" : "TOK_SYMBOL_PLUS",
    "-" : "TOK_SYMBOL_MINUS",
    "*" : "TOK_SYMBOL_MUL",
    "/" : "TOK_SYMBOL_DIV",

    "==" : "TOK_SYMBOL_EQUALS",
    "!=" : "TOK_SYMBOL_NEQ",
    ">=" : "TOK_SYMBOL_GREQ",
    "<=" : "TOK_SYMBOL_LEQ",
    ">" : "TOK_SYMBOL_GREATER",
    "<" : "TOK_SYMBOL_LESS",

    "," : "TOK_SYMBOL_COMMA",
    ";" : "TOK_SEMICOLON",

        #Pointers
    "#" : "TOK_SYMBOL_REFERENCE",
    "@" : "TOK_SYMBOL_DEREFERENCE",

        # Braces
    "(" : "TOK_BRACE_OPEN_PAREN",
    ")" : "TOK_BRACE_CLOSE_PAREN",
    "{" : "TOK_BRACE_OPEN_CURLEY",
    "}" : "TOK_BRACE_CLOSE_CURLEY",
    "[" : "TOK_BRACE_OPEN_SQUARE",
    "]" : "TOK_BRACE_CLOSE_SQUARE",
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
                hFile.write("\t" + str(value) + " = " + str(index) + ", " + whiteSpace + "//" + str(index) + " ::  " + str(key) + "\n");
        
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


