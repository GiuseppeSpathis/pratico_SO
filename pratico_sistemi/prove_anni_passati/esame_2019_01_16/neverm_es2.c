/*
   devi stampare il proprio pid e attendere segnali
   */
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

/*
modificare neverm per fare in modo che neverm ripristini anche il contenuto dei file a seguito della
cancellazione (il modo è lasciato alla creatività del candidato)

*/
//idea: creo per ogni file nella cartella un hard link 
//cosi se il file viene eliminato,creo un nuovo hard link all'hard link
//che ha il nome del file eliminato



#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

#define DIR_SIZE 20



//NON FUNZIONA
int main(int argc, char *argv[])
{   
    char * list_hard_links[DIR_SIZE];

    char buffer[BUF_LEN];
    struct inotify_event *event;
    int fd = inotify_init();
    int wd = inotify_add_watch(fd, argv[1], IN_DELETE); // wd e' un intero chiamato watch
    int length = 0;
    
    while (1)
    {
        //creo hard links
        chdir(argv[1]);
        DIR * dir = opendir(".");
        struct dirent * entry;
        int size = 0;
        while((entry = readdir(dir)) != NULL){
            if(entry->d_type == DT_REG) { //consideri solo i file e non le directory
            printf("elemento %s \n", entry->d_name);
            char *tmp = malloc(strlen("hard_link_") + strlen(entry->d_name) + 1);
            
            sprintf(tmp, "%s%s", "hard_link_", entry->d_name);
            
            link(entry->d_name, tmp);
            
            list_hard_links[size] = tmp;
            size++;
            }
        }
        //return 0;
        length = read(fd, buffer, BUF_LEN);
        // Gestisci ogni evento ricevuto
        int i = 0;
        while (i < length)
        {
            event = (struct inotify_event *)&buffer[i];
            if (event->mask & IN_DELETE)
            {
                char *tmp1 = malloc(strlen("hard_link_") + strlen(event->name) + 1);
                
                sprintf(tmp1, "%s%s", "hard_link_", event->name);

                for(int j = 0; j < size; j++){
                    if(strcmp(tmp1, list_hard_links[j]) == 0){
                        printf("sto creando un link from %s to %s \n",list_hard_links[j],event->name);
                        link(list_hard_links[j], event->name);
                        unlink(list_hard_links[j]);
                        //aggiorno la lista
                        
                        list_hard_links[j] = list_hard_links[size - 1];
                        //strcpy(list_hard_links[j], list_hard_links[size - 1]);
                        printf(" ho messo in posizione %d la stringa %s \n",j, list_hard_links[j]);
                        list_hard_links[size - 1][0] = '\0'; 
                        free(list_hard_links[size - 1]);
                        size --;
                        break;
                    }
                    
                }
                
                //int fd = open(event->name, O_CREAT, S_IRUSR | S_IWUSR);

            }
            i += EVENT_SIZE + event->len;
        }
        for(int j = 0; j < size; j++){
            printf("elimino la stringa %s \n", list_hard_links[j]);
            unlink(list_hard_links[j]);
        }
        
        closedir(dir);
    }

    return 0;
}
