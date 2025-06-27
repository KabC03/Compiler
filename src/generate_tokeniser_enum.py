import sys;
import os;

fileName = "./src/tokens";


internalTokens = {
    "TOKEN_INVALID" : "TOK_INVALID",
}
specifierTokens = {
    "SPECIFIER_IMMEDIATE" : "SPECIFIER_IMMEDIATE",
    "SPECIFIER_IDENTIFIER" : "SPECIFIER_IDENTIFIER",
};
reservedTokens = {

    "fn" : "KEYWORD_FN",
    "call" : "KEYWORD_CALL",
    "return" : "KEYWORD_RETURN",
    "if" : "KEYWORD_IF",
    "elif" : "KEYWORD_ELIF",
    "while" : "KEYWORD_WHILE",
    "decl" : "KEYWORD_DECL",

    "," : "DELIMITER_COMMA",
    ";" : "DEMIMITER_SEMICOLON",
    "(" : "DELIMETER_OPEN_BRACE",
    ")" : "DELIMETER_CLOSE_BRACE",
    "{" : "DELIMETER_OPEN_CURLEY_BRACE",
    "}" : "DELIMETER_CLOSE_CURLEY_BRACE",
    "[" : "DELIMETER_OPEN_SQUARE_BRACE",
    "]" : "DELIMETER_CLOSE_SQUARE_BRACE",

    "@" : "OPERATOR_INDIRECTION",
    "#" : "OPERATOR_ADDRESS_OF",
    "=" : "OPERATOR_ASSIGNMENT",
    "+" : "OPERATOR_PLUS",
    "-" : "OPERATOR_SUBTRACT",
    "*" : "OPERATOR_MULTIPLY",
    "/" : "OPERATOR_DIVIDE",
    "==" : "OPERATOR_EQUAL_TO",
    ">=" : "OPERATOR_GREATER_EQUAL_TO",
};




def write_to_c_file(cFileName : str, hFileName : str, verboseOutput : bool) -> int:
    longestKeyLength = len(max(reservedTokens.keys(), key = len));


    try:
        with open(str(cFileName), 'w') as cFile:
            cFile.write(f"#include \"{hFileName}\"\n");
            cFile.write(f"#include <string>\n");
            cFile.write(f"#include <vector>\n\n");
            cFile.write(f"extern std::vector<std::string> = {{\n")
            for key, value in reservedTokens.items():
                cFile.write(f"\t\"{key}\", {" " * (longestKeyLength - len(value))}//{value}\n");
            cFile.write(f"}};\n\n")
            return 0;

    except OSError as e:
        print(f"File open error for c file: {e}");
        return 1;



def write_to_h_file(hFileName : str, verboseOutput : bool) -> int:
    try:
        with open(str(hFileName), 'w') as hFile:
            hFile.write(f"#ifndef TOKENS_HPP\n");
            hFile.write(f"#define TOKENS_HPP\n\n");
            hFile.write("typedef enum TOKENS : int {\n");

            index = -1;
            hFile.write("\n\t//Internal tokens\n");
            for key, value in internalTokens.items():

                hFile.write(f"\t{value} = {index}, //'{key}'\n")
                index -= 1;
            
            hFile.write("\n\t//Specifier tokens\n");
            for key, value in specifierTokens.items():
                hFile.write(f"\t{value} = {index}, //'{key}'\n")
                index -= 1;

            hFile.write("\n\t//Reserved tokens\n");
            index = 0;
            for key, value in reservedTokens.items():
                hFile.write(f"\t{value} = {index}, //'{key}'\n")
                index += 1;
            
            hFile.write("\n\n} TOKENS;\n");
            hFile.write("\n#endif\n\n");
            return 0;

    except OSError as e:
        print(f"File open error for h file: {e}");
        return 1;


def check_cmd_args(argv : list[str]) -> tuple[int, bool, str, str]:
    
    verboseOutput = False;
    cFileName = "";
    hFileName = "";
    
    #Process args
    for item in argv:
        item = item.strip();
        if item in __file__:
            pass;
        elif item == "-v" and verboseOutput == False:
            verboseOutput = True;
        elif item.endswith((".cpp" ,".c++", ".cc")) == True and cFileName == "":
            cFileName = item;
        elif item.endswith((".hpp" ,".h++", ".hh")) == True and hFileName == "":
            hFileName = item;
        else:
            print(f"{__file__} Command line argument error: {item}");
            print(f"python3 {__file__} [-options] <C++ file name> <H++ file name>\n");
            print("\t-v\t::\tShow verbose output");

            return 1, verboseOutput, cFileName, hFileName;

    #Check file names were recieved
    if cFileName == "" or hFileName == "":
            print(f"{__file__} Command line argument error");
            print(f"python3 {__file__} [-options] <C++ file name> <H++ file name>\n");
            print("\t-v\t::\tShow verbose output");
            return 1, verboseOutput, cFileName, hFileName;

    return 0, verboseOutput, cFileName, hFileName;


def main(argv : list[str]) -> int:

    returnVal, verboseOutput, cFileName, hFileName = check_cmd_args(argv); 
    if returnVal != 0:
        return 1;

    if write_to_c_file(cFileName, hFileName, verboseOutput) != 0:
        return 2;

    if write_to_h_file(hFileName, verboseOutput) != 0:
        return 3;

    return 0;


if __name__ == "__main__":
    sys.exit(main(sys.argv));


