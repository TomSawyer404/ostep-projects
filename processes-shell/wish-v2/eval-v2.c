/* eval-v2.c
 * notes: 1. add a funciton to deal with redirection
 *        2. finish test-point 1~7, 8~12, 13~16
 *        3. refactors the program
 * author: MrBanana in ChengDu
 **/

#include <stdio.h>
#include <sys/wait.h>   // wait()
#include <string.h>     // strncpy()
#include <unistd.h>     // execvp()
#include <stdlib.h>     // exit()


char path[32] = {"/bin\0"};         // path of executable
int stdoutFD = 1;


int parseLine(char*, char**);          // in CommandConstructor.c
int isBuiltinCommand(char**, char*);   // in CommandConstructor.c
char* executePath(char*, char**);      // in CommandConstructor.c
int DoRedirection(char*, int);         // in Redirection.c 


void eval(char* cmdLine) {
    char* argv[128];    // argument list execve()
    char buf[128];      // holds modified command line
    strncpy(buf, cmdLine, 128);

    if(stdoutFD != 1 ) {  // check fd of stdout
        close(1);
        dup(stdoutFD);
    }

    /** is there a '>' in buf? */
    for(int i = 0; i < strlen(buf); i++) {
        if( buf[i] == '>' ) {
            stdoutFD = DoRedirection(buf, i);
            break;
        }
    }

    parseLine(buf, argv); 
    if(argv[0] == NULL) 
        return;         // Ignore empty lines

    pid_t pid;
    if( !isBuiltinCommand(argv, path) ) {
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

