/*
   devi stampare il proprio pid e attendere segnali
   */
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

/*
Se si esegue il programa dell'esercizio 1 in questo modo: rilancia cat /etc/hostname 
il comando (cat) viene eseguito ripetutamente all'infinito. Modificare il programma 
rilancia per fare in modo che se l'esecuzione del programma (in questo caso cat /etc/hostname) 
dura meno di un secondo non si proceda alla riattivazione.
*/
#define BUFF_SIZE 4096

int main(int argc, char *argv[]){
    while(1){

        time_t current_time;
        long start_time  = time(NULL);

        int value = fork();
        if(value==0){ //figlio
           
            char **myargv = NULL;
            for(int i=0; i<argc - 1; i++){
                myargv = realloc(myargv, i * sizeof(char*));
                myargv[i] = argv[i+1];
            }
            myargv[argc-1] = NULL;

            execvp(myargv[0], myargv);
            
        }
        else{//padre
            int status;
            wait(&status);
            long end_time = time(NULL);
            long tempo_trascorso = end_time - start_time;
            if(tempo_trascorso < 1)
                return 0;
            if(status == EXIT_SUCCESS){
                continue;
            }
            else{
                return 0;
            }
        }
    }
    

	return 0;
}


