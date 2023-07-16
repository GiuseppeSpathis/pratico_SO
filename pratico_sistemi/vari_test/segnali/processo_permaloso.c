#include <unistd.h>
#include <stdio.h>
#include <signal.h>



static void handler(int signo, siginfo_t *info, void *arg){ //la struttura siginfo_t contiene tantissime info sul processo che ha lanciato il segnale, vedere il man
    printf("received %d from %d\n",signo, info->si_pid);
    kill(info->si_pid, SIGKILL);
}

int main(int argc, char *argv[]){ 
    int c;
    static struct sigaction act ;
    act.sa_sigaction = handler; //usiamo sigaction invece di sighandler per avere piu' informazioni
    act.sa_flags = SA_RESTART | SA_SIGINFO; //SA_SIGINFO serve a ottenere le informazioni su chi ha inviato il segnale
    sigfillset(&act.sa_mask);
    int signo;

    for(signo=0; signo<32; signo++)   //setto l'handling di uccidere il processo che mi invia il segnale per tutti i segnali
        sigaction(signo, &act, NULL);

    for(;;)
        pause(); 
}
