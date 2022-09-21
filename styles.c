#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "styles.h"
#include "values.h"

int sequential(int max, char *args[max/2+1], int argsLen, int current);
int parallel(int max, char *args[max/2+1], int argsLen, int current);

int sequential(int max,char *args[max/2+1], int argsLen, int current)
{
    if (strcmp(args[current],"exit") == 0){
        return 0;
    }
    else if (strcmp(args[current],"style") == 0){
        current++;
        if (strcmp(args[current],"sequential") == 0){
            setStyle(0);
        } 
        else if (strcmp(args[current],"parallel") == 0){
            setStyle(1);
        } else {
            printf("Style invalido\n");
        }
    } else {
        pid_t pid;
        pid = fork();

        if (pid < 0){
            /*
            TODO: TRATAMENTO DE ERROS 
            */
        } 
        else if (pid == 0){ // Child Process
                execvp(args[current],args);
                exit(pid);
        } else { // Parent process
            wait(NULL);
        }
    }
    //getStyle();
    return 1;
}

int parallel(int max,char *args[max/2+1], int argsLen, int current)
{
    if (strcmp(args[current],"exit") == 0){
        return 0;
    }
    else if (strcmp(args[current],"style") == 0){
        current++;
        if (strcmp(args[current],"sequential") == 0){
            setStyle(0);
        } 
        else if (strcmp(args[current],"parallel") == 0){
            setStyle(1);
        } else {
            printf("Style invalido\n");
        }
    } else {
        pid_t pid;
        pid = fork();

        if (pid < 0){
            /*
            TODO: TRATAMENTO DE ERROS 
            */
        } 
        else if (pid == 0){ // Child Process
                execvp(args[current],args);
                exit(pid);
        } else { // Parent process
            wait(NULL);
        }
    }

    return 1;
}