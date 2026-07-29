#pragma once
#include "generator.h"
#include <stdlib.h>

typedef struct{
    int val;
    bool isReg;
    bool isX;
} op;

void assertCondition(bool condition, char* errmsg);
void skipWhitespace(FILE* input);
bool skipToNextToken(FILE* input);
char get(FILE* input);
int32_t get_offset(FILE* input);
op parse_op(FILE* input);
