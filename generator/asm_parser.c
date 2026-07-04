#include "asm_parser.h"

bool isInt(char* code){
    regex_t regex;
    bool isInt;

    if(regcomp(&regex, "^#[0-9]+$", REG_EXTENDED)!=0) perror("regcomp");
    isInt = regexec(&regex, code, 0, NULL, 0) == 0;

    regfree(&regex);
    return isInt;
}
bool isReg(char* code){
    regex_t regex;
    bool isInt;

    if(regcomp(&regex, "^x[0-9]+$", REG_EXTENDED)!=0) perror("regcomp");
    isInt = regexec(&regex, code, 0, NULL, 0) == 0;

    regfree(&regex);
    return isInt;
}

void parseFile(char* fpath){
    FILE *file = fopen(fpath, "r");
    if (file == NULL) perror("Error opening file");

    fclose(file);
}
