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
//cerca tutti i link simbolici dentro la directory e sostituisce ogni link simbolico che punta ad un file con la copia del file puntato

#define SIZE 2048

int main(int argc, char *argv[]){
    DIR *dir = opendir(argv[1]);
    struct dirent * entry;
    
    while((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_LNK){  //il file e' un link simbolico
            char path_relativo[SIZE];
            char path_sl[SIZE];
            sprintf(path_sl, "%s%s%s", argv[1], "/", entry->d_name); //ottengo il path relativo del link simbolico
            printf("il path del link simbolico e' %s \n", path_sl);

            ssize_t len = readlink(path_sl, path_relativo, sizeof(path_relativo)); //ottengo il path relativo del file al quale punta il link simbolico
            path_relativo[len] = '\0';

            unlink(path_sl); //rimuove il link simbolico
            
            chdir(argv[1]); //setto la current working directory quella passata come parametro

            char path_assoluto[SIZE/2];
            getcwd(path_assoluto, sizeof(path_assoluto));  //getcwd ritorna il path assoluto della working directory
        
            char path_new_hard_link[SIZE];

            sprintf(path_new_hard_link, "%s%s%s", path_assoluto, "/hardlink_", entry->d_name); //ottengo il path relativo del link simbolico
            printf("il path del link fisico e' %s \n", path_new_hard_link);
            //path relativo del file puntato dall'hard link
            //path new hard link: path dove sara' salvato il nuovo hard link
            link(path_relativo,path_new_hard_link); //crea l'hard link, avendo impostato la current working directory come quella
            //associata al path relativo allora al link gli posso passare un path relativo

           
            
        }
        
    }
	return 0;
}
