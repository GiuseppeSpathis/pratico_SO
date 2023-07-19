#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


/*
usando “getopt” consentire di scegliere il grado di parallelismo voluto:             
pcp -j 8 file1 file2 
deve creare 8 processi, ogni processo copia 1/8 del file.
*/

#define BUFF_SIZE 2
int main(int argc, char *argv[]) {
    if(strcmp(argv[1], "-j") != 0){
        execve("./pcp", argv, NULL); 
    }
    else{
        int n_children = atoi(argv[2]);

        int fileInput = open(argv[3], O_RDONLY); 
        int fileOutput = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC); 
        int file_size = lseek(fileInput, 0, SEEK_END);
        int max_byte_to_read = file_size/n_children;
        
        for(int i = 0; i<n_children; i++){
            int pid = fork();
            if(pid == 0){ //sono il figlio
                printf("sono il figlio %d e ho offset %d \n",i,i * max_byte_to_read);
                int n_byte_letti_totali = 0;
                int n_byte_letti;
                char buff[BUFF_SIZE];

                while ((n_byte_letti = pread(fileInput, buff, BUFF_SIZE, i * max_byte_to_read + n_byte_letti_totali)) > 0){ 
                    
                    printf("sono il figlio %d byte copiati = %d \n",i, n_byte_letti);
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
