#include <stdio.h>
#include "shellModels.h"
#include "values.h"

#define BATCH 1
#define INTERACTIVE 0

int main(int argc, char *argv[])
{
    int *style;
    int model;
    FILE *arq;

    if (argc == 2){
        if (isArqAvaiable(arq,argv[1])){
            model = BATCH;
            shell(model, argv[1]);
        } else {
            printf("Arquivo invalido\n");
        }
    } 
    else if (argc == 1){ 
        model = INTERACTIVE;
        shell(model,NULL);
    } else {
        /*
        TODO: Tratar os erros de argcs maiores ou menosres que 1 e 0
        */
    }
    
	return 0;
}