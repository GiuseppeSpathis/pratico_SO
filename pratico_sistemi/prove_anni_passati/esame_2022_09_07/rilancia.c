
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

/*
Scrivere un programma C rilancia: che esegua il programma indicato in argv[1] 
con i relativi parametri (in argv[2] e seguenti): es: rilancia tr a-z A-Z esegue il comando
tr coi parametri. Se il programma lanciato termina senza errori (non per colpa di un segnale 
e con valore di ritorno 0) rilancia deve rieseguire il programma (nell'esempio tr) con i 
medesimi parametri.
*/
#define BUFF_SIZE 4096

int main(int argc, char *argv[]){
    while(1){
        int value = fork();
        if(value==0){ //figlio
           // char path[2048];
            //sprintf(path, "%s%s", "/bin/",argv[1]);
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
            if(status==EXIT_SUCCESS){
                continue;
            }
            else{
                return 0;
            }
        }
    }
	return 0;
}