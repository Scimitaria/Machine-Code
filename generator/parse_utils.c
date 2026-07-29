#include "parse_utils.h"

void assertCondition(bool condition, char* errmsg){
  if (!condition) {
    fprintf(stderr, "Assertion failed: %s\n", errmsg);
    exit(EXIT_FAILURE);
  }
}

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

    return 0;
}

int readNumber(FILE* input, char c){
    int val = atoi(c);
    while(isdigit(c)){
        val *= 10;
        val += atoi(c);
        getc(input);
    }
    return val;
}
op parse_op(FILE* input){
    skipToNextToken(input);
    char c = tolower(peek(input));
    op o;

    switch(c){
        case '#':
            c = getc(input);
            o.isReg = false;
            o.isX = false;
            break;
        case 'x':
            c = getc(input);
            o.isReg = true;
            o.isX = true;
            break;
        case 'w':
            c = getc(input);
            o.isReg = true;
            o.isX = false;

    }
    if(!isdigit(c)) perror(sprintf("Attempted to read non-numeric value: %c", c));
    o.val = readNumber(input,c);
    return o;
}
