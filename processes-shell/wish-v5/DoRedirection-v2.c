/* DoRedirection-v2.c
 * @notes: 1. if the string contains '>', we gonna do something
 *         2. do some changes for parallel conditional string
 * @author: MrBanana in ChengDu
 **/

#include <stdio.h>
#include <string.h>     // strlen()
#include <stdlib.h>     // exit()
#include <ctype.h>      // isalpha()
#include <fcntl.h>      // creat() 
#include <unistd.h>     // dup2(), close()

void isCommandBeforeRedirection(char*);


int DoRedirection(char* buf, int redirPos) {
    /** Any commands before '>' ? */
    isCommandBeforeRedirection(buf);

    char* indicator = buf + redirPos + 1;
    while( *(indicator) == ' ' )  // ignore spaces
        indicator++; 

    /** Nothing behinds '>' */
    if( *indicator == '\n' ) {
        fprintf(stderr, "An error has occurred\n");
        exit(0);
    }

    /** Multiple files behinds '>', or number of '>' more than 1 */
    char* tmpPtr = strchr(indicator, ' ');
    if( tmpPtr != NULL ) {
        while( *tmpPtr == ' ' ) 
            tmpPtr++; 
        if( *tmpPtr != '\n' ) {
            if(*tmpPtr != 0x0) {
                fprintf(stderr, "An error has occurred\n");
                exit(0);
            }
        }
    }
    
    /** one file behinds '>' */
    char outputFile[32];
    sscanf(indicator, "%s", outputFile);

    int stdoutFD = dup(1);              // back up stdout
    int fd = creat(outputFile, 0644);   // create new file
    int newfd = dup2(fd, 1);            // redirects stdout to outputFile
    if( newfd == -1 ) {
        perror("dup2");  exit(1);
    }

    *(buf + redirPos) = '\0'; 
    return stdoutFD;
}


void isCommandBeforeRedirection(char* buf) {
    char* indicator = buf;
    int isCommandInside = 0;  // 0 means no command inside, otherwise 1
    while( *indicator != '>' ) {
        if( isalpha(*indicator) ) {
            isCommandInside = 1;
            break;
        }
        indicator++;
    }
    if( isCommandInside == 0 ) {
        fprintf(stderr, "An error has occurred\n");
        exit(0);
    }
}
