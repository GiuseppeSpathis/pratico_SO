#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/*
estendere para a paran che ha un parametro che indica il numero massimo di esecuzioni concorrenti:
paran 3 sleep 20 // ls -l // ps // sleep 3
al max esegue 3 comandi in parallelo, quindi esegue i primi 3 comandi, qundo uno fra essi termina
ne attiva un successivo e cosi' via
*/
#define N_COMMANDS 20

int main(int argc, char *argv[]) {

    char **argvs[N_COMMANDS];
    int max_proc = atoi(argv[1]);

    int count = 0;
    int i = 2;
    int tmp = 0;

    while(argv[i] != NULL){
        
        argvs[count] = realloc(argvs[count], tmp * sizeof(char*));
        
        if(strcmp(argv[i], "//") != 0){ //le due stringhe sono uguali
            argvs[count][tmp] = argv[i];
            tmp++;
        }
        else{
            tmp = 0;
            count ++;
        }
        i++;
    }
    count++;


    int children[count];
    int n_active_children = 0;  //serve a implementare il fatto di avere max max_proc in concorrenza
    for(int i = 0; i < count; i++){
        
        while(n_active_children >= max_proc){
            wait(NULL);
            n_active_children--;
        }
        
        int pid = fork();
        if (pid==0){ //sono il figlio
            execvp(argvs[i][0], argvs[i]);
            printf("mando segnale a %d", getppid());
            kill(getppid(), SIGINT);
            _exit(0);
        }
        if(pid > 0){ //sono il padre
            n_active_children++;
            children[i] = pid;
        }
    }
   
    for(int i=0; i < count; i++){
        int status;
        waitpid(children[i], &status, 0);
        printf("il figlio %d ha terminato con successo \n", children[i]);

    }
    
}
