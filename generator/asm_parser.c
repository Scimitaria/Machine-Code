#include "generator.h"

int main(int argc, char *argv[]){
    //manual generation goes here

    if(argc!=0){
        char* fpath = argv[0];
        parse(fpath);
    }
    return 0;
}
