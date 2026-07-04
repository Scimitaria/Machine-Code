#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "asm_parser.h"

//fixed hexcodes
#define nop 0xD503201F //idle
#define ret 0xD65F03C0 //return
#define svc 0xD4001001 //syscall
#define sp (uint8_t)31 //stack pointer reg

//common opcodes for b.cond
typedef enum {
    eq = 0b0000, // ==
    ne = 0b0001, // !=
    ge = 0b1010, // >=
    lt = 0b1011, // <
    gt = 0b1100, // >
    le = 0b1101  // <=
} cond;

void print_binary(uint32_t code) {
    printf("0b");
    for (int i = 31; i >= 0; i--) {
        uint32_t bit = (code >> i) & 1;
        printf("%u", bit);
    }
    printf("\n");
}
void print_hex(u_int32_t code){
    printf("0x%" PRIX32 "\n",code);
}

//generates mov call
uint32_t mov(uint8_t reg, uint16_t val){
    uint32_t code = 0;

    uint8_t bitSize = 0b1; //64-bit
    code |= bitSize;

    code <<= 2;
    uint8_t opcode = 0b10; //MOV
    code |= opcode;

    code <<= 6;
    uint8_t moveType = 0b100101; //move wide
    code |= moveType;

    code <<= 2;
    uint8_t leftShift = 0b0; //none
    code |= leftShift;

    code <<= 16;
    code |= val; //value to load

    code <<= 5;
    code |= reg; //register 

    return code;
}

//generates adr call
uint32_t adr(uint8_t reg, int32_t string_offset){
    uint32_t immlo = string_offset & 0x3;
    uint32_t immhi = (string_offset >> 2) & 0x7FFFF;

    return 0x10000000
         | (immlo << 29)
         | (immhi << 5)
         | (reg & 0x1F);
}

/* MATH */
//generates add call
uint32_t add(uint8_t destination, uint8_t op1, uint16_t op2, int is_immediate){
    uint32_t code = 0;

    u_int8_t bitSize = 0b1; //64-bit
    code |= bitSize;

    code <<= 1;
    u_int8_t isSub = 0b0; //is add, not sub
    code |= isSub;

    code <<= 1;
    u_int8_t setFlags = 0b0; //do not set additional flags
    code |= setFlags;

    if(is_immediate){
        code <<= 6;
        uint16_t opcode = 0b100010; //immediate add
        code |= opcode;

        code <<= 13;
        code |= op2; //literal value to add

        code <<= 5;
        code |= op1; //register value to add

        code <<= 5;
        code |= destination; //register to add value into

        return code;
    } else {
        code <<= 5;
        uint8_t opcode = 0b01011; //add
        code |= opcode;

        code <<= 3;
        uint8_t shift = 0b000; //no shift
        code |= shift;

        code <<= 5;
        code |= op2; //register value to add

        code <<= 6;
        u_int8_t imm6 = 0b000000; //no additional flags
        code |= imm6;

        code <<= 5;
        code |= op1; //second register value to add

        code <<= 5;
        code |= destination; //register to add value into

        return code;
    }
}
//generates sub call
uint32_t sub(uint8_t destination, uint8_t op1, uint16_t op2, int is_immediate){
    uint32_t code = 0;

    u_int8_t bitSize = 0b1; //64-bit
    code |= bitSize;

    code <<= 1;
    u_int8_t isSub = 0b1; //is sub
    code |= isSub;

    code <<= 1;
    u_int8_t setFlags = 0b0; //do not set additional flags
    code |= setFlags;

    if(is_immediate){
        code <<= 6;
        uint16_t opcode = 0b100010; //immediate sub
        code |= opcode;

        code <<= 13;
        code |= op2; //literal value to sub

        code <<= 5;
        code |= op1; //register value to sub

        code <<= 5;
        code |= destination; //register to sub value into

        return code;
    } else {
        code <<= 5;
        uint8_t opcode = 0b01011; //sub
        code |= opcode;

        code <<= 3;
        uint8_t shift = 0b000; //no shift
        code |= shift;

        code <<= 5;
        code |= op2; //register value to sub

        code <<= 6;
        u_int8_t imm6 = 0b000000; //no additional flags
        code |= imm6;

        code <<= 5;
        code |= op1; //second register value to sub

        code <<= 5;
        code |= destination; //register to sub value into

        return code;
    }
}
//generates mul call
uint32_t mul(uint8_t destination, uint8_t op1, uint8_t op2){
    uint32_t code = 0;

    u_int8_t bitSize = 0b1; //64-bit
    code |= bitSize;

    code <<= 1;
    u_int8_t isMSub = 0b1; //MADD adds product into third register - in our case, xzr (0)
    code |= isMSub;

    code <<= 1;
    u_int8_t setFlags = 0b0; //do not set additional flags
    code |= setFlags;

    code <<= 5;
    uint8_t opcode = 0b11011; //mult
    code |= opcode;

    code <<= 3;
    uint8_t shift = 0b000; //no shift
    code |= shift;

    code <<= 5;
    code |= op1; //register value to mult

    code <<= 6;
    u_int8_t imm6 = 0b000000; //no additional flags
    code |= imm6;

    code <<= 5;
    code |= op2; //second register value to mult

    code <<= 5;
    code |= destination; //register to mult value into

    return code;
}
//generates MSUB call
uint32_t msub(uint8_t destination, uint8_t op1, uint8_t op2, uint8_t op3){
    uint32_t code = 0;

    u_int8_t bitSize = 0b1; //64-bit
    code |= bitSize;

    code <<= 7;
    uint8_t opcode = 0b0011011; //mult
    code |= opcode;

    code <<= 3;
    uint8_t shift = 0b000; //no shift
    code |= shift;

    code <<= 5;
    code |= op2; //second register value to mult

    code <<= 1;
    u_int8_t isMSub = 0b1; //MSUB subs product from third register
    code |= isMSub;

    code <<= 5;
    code |= op3; //minuend

    code <<= 5;
    code |= op1; //first register value to mult

    code <<= 5;
    code |= destination; //register to sub value into

    return code;
}
//generates div call
uint32_t div(uint8_t destination, uint8_t numerator, uint8_t denominator){
    uint32_t code = 0;

    code <<= 11;
    u_int16_t fixed = 0b10011010110; //don't have the fixed breakdown on this one
    code |= fixed;

    code <<= 5;
    code |= denominator;

    code <<= 6;
    uint8_t opcode = 0b000010; //UDIV
    code |= opcode;

    code <<= 5;
    code |= numerator;

    code <<= 5;
    code |= destination;

    return code;
}

