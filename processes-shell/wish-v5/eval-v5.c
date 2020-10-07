/* eval-v5.c
 * @notes: 1. add a funciton to deal with redirection
 *         2. finish test-point 1~7, 8~12, 13~15, 16~21
 *         3. refactors the program
 *         4. chage PATH from a string to pointer array, 
 *             so it can hand multiple pathes condition
 *         5. do something to deal with parallel command
 * @author: MrBanana in ChengDu
 **/

#include <stdio.h>
#include <sys/wait.h>   // wait()
#include <string.h>     // strncpy()
#include <unistd.h>     // execvp()
#include <stdlib.h>     // exit()

char* PATH[16] = {"/bin", NULL};       // path of executable
int stdoutFD = 1;


int parseLine(char*, char**);          // in CommandConstructor.c
int isBuiltinCommand(char**, char**);  // in CommandConstructor.c
char* executePath(char**, char**);     // in CommandConstructor.c
int DoRedirection(char*, int);         // in Redirection.c 
int ParseForParallel(char*, char**);   // in ParseForParallel.c


void eval(char* cmdLine, int isBackground) {
    char buf[128];      // holds modified command line
    strncpy(buf, cmdLine, 128);

    /** Does commands run in parallel? */
    if( strchr(buf, '&') != NULL) {
        char tmp[128];
        char* paraArgv[16];
        strncpy(tmp, buf, 128);
        isBackground = ParseForParallel(tmp, paraArgv);

        char* modifyBuf;
        modifyBuf = strrchr(buf, '&');  // modify buf for the command with no '&' behind
        strncpy(buf, modifyBuf+1, 64);
    
        if(isBackground == 1) {  // run in parallel
            for(int i = 0; paraArgv[i] != NULL; i++)
                eval(paraArgv[i], 1);
        }
        isBackground = 0;  // all parallel jobs done
    }

    /** Check whether fd of stdout is 1 */
    if(stdoutFD != 1 ) { 
        close(1);
        dup(stdoutFD);
    }

    /** Is there a '>' in buf? */
    for(int i = 0; i < strlen(buf); i++) {
        if( buf[i] == '>' ) {
            stdoutFD = DoRedirection(buf, i);
            break;
        }
    }

    /** Build the argv list for execvp() */
    char* argv[128]; 
    parseLine(buf, argv); 
    if(argv[0] == NULL) 
        return;         // Ignore empty lines

    pid_t pid;
    if( !isBuiltinCommand(argv, PATH) ) {
        if( (pid = fork()) == 0 ) {  // child runs user job
            if( execv(executePath(PATH, argv), argv) < 0 ) {
                fprintf(stderr, "An error has occurred\n");
                exit(0);
            }
            
        }   
        if( 1 ) {  // parent waits child
            int waitStatus;
            if( waitpid(pid, &waitStatus, 0) < 0 ) {
                fprintf(stderr, "child return code: %d\n", waitStatus);
                exit(1);
            }
        } 
    }
}

