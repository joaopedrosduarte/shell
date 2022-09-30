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

int sequential(int max,char *args[max/2+1], int argsLen, int isPipe)
{
    if (isPipe != 0){
        char *argsPipe1[max/2+1];
        char *argsPipe2[max/2+1];
        argsPipe1[0] = args[0];
        argsPipe1[1] = args[1];
        argsPipe2[0] = args[2];
        argsPipe2[1] = args[3];

        int p[2];
        if (pipe(p) == -1){
            /*
            TODO: TRATAR ERRO DE CRIAÇÃO DE PIPES
            */
        } 
        int pidWriter = fork();
        if (pidWriter == -1){
            /*
            TODO: TRATAR ERRO DE CRIAÇÃO DE FILHO ESCRITOR
            */
        }

        if (pidWriter == 0){
            dup2(p[1], STDOUT_FILENO);
            close(p[0]);
            close(p[1]);
            execvp(argsPipe1[0],argsPipe1);
        }

        int pidReader = fork();
        if (pidReader == -1){
            /*
            TODO: TRATAR ERRO DE CRIAÇÃO DE FILHO LEITOR
            */
        } 

        if (pidReader == 0){
            dup2(p[0], STDIN_FILENO);
            close(p[0]);
            close(p[1]);
            execvp(argsPipe2[0],argsPipe2);
        }

        close(p[0]);
        close(p[1]);

        waitpid(pidWriter,NULL,0);
        waitpid(pidReader,NULL,0);
        return 1;

    } else {
        if (strcmp(args[0],"!!") == 0){
            strcpy(args[0],getLastComand());
            if (strcmp(getLastComand(),"No commands") == 0){
                printf("%s\n",getLastComand());
                return 1;
            }
            formatArgs(max,args[0],args);
        }

        if (strcmp(args[0],"exit") == 0){
            return 0;
        }
        else if (strcmp(args[0],"style") == 0){
            if (strcmp(args[1],"sequential") == 0){
                setStyle(0);
            } 
            else if (strcmp(args[1],"parallel") == 0){
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
                execvp(args[0],args);
                exit(pid);
            } else { // Parent process
                wait(NULL);
            }
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