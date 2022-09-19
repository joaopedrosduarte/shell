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

int shell(int model)
{
    int shouldRun = 1;
    char line[MAX_LINE];
    int style;
    char c;
    int argsLen;
    char styleHead[] = "seq";
    char *args[MAX_LINE/2 + 1];

    while (shouldRun == 1)
    {
        style = getStyle();

        if (style == SEQUENTIAL){
            strcpy(styleHead,"seq");
        } else if (style == PARALLEL) {
            strcpy(styleHead,"par");
        }

        //printf("( Model : %d - style : %d - should run : %d - StyleHead : %s )\n",model, style, shouldRun, styleHead);

        printf("jpds %s> ",styleHead);
        fflush(stdout);
        if (model == INTERACTIVE){
            fgets(line,40,stdin);
            while(line[0] == '\n'){
                printf("jpds %s> ",styleHead);
                fgets(line,40,stdin);
            }
        } 
        else if (model == BASH){
        /* 
            TODO:   LEITURA DE ARQUIVO
        */
        }
        
        int const argsLen = arrayCleaning(line, args);

        for (int i = 0;i < argsLen;i++){
            printf("(%s)\n",args[i]);
        }

        for (int i = 0;i < argsLen;i++){
            char atualArrayArgs[MAX_LINE/2+1];
            char *newArrayArgs[MAX_LINE/2+1];
            strcpy(atualArrayArgs,args[i]);

            int newArgsLen = formatArgs(MAX_LINE, atualArrayArgs, newArrayArgs);

            if (style == SEQUENTIAL){
                shouldRun = sequential(MAX_LINE, newArrayArgs, newArgsLen, 0);
            } else {
                shouldRun = parallel(args, argsLen, 0);
            }
        }
    }
    return 0;
}