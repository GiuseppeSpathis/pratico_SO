/*
   devi stampare il proprio pid e attendere segnali
   */
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/sysmacros.h> 


/*
bisogna stampare i pid dei processi attivi che sono stati lanciati con una specifica riga di 
comando (devono coincidere tutti gli argomenti)
es:
    il comando "pidcmd less /etc/hostname" deve stampare il numero di processi attivi che sono
    stati lanciati con "less /etc/hostname"

aiuto: cercare nelle sottodirectory dei processi in /proc i file chiamati cmdline
*/
#define BUFF_SIZE 2048

int main(int argc, char *argv[]){
    DIR * dir = opendir("/proc");
    struct dirent * entry;
    int number = 0;

    while((entry = readdir(dir)) != NULL){
        if((entry->d_type == DT_DIR) && (atoi(entry->d_name)!=0)){
            char tmp[BUFF_SIZE];
            sprintf(tmp, "%s%s%s", "/proc/", entry->d_name, "/cmdline");
            //printf("controllo il cmdline  %s \n", tmp);
            int fd = open(tmp, O_RDONLY);
            char buff[20][BUFF_SIZE];
            for(int i=0; i<argc-1; i++){
                read(fd, buff[i], strlen(argv[i+1]));
                lseek(fd,1, SEEK_CUR);
            }
            int are_not_equal = 0;
            for(int i = 0; i<argc-1; i++){
                if(strcmp(argv[i+1], buff[i]) != 0){
                    are_not_equal = 1; 
                }
            }
            if(!are_not_equal){
                number++;
            }    
        }
    }
    closedir(dir);

	return 0;
}
