#include "parse_ops.h"

u_int32_t readLine(FILE* input){
    char c = get(input);
    switch(c){
        case 'a': //ADD, ADR
            if(get(input)=='d'){
                c = get(input);
                switch(c){
                    case 'd': return parse_add(input);
                    case 'r': return parse_adr(input);
                    default: perror(sprintf("Input ad followed by %c rather than d or r", c));
                }
            }
            else perror(sprintf("Input a followed by %c rather than d", c));
        case 'b': //B, B.COND
            c = get(input);
            switch(c){
                case ' ': return parse_b(input);
                case '.': return parse_b_cond(input);
                default: perror(sprintf("Input b followed by %c rather than .", c));
            }
        case 'c': //CBZ, CMP
            c = get(input);
            switch(c){
                case 'b': 
                    if(get(input)=='z') return parse_cbz(input);
                    else perror("Input cb not followed by z");
                case 'm':
                    if(get(input)=='p') return parse_cmp(input);
                    else perror("Input cm not followed by p");
                default: perror(sprintf("Input c followed by %c rather than b or m", c));
            }
        case 'd': //DIV
            if(get(input)=='i'&&get(input)=='v') return parse_udiv(input);
            else perror("Input d not followed by iv");
        case 'l': //LDRB
            if(get(input)=='d'&&get(input)=='r'&&get(input)=='b') return parse_ldrb(input);
            else perror("Input l not followed by drb");
        case 'm': //MOV, MSUB, MUL
            c = get(input);
            switch(c){
                case 'o':
                    if(get(input)=='v') return parse_mov(input);
                    else perror("Input mo not followed by v");
                case 's':
                    if(get(input)=='u'&&get(input)=='b') return parse_msub(input);
                    else perror("Input ms not followed by ub");
                case 'u':
                    if(get(input)=='l') return parse_mul(input);
                    else perror("Input mu not followed by l");
                default: perror(sprintf("Input m followed by %c rather than o, s, or u", c));
            }
        case 'n': //NOP
            if(get(input)=='o'&&get(input)=='p') return nop;
            else perror("Input n not followed by op");
        case 'r': //RET
            if(get(input)=='e'&&get(input)=='t') return ret;
            else perror("Input r not followed by et");
        case 's': //STRB, SUB, SVC
            c = get(input);
            switch(c){
                case 't':
                    if(get(input)=='r'&&get(input)=='b') return parse_strb(input);
                    else perror("Input st not followed by rb");
                case 'u':
                    if(get(input)=='b') return parse_sub(input);
                    else perror("Input su not followed by b");
                case 'v':
                    if(get(input)=='c') return parse_svc(input);
                    else perror("Input sv not followed by c");
                default: perror(sprintf("Input s followed by %c rather than t, u, or v", c));
            }
        case 'u': //UDIV
            if(get(input)=='d'&&get(input)=='i'&&get(input)=='v') return parse_udiv(input);
            else perror("Input u not followed by div");
    }
}

u_int32_t* parse(char* fpath, int* size){
    FILE *file = fopen(fpath, "r");
    if (file == NULL) perror("Error opening file");

    u_int32_t* machine_code = malloc(sizeof(u_int32_t)*(*size));
    while(skipToNextToken(file)){
        (*size)++;
        u_int32_t code = readLine(file);
        machine_code = realloc(machine_code, (*size) * sizeof(u_int32_t));
        machine_code[(*size)-1] = code;
    }

    return machine_code;
}

int main(int argc, char *argv[]){
    //manual generation goes here

    if(argc!=0){
        char* fpath = argv[0];

        int mc_size = 0;
        u_int32_t* machine_code = parse(fpath,&mc_size);

        for(int i=0; i<mc_size; i++) print_hex(machine_code[i]);
    }
    return 0;
}
