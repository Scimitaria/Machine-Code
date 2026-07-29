#include "parser.h"

char peek(FILE *input){
    char c = getc(input);
    ungetc(c,input);
    return c;
}

void skipLine(FILE* input){
  char c = getc(input);
  while(c != '\n' && c != EOF) c= getc(input);
}

const char* get_file_extension(const char *fpath) {
    // Find the last occurrence of '.'
    const char *dot = strchr(fpath, '.');

    // If dot is not found, or it is the first character (hidden file like .htaccess), return empty string
    if (!dot || dot == fpath) return "";

    // Return the extension (characters after the dot)
    return dot;
}

int current_size=0;

u_int32_t* parse_hex(char* fpath){
    //open as binary
    FILE *file = fopen(fpath, "r");
    if (file == NULL) perror("Error opening file");

    current_size = 0;
    u_int32_t* machine_code = malloc(sizeof(u_int32_t)*current_size);

    char c = '\0';
    char str[20] = "";
    while(c!=EOF){
        c = getc(file);
        if(c=='#') skipLine(file);//comment
        else if(!isspace(c)&&!(c==EOF)&&!(c=='\n')) strncat(str,&c,1);
        else{
            //don't append empty
            if(strcmp(str,"")==0) continue;

            //append
            current_size++;
            machine_code = realloc(machine_code, current_size * sizeof(u_int32_t));
            machine_code[current_size-1]=(u_int32_t)strtoul(str,NULL,16);

            //reset string
            strncpy(str, "", sizeof(str) - 1);

            //print_binary(machine_code[current_size-1],0);
        }
    }

    fclose(file);
    return machine_code;
}

u_int32_t parse_binary_op(FILE* file){
    u_int32_t code = 0b00000000000000000000000000000000;

    for(int i=31; i>=0; i--){
        char c = peek(file);
        if(isspace(c)||(c==EOF)||(c=='\n')||(c=='#')) return code;
        switch(getc(file)){
            case '1': code |= (1<<i);break;
            case '0': break;
            default: perror("Non-binary character");
        }
    }
    return code;
}
u_int32_t* parse_binary(char *fpath){
    FILE *file = fopen(fpath, "r");
    if (file == NULL) perror("Error opening file");

    current_size = 0;
    u_int32_t* machine_code = malloc(sizeof(u_int32_t)*current_size);

    char c = peek(file);
    while(c!=EOF){
        if(c=='#'){
            //comment
            printf("Skipping comments...\n");
            skipLine(file);
            c = peek(file);
            continue;
        }
        if(isspace(c)||c=='\n'){
            //not binary
            getc(file);
            c = peek(file);
            continue;
        }
        u_int32_t code = parse_binary_op(file);

        current_size++;
        machine_code = realloc(machine_code, current_size * sizeof(u_int32_t));
        machine_code[current_size-1] = code;

        //printf("%c, %d\n", c, current_size);
        //print_binary(code,0);
        c = peek(file);
    }
    return machine_code;
}

u_int32_t* parse(char* fpath){
    if(strcmp(get_file_extension(fpath),".bin.s")==0) return parse_binary(fpath);
    return parse_hex(fpath);
}
