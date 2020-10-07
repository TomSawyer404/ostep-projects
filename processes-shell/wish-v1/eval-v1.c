/* eval-v1.c
 * notes: finish Built-in Commands `exit`, `cd`, 'path'
 *        finish test-point 1, 2, 3, 4, 5, 6, 7
 * author: MrBanana in ChengDu
 **/

#include <stdio.h>
#include <sys/wait.h>   // wait()
#include <string.h>     // strcmp()
#include <unistd.h>     // execvp(), chdir()
#include <stdlib.h>     // exit()

char* path[128] = {"/bin", NULL};

int parseLine(char*, char**);  // in parseLine.c
int isBuiltinCommand(char**);
char* executePath(char**, char**);


void eval(char* cmdLine) {
    char* argv[128];    // argument list execve()
    char buf[128];      // holds modified command line

    strncpy(buf, cmdLine, 128);
    parseLine(buf, argv); 
    if(argv[0] == NULL) 
        return;         // Ignore empty lines

    pid_t pid;
    if( !isBuiltinCommand(argv) ) {
        if( (pid = fork()) == 0 ) {  // child runs user job
            if( execv(executePath(path, argv), argv) < 0 ) {
                fprintf(stderr, "An error has occurred\n");
                exit(0);
            }
            
        } else {    // parent waits child
            int waitStatus, childRet;
            if( (childRet = wait(&waitStatus)) == -1 ) {
                fprintf(stderr, "child return code: %d\n", waitStatus);
                exit(1);
            }
        }
    }
}


int isBuiltinCommand(char** argv) {
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
        path[0] = NULL;
        int i;
        for(i = 0; argv[i+1] != NULL; i++) 
            path[i] = strdup( argv[i + 1] );
        path[i] = NULL;
        
        return 1;
    }

    return 0;
}


char* executePath(char** paths, char** argv) {
/** Construct a execute path with 2 vectors: path and argv */
    char* exePath = (char*)malloc(64);
    memset(exePath, 0x0, 64);
    
    if( paths[0] == NULL ) {
        strcpy(exePath, "no/path/setted/");
        return exePath;
    }
    strcpy(exePath, paths[0]);

    if( exePath[ strlen(exePath) - 1 ] != '/' ) {
        exePath[ strlen(exePath) ] = '/';
        exePath[ strlen(exePath) + 1 ] = '\0';
    }
    strcat(exePath, argv[0]);

    return exePath;
}
