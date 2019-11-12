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

#define PORT 0x5B7F
#define STDIN_FILENO 0

// argv[0] filename
// argv[1] server_ipaddress
// argv[2] port number
int main(int argc, char const *argv[]) 
{                                     
    struct sockaddr_in address;
    int socketfd = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creando el socket.\n");
        exit(1);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;  // Dominio, IPv4
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        exit(1);
    }

    if (connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Cannot connect to server\n");
        exit(1);
    }

    char * answer = "entendido\n";
    char * answer2 = "#0854780*\n";
    char * answer3 = "morse\n";
    char * answer4 = "EBADF: bad file descriptor, read\n";
    char buff[50] = {0};
    send(socketfd, answer, strlen(answer), 0);
    sleep(2);
    send(socketfd, answer2, strlen(answer2), 0);
    sleep(2);
    send(socketfd, answer3, strlen(answer3), 0);
    int socketCpy = socketfd;
    sleep(2);
    int fd = dup2(5, STDIN_FILENO );
    read(fd, &buff, 42);
    // buff[strlen(buff)] = '\n';
    // dup2(socketfd, socketCpy);
    send(socketfd, "5\n", 2, 0);
    close(socketfd);
    return 0;
}




/*
    SERVER SIDE
    int newsockfd = accept(int sockfd, (struct sockaddr*)&addr, &addrlen);
    +-> toda comunicacion sale
        de este fd    

*/