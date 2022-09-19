#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    char *args[41];
    char *newArgs[41];
    char cmd2[100];
    char cmd[41];
    char elm[2] = ";";
    char elm2[2] = "  ";
    char *slice, *slice2;
    int *tam;
    int i = 0, lock1 = 1, lock2 = 1, n = 0, k = 0;

    fgets(cmd,40,stdin);

    slice = strtok(cmd,elm);
    args[i] = slice; i++;
    while (slice != NULL)
    {
        slice = strtok(NULL,elm);
        args[i] = slice;
        if(slice != NULL)
            i++;
    }

    while (lock1 != 0)
    {
        if (args[i-1][n] == '\n'){
            args[i-1][n] = '\0';
            lock1 = 0;
        }
        n++;
    }
    strcpy(cmd2, args[0]);

    slice2 = strtok(cmd2, elm2);
    newArgs[k] = slice2; k++;
    for (int in = 0;in < i;in++)
    {
        while (slice2 != NULL)
        {
            slice2 = strtok(NULL,elm2);
            newArgs[k] = slice2;
            if(slice2 != NULL)
                k++;
        }
    }

    

    //for (int k = 0;k < i;k++){
    int limite = 0;
    /*
    for (int k = 0;k < i;k++){
        slice = strtok(args[k],elm2);
        while (slice != NULL && limite < 10)
        {
            slice = strtok(slice,elm2);
            if (slice != NULL){
                newArgs[k] = slice;
                printf("( %s )\n",newArgs[k]);
                break;
            }
            limite++;
        }
    }
    */
    
    
    /* 
    for (int k = 0;k < i;k++){
        int spaceCount = 0;
        n = 0;
        printf("( %s )\n",args[k]);
        while (lock2 != 0)
        {
            if (args[k][n] != '\0'){
                if (args[k][n] == ' '){
                    spaceCount++;
                } else {
                    spaceCount = 0;
                }

                if (spaceCount < 2){
                    newArgs[k][n] = args[k][n];
                    n++;
                }
            } else {
                lock2 = 0;
            }
        }
    }
    */
    
    for (int j = 0; j < i;j++){
        printf("%s\n", args[j]);
    }

    for (int j = 0; j < k;j++){
        printf("%s\n", newArgs[j]);
    }
}