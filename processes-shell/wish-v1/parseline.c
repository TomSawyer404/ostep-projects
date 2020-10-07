/* parseline.c
 * notes: Parse the command line and build the argv array
 * author: MrBanana in ChengDu
 **/

#include <stdio.h>
#include <string.h>


int parseLine(char* buf, char** argv) {
    char* delim;    // points to first space delimiter
    int bg;         // background job?
    
    buf[strlen(buf) - 1] = ' ';     // replace trailing '\n' with space
    while( *buf && (*buf == ' ') ) {  // ignore leading spaces
        buf++;
    }
    
    /** Build the argv list */
    int argc = 0;
    while( (delim = strchr(buf, ' ')) != NULL ) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while( *buf && (*buf == ' ') )   // ignore spaces
            buf++;
    }
    argv[argc] = NULL;

    if(argc == 0)  // ignore blank line
        return 1;

    /** Should the job run in the background? */
    if( (bg = (*argv[argc-1] == '&')) != 0 ) 
        argv[--argc] = NULL;
    return bg;
}
