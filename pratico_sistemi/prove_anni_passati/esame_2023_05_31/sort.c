#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *myargv[] = {"less","/etc/hostname", NULL};
    printf("il mio pid e' %d \n", getpid());
    execve("/bin/less", myargv, NULL);
    return 0;
}