/* 
   wcat.c - version 0.1 of cat 
  - Print everything it reads;
 */

#include <stdio.h>
#include <stdlib.h>

void do_cat(FILE*);

int main(int argc, char** argv) {

    // Open a file
    FILE* filePointer;
    while( --argc ) {
        if( (filePointer = fopen(*(++argv), "r")) != NULL ) {
            do_cat(filePointer);           
            fclose(filePointer);
        } else {
            printf("wcat: cannot open file\n");
            exit(1);
        }
    }

    return 0;
}

/** Print everything it reads */
void do_cat(FILE* fp) {
    char buffer[2048];   
    while( fgets(buffer, 2048, fp) ) {
        fputs(buffer, stdout);
    }
}
