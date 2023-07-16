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
	char buffer[BUF_LEN];
	struct inotify_event *event;
	int fd = inotify_init();
	int wd = inotify_add_watch(fd, argv[1], IN_CREATE | IN_MOVED_TO); //wd e' un intero chiamato watch 
	int length = 0;
	int i = 0;
	int fileOutput = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
	while(1){
		length = read(fd, buffer, BUF_LEN);
		// Gestisci ogni evento ricevuto
		while (i < length) {
			event = (struct inotify_event *) &buffer[i];

			if (event->mask & IN_CREATE || (event->mask & IN_MOVED_TO)) {
				write(fileOutput,event->name, strlen(event->name));
				write(fileOutput,"\n", 1);

				char path[1024];
				sprintf(path, "%s%s%s", argv[1], "/", event->name); // Concatena le tre stringhe

				int file_to_read = open(path, O_RDONLY);
				int n_byte_letti;
				char buff[1024];
				while ((n_byte_letti = read(file_to_read, buff, 1024)) > 0){
					write(fileOutput, buff, n_byte_letti);
				}
				write(fileOutput,"\n", 1);
				write(fileOutput,"\n", 1);
				close(file_to_read);  
				unlink(path);       //rimuovo il file     
			}
			i += EVENT_SIZE + event->len;
		}
		i = 0;
	}
	close(fileOutput);

	return 0;
}
