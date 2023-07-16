/*
devi trasferire a rx stringhe di max 8 caratteri usando i valori assegnati ai segnali (il parametro value della funzione sigqueue)
questo programma ha due parametri il pid di rx e il messaggio
*/
/*
devi stampare il proprio pid e attendere segnali
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
printf("si %ld \n", sizeof(argv[2]));

    if(strlen(argv[2])>8)
        return 0;
    int pidRx = atoi(argv[1]);
    union sigval value;
    //inserimento stringa in un long, puoi inserire al massimo 8 caratteri perche' un long in c ha 8 byte, per essere piu' specifici invece di usare long avremmo dovuto usare int64_t
    long msg_long = 0;
    for(int i=strlen(argv[2])-1; i>=0; i--){ //il for lo faccio partire dalla fine perche' all'inizio mi stampava la stringa la contrario
        msg_long = msg_long << 8; 
        msg_long = msg_long | argv[2][i];
    }
    //fine inserimento
    value.sival_ptr = (void *) msg_long;
    sigqueue(pidRx, SIGINT, value);
    return 0;
}
