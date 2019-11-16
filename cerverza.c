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
#include "serverGame.h"

#define PORT 0x5B7F

int main() {

    int socketfd, newsocket;
    struct sockaddr_in serverAddress, clientAddress;

    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creando el socket\n");
        exit(1);
    } 

    bzero(&serverAddress, sizeof(serverAddress));

    if(setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int)) < 0) {
        printf("Error seteando el socket\n");
        exit(1);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(PORT);

    if((bind(socketfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress))) != 0) {
        printf("Error en el enlace\n");
        exit(1);
    }

    if((listen(socketfd, 5)) != 0) {
        printf("Error escuchando al socket\n");
        exit(1);
    }

    int clientSize = sizeof(clientAddress);

    if((newsocket = accept(socketfd, (struct sockaddr *)&clientAddress, &clientSize)) < 0) {
        printf("Error aceptando al cliente\n");
        exit(1);
    }

    playGame(newsocket);
    return 0;
}