#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <string.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int fd[2];
    if(pipe(fd) < 0)
        printf("error\n");
    char buffer[50];
    if(fork() == 0) {
        while(1) {
            bzero(buffer, 50);
            while(1) {
                read(fd[0], buffer, 50);
            }
        }
    }
    dup2(fd[1], 1);
    printf("string = %s\n", buffer);
    return 0;
}