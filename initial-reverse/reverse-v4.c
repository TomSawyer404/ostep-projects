/* reverse-v4.c
 * Purpose: Determines whether the name of input
 *            file and output file is equal.
 *          Finish test point 1, 2, 3, 4.
 * Author: MrBanana in Chengdu
 **/

#include <stdio.h>
#include <stdlib.h>     // exit()
#include <string.h>     // strcmp()

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
    else if(argc == 3) {  // number of argc == 3
        if( strcmp(argv[1], argv[2]) == 0 ) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }

        FILE *fpIn, *fpOut;
        ++argv;    // ignore first argument
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
