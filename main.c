#include <stdio.h>
#include "shellModels.h"

#define BATCH 1
#define INTERACTIVE 0

int main(int argc, char *argv[])
{
    int *style;
    int model;

    if (argc >= 2){
        model = BATCH;
    } 
    else if (argc == 1){ 
        model = INTERACTIVE;
    } else {
        /*
        TODO: Tratar os erros de argcs maiores ou menosres que 1 e 0
        */
    }
    
    shell(model);
    
	return 0;
}