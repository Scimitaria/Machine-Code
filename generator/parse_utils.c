#include "parse_utils.h"

void skipWhitespace(FILE* input) {
    char c = getc(input);
    while (c != EOF && isspace(c)) c = getc(input);
    ungetc(c, input);
    return;
}
bool skipToNextToken(FILE* input){
    if(input==NULL) error("invalid file in skipToNextToken");
    char c = getc(input);
    while(isspace(c) || c == '/' || c == ',') {
        if(c == '/') skipLine(input);
        else skipWhitespace(input);
        c = getc(input);
    }
    bool cont = c != EOF;
    ungetc(c, input);
    return cont;
}

char get(FILE* input){
    return tolower(getc(input));
}

int32_t get_offset(FILE* input){
    FILE* BOF = input;
    rewind(BOF); //start of file
}
