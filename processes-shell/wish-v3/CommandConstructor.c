/* CommandConstructor.c
 * @notes: contains 3 function to construct command
 **/

#include <stdio.h>
#include <string.h>     // strdup()
#include <stdlib.h>     // exit()
#include <unistd.h>     // chdir(), access()


int parseLine(char* buf, char** argv) {
/** Parse the command line and build the argv array */
    buf[strlen(buf) - 1] = ' ';         // replace trailing '\n' with space
    while( *buf && (*buf == ' ') ) {    // ignore leading spaces
        buf++;
    }
    
    /** Build the array list */
    int argc = 0; 
    char* delim;
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

    return 0;
}


int isBuiltinCommand(char** argv, char** PATH) {
/** If first arg is a builtin command, run it and return true */
    if( !strcmp(argv[0], "exit") ) {    // quit command
        if(argv[1] != NULL) 
            fprintf(stderr, "An error has occurred\n");
        exit(0);
    }
    if( !strcmp(argv[0], "cd") ) {      // change directory
        if(argv[2] != NULL || argv[1] == NULL) { 
            fprintf(stderr, "An error has occurred\n");
            exit(0);
        }
        
        if( chdir(argv[1]) == -1 ) {
            perror("chdir");
            exit(1);
        }
        return 1;
    }
    if( !strcmp(argv[0], "path") ) {    // path command
        PATH[0] = NULL;
        int i = 1;
        while( argv[i] != NULL ) { 
            PATH[i-1] = strdup( argv[i] );
            i++;
        }
        PATH[i] = NULL;
        return 1;
    }
    return 0;
}


char* executePath(char** PATH, char** argv) {
/** Construct a executable path */
    char* exePath = (char*)malloc(64);
    memset(exePath, 0x0, 64);
    
    if( PATH[0] == NULL ) {
        strcpy(exePath, "no/path/setted/");
        return exePath;
    }

    for(int i = 0; PATH[i] != NULL; i++) {
        char tmpPath[64];
        strcpy(tmpPath, PATH[i]);
        if( tmpPath[ strlen(PATH[i])-1 ] != '/' ) {
            tmpPath[ strlen(PATH[i]) ] = '/';
            tmpPath[ strlen(PATH[i])+1 ] = '\0';
        }
        strcat(tmpPath, argv[0]);

        if( access(tmpPath, X_OK) == 0 ) 
            strncpy(exePath, tmpPath, 64);
    }

    return exePath;
}
