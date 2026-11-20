#include "parse_ops.h"

u_int32_t readLine(FILE* input){
    for(;;){
        int c;
        while((c = getc(input)) != EOF && isspace(c));
        if(c == EOF) return 0x00000000;

        switch(tolower(c)){
            case 'a': //ADD, ADR
                if(eat(input,'d')){
                    if(eat(input,'d')){ if(endsMnemonic(input)) return parse_add(input); }
                    else if(eat(input,'r')){ if(endsMnemonic(input)) return parse_adr(input); }
                }
                break;

            case 'b': //B, BL, B.COND
                if(endsMnemonic(input)) return parse_b(input);
                if(eat(input,'l')){ if(endsMnemonic(input)) return parse_bl(input); }
                else if(eat(input,'.')) return parse_b_cond(input);
                break;

            case 'c': //CBZ, CBNZ, CMP
                if(eat(input,'b')){
                    if(eat(input,'z')){ if(endsMnemonic(input)) return parse_cbz(input,false); }
                    else if(eatStr(input,"nz")){ if(endsMnemonic(input)) return parse_cbz(input,true); }
                }
                else if(eatStr(input,"mp") && endsMnemonic(input)) return parse_cmp(input);
                break;

            case 'd': //DIV
                if(eatStr(input,"iv") && endsMnemonic(input)) return parse_udiv(input);
                break;

            case 'l': //LDRB
                if(eatStr(input,"drb") && endsMnemonic(input)) return parse_ldrb(input);
                break;

            case 'm': //MOV, MSUB, MUL
                if(eat(input,'o')){ if(eat(input,'v') && endsMnemonic(input)) return parse_mov(input); }
                else if(eat(input,'s')){ if(eatStr(input,"ub") && endsMnemonic(input)) return parse_msub(input); }
                else if(eat(input,'u')){ if(eat(input,'l') && endsMnemonic(input)) return parse_mul(input); }
                break;

            case 'n': //NOP
                if(eatStr(input,"op") && endsMnemonic(input)) return nop;
                break;

            case 'r': //RET
                if(eatStr(input,"et") && endsMnemonic(input)) return ret;
                break;

            case 's': //STRB, SUB, SVC
                if(eat(input,'t')){ if(eatStr(input,"rb") && endsMnemonic(input)) return parse_strb(input); }
                else if(eat(input,'u')){ if(eat(input,'b') && endsMnemonic(input)) return parse_sub(input); }
                else if(eat(input,'v')){ if(eat(input,'c') && endsMnemonic(input)) return parse_SVC(input); }
                break;

            case 'u': //UDIV
                if(eatStr(input,"div") && endsMnemonic(input)) return parse_udiv(input);
                break;

            case '.': //.asciz
                if(eatStr(input,"asciz") && endsMnemonic(input)) return parse_string(input);
                break;

            default:
                break;
        }

        // No match (label, directive, unknown): drop the rest of this line and try the next.
        skipLine(input);
    }
}
u_int32_t* parse(char* fpath, int* size){
    FILE *file = fopen(fpath, "r");
    if (file == NULL) error("Error opening file");

    u_int32_t* machine_code = malloc(sizeof(u_int32_t)*(*size));
    while(skipToNextToken(file)){
        (*size)++;
        u_int32_t code = readLine(file);
        if(code==0x00000000) continue; //skip edge cases
        print_hex(code);
        machine_code = realloc(machine_code, (*size) * sizeof(u_int32_t));
        machine_code[(*size)-1] = code;
    }

    fclose(file);
    return machine_code;
}

int main(int argc, char *argv[]){
    //manual generation goes here

    if(argc>1){
        char* fpath = argv[1];

        int mc_size = 0;
        u_int32_t* machine_code = parse(fpath,&mc_size);

        //for(int i=0; i<mc_size; i++) print_hex(machine_code[i]);

        free(machine_code);
    }

    return 0;
}
