#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *myargv[] = {"nulla", NULL};
    execve("./temp", myargv, NULL);
    return 0;
}