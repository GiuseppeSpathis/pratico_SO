/*
devi stampare il proprio pid e attendere segnali
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
// argv[1] e' il path name di una directory vuota
//argv[2] file F
//ogni volta che viene aggiunto un file alla directory, devi aggiungere a F il nome del file aggiunto e il suo contenuto e 
//poi rimuovi il file dalla directory

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))

int main(int argc, char *argv[]){
while(1){
printf("ciao");    
}

    return 0;
}