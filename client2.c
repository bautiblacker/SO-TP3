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

#define PORT 0x5B7F

int main(int argc, char const *argv[]) 
{                                     
    struct sockaddr_in address;
    int socketfd = 0;
    struct sockaddr_in serverAddress;
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creando el socket.\n");
        exit(1);
    }

    memset(&serverAddress, '0', sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        printf("Invalid address\n");
        exit(1);
    }

    if(connect(socketfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Connection error\n");
        exit(1);
    }
    

    printf("connection check\n");

    char * answer = "esto vale un punto mas\n";
    char * answer2 = "#0854780*\n";
    char * answer3 = "hola ariel\n";
    char * answer4 = "10\n";
    char * answer5 = "easter_egg\n";
    char * answer6 = ".whatAmI\n";
    char * answer7 = "indeterminada\n";
    char * answer8 = "pi\n";
    char * answer9 = "hello there\n";
    char * answer10 = "un acertijo\n";
    char * answer11 = "gdbinit a full\n";

    sleep(1);
    send(socketfd, answer, strlen(answer), 0);
    sleep(3);
    send(socketfd, answer2, strlen(answer2), 0);
    sleep(3);
    send(socketfd, answer3, strlen(answer3), 0);
    sleep(3);
    send(socketfd, answer4, strlen(answer4), 0);
    sleep(3);
    send(socketfd, answer5, strlen(answer5), 0);
    sleep(3);
    send(socketfd, answer6, strlen(answer6), 0);
    sleep(3);
    send(socketfd, answer7, strlen(answer7), 0);
    sleep(3);
    send(socketfd, answer8, strlen(answer8), 0);
    sleep(3);
    send(socketfd, answer9, strlen(answer9), 0);
    sleep(3);
    send(socketfd, answer10, strlen(answer10), 0);
    sleep(3);
    send(socketfd, answer11, strlen(answer11), 0);
    sleep(3);

    close(socketfd);

    return 0;
}