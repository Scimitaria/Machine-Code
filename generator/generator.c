#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define nop 0xD503201F
#define ret 0xD65F03C0
#define svc 0xD4001001

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
uint32_t adr(size_t string_offset, uint8_t reg)
{
    int32_t off = (int32_t)string_offset;

    uint32_t immlo = off & 0x3;
    uint32_t immhi = (off >> 2) & 0x7FFFF;

    return 0x10000000
         | (immlo << 29)
         | (immhi << 5)
         | (reg & 0x1F);
}

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

int main(){
    print_hex(mov(1,21));;
    print_hex(add(2,1,27,1));
    print_hex(add(0,1,2,0));
    print_hex(ret);
    return 0;
}
