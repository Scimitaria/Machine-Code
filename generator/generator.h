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

const char *const condStrings[] = {
    [eq] = "eq",
    [ne] = "ne",
    [ge] = "ge",
    [lt] = "lt",
    [gt] = "gt",
    [le] = "le"
};
