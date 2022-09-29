#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "styles.h"
#include "values.h"
#include "formatArgs.h"

int sequential(int max, char *args[max/2+1], int argsLen, int current);
int parallel(int max, char *args[max/2+1], int argsLen,int current);

int sequential(int max,char *args[max/2+1], int argsLen, int current)
{
    if (strcmp(args[current],"!!") == 0){
        strcpy(args[current],getLastComand());
        printf("%s\n",getLastComand());
        formatArgs(max,args[current],args);
    }

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

int parallel(int max,char *args[max/2+1], int argsLen,int current)
{
    pid_t pid;
    int backup = -1;

    char atualArrayArgs[max/2+1];
    char *newArrayArgs[max/2+1];

    strcpy(atualArrayArgs,args[0]);

    formatArgs(max, atualArrayArgs, newArrayArgs);

    if (strcmp(newArrayArgs[0],"!!") == 0){
        strcpy(args[current],getLastComand());
    }

    if (strcmp(newArrayArgs[0],"exit") == 0){
        return 0; 
    } 
    else if (strcmp(newArrayArgs[0],"style") == 0){
        if (strcmp(newArrayArgs[1],"parallel") == 0){
            setStyle(1);
        }
        else if (strcmp(newArrayArgs[1],"sequential") == 0){
            setStyle(0);
        }
    } else {

        for (int i = 0;i < argsLen;i++)
        {
            backup++;
            pid = fork();
            if (pid < 0){
                /*
                TODO: TRATAMENTO DE ERRO PID
                */
            } 
            else if (pid == 0){
                char atualArrayArgs[max/2+1];
                char *newArrayArgs[max/2+1];
                strcpy(atualArrayArgs,args[backup]);

                formatArgs(max, atualArrayArgs, newArrayArgs);

                execvp(newArrayArgs[0],newArrayArgs);
                exit(pid);
            } 
        }   

        for (int i = 0;i < argsLen;i++){
            if (pid > 0){
                wait(NULL);
            }
        } 

        setLastComand(max, args[argsLen-1]);
    }

    return 1;
}