#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int c = 5;
    int id = fork(); // crea due thread figlio e padre, la fork ritorna 0 se sei il figlio, il pid del figlio se sei il padre
    printf("le variabili fra figlio e padre non sono condivise \n");
    if (id == 0)
    {
        printf("sono il processo figlio e questo e' il mio id = %d \n", getpid());
        c = 6;
        _exit(0);
        printf("variabile c = %d \n", c);
    }
    else
    {
        printf("sono il padre e questo e' l'id di mio figlio=%d \n", id);
        c = 10;
        printf("variabile c = %d", c);
    }
    return 0;
}