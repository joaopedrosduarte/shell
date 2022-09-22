#include <stdio.h>
#include "values.h"

int STYLE = 1;
int DELIVER;
int *LAST_COMAND;

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