//Separar os comandos futuros e os proximos comandos 
int formatArgs(int max, char *args, char *arrayArgs[max/2+1]);
//Separar os comandos de escrita e de leitura do pipe
void formatForPipe(int max,char cmd[41], char *args[41]);