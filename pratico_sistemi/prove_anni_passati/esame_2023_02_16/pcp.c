#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/*
Fare un programma di copia parallelo di file.
    pcp file1 file2 
dove file1 e' il file in input che deve essere copiato e file2 e' il file dove bisogna copiare
pcp deve creare due processi figli;
mentre un processo copia la prima meta’ del file, l'altro deve copiare l’altra meta’.
*/

//idea: mi calcolo quanto e' la prima meta del file e faccio incominciare la copiatura del secondo figlio da quel punto con
//la pread e pwrite
#define BUFF_SIZE 2
int main(int argc, char *argv[]) {

    int fileInput = open(argv[1], O_RDONLY); 
    int fileOutput = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC); 
    int file_size = lseek(fileInput, 0, SEEK_END);
    int max_byte_to_read = file_size/2;


    for(int i = 0; i<2; i++){
        int pid = fork();
        if(pid == 0){ //sono il figlio
            int pid = fork();
            if(pid == 0){ //sono il figlio
                int n_byte_letti_totali = 0;
                int n_byte_letti;
                char buff[BUFF_SIZE];

                while ((n_byte_letti = pread(fileInput, buff, BUFF_SIZE, i * max_byte_to_read + n_byte_letti_totali)) > 0){ 
                    
                    pwrite(fileOutput, buff, n_byte_letti, i * max_byte_to_read + n_byte_letti_totali);
                    n_byte_letti_totali += n_byte_letti; 
                    if(n_byte_letti_totali >= max_byte_to_read){
                        _exit(0);
                    }
                }
            }
        }
    }
}
