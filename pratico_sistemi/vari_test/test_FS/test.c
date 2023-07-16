#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syscall.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h> 
int main(int argc, char *argv[])
{ /*
     // test getcwd
     char *buff = NULL;
     char *d;
     d = getcwd(buff, 0);
     printf("stampo il path assoluto della directory corrente = %s \n", d);
     // test mkdir
     if (mkdir("./pippo", S_IRUSR | S_IXUSR | S_IWUSR | S_IWGRP | S_IXGRP | S_IRGRP | S_IROTH | S_IWOTH | S_IXOTH) == 0)
     {
         printf("la cartella pippo e' stata creata con successo \n");
         sleep(5);
         rmdir("./pippo");
     }
     // test link
     if (link("./test.c", "./hardlink.c") == 0)
     {
         printf("l'hard link e' avvenuto con successo \n");
         sleep(5);
         unlink("./hardlink.c");
     }
     if (symlink("./test.c", "./symlink.c") == 0)
     {
         printf("il symbolic link e' avvenuto con successo \n");
         sleep(5);
         unlink("./symlink.c");
     }
     // test stat
     struct stat filestat;
     if (stat("./test.c", &filestat) == 0)
     {
         printf("la system call stat e' andata a buon fine e la dimensione del file e' = %ld byte", filestat.st_size);
     }
    // test chown
    setuid(0);
    setgid(0);
    struct stat filestat1;
    stat("./tmp.txt", &filestat1);
    printf("il proprietario id e' = %d e il gruppo id e' = %d \n", filestat1.st_uid, filestat1.st_gid);
    struct stat filestat2;
    chown("./tmp.txt", 0, 0);
    stat("./tmp.txt", &filestat2);
    printf("il nuovo proprietario id e' = %d  e il nuovo gruppo id e' = %d \n", filestat2.st_uid, filestat2.st_gid);
    chown("./tmp.txt", 1000, 1000);

    //test truncate
    struct stat filestat3;
    stat("./tmp.txt", &filestat3);
    size_t old_size = filestat3.st_size;
    printf("la dimensione del file e' = %ld \n", old_size);
    truncate("./tmp.txt", old_size + 200);
    stat("./tmp.txt", &filestat3);
    printf("la nuova dimensione del file e' = %ld \n", filestat3.st_size);
    truncate("./tmp.txt", old_size);
    // test open,read,lseek
    
    int fdInput = open("./fileInput.txt", O_RDONLY);
    int fdOutput = open("./fileOutput.txt", O_WRONLY | O_CREAT | O_TRUNC);
    const int buff_size = 1024;
    char buff[buff_size];
    int offset = lseek(fdInput, 2,SEEK_SET); //parto con la read dopo il secondo byte
    int n_byte_letti;
    while ((n_byte_letti = read(fdInput, buff, buff_size)) > 0)
    {
        printf("byte copiati = %d \n", n_byte_letti);
        write(fdOutput, buff, n_byte_letti);
    }
    close(fdInput);
    close(fdOutput);
*/
    return 0;
}