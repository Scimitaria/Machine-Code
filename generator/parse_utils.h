#pragma once
#include "generator.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdnoreturn.h>

typedef struct{
    int val;
    bool isReg;
    bool isX;
} op;

void assertCondition(bool condition, char* errmsg);
void skipWhitespace(FILE* input);
bool skipToNextToken(FILE* input);
char get(FILE* input);
int read_u32(FILE *fp, uint32_t *out);
int32_t get_offset(FILE* input);
op parse_op(FILE* input);
noreturn void error(char* msg);
