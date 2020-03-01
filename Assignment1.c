
/**************************************************************
* Class: CSC-415-0# Spring 2020
* Name: Andrew Hwang
* Student ID: 918450486
* Project: Assignment 1 – Simple Shell
*
* File: <name of this file>
*
* Description:
*
**************************************************************/
#include <stdio.h>
#define BYTEBUFFER 1024 


int main(){
    char input[BYTEBUFFER];
    char* argv[100];
    int argc;
    while(1){
        printf("Prompt$ ");
        fgets(input, BYTEBUFFER, stdin);
        char* token = strtok(input, " ");
        int i = 0;
        while (token != NULL){
            argv[i] = token;
            token = strtok(NULL," ");
            i++;
        }
        argv[i] = NULL;
        argc = i;
        for(int i = 0; i < argc; i++){
            printf("%s\n", argv[i]);

        }

        char* execPath[50];
        strcpy(execPath, "/bin/");           //copy /bin/ to file path
        strcat(execPath, argv[0]);            //add program to path

        for(i=0; i<strlen(execPath); i++){    //delete newline
            if(execPath[i]=='\n'){      
                execPath[i]='\0';
            }
        }
        int pid= fork();              //fork child

        if(pid==0){               //Child
            execvp(execPath,argv);
            fprintf(stderr, "Child process could not do execvp\n");

        }else{                    //Parent
            wait(NULL);
            printf("Child exited\n");
        }

    }

    return 0;
}