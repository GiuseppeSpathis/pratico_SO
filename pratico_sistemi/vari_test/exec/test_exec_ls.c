#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *myargv[] = {"ls","-l", NULL};
    execve("/bin/ls", myargv, NULL);
    return 0;
}