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

int current_size=0;

u_int32_t* parse(char* fpath){
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

            //printf("0x%" PRIX32 "\n",machine_code[current_size-1]);
        }
    }

    fclose(file);
    return machine_code;
}
