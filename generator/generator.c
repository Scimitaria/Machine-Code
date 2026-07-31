#include "generator.h"

//generates mov call
uint32_t mov(uint8_t reg, uint16_t val, bool isX){
    uint32_t code = 0;

    code |= isX; //64-bit (x) or 32-bit (w)

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
//generates mov call with registers
uint32_t movreg(uint8_t destination, uint8_t source, bool isX){
    uint32_t code = 0;

    code <<= 1;
    code |= isX;

    code <<= 2;
    code |= 0b01; //ORR

    code <<= 5;
    uint8_t opcode = 0b01010; //logical-shifted-register
    code |= opcode;

    code <<= 2;
    uint8_t shift = 0b00;
    code |= shift;

    code <<= 1;
    uint8_t invertRM = 0b0; //1 makes ORN
    code |= invertRM;

    code <<= 5;
    code |= source;

    code <<= 6;
    uint8_t imm6 = 0b000000;
    code |= imm6;

    code <<= 5;
    code |= xzr;

    code <<= 5;
    code |= destination;

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
uint32_t add(uint8_t destination, uint8_t op1, uint16_t op2, bool is_immediate, bool isX, bool isSP){
    uint32_t code = 0;

    code |= isX;

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
    } else if (isSP) {
        // ADD (extended register) — required whenever op1 (Rn) or destination (Rd) is SP
        code <<= 5;
        code |= 0b01011; // opcode

        code <<= 2;
        code |= 0b00; // opt

        code <<= 1;
        code |= 0b1; // <-- the bit your old code hardcoded to 0

        code <<= 5;
        code |= op2; // Rm

        code <<= 3;
        code |= isX ? 0b011 : 0b010; // option: UXTX (64-bit) / UXTW (32-bit)

        code <<= 3;
        code |= 0b000; // imm3 shift amount

        code <<= 5;
        code |= op1; // Rn (can be SP here)

        code <<= 5;
        code |= destination; // Rd (can be SP here)

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
uint32_t sub(uint8_t destination, uint8_t op1, uint16_t op2, bool is_immediate, bool isX){
    uint32_t code = 0;

    code |= isX;

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
uint32_t mul(uint8_t destination, uint8_t op1, uint8_t op2, bool isX){
    uint32_t code = 0;

    code |= isX;              // sf (bit 31): 1 = 64-bit (X regs), 0 = 32-bit (W regs)

    code <<= 2;
    code |= 0b00;              // fixed bits (30-29)

    code <<= 5;
    code |= 0b11011;           // opcode: mul/madd family (28-24)

    code <<= 3;
    code |= 0b000;             // fixed bits (23-21)

    code <<= 5;
    code |= op2;               // Rm (20-16) - second source register

    code <<= 1;
    code |= 0b0;               // o0 (15): 0 = MADD (mul), 1 = MSUB

    code <<= 5;
    code |= 0b11111;           // Ra (14-10): XZR = register 31, not 0!

    code <<= 5;
    code |= op1;               // Rn (9-5) - first source register

    code <<= 5;
    code |= destination;       // Rd (4-0)

    return code;
}
//generates MSUB call
uint32_t msub(uint8_t destination, uint8_t op1, uint8_t op2, uint8_t op3, bool isX){
    uint32_t code = 0;

    code |= isX;

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
//generates udiv call
uint32_t udiv(uint8_t destination, uint8_t numerator, uint8_t denominator, bool isX){
    uint32_t code = 0;

    code <<= 1;
    code |= isX;

    code <<= 10;
    u_int16_t fixed = 0b0011010110; //don't have the fixed breakdown on this one
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

/* BRANCH */
//generates b (branch jump)
uint32_t b(int32_t offset){
    uint32_t code = 0b000101; //B opcode
    code <<= 26;
    code |= (offset & 0x3FFFFFF); // mask to 26 bits in case of negative numbers

    return code;
}
//generates b.cond (conditional jump)
uint32_t b_cond(uint8_t cond, int32_t offset){
    uint32_t code = 0b01010100;      // B.cond opcode

    code <<= 19;
    code |= (offset & 0x7FFFF);      // mask to 19 bits

    code <<= 5;                      // shift left 1 extra to leave bit 4 = 0
    code |= (cond & 0xF);            // condition code in bits [3:0]
    return code;
}
//generates cbz (compare and jump on zero)
uint32_t cbz(uint8_t reg, int32_t offset, bool isCBNZ, bool isX){
    uint32_t code = 0;

    code <<= 1;
    code |= isX;

    code <<= 6;
    uint8_t opcode = 0b011010; //CBZ/CBNZ
    code |= opcode;

    code <<= 1;
    code |= isCBNZ; //0 is CBZ, 1 is CBNZ

    //CBZ jump should be in instrs, not bits
    code <<= 19;
    code |= (offset & 0x7FFFF); // mask to 19 bits

    code <<= 5;
    code |= reg;

    return code;
}

//generates cmp (comparison, required for b.cond)
//this is actually just subtraction with flags on and discarding the result
uint32_t cmp(uint8_t op1, uint16_t op2, bool is_immediate, bool isX){
    uint32_t code = 0;

    code |= isX;

    code <<= 1;
    u_int8_t isSub = 0b1; //is sub
    code |= isSub;

    code <<= 1;
    u_int8_t setFlags = 0b1; //set flags for CMP
    code |= setFlags;

    if(is_immediate){
        code <<= 5;
        uint8_t opcode = 0b10001; //immediate add/subtract
        code |= opcode;

        code <<= 2;
        uint8_t shift = 0b00;
        code |= shift;

        code <<= 12;
        code |= op2;
    } else {
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
    }

    code <<= 5;
    code |= op1; //second register value to compare

    code <<= 5;
    u_int8_t destination = 0b11111; // XZR ; throws result away
    code |= destination;
    
    return code;
}

/* LOAD/STORE */
//generates strb (store byte) w/o bounds
uint32_t strb_nb(uint8_t source, uint8_t base, bool isX){
    uint32_t code = 0;

    code <<= 2;
    uint8_t size = 0b00; // always 00 for byte access; isX is irrelevant here
    code |= size;

    code <<= 1;
    uint8_t isStore = 0b1; //store
    code |= isStore;

    code <<= 5;
    uint8_t opcode = 0b11001; //load/store
    code |= opcode;

    code <<= 2;
    uint8_t high_bits = 0b00; //immediate high bits
    code |= high_bits;

    code <<= 12;
    uint16_t immediate = 0b000000000000; //immediate bits
    code |= immediate;

    code <<= 5;
    code |= base;

    code <<= 5;
    code |= source;

    return code;
}
//generates strb w/ bounds
uint32_t strb(uint8_t destination, uint8_t base, uint8_t offset, bool isX){
    uint32_t code = 0;

    code <<= 2;
    uint8_t size = 0b00; // always 00 for byte access; isX is irrelevant here
    code |= size;

    code <<= 9;
    uint16_t opcode = 0b111000001;
    code |= opcode;

    code <<= 5;
    code |= offset;

    code <<= 6;
    uint8_t options = 0b011010;
    code |= options;

    code <<= 5;
    code |= base;

    code <<= 5;
    code |= destination;

    return code;
}
//generates ldrb w/o bounds
uint32_t ldrb_nb(uint8_t destination, uint8_t base, bool isX){
    uint32_t code = 0;

    code <<= 2;
    uint8_t size = 0b00; // always 00 for byte access; isX is irrelevant here
    code |= size;

    code <<= 6;
    uint8_t opcode = 0b111001;
    code |= opcode;

    code <<= 2;
    uint8_t isLoad = 0b01;
    code |= isLoad;

    code <<= 12;
    uint16_t immediate = 0b000000000000;
    code |= immediate;

    code <<= 5;
    code |= base;

    code <<= 5;
    code |= destination;

    return code;
}
//generates ldrb w/ bounds
uint32_t ldrb(uint8_t destination, uint8_t base, uint8_t offset, bool isX){
    uint32_t code = 0;

    code <<= 2;
    uint8_t size = 0b00; // always 00 for byte access; isX is irrelevant here
    code |= size;

    code <<= 1;
    uint8_t isLoad = 0b1;
    code |= isLoad;

    code <<= 8;
    uint16_t opcode = 0b11000011;
    code |= opcode;

    code <<= 5;
    code |= offset;

    code <<= 6;
    uint8_t options = 0b011010;
    code |= options;

    code <<= 5;
    code |= base;

    code <<= 5;
    code |= destination;

    return code;
}