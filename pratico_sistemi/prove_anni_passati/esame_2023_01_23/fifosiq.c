/*
   devi stampare il proprio pid e attendere segnali
   */
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>

/*
Il programma fifosig è una estensione di fifotext. Le righe che riceve attraverso la named pipe sono
composte da due numeri, il pid di un processo e il numero di un segnale. Per ogni riga correttamente
formata il segnale indicato viene mandato al processo indicato dal pid.
In un esempio simile la precedente il comando echo 12345 15 > ./ff deve causare l'invio del
segnale 15 al processo 12345.
Scrivere il programma fifosig e un programma di prova che scriva nella pipe il proprio pid e il numero
di SIGUSR1 e controlli di ricevere SIGUSR1.
*/
#define BUFF_SIZE 4096
int main(int argc, char *argv[]){
    if(argc > 2){
        printf("error");
        return 0;
    }
    mknod(argv[1], S_IFIFO | 0666, 0);

    char  * buf; 
    while(1){
        int fdFifo = open(argv[1], O_RDONLY);
        buf = malloc(BUFF_SIZE);
        int n_byte_letti;
        while ((n_byte_letti = read(fdFifo, buf, BUFF_SIZE)) > 0){
        }
        int pid = -1;
        int number;
        char *token = strtok(buf, " ");
        int i=0;
        while (token != NULL) {
            if(i==0){
                pid = atoi(token);
            }
            if(i==1){
                number = atoi(token);
                if(number > 31) {
                    printf("hai scelto un valore errato come segnale da mandare");
                    exit(EXIT_FAILURE);
                }
                break;
            }
            token = strtok(NULL, " ");
            i++;
        }
        
        if(pid != -1){
            printf("lancio al pid %d il segnale %d", pid, number);
            kill(pid, number);
        }
        close(fdFifo);
        free(buf);
    }
    


	return 0;
}