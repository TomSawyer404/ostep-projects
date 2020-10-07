/* CommandConstructor.c
 * notes: contains 3 function to construct command
 **/

#include <stdio.h>
#include <string.h>     // strcmp(), memset()
#include <stdlib.h>     // exit()
#include <unistd.h>     // chdir()


int parseLine(char* buf, char** argv) {
/** Parse the command line and build the argv array */
    char* delim;    // points to first space delimiter
    int bg;         // background job?
    
    buf[strlen(buf) - 1] = ' ';         // replace trailing '\n' with space
    while( *buf && (*buf == ' ') ) {    // ignore leading spaces
        buf++;
    }
    
    /** Build the array list */
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


int isBuiltinCommand(char** argv, char* path) {
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
        memset(path, 0x0, 32);
        if( argv[1] != 0x0 ) 
            strncpy(path, argv[1], strlen(argv[1]));
        return 1;
    }
    return 0;
}


char* executePath(char* paths, char** argv) {
/** Construct a execute path */
    char* exePath = (char*)malloc(64);
    memset(exePath, 0x0, 64);
    
    if( paths == NULL ) {
        strcpy(exePath, "no/path/setted/");
        return exePath;
    }
    strcpy(exePath, paths);

    if( exePath[ strlen(paths)-1 ] != '/' ) {
        exePath[ strlen(paths) ] = '/';
        exePath[ strlen(paths)+1 ] = '\0';
    }
    strcat(exePath, argv[0]);

    return exePath;
}
