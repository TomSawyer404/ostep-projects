/* reverse-v5.c
 * Purpose: Determines if the input file and output
 *            file is the same, using i-node number
 *            to judge. (need stat() system call)
 *          Finish test point 1, 2, 3, 4, 5.
 * Author: MrBanana in Chengdu
 **/

#include <stdio.h>
#include <stdlib.h>     // exit()
#include <string.h>     // strcmp()
#include <sys/stat.h>   // stat()

int isSameFile(char*, char*);

int
main(int argc, char** argv) {
    if( argc > 3 ) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    else if( argc == 1 ) {  // read from stdin
        
    } 
    else if(argc == 2){  // number of argc == 2
        FILE *fpIn;
        if( ( fpIn = fopen(*++argv, "r") ) == NULL ) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", *argv);
            exit(1);
        }
    } 
    else if(argc == 3) {  // number of argc == 3
        /*if( strcmp(argv[1], argv[2]) == 0 ) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }*/

        FILE *fpIn, *fpOut;
        ++argv;    // ignore first argument
        if( ( fpIn = fopen(*argv, "r") ) == NULL ) {
           fprintf(stderr, "reverse: cannot open file '%s'\n", *argv);
           exit(1);
        } else if( ( fpOut = fopen(*(argv+1), "w") ) == NULL ) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", *argv);
            exit(1);
        }

        if( isSameFile(*argv, *(argv+1)) ) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }

        /** do something */

    }
   
    return 0;
}


int isSameFile(char* inFile, char* outFile) {
    struct stat inStat, outStat;
    if( stat(inFile, &inStat) == -1 ) {
        perror("stat-inFile");
        exit(1);
    }
    if( stat(outFile, &outStat) == -1 ) {
        perror("stat-outFile");
        exit(1);
    }

    if( inStat.st_ino == outStat.st_ino ) {
        return 1;  // They are the same file
    }
    return 0;
}
