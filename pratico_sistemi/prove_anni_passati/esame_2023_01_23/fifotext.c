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


/*
Scrivere un programma fifotext che:
* crei una named pipe (FIFO) al pathname indicato come primo (e unico) argomento.
* apra la named pipe in lettura
* stampi ogni riga di testo ricevuta
* se la named pipe viene chiusa la riapra
* se riceve la riga "FINE" termini cancellando la named pipe.
Esempio:
fifotext /tmp/ff
....
se in un altra shell si fornisce il comando: "echo ciao > /tmp/ff", fifotext stampa ciao e rimane in attesa
(questo esperimento si può provare più volte). Con il comando "echo FINE > /tmp/ff" fifotext termina.

*/
#define BUFF_SIZE 2048

int main(int argc, char *argv[]){
    if(argc > 2){
        printf("error");
        return 0;
    }
    mknod(argv[1], S_IFIFO | 0666, 0);

    char  * buf; 
    while(1){
        int fdFifo = open(argv[1], O_RDONLY | O_NONBLOCK);
        buf = malloc(BUFF_SIZE);
        int n_byte_letti;
        while ((n_byte_letti = read(fdFifo, buf, BUFF_SIZE)) > 0){
            if(strstr(buf, "FINE")!=NULL){   //se trovo FINE chiudo la named pipe
                close(fdFifo);
                unlink(argv[1]);
                free(buf);
                return 0;
            }
            printf("%s \n",buf);
        }
        close(fdFifo);
        free(buf);
    }
    


	return 0;
}
