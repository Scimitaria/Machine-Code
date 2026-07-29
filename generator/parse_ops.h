#pragma once
#include "parse_utils.h"
#include <string.h>

uint32_t parse_add(FILE* input);
uint32_t parse_adr(FILE* input);
uint32_t parse_b(FILE* input);
uint32_t parse_b_cond(FILE* input);
uint32_t parse_cbz(FILE* input, bool isCBNZ);
uint32_t parse_cmp(FILE* input);
uint32_t parse_udiv(FILE* input);
uint32_t parse_ldrb(FILE* input);
uint32_t parse_mov(FILE* input);
uint32_t parse_msub(FILE* input);
uint32_t parse_mul(FILE* input);
uint32_t parse_strb(FILE* input);
uint32_t parse_sub(FILE* input);
uint32_t parse_svc(FILE* input);
