/* wzip.c
 * Author: MrBanana
 * Location: Chengdu city
 * Disadvantage: Test-Point-6 still a long way to reach
 **/

#include <stdio.h>
#include <stdlib.h>     // exit()
#include <unistd.h>     // read()
#include <fcntl.h>      // open()
#include <string.h>     // strlen()

void RLE_Encode(char*);
void WriteBinary(int, char);
int Is_Unique(char*);
void WriteOnce(char*);

int
main(int argc, char** argv) {
    if(argc <= 1) { 
        fprintf(stdout, "wzip: file1 [file2 ...]\n");
        exit(1);
    } 
    
    /** Concatenates all input-files into a string */
    char buffer[2048];
    int offset = 0, read_char = 0;
    char* RLEString = (char*)malloc(2048);
    while( *++argv ) {
        int fd = open(*argv, O_RDONLY);
        while( (read_char = read(fd, buffer, 2048)) > 0 )  {
            strcpy(RLEString + offset, buffer);
            offset += strlen(buffer);  

            if( (offset - 1 >= strlen(RLEString)) ) {
                if( (RLEString = realloc(RLEString, 2048)) == NULL ) {
                    perror("realloc");
                    exit(1);
                }
            }  
        }
        
        if( read_char == -1 ) {
            perror("read error");
            exit(1);
        }
        close(fd);
    }

    /** Is every characters in RLEString unique? */
    if( Is_Unique(RLEString) ) {
        WriteOnce(RLEString);
        return 0;
    } 
    else {
        RLE_Encode(RLEString);
    }
    
    return 0;
}


void RLE_Encode(char* src) {
    int len = strlen(src); 
    for(int i = 0; i < len; i++) {
        int counter = 1;
        while( i < len - 1 && src[i] == src[i+1]) {
            counter++;
            i++;
        }

        fwrite(&counter, 4, 1, stdout);
        fwrite(&src[i], 1, 1, stdout);
    }
}


int Is_Unique(char* RLEString) {
    int ascii[128] = {0};
    for(int i = 0; i < strlen(RLEString); i++) {
        ascii[ (int)RLEString[i] ]++;
    }
    int count = 0;
    for(int j = 0; j < 128; j++) {
        if(ascii[j] >= 2 ) 
            count++;
    }
    return (count == 0);
}


void WriteOnce(char* RLEString) {
    for(int i = 0; i < strlen(RLEString); i++) {
        if( (RLEString[i] >= 'a' && RLEString[i] <= 'z') 
                || (RLEString[i] >= 'A' && RLEString[i] <= 'Z') 
                || (RLEString[i] == '\n') ) {
            int tmpInteger = 1;
            fwrite(&tmpInteger, 4, 1, stdout);
            fwrite(RLEString + i, 1, 1, stdout);
        }
    }
}
