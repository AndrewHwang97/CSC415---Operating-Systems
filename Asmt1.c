/**************************************************************
* Class: CSC-415-02 Spring 2020
* Name: Andrew Hwang
* Student ID: 918450486
* Project: Assignment 1 – Simple Shell
*
* File: Assignment1.c
*
* Description: A simple shell that uses fork() and execvp()
*              to take commands from the command line
*
**************************************************************/
#include <stdio.h>
#include <string.h>

#define BYTEBUFFER 1024 

int main(){
    char input[BYTEBUFFER]; //line from command line
    char* line[50]; //used for tokenized string
    char execPath[100]; //the path that will be used when we call exec

    while(1){       //loop
        printf("Prompt$ ");
        fgets(input, BYTEBUFFER, stdin); //gets an input line from the user

        int len = strlen(input); //gets the length of the line
        if(len == 1) //if there is one character(\0), we want to exit
            break;

        if(input[len - 1] == '\n') //we want to change the new line to a null character
            input[len - 1] = '\0';

        if(strcmp(input, "exit") == 0) //if user enters exit, close program
            return 0;


        char *token = strtok(input, " "); //beginning of string tokenization

        int i = 0;
        while (token != NULL){
            line[i] = token;    //places each arg into the execLine
            token = strtok(NULL," ");
            i++;
        }
        line[i] = NULL; //sets the last value to null
        strcpy(execPath, "/bin/"); //copies "/bin/" to the path          
        strcat(execPath, line[0]); //creates a "/bin/{command}" string          

        int pid= fork();   //begins fork           

        if(pid < 0){
            printf("FORK ERROR"); //if no fork, print error
        }
        if(pid==0){               
            execvp(execPath,line); //if there is child, execute

        }                    
        
        wait(NULL);
        printf("Child %d exited\n" , getpid());
        //endloop
    }

    return 0;
}


