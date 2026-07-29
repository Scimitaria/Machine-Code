#pragma once
#include "generator.h"

u_int32_t parse_add(FILE* input);
u_int32_t parse_adr(FILE* input);
u_int32_t parse_b(FILE* input);
u_int32_t parse_b_cond(FILE* input);
u_int32_t parse_cbz(FILE* input);
u_int32_t parse_cmp(FILE* input);
u_int32_t parse_udiv(FILE* input);
u_int32_t parse_ldrb(FILE* input);
u_int32_t parse_mov(FILE* input);
u_int32_t parse_msub(FILE* input);
u_int32_t parse_mul(FILE* input);
u_int32_t parse_strb(FILE* input);
u_int32_t parse_sub(FILE* input);
u_int32_t parse_svc(FILE* input);
