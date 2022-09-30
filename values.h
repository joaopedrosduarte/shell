//Função para setar o valor da variavel style
int setStyle(int valor);
//Função para acessar o valor da variavel style
int getStyle();
//Verifica se o arquivo pode ser aberto ou existe
int isArqAvaiable(FILE *arq, char *array);
//Função para acessar o valor da variavel Deliver
int getDeliver();
//Função para setar o valor da variavel Deliver
int setDeliver();
//Função para setar o valor da variavel LastComand
void setLastComand(int max, char *args);
//Função para acessar o valor da variavel LastComand
char *getLastComand();
//Função para verificar se o comando tem um | no meio, ou seja, tem um pipe
int hasPipe(int max, char *args);