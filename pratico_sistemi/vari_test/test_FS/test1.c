#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syscall.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/sysmacros.h> 

int main(int argc, char *argv[])
{/*
    // test opendir, readdir, closedir
    DIR * dir = opendir(".");
    struct dirent * entry;
    while((entry = readdir(dir)) != NULL){
        printf("nome file = %s \n", entry->d_name);
    }

    //test mknode e makedev
    if(mknod("devCaratteri", S_IFCHR | 0777, makedev(1, 3)) != - 1){
        printf("creazione del device a caratteri avvenuta con successo \n");
        
    }
    chmod("devCaratteri", 0666);
    if(mknod("devBlocchi", S_IFBLK | 0777, makedev(1, 3)) != - 1){
        printf("creazione del device a blocchi avvenuta con successo \n");
        
    }
    chmod("devBlocchi", 0666);
    sleep(4);
    unlink("devCaratteri");
    unlink("devBlocchi");
    */
    //test pipe
    int fdpipe[2];
    pipe(fdpipe);
    int value = fork();
    if(value == 0){ //figlio
        close(fdpipe[1]);
        char buff[20];
        read(fdpipe[0], buff, sizeof(buff));
        printf("ho letto da mio padre %s \n", buff);
    }
    else { //padre
        close(fdpipe[0]);
        write(fdpipe[1], "ciao", 5);
    }
    return 0;
}