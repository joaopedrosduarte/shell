#include <stdio.h>
#include <string.h>
#include "formatArgs.h"

int formatArgs(int max,char *args, char *arrayArgs[max/2+1]){
    char *slice;
    int i = 0;

    slice = strtok(args," ");
    arrayArgs[i] = slice; i++;

    while (slice != NULL){
        slice = strtok(NULL," ");
        arrayArgs[i] = slice;
        i++;
    }

    return i;
}

void formatForPipe(int max,char cmd[max], char *args[max]){
    char *slice;

    slice = strtok(cmd,"|");
    args[0] = slice;
    slice = strtok(NULL,"|");
    args[1] = slice;
}