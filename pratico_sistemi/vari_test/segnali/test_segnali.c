#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sigint_handler(int sig) {
    printf("Ricevuto il segnale SIGINT (%d)\n", sig);
    printf("PRRR \n");
}

int main(){
    /*
    //test signal
    int curr_processid = getpid();
    signal(SIGINT, sigint_handler);
    kill(curr_processid, SIGINT);
    
    //test sigaction
    struct sigaction act;
    act.sa_handler = sigint_handler; //handler del segnale
    act.sa_flags = SA_RESTART;  //questo flag dice che se una system call e' interrotta dall'handling di un segnale invece di ritornare errore (-1) essa viene restartata
    sigemptyset(&act.sa_mask); //sa_mask sono i segnali che vengono bloccati quando vi e' l'handling di questo segnale, con questa macro inizializzi la mask a un insieme vuoto, quindi nessun segnale viene mascherato(bloccato)
    sigaction(SIGINT, &act, NULL);

    int curr_processid = getpid();
    kill(curr_processid, SIGINT);

    //test sigsuspend
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigsuspend(&mask) //attendiamo il segnale sigint
*/

    return 0;
    }