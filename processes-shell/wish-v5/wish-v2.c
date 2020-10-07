/* wish-v2.c
 * @notes: 1. main function of wish
 *         2. add an argument in eval() to check 
 *             whether cmd is running in parallel
 * @author: MrBanana in ChengDu
 **/

#include <stdio.h>
#include <stdlib.h>

void eval(char*, int);

int
main(int argc, char** argv) {
    char cmdLine[128];  // command line

    if(argc == 1) {     // interactive mode
        while(1) {
            printf("wish> ");
            fgets(cmdLine, 128, stdin);
            if( feof(stdin) )  exit(0);

            eval(cmdLine, 0);
        }
    } 
    else {              // batch mode
        while(*++argv) {
            FILE* fpIn;
            if( (fpIn = fopen(*argv, "r")) == NULL ) {
                fprintf(stderr, "An error has occurred\n");
                exit(1);
            }

            while( fgets(cmdLine, 128, fpIn) ) {
                eval(cmdLine, 0);
            }
        }
    }

    return 0;
}
