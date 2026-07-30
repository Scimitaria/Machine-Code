#include "parse_ops.h"

const char *const condStrings[] = {
    [eq] = "eq",
    [ne] = "ne",
    [ge] = "ge",
    [lt] = "lt",
    [gt] = "gt",
    [le] = "le"
};

uint32_t parse_add(FILE* input){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"Destination for add must be a register");
    skipToNextToken(input);
    op op1 = parse_op(input);
    assertCondition(op1.isReg,"First operand for add must be a register");
    skipToNextToken(input);
    op op2 = parse_op(input);
    skipToNextToken(input);

    bool isImmediate = !op2.isReg;
    bool isX = dest.isX || op1.isX || op2.isX;
     //printf("#ADD %d,%d,%d; isImmediate: %d, isX: %d\n", dest.val,op1.val,op2.val,isImmediate,isX);
    return add(dest.val,op1.val,op2.val,isImmediate,isX);
}
uint32_t parse_adr(FILE* input){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"ADR destination must be a register");
    skipToNextToken(input);
    int32_t offset = get_offset(input);
    //printf("#ADR %d, %d\n", dest.val, offset);
    skipToNextToken(input);
    return adr(dest.val,offset);
}
uint32_t parse_b(FILE* input){
    int32_t offset = get_offset(input)/4;
    skipToNextToken(input);
    return b(offset);
}
uint32_t parse_b_cond(FILE* input){
    cond con = cond_count;
    char condStr[3];
    //printf(condStr,"%c%c", get(input), get(input));
    for(int i=0; i<cond_count; i++){
        if(strcmp(condStr,condStrings[i])==0){
            con = (cond)i;
            break;
        }
    }
    if(con == cond_count) error("Invalid condition in b.cond");
    int32_t offset = get_offset(input)/4;
    skipToNextToken(input);
    return b_cond(con,offset);
}
uint32_t parse_cbz(FILE* input, bool isCBNZ){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"Destination for CBZ/CBNZ must be a register");
    skipToNextToken(input);
    int32_t offset = get_offset(input);
    skipToNextToken(input);
    return cbz(dest.val,offset,isCBNZ,dest.isX);
}
uint32_t parse_cmp(FILE* input){
    op op1 = parse_op(input);
    assertCondition(op1.isReg,"First operand for cmp must be a register");
    skipToNextToken(input);
    op op2 = parse_op(input);
    skipToNextToken(input);

    bool isImmediate = !op2.isReg;
    bool isX = op1.isX || op2.isX;
    //printf("CMP %d, %d; isImmediate: %d, isX: %d\n", op1.val, op2.val, isImmediate, isX);
    return cmp(op1.val,op2.val,isImmediate,isX);
}
uint32_t parse_udiv(FILE* input){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"Destination for div must be a register");
    skipToNextToken(input);
    op op1 = parse_op(input);
    assertCondition(op1.isReg,"First operand for div must be a register");
    skipToNextToken(input);
    op op2 = parse_op(input);
    assertCondition(op2.isReg,"Second operand for div must be a register");
    skipToNextToken(input);

    bool isX = dest.isX || op1.isX || op2.isX;
    return udiv(dest.val,op1.val,op2.val,isX);
}
uint32_t parse_ldrb(FILE* input){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"LDRB destination must be a register");
    skipToNextToken(input);
    assertCondition(get(input)=='[',"Incorrect formatting on LDRB args");
    skipToNextToken(input);
    op op1 = parse_op(input);
    assertCondition(op1.isReg,"First LDRB operand must be a register");
    skipToNextToken(input);
    if(peek(input)==']'){
        getc(input);
        skipToNextToken(input);
        bool isX = dest.isX || op1.isX;
        return ldrb_nb(dest.val,op1.val,isX);
    } else {
        op op2 = parse_op(input);
        assertCondition(op2.isReg,"Second LDRB operand must be a register");
        skipToNextToken(input);
        bool isX = dest.isX || op1.isX || op2.isX;
        return ldrb(dest.val,op1.val,op2.val,isX);
    }
}
uint32_t parse_mov(FILE* input){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"Destination for mov must be a register");
    skipToNextToken(input);
    op src = parse_op(input);
    skipToNextToken(input);

    bool isX = dest.isX || src.isX;
     //printf("#MOV %d,%d; isImmediate: %d, isX: %d\n", dest.val,src.val,!src.isReg,isX);
    if(!src.isReg) return mov(dest.val,src.val,isX);
    else return movreg(dest.val,src.val,isX);
}
uint32_t parse_msub(FILE* input){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"Destination for add must be a register");
    skipToNextToken(input);
    op op1 = parse_op(input);
    assertCondition(op1.isReg,"First operand for add must be a register");
    skipToNextToken(input);
    op op2 = parse_op(input);
    assertCondition(op2.isReg,"Second operand for add must be a register");
    skipToNextToken(input);
    op op3 = parse_op(input);
    assertCondition(op3.isReg,"Third operand for add must be a register");
    skipToNextToken(input);

    bool isX = dest.isX || op1.isX || op2.isX;
     //printf("#ADD %d,%d,%d, isX: %d\n", dest.val,op1.val,op2.val,isX);
    return msub(dest.val,op1.val,op2.val,op3.val,isX);
}
uint32_t parse_mul(FILE* input){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"Destination for mul must be a register");
    skipToNextToken(input);
    op op1 = parse_op(input);
    assertCondition(op1.isReg,"First operand for mul must be a register");
    skipToNextToken(input);
    op op2 = parse_op(input);
    assertCondition(op2.isReg,"Second operand for mul must be a register");
    skipToNextToken(input);

    bool isX = dest.isX || op1.isX || op2.isX;
     //printf("#MUL %d,%d,%d, isX: %d\n", dest.val,op1.val,op2.val,isX);
    return mul(dest.val,op1.val,op2.val,isX);
}
uint32_t parse_strb(FILE* input){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"STRB destination must be a register");
    skipToNextToken(input);
    assertCondition(get(input)=='[',"Incorrect formatting on STRB args");
    skipToNextToken(input);
    op op1 = parse_op(input);
    assertCondition(op1.isReg,"First STRB operand must be a register");
    skipToNextToken(input);
    if(peek(input)==']'){
        getc(input);
        skipToNextToken(input);
        bool isX = dest.isX || op1.isX;
        return strb_nb(dest.val,op1.val,isX);
    } else {
        op op2 = parse_op(input);
        assertCondition(op2.isReg,"Second STRB operand must be a register");
        skipToNextToken(input);
        bool isX = dest.isX || op1.isX || op2.isX;
        return strb(dest.val,op1.val,op2.val,isX);
    }
}
uint32_t parse_sub(FILE* input){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"Destination for sub must be a register");
    skipToNextToken(input);
    op op1 = parse_op(input);
    assertCondition(op1.isReg,"First operand for sub must be a register");
    skipToNextToken(input);
    op op2 = parse_op(input);
    skipToNextToken(input);

    bool isImmediate = !op2.isReg;
    bool isX = dest.isX || op1.isX || op2.isX;
     //printf("#SUB %d,%d,%d; isImmediate: %d, isX: %d\n", dest.val,op1.val,op2.val,isImmediate,isX);
    return sub(dest.val,op1.val,op2.val,isImmediate,isX);
}
uint32_t parse_svc(FILE* input){
    parse_op(input);
    skipToNextToken(input);
     //printf("#SVC #0x80\n");
    return svc;
}
uint32_t parse_string(FILE* input){
    enum {
        READ_DONE = 0,     // no word produced
        READ_WORD = 1,     // produced a word, more may follow
        READ_LAST = 2      // produced the final word
    };
    int status;

    skipToNextToken(input);
    getc(input); //skip "
    uint32_t word;
    do {
        status = read_u32(input, &word);
        if (status) printf("0x%08X\n", word);
    } while (status == READ_WORD);
    skipToNextToken(input);
    return 0x00000000; //we're  printing here, so want to return a nonfunctional value
}
