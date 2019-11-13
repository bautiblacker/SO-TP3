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

// argv[0] filename
// argv[1] server_ipaddress
// argv[2] port number
int main(int argc, char const *argv[]) 
{                                     
    struct sockaddr_in address;
    int socketfd = 0;
    struct sockaddr_in serv_addr;
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
    char * answer4 = "pistolero\n";
    char * answer5 = "easter_egg\n";
    char * answer6 = ".whatAmI\n";

    sleep(1);
    send(socketfd, answer, strlen(answer), 0);
    sleep(1);
    send(socketfd, answer2, strlen(answer2), 0);
    sleep(1);
    send(socketfd, answer3, strlen(answer3), 0);
    sleep(1);
    send(socketfd, answer4, strlen(answer4), 0);
    sleep(1);
    send(socketfd, answer5, strlen(answer5), 0);
    sleep(1);
    send(socketfd, answer6, strlen(answer6), 0);
    int fd[2];
    char * buffer = malloc(100);
    pipe(fd);
    close(0);
    dup2(fd[0], 0);
    read(fd[0], buffer, 100);
    sleep(2);
    return 0;
}

/*
    while(1){
        i=0;

        while((c = getchar()) != '\n'){
            msg[i] = c;
            i++;
        }
        msg[i] = '\n';
        write(sock , msg , strlen(msg));
	
        bzero(msg,SIZE);

    }
*/


/*
    SERVER SIDE
    int newsockfd = accept(int sockfd, (struct sockaddr*)&addr, &addrlen);
    +-> toda comunicacion sale
        de este fd    

*/