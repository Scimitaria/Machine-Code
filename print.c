#include "print.h"

void print_binary(u_int32_t code, int header) {
    if(header) printf("0b");
    for (int i = 31; i >= 0; i--) {
        u_int32_t bit = (code >> i) & 1;
        printf("%u", bit);
    }
    printf("\n");
}
void print_hex(u_int32_t code){
    printf("0x%" PRIX32 "\n",code);
}