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
//prende come parametro il pathname di una directory
//cerca tutti i link simbolici dentro la directory e trasformarli in link simbolici che puntano al path name assoluto e non relativo


int main(int argc, char *argv[]){
	DIR * dir = opendir(argv[1]);
    struct dirent * entry;
    
    while((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_LNK){  //il file e' un link simbolico
            char path_relativo[1024];
            char path_sl[1024];
            sprintf(path_sl, "%s%s%s", argv[1], "/", entry->d_name); //ottengo il path relativo del link simbolico
            printf("il path del link simbolico e' %s \n", path_sl);

            ssize_t len = readlink(path_sl, path_relativo, sizeof(path_relativo)); //ottengo il path relativo del file al quale punta il link simbolico
            path_relativo[len] = '\0';
            printf("il path relativo del link simbolico e' %s \n", path_relativo);

            char path_assoluto[1024];   
            realpath(path_relativo, path_assoluto);  //ottengo il path assoluto da un path relativo

            unlink(path_sl);
            symlink(path_assoluto, path_sl);
            //queste righe in seguito servono solo a vedere se e' tutto giusto
            char read_path[1024];
            ssize_t len1 = readlink(path_sl, read_path, sizeof(read_path));
            read_path[len] = '\0';
            printf("il path assoluto del link simbolico e' %s \n", read_path);

           
            
        }
        
    }
	return 0;
}
