/*
devi stampare il proprio pid e attendere segnali
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>

static void handler(int signo, siginfo_t *info, void *arg){

//estrazione stringa dal long
long msg_long = (long)info->si_value.sival_ptr;
const unsigned long SIZE = sizeof(msg_long);
char str_out[SIZE];
for(int i=0; i<SIZE; i++){
    str_out[i] = msg_long % 256; //2^8=256, otteniamo il byte meno significativo
    msg_long = msg_long >> 8;  //shiftare di 8 a destra serve a rimuovere il byte meno significativo e a far avanzare gli altri byte
}
str_out[SIZE] = '\0';
//fine estrazione
printf("ricevuto %s", str_out);


    //printf("ricevuto segnale numero %d che ha come messaggio %s\n",signo, (char *)value.sival_ptr);
}

int main(){
    static struct sigaction act ;
    act.sa_sigaction = handler; //usiamo sigaction invece di sighandler per avere piu' informazioni
    act.sa_flags = SA_RESTART | SA_SIGINFO; //SA_SIGINFO serve a ottenere le informazioni su chi ha inviato il segnale
    sigemptyset(&act.sa_mask);
    /*
    int signo;
    for(signo=0; signo<32; signo++)   //setto l'handling per tutti i segnali
        sigaction(signo, &act, NULL);
    */
    sigaction(SIGINT, &act, NULL);

    int pid = getpid();
    printf("il mio pid e' %d \n", pid);
    
    pause();
    return 0;
}