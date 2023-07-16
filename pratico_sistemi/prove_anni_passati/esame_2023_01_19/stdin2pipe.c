#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 prenda in input due righe di testo, ogni riga contiene un
comando coi rispettivi parametri. Il programma deve lanciare entrambi i comandi in modo tale
l'output del primo diventi input del secondo.
Per esempio, dato il file cmds:
 ls -l
 awk '{print $1}'
l'esecuzione di:
 stdin2pipe < cmds
sia equivalente al comando:
 ls -l | awk '{print $1}'
*/

int main(){
    
    char command1[1024];
    char command2[1024];

    // Leggi i due comandi dallo standard input
    fgets(command1, sizeof(command1), stdin);
    fgets(command2, sizeof(command2), stdin);

    // Rimuovi il carattere di newline dalle stringhe lette
    command1[strcspn(command1, "\n")] = 0; //strcspn restituisce la lunghezza della stringa - tutte le occorrenze di \n (in questo caso 1)
    command2[strcspn(command2, "\n")] = 0;


    //tutto questo codice serve solamente dividere la stringa command1 in varie sottostringhe divise da " " e metterle in myargv con alla fine NULL
    char *token = strtok(command1, " ");
    int argc = 0;
    char **myargv = NULL;
    while (token != NULL) {
        argc++;
        myargv = realloc(myargv, argc * sizeof(char*));
        myargv[argc - 1] = token;
        token = strtok(NULL, " ");
    }
    myargv = realloc(myargv, (argc + 1) * sizeof(char*));
    myargv[argc] = NULL;
    free(token);
    //fine

    //uguale per il comando2
    char *token1 = strtok(command2, " ");
    int argc1 = 0;
    char **myargv1 = NULL;
    while (token1 != NULL) {
        argc1++;
        myargv1 = realloc(myargv1, argc1 * sizeof(char*));
        myargv1[argc1 - 1] = token1;
        token1 = strtok(NULL, " ");
    }
    myargv1 = realloc(myargv1, (argc1 + 1) * sizeof(char*));
    myargv1[argc1] = NULL;
    free(token1);

    //uso una pipe
    int fdpipe[2];
    pipe(fdpipe);
    int pid = fork();
    if(pid == 0){ //figlio
        dup2(fdpipe[0],0);
        close(fdpipe[0]);
        close(fdpipe[1]);
        //il comando 1 deve aspettare per forza un input essendo un comando con input quindi lascia il tempo
        //al padre a eseguire il proprio processo
        execvp(myargv1[0], myargv1);
        free(myargv1);
        exit(0);
    }
    else { //padre
        dup2(fdpipe[1],1);
        close(fdpipe[0]);
        close(fdpipe[1]);
        execvp(myargv[0], myargv);
        free(myargv);

    }
    
    return 0;
}