#include <stdio.h>
#include <string.h>
#include "values.h"

int STYLE = 0;
int DELIVER;
char LAST_COMAND[180/2+1] = "No commands";

int hasPipe(int max,char args[max/2+1]){
    char aux[max/2+1], *slice;
    strcpy(aux,args);
    if (strchr(aux,'|')){
        return 0;
    } else {
        return 1;
    }

}

void setLastComand(int max,char args[max/2+1]){
    strcpy(LAST_COMAND,args);
}

char *getLastComand(){
    return LAST_COMAND;
}

int isArqAvaiable(FILE *arq,char *array){
    if ((arq = fopen(array,"r"))){
        fclose(arq);
        return 1;
    } else {
        return 0;
    }
}

int setStyle(int valor){
    if (valor < 0){
        printf("valor invalido\n");
        return 1;
    } else if (valor > 1){
        printf("valor invalido\n");
        return 1;
    } else {
        STYLE = valor;
    }

    return 0;
}

int getStyle(){
    return STYLE;
}

int setDeliver(int valor){
    if (valor < 0){
        printf("valor invalido\n");
        return 1;
    } else if (valor > 1){
        printf("valor invalido\n");
        return 1;
    } else {
        DELIVER = valor;
    }

    return 0;
}

int getDeliver(){
    return DELIVER;
}