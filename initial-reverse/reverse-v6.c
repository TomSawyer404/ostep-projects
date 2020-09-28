/* reverse-v6.c
 * Purpose: Implements the simple function using
 *            linked list. Read data and store them
 *            in list, then reverse the list. Last
 *            Print them out.
 *          Finish test point 1, 2, 3, 4, 5, 6.
 * Author: MrBanana in Chengdu
 **/

#include <stdio.h>
#include <stdlib.h>     // exit()
#include <string.h>     // strcmp()
#include <sys/stat.h>   // stat()

typedef struct linkText {
    char content[100];
    struct linkText* next;
}node;


int isSameFile(char*, char*);
void ReadData(FILE*, node*);
node* ReverseList(node*);
inline void WriteData(FILE*, node*);


int
main(int argc, char** argv) {
    if( argc > 3 ) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    else if( argc == 1 ) {  // read from stdin
        
    } 
    else if(argc == 2){  // number of argc == 2
        FILE *fpIn;
        if( ( fpIn = fopen(argv[1], "r") ) == NULL ) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    } 
    else if(argc == 3) {  // number of argc == 3
        FILE *fpIn, *fpOut;
        ++argv;    // ignore first argument
        if( ( fpIn = fopen(*argv, "r") ) == NULL ) {
           fprintf(stderr, "reverse: cannot open file '%s'\n", *argv);
           exit(1);
        } else if( ( fpOut = fopen(*(argv+1), "w") ) == NULL ) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", *argv);
            exit(1);
        }

        if( isSameFile(*argv, *(argv+1)) ) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }

        node* head = (node*)malloc(sizeof(node));
        ReadData(fpIn, head);
        head = ReverseList(head);
        WriteData(fpOut, head);

        fclose(fpIn);
        fclose(fpOut);
    }
   
    return 0;
}


int isSameFile(char* inFile, char* outFile) {
    struct stat inStat, outStat;
    if( stat(inFile, &inStat) == -1 ) {
        perror("stat-inFile");
        exit(1);
    }
    if( stat(outFile, &outStat) == -1 ) {
        perror("stat-outFile");
        exit(1);
    }

    if( inStat.st_ino == outStat.st_ino ) {
        return 1;  // They are the same file
    }
    return 0;
}


void ReadData(FILE* fpIn, node* head) {
    char buf[100];
    if( fgets(buf, 100, fpIn) ) {  // read a line and add new node to list
        node* newNode = (node*)malloc(sizeof(node));
        newNode->next = NULL;
        
        strncpy(newNode->content, buf, 100);
        
        head->next = newNode;
        ReadData(fpIn, newNode);
    }
}


node* ReverseList(node* head) {
    node* prevNode = NULL;
    node* currNode = head; 
    node* nextNode = NULL;
    while( currNode != NULL ) {
        nextNode = currNode->next;
        currNode->next = prevNode;
        prevNode = currNode;
        currNode = nextNode;
    }
    head = prevNode;
    return head;
}


void WriteData(FILE* fpOut, node* head) {
    while(head->next) {
        fprintf(fpOut, "%s", head->content);
        head = head->next;
    }
}
