#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <string.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>

#define PORT 0x5B7F

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
    //char * answer2 = "# ⬅ ⬆ ⬆ ⬅ ⬇ ➡ ⬇ ⬅ *";
    //char * answer2 = "# 42248684 *\n";
    //char * answer2 = "# GAAGTMTG *\n";
    char * answer2 = "#origin*";
    send(socketfd, answer, strlen(answer), 0);
    sleep(2);
    send(socketfd, answer2, strlen(answer2), 0);
    sleep(2);
    close(socketfd);
    return 0;
}




/*
    SERVER SIDE
    int newsockfd = accept(int sockfd, (struct sockaddr*)&addr, &addrlen);
    +-> toda comunicacion sale
        de este fd    

*/