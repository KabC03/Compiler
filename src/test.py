




def parse_add(tokens, index):

    nextToken = tokens[index+=1];

    if nextToken == "=":
        parse_equals();
    elif nextToken == "-":
        parse_subtract();
    elif nextToken == "*" and tokens[index+1] == "c":
        parse_lookahead();












