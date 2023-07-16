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

#define N_COMMANDS 20

int main(){
    
    char commands[N_COMMANDS][2048];
    char **argvs[N_COMMANDS];

    int count = 0;
    while(fgets(commands[count], sizeof(commands[count]), stdin) != NULL){
        
        commands[count][strcspn(commands[count], "\n")] = 0;
        char *token = strtok(commands[count], " ");
        int argc = 0;
        argvs[count] = NULL;
        while (token != NULL) {
            argc++;
            argvs[count] = realloc(argvs[count], argc * sizeof(char*));
            argvs[count][argc - 1] = token;
            token = strtok(NULL, " ");
        }
        argvs[count] = realloc(argvs[count], (argc + 1) * sizeof(char*));
        argvs[count][argc] = NULL;
        free(token);
        count ++;
    }
    
    // Crea le pipe per collegare i comandi
    int pipes[count][2];
    for (int i = 0; i < count; i++) {
        pipe(pipes[i]);
    }

// Esegui i comandi in sequenza, concatenando le pipe tra di essi
    int pid;
    for (int i = 0; i < count; i++) {
        pid = fork();
        if (pid == 0) {  // processo figlio
            if (i > 0) {  // se non è il primo comando, leggi l'input dalla pipe precedente
                dup2(pipes[i - 1][0], 0);
                close(pipes[i - 1][0]);
                close(pipes[i - 1][1]);
            }
            if (i < count - 1) {  // se non è l'ultimo comando, scrivi l'output sulla pipe successiva
                dup2(pipes[i][1], 1);
                close(pipes[i][0]);
                close(pipes[i][1]);
            }
            execvp(argvs[i][0], argvs[i]);  // esegui il comando
        }
    
        else{// processo padre
        if (i > 0) {  // se non è il primo comando, chiudi l'estremità di lettura della pipe precedente
            close(pipes[i - 1][0]);
            close(pipes[i - 1][1]);
        }
        // aspetta il completamento del processo figlio corrente
        waitpid(pid, NULL, 0);
        }
    }

    // Dealloca la memoria allocata per i comandi
    for (int i = 0; i < count; i++) {
        free(argvs[i]);
    }

    return 0;
}