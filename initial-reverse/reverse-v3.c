/* reverse-v3.c
 * Purpose: Deal with the problem that input file 
 *            and output file cannot be opened.
 *          Finish test point 1, 2, 3.
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
        ++argv;  // ignore the first argument
        FILE *fpIn, *fpOut;
        if( ( fpIn = fopen(*argv, "r") ) == NULL ) {
           fprintf(stderr, "reverse: cannot open file '%s'\n", *argv);
           exit(1);
        } else if( ( fpOut = fopen(*++argv, "w") ) == NULL ) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", *argv);
            exit(1);
        }
        
        /** do something */

    }
   
    return 0;
}
