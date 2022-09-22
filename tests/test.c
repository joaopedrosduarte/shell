#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int release = 0;

int main(){
  while (1){
    if (release == 0){
        producer();
        semWait(n);
        if (n < budder){
            append();
            n++;
            semSignal(n);
        } else {
            realease = 1;
        }
    } else {
        semWait(release);
    }
  }
}