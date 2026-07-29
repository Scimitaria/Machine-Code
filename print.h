#pragma once
#include <stdio.h>
#include <inttypes.h>

void print_hex(u_int32_t code);
void print_binary(u_int32_t code, int header);
char peek(FILE *input);
void skipLine(FILE* input);
