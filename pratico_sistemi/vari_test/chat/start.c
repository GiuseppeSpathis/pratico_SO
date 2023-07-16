#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{ 
    mknod("myfifo", S_IFIFO | 0666, 0);
    printf("named pipe creata");
    return 0;
}