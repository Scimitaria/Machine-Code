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
                    default: 
                        printf("Input ad followed by %c", c);
                        error("rather than d or r");
                }
            }
            else{
                printf("Input a followed by %c", c);
                error("rather than d");
            }
        case 'b': //B, B.COND
            c = get(input);
            switch(c){
                case ' ': return parse_b(input);
                case '.': return parse_b_cond(input);
                default:
                    printf("Input b followed by %c", c);
                    error("rather than .");
            }
        case 'c': //CBZ, CMP
            c = get(input);
            switch(c){
                case 'b':
                    c = get(input);
                    switch(c){
                        case 'z': return parse_cbz(input,false);
                        case 'n':
                            if(get(input)=='z') return parse_cbz(input,true);
                            else error("Input cbn not followed by z");
                        default: error("Input cb not followed by z");
                    }
                case 'm':
                    if(get(input)=='p') return parse_cmp(input);
                    else error("Input cm not followed by p");
                default: 
                    printf("Input c followed by %c", c);
                    error("rather than b or m");
            }
        case 'd': //DIV
            if(get(input)=='i'&&get(input)=='v') return parse_udiv(input);
            else error("Input d not followed by iv");
        case 'l': //LDRB
            if(get(input)=='d'&&get(input)=='r'&&get(input)=='b') return parse_ldrb(input);
            else error("Input l not followed by drb");
        case 'm': //MOV, MSUB, MUL
            c = get(input);
            switch(c){
                case 'o':
                    if(get(input)=='v') return parse_mov(input);
                    else error("Input mo not followed by v");
                case 's':
                    if(get(input)=='u'&&get(input)=='b') return parse_msub(input);
                    else error("Input ms not followed by ub");
                case 'u':
                    if(get(input)=='l') return parse_mul(input);
                    else error("Input mu not followed by l");
                default:
                    printf("Input m followed by %c", c);
                    error("rather than o, s, or u");
            }
        case 'n': //NOP
            if(get(input)=='o'&&get(input)=='p') return nop;
            else error("Input n not followed by op");
        case 'r': //RET
            if(get(input)=='e'&&get(input)=='t') return ret;
            else error("Input r not followed by et");
        case 's': //STRB, SUB, SVC
            c = get(input);
            switch(c){
                case 't':
                    if(get(input)=='r'&&get(input)=='b') return parse_strb(input);
                    else error("Input st not followed by rb");
                case 'u':
                    if(get(input)=='b') return parse_sub(input);
                    else error("Input su not followed by b");
                case 'v':
                    if(get(input)=='c') return parse_svc(input);
                    else error("Input sv not followed by c");
                default:
                    printf("Input s followed by %c", c);
                    error("rather than t, u, or v");
            }
        case 'u': //UDIV
            if(get(input)=='d'&&get(input)=='i'&&get(input)=='v') return parse_udiv(input);
            else error("Input u not followed by div");
        case '.': //.asciz
            if(get(input)=='a'&&get(input)=='s'&&get(input)=='c'&&get(input)=='i'&&get(input)=='z') return parse_string(input);
        default:
            while(!isspace(c)) c=getc(input);
            skipToNextToken(input);
            return readLine(input);
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

    if(argc!=0){
        char* fpath = argv[1];

        int mc_size = 0;
        u_int32_t* machine_code = parse(fpath,&mc_size);

        //for(int i=0; i<mc_size; i++) print_hex(machine_code[i]);

        free(machine_code);
    }
    return 0;
}
