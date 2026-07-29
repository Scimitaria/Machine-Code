#include "parse_ops.h"

u_int32_t parse_add(FILE* input){
    return add();
}
u_int32_t parse_adr(FILE* input){
    return adr();
}
u_int32_t parse_b(FILE* input){
    return b();
}
u_int32_t parse_b_cond(FILE* input){
    return b_cond();
}
u_int32_t parse_cbz(FILE* input){
    return cbz();
}
u_int32_t parse_cmp(FILE* input){
    return cmp();
}
u_int32_t parse_udiv(FILE* input){
    return div();
}
u_int32_t parse_ldrb(FILE* input){
    return ldrb();
    return ldrb_nb();
}
u_int32_t parse_mov(FILE* input){
    return mov();
}
u_int32_t parse_msub(FILE* input){
    return msub();
}
u_int32_t parse_mul(FILE* input){
    return mul();
}
u_int32_t parse_strb(FILE* input){
    return strb();
    return strb_nb();
}
u_int32_t parse_sub(FILE* input){
    return sub();
}
u_int32_t parse_svc(FILE* input){
    return svc;
}
