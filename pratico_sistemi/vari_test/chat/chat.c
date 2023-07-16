#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>

#define BUFLENGTH 1024

int main(int argc, char *argv[])
{ 
    int fdin = open(argv[2], O_RDONLY | O_NONBLOCK); 
    int fdout = open(argv[1], O_WRONLY); 
    struct pollfd pfd[] = {{0, POLLIN | POLLHUP,0}, {fdin,POLLIN | POLLHUP,0}};
    char buf[BUFLENGTH];
    for(;;){ 
        poll(pfd, sizeof(pfd)/sizeof(*pfd),-1 );
        if(pfd[0].revents & POLLHUP) return 0; 
        if(pfd[1].revents & POLLHUP) return 0;

        if(pfd[0].revents & POLLIN){ 
            size_t len = read(0, buf, BUFLENGTH); 
            if(len == 0) 
            break; 
            write(fdout, buf, len); 
        } 

        if(pfd[1].revents & POLLIN){ 
            size_t len = read(fdin, buf, BUFLENGTH); 
            if(len == 0) 
            break; 
            write(1, buf, len); 
        } 
    } 
    close(fdin); 
    close(fdout); 
    return 0;
} 
