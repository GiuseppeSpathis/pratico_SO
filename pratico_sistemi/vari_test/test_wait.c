#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pid = fork();
    if(pid){
        int childStatus;
        int childPid = wait(&childStatus);
        printf("il pid di mio figlio e' %d e il suo stato e' %d \n", childPid, WEXITSTATUS(childStatus));
    }
    else{
        printf("ciao sono il figlio e il mio pid e' %d \n", getpid());
        _exit(5);
    }
    return 0;
}