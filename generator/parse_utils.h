#pragma once
#include "generator.h"

void skipWhitespace(FILE* input);
bool skipToNextToken(FILE* input);
char get(FILE* input);
int32_t get_offset(FILE* input);
