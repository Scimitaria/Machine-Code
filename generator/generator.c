#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

//generates adr call
uint32_t adr(size_t string_offset, uint8_t rd)
{
    int32_t off = (int32_t)string_offset;

    uint32_t immlo = off & 0x3;
    uint32_t immhi = (off >> 2) & 0x7FFFF;

    return 0x10000000
         | (immlo << 29)
         | (immhi << 5)
         | (rd & 0x1F);
}

int main(){
    printf("0x%" PRIX32 "\n", adr(20,1));
    return 0;
}
