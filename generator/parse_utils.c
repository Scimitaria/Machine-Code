#include "parse_utils.h"

noreturn void error(char* msg){
  fprintf(stderr, "Error: %s\n", msg);
  exit(EXIT_FAILURE);
}
void assertCondition(bool condition, char* errmsg){
  if (!condition) {
    fprintf(stderr, "Assertion failed: %s\n", errmsg);
    exit(EXIT_FAILURE);
  }
}

void skipWhitespace(FILE* input) {
    char c = getc(input);
    while (c != EOF && isspace(c)) c = getc(input);
    ungetc(c, input);
    return;
}
bool skipToNextToken(FILE* input){
    if(input==NULL) error("invalid file in skipToNextToken");
    char c = getc(input);
    while(isspace(c) || c == '/' || c == ',') {
        if(c == '/') skipLine(input);
        else skipWhitespace(input);
        c = getc(input);
    }
    bool cont = c != EOF;
    ungetc(c, input);
    return cont;
}

char get(FILE* input){
    int c = getc(input);
    return c == EOF ? EOF : tolower((unsigned char)c);
}

void readString(FILE *input, char *label){
    int c;
    int i = 0;

    while ((c = getc(input)) != EOF && !isspace(c)) label[i++] = (char)c;

    label[i] = '\0';
}
int32_t get_offset(FILE *fp) {
    int32_t start_pos = ftell(fp);
    if (start_pos < 0) return -1;

    char line[512];
    int32_t offset_bytes = 4; //starts at end of ADR byte
    char label[300]; 
    readString(fp,label);
    char label_pattern[300];
    snprintf(label_pattern, sizeof(label_pattern), "%s:", label);
    //printf("Branch: %s; Label: %s\n", label, label_pattern);

    while (fgets(line, sizeof(line), fp)) {
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;

        if (*p == '\0' || *p == '\n' || (p[0] == '/' && p[1] == '/')) continue; // blank or comment-only line
        if (strncmp(p, label_pattern, strlen(label_pattern)) == 0) {
            fseek(fp, start_pos, SEEK_SET);
            return offset_bytes; // found it
        }

        if (*p == '.') continue; // directive, no instruction bytes (adjust if needed)
        char *colon = strchr(p, ':');
        if (colon) {
            // check if there's anything but whitespace after the colon
            char *rest = colon + 1;
            while (*rest == ' ' || *rest == '\t') rest++;
            if (*rest == '\0' || *rest == '\n' || (rest[0]=='/' && rest[1]=='/'))
                continue; // label-only line, no instruction bytes
        }

        offset_bytes += 4; // one AArch64 instruction
    }

    fseek(fp, start_pos, SEEK_SET);
    return -1; // label not found
}

int read_u32(FILE *fp, uint32_t *out){
    uint32_t word = 0;

    for (int i = 0; i < 4; i++) {
        int c = fgetc(fp);

        if (c == '\\') {
            c = fgetc(fp);
            switch (c) {
            case 'n': c = '\n'; break;
            case 't': c = '\t'; break;
            case '\\': c = '\\'; break;
            case '"': c = '"'; break;
            }
        }

        if(c=='\"') {
            if (i == 0) return 0; // No more data
            *out = word;         // Partial word, zero-padded
            return 2;
        }
        if (c == EOF) {
            if (i == 0) return 0; // No more data
            *out = word;         // Partial word, zero-padded
            return 1;
        }

        word |= (uint32_t)(uint8_t)c << (8 * i);
    }

    *out = word;
    return 1;
}

int readNumber(FILE *input, int c){
    int val = 0;

    while (isdigit(c)) {
        val = val * 10 + (c - '0');
        c = getc(input);
    }

    if (c != EOF) ungetc(c, input);

    return val;
}
op parse_op(FILE* input){
    skipToNextToken(input);
    char c = get(input);
    op o;
    o.isSP = false;
    switch(c){
        case '#':
            c = getc(input);
            o.isReg = false;
            o.isX = false;
            break;
        case 'x':
            o.isReg = true;
            o.isX = true;

            if (tolower(peek(input)) == 'z') {
                get(input);              // z
                if (get(input) != 'r') error("expected r");
                o.val = xzr;
                return o;
            }
            c = get(input);
            break;
        case 'w':
            c = getc(input);
            o.isReg = true;
            o.isX = false;
            break;
        case 's':
            c = get(input);
            if(c=='p'){
                o.val = sp;
                o.isReg = true;
                o.isX = true;
                o.isSP = true;
                return o;
            } else error("failed to parse sp");
        case '\'':
            o.val = (c = getc(input));
            assertCondition((c = getc(input))=='\'',"failed to parse char op");
            o.isReg = false;
            o.isX = false;
            return o;
        default:
            o.isReg = false;
            o.isX = false;
    }
    if(!isdigit(c)){
        printf("Attempted to read non-numeric value %c with next value %c", c, peek(input));
        error("in parse_op");
    }
    o.val = readNumber(input,c);
    return o;
}
