//Processo sequencial ou seja uma thread por linha de comando
int sequential(int max, char *args[max/2+1], int argsLen, int current);
//Processo paralelo ou seja uma thread por comando
int parallel(int max, char *args[max/2+1], int argsLen,int current);
//Função para setar o valor da variavel set
int setStyle(int valor);