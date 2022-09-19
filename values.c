#include <stdio.h>

int STYLE = 0;

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