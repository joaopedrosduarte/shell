#include <stdio.h>
#include <string.h>
#include "styles.h"
#include "shellModels.h"
#include "arrayCleaning.h"
#include "values.h"
#include "formatArgs.h"

#define MAX_LINE 80
#define SEQUENTIAL 0
#define PARALLEL 1
#define BASH 1
#define INTERACTIVE 0

int shell(int model, char *fileName)
{
    int shouldRun = 1;
    FILE *arq;
    char line[MAX_LINE];
    int lock = 1;
    char styleHead[] = "seq";
    char *args[MAX_LINE/2 + 1];
    setDeliver(0);

    arq = fopen(fileName,"r");

    while (shouldRun == 1)
    {
        if (getDeliver() == 1){
            lock = 0;
        }

        strcpy(line,"");

        if (getStyle() == SEQUENTIAL){
            strcpy(styleHead,"seq");
        } else if (getStyle() == PARALLEL) {
            strcpy(styleHead,"par");
        }

        //printf("( Model : %d - style : %d - should run : %d - StyleHead : %s )\n",model, style, shouldRun, styleHead);
        fflush(stdout);
        if (model == INTERACTIVE){
            printf("jpds %s> ",styleHead);
            if (fgets(line,MAX_LINE/2+1,stdin)){
                while(line[0] == '\n'){
                    printf("jpds %s> ",styleHead);
                    fgets(line,MAX_LINE/2+1,stdin);
                }
            }
        }
        else if (model == BASH && lock == 1){
            printf("jpds %s> ",styleHead);
            fgets(line,MAX_LINE/2+1,arq);
            if (line[0] == EOF){
                printf("%d\n",getDeliver());
                lock = 0;
            } 
            else if (line[strlen(line)-1] == '\0'){
                setDeliver(1);
                printf("%s\n",line);
            }

            else if (line[strlen(line)-1] == '\n'){
                line[strlen(line)-1] = '\0';
                printf("%s\n",line);
            }
        }

        if (shouldRun == 1 && lock == 1) {
            int const argsLen = arrayCleaning(line, args);

            if (getStyle() == SEQUENTIAL)
            {    
                for (int i = 0;i < argsLen;i++){
                    char atualArrayArgs[MAX_LINE/2+1];
                    char *newArrayArgs[MAX_LINE/2+1];
                    
                    strcpy(atualArrayArgs,args[i]);
                    
                    if (strcmp(atualArrayArgs,"!!") != 0){
                        setLastComand(MAX_LINE, atualArrayArgs);
                    }

                    if (hasPipe(MAX_LINE, atualArrayArgs) == 0){
                        formatForPipe(MAX_LINE, atualArrayArgs, newArrayArgs);
                        char *auxGeral[MAX_LINE/2+1];
                        char *argsPipe1[MAX_LINE/2+1];
                        int lenPipe1;
                        char *argsPipe2[MAX_LINE/2+1];
                        int lenPipe2;
                        int j = 0;

                        arrayCleaning(newArrayArgs[0],argsPipe1);
                        lenPipe1 = formatArgs(MAX_LINE, argsPipe1[0], argsPipe1);
                        
                        arrayCleaning(newArrayArgs[1],argsPipe2);
                        lenPipe2 = formatArgs(MAX_LINE, argsPipe2[0], argsPipe2);

                        for (int i = 0;i < 4;i++){
                            if (i < 2){
                                auxGeral[i] = argsPipe1[i];
                            } else {
                                auxGeral[i] = argsPipe2[i-2];
                            }
                        }

                        shouldRun = sequential(MAX_LINE, newArrayArgs, 0, 1);

                    } else {
                        int newArgsLen = formatArgs(MAX_LINE, atualArrayArgs, newArrayArgs);
                        
                        shouldRun = sequential(MAX_LINE, newArrayArgs, newArgsLen, 0);
                    }
                }
            } else {
                shouldRun = parallel(MAX_LINE, args, argsLen, 0);
            }     
        }
    }

    return 0;
}