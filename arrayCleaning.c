#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "values.h"
#include "arrayCleaning.h"

int arrayCleaning(char cmd[41], char *args[41])
{
    char *slice;
    char cmd2[41];

    char elm[2] = ";";
    char elm2[2] = "  ";
    char *space = " ";

    int i = 0, n = 0, count = 0;
    int lock = 1;

    slice = strtok(cmd,elm);
    args[i] = slice; i++;
    while (slice != NULL)
    {
        slice = strtok(NULL,elm);
        args[i] = slice;
        if(slice != NULL)
            i++;
    }

    if (!getDeliver()){
        if (args[i-1][strlen(args[i-1])-1] == '\n' && getDeliver() == 0){
            args[i-1][strlen(args[i-1])-1] = '\0';
        }
    }

    if(getDeliver()){
        i--;
    }

    for (int j = 0;j < i;j++)
    {
        char newArg[41] = "";
        strcpy(cmd2,args[j]);
        slice = strtok(cmd2,elm2);
        strcat(newArg,slice);
        while (slice != NULL)
        {
            slice = strtok(NULL,elm2);
            if (slice != NULL){
                count++;
                strcat(newArg,space);
                strcat(newArg,slice);
            }
        }
        strcpy(args[j],newArg);
    }
 
    return i;
}
