#include <stdio.h>
#include <unistd.h>
#include <string.h> 
int main(int argc, char *argv[])
{ 
    //test strtok
    char string[] = "pippo,pluto,paperino";
    char *token = strtok(string, ",");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
    return 0;
}