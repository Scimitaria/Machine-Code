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
    return add(dest.val,op1.val,op2.val,isImmediate,isX);
}
uint32_t parse_adr(FILE* input){
    op dest = parse_op(input);
    assertCondition(dest.isReg,"ADR destination must be a register");
    int32_t offset = get_offset(input);
    skipToNextToken(input);
    return adr(dest.val,offset);
}
uint32_t parse_b(FILE* input){
    int32_t offset = get_offset(input);
    skipToNextToken(input);
    return b(offset);
}
uint32_t parse_b_cond(FILE* input){
    cond con = cond_count;
    char condStr[3];
    sprintf(condStr,"%c%c", get(input), get(input));
    for(int i=0; i<cond_count; i++){
        if(strcmp(condStr,condStrings[i])==0){
            con = (cond)i;
            break;
        }
    }
    if(con == cond_count) error("Invalid condition in b.cond");
    int32_t offset = get_offset(input);
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
    if(src.isReg) return mov(dest.val,src.val,isX);
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
    return sub(dest.val,op1.val,op2.val,isImmediate,isX);
}
uint32_t parse_svc(FILE* input){
    parse_op(input);
    skipToNextToken(input);
    return svc;
}
