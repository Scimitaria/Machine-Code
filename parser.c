#include "parser.h"

char peek(FILE *input){
    char c = getc(input);
    ungetc(c,input);
    return c;
}

int isEOL(FILE *input){return (peek(input)==EOF || peek(input)=='\n');}

void skipWhitespace(FILE* input) {
  char c = getc(input);
  while (c != EOF && isspace(c)) {
    c = getc(input);
  }
  ungetc(c, input);
  return;
}

void skipLine(FILE* input){
  char c = getc(input);
  while(c != '\n' && c != EOF) c= getc(input);
}

u_int32_t* parse(char* fpath){
    //open as binary
    FILE *file = fopen(fpath, "r");
    if (file == NULL) perror("Error opening file");

    int current_size = 0;
    u_int32_t* machine_code = malloc(sizeof(u_int32_t)*current_size);

    char c = '\0';
    char str[20] = "";
    while(c!=EOF){
        c = getc(file);
        if(!isspace(c)&&!(c==EOF)&&!(c=='\n')) strncat(str,&c,1);
        else{
            //append 
            current_size++;
            u_int32_t* temp = realloc(machine_code, current_size * sizeof(u_int32_t));
            machine_code=temp;
            char *endptr;
            u_int32_t code = (u_int32_t)strtoul(str, &endptr, 16);
            machine_code[current_size-1]=code;
            //printf("0x%" PRIX32 "\n",machine_code[current_size-1]);
        }
    }

    fclose(file);
    return machine_code;
}
