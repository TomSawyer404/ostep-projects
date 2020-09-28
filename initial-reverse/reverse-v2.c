/* reverse-v2.c
 * Purpose: print stderr information when argument number is 2.
 *          Finish test point 1, 2.
 * Author: MrBanana in Chengdu
 **/

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char** argv) {
    if( argc > 3 ) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    else if(argc == 2){  // number of argc == 2
        FILE *fpIn;
        if( ( fpIn = fopen(*++argv, "r") ) == NULL ) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", *argv);
            exit(1);
        }
    } 
    else {  // number of argc == 3
        
    }
   
    return 0;
}
