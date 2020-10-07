/* wish.c
 * notes: main function of wish
 * author: MrBanana in ChengDu
 **/

#include <stdio.h>
#include <stdlib.h>

void eval(char*);

int
main(int argc, char** argv) {
    char cmdLine[128];  // command line

    if(argc == 1) {     // interactive mode
        while(1) {
            printf("wish> ");
            fgets(cmdLine, 128, stdin);
            if( feof(stdin) )  exit(0);

            eval(cmdLine);
        }
    } 
    else {              // batch mode
        while(*++argv) {
            FILE* fpIn;
            if( (fpIn = fopen(*argv, "r")) == NULL ) {
                perror(*argv);
                exit(1);
            }

            while( fgets(cmdLine, 128, fpIn) ) {
                eval(cmdLine);
            }
        }
    }

    return 0;
}