//generates b (branch jump)
uint32_t b(int32_t offset){
    uint32_t code = 0b000101; //B opcode
    code <<= 26;
    code |= (offset & 0x3FFFFFF); // mask to 26 bits in case of negative numbers

    return code;
}
//generates b.cond (conditional jump)
uint32_t b_cond(int32_t offset, uint8_t cond) {
    uint32_t code = 0b01010100;      // B.cond opcode

    code <<= 19;
    code |= (offset & 0x7FFFF);      // mask to 19 bits

    code <<= 5;                      // shift left 1 extra to leave bit 4 = 0
    code |= (cond & 0xF);            // condition code in bits [3:0]
    return code;
}

//generates cmp (comparison, required for b.cond)
//this is actually just subtraction with flags on and discarding the result
uint32_t cmp(uint8_t op1, uint8_t op2){
    uint32_t code = 0;

    u_int8_t bitSize = 0b1; //64-bit
    code |= bitSize;

    code <<= 1;
    u_int8_t isSub = 0b1; //is sub
    code |= isSub;

    code <<= 1;
    u_int8_t setFlags = 0b1; //set flags for CMP
    code |= setFlags;

    code <<= 5;
    u_int8_t opcode = 0b01011; //opcode for add/sub
    code |= opcode;

    code <<= 3;
    u_int8_t shift = 0b000; //no shift
    code |= shift;

    code <<= 5;
    code |= op2; //register value to compare

    code <<= 6;
    u_int8_t imm6 = 0b000000; //no additional flags
    code |= imm6;

    code <<= 5;
    code |= op1; //second register value to compare

    code <<= 5;
    u_int8_t destination = 0b11111; // XZR ; throws result away
    code |= destination;
    
    return code;
}

int main(){
    print_hex(mov(0,1));
    print_hex(add(1,sp,0,1));
    print_hex(mov(2,8));
    print_hex(mov(16,4));
    print_hex(svc);
    return 0;
}
