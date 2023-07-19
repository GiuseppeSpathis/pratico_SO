/*
   devi stampare il proprio pid e attendere segnali
   */
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/*
Usando inotify creare il programma neverm che controlli una directory. Ogni volta che viene
cancellato un file nella directory sotto osservazione crei un file vuoto di uguale nome. Per esempio
eseguendo
neverm dir
dove dir e' una directory contenente i file a, b, c, anche a seguito dei comandi 'rm dir/a' e 'rm dir/b',
dir deve contenere sempre i file a, b e c, a e b saranno file vuoti.

*/

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

int main(int argc, char *argv[])
{
    char buffer[BUF_LEN];
    struct inotify_event *event;
    int fd = inotify_init();
    int wd = inotify_add_watch(fd, argv[1], IN_DELETE); // wd e' un intero chiamato watch
    int length = 0;
    
    while (1)
    {
        length = read(fd, buffer, BUF_LEN);
        // Gestisci ogni evento ricevuto
        int i = 0;
        while (i < length)
        {
            event = (struct inotify_event *)&buffer[i];
            if (event->mask & IN_DELETE)
            { 
                chdir(argv[1]);
                int fd = open(event->name, O_CREAT, S_IRUSR | S_IWUSR);
           }
            i += EVENT_SIZE + event->len;
        }
    }

    return 0;
}
