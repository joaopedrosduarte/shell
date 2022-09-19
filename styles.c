#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "styles.h"
#include "values.h"

int sequential(int max, char *args[max/2+1], int argsLen, int current);
int parallel(char *args[], int argsLen, int current);

int sequential(int max,char *args[max/2+1], int argsLen, int current)
{
    if (strcmp(args[current],"exit") == 0){
        return 0;
    }
    else if (strcmp(args[current],"style sequential") == 0){
        setStyle(0);
    } 
    else if (strcmp(args[current],"style parallel") == 0){
        setStyle(1);
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

int parallel(char *args[], int argsLen, int current)
{
    printf("Paralelo\n");
    for (current;current < argsLen;current++){
        if (strcmp(args[current],"exit") == 0){
            return 0;
        }
        else if (strcmp(args[current],"style sequential") == 0){
            setStyle(0);
        } 
        else if (strcmp(args[current],"style parallel") == 0){
            setStyle(1);
        } else {
            printf("deu certo\n");
        }
    }
    /*
        TODO: Completar o paralelo
    */
    return 0;
}