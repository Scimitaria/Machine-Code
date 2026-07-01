#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

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

void parse(char* fpath){
    //open as binary
    FILE *file = fopen(fpath, "r");
    if (file == NULL) perror("Error opening file");
    
    char c = '\0';
    char str[20] = "";
    while(c!=EOF){
        c = getc(file);
        if(!isspace(c)&&!(c==EOF)&&!(c=='\n')) strncat(str,&c,1);
    }
    printf("%s\n",str);

    fclose(file);
}

int main(){
    parse("bin/ret.s");
    return 0;
}
