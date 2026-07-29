#pragma once
#include "../print.h"
#include <stdint.h>
#include <stdbool.h>

//fixed hexcodes
#define nop 0xD503201F //idle
#define ret 0xD65F03C0 //return
#define svc 0xD4001001 //syscall

//registers
#define sp (uint8_t)31 //stack pointer reg
#define xzr (uint8_t)31 //zero register???

//common opcodes for b.cond
typedef enum {
    eq = 0b0000, // ==
    ne = 0b0001, // !=
    ge = 0b1010, // >=
    lt = 0b1011, // <
    gt = 0b1100, // >
    le = 0b1101, // <=
    cond_count
} cond;

uint32_t mov(uint8_t reg, uint16_t val, bool isX);
uint32_t movreg(uint8_t destination, uint8_t source, bool isX);
uint32_t adr(uint8_t reg, int32_t string_offset);
uint32_t add(uint8_t destination, uint8_t op1, uint16_t op2, bool is_immediate, bool isX);
uint32_t sub(uint8_t destination, uint8_t op1, uint16_t op2, bool is_immediate, bool isX);
uint32_t mul(uint8_t destination, uint8_t op1, uint8_t op2, bool isX);
uint32_t msub(uint8_t destination, uint8_t op1, uint8_t op2, uint8_t op3, bool isX);
uint32_t udiv(uint8_t destination, uint8_t numerator, uint8_t denominator, bool isX);
uint32_t b(int32_t offset);
uint32_t b_cond(uint8_t cond, int32_t offset);
uint32_t cbz(uint8_t reg, int32_t offset, bool isCBNZ, bool isX);
uint32_t cmp(uint8_t op1, uint16_t op2, bool is_immediate, bool isX);
uint32_t strb_nb(uint8_t source, uint8_t base, bool isX);
uint32_t strb(uint8_t destination, uint8_t base, uint8_t offset, bool isX);
uint32_t ldrb_nb(uint8_t destination, uint8_t base, bool isX);
uint32_t ldrb(uint8_t destination, uint8_t base, uint8_t offset, bool isX);
