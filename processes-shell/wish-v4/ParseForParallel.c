/* ParseForParallel.c
 * @note: Parse a string into an pointer array
 * @author: MrBanana in ChengDu
 **/

#include <stdio.h>
#include <string.h>     // strchr()
#include <stdlib.h>     // exit()
#include <ctype.h>      // isalpha()


int ParseForParallel(char* buf, char** paraArgv) {
/** Parse the command line and build the argv array */
    buf[strlen(buf) - 1] = ' ';    // replace trailing '\n' with space
    while( *buf && (*buf == ' ') ) 
        buf++;  // ignore leading spaces

    /** Build the array list */
    int argc = 0;
    char* delim;
    while( (delim = strchr(buf, '&')) != NULL ) {
        paraArgv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while( *buf && (*buf == ' ') )
            buf++;  // ignore spaces
    }
    paraArgv[argc] = NULL;

    /** Are you a NULL string? */
    int isNullString = 1;  // 1 means null string, otherwise 0
    char tmpStr[32];
    strcpy(tmpStr, paraArgv[0]);
    for(int i = 0; i < strlen(tmpStr); i++) {
        if(tmpStr[i] >= 'a' || tmpStr[i] <= 'z') {
            isNullString = 0;
            break;
        }
    }
    if( isNullString == 1 )  exit(0);

    return 1;
}
