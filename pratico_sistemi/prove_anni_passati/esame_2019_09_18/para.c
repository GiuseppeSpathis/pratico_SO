#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
scrivere un programma para per lanciare parallelamente comandi
para sleep 20 // ls -l // ps // sleep 3
deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti
*/
#define N_COMMANDS 20

int main(int argc, char *argv[]) {

    char **argvs[N_COMMANDS];

    int count = 0;
    int i = 1;
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
    for(int i = 0; i < count; i++){
        int pid = fork();
        if (pid==0){ //sono il figlio
            execvp(argvs[i][0], argvs[i]);
            _exit(0);
        }
        if(pid > 0){ //sono il padre
            children[i] = pid;
        }
    }
   
    for(int i=0; i < count; i++){
        int status;
        waitpid(children[i], &status, 0);
        printf("il figlio %d ha terminato con successo \n", children[i]);

    }
    
}
