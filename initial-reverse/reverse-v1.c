/* reverse-v1.c
 * Purpose: print stderr information.
 *          Finish test point 1.
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
    
    return 0;
}
