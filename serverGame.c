#include "serverGame.h"
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

#define TRUE 1
#define FALSE 0

static char * challengeString    = "-------- DESAFIO ---------\n";
static char * correctAnswer      = "Respuesta correcta: ";
static char * incorrectAnswer    = "Respuesta incorrecta: ";
static char * greeting           = "Bienvenido al nuevo cliente! Felicitaciones por conectarte exitosamente\nPara seguir ingresá el string \"esto vale un punto mas\\n\"";
static char * numberPadString    = "# \\033[D \\033[A \\033[A \\033[D \\033[B \\033[C \\033[B \\033[D *";
static char * morseString        = "https://vocaroo.com/i/s0H6RyRLBQlx\n";
static char * EBADFString        = "EBADF... abrelo y verás o redirigí\n";
static char * string5            = "La respuesta al desafio es la nota que merecemos, osea 10 :)\n";
static char * easterEggString    = "respuesta = strings[74]";
static char * whatAmIString      = ".data .bss .comment ? .shstrtab .symtab .strtab\n";
static char * mixedfdsString     = "Mixed File Descriptors\n";
static char * indeterminedString = "La respuesta a este acertijo es indeterminada\n";
static char * gibberish          = "fdnfkjsdnfsfdkjnsfkjdnfjksdnflsdkjcnsigjfdpoihgjfdgsopbñfoigjbofsibmdivmfoivdmsñoifvsdjnfpaokdpasodkpaosjfdpifjnñsddskfñaoisnfvoisnvcsoinvcñsoicnsovkñasigfdaopgjñvfoimapñodivmdofvinñsoivndopvñdsfovnfinmvmfvposdñvoijsopvmsdvaofniaifnmasddfoimdc\n";
static char * helloThereString   = "Hotel Echo Lima Lima Oscar Tango Hotel Echo Romeo Echo\n";
static char * quineString        = "¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde:\n";
static char * quineValidString   = "La respuesta al acertijo es un acertijo\n";
static char * gdbmeString        = "b gdbme y encontrá el valor mágico\n";
static char * magicNumberString  = "La respuesta a este acertijo es: gdbinit a full\n";
static char * endingString       = "Felicitaciones por terminar el juego! Ahora a aprobar al grupo 5 :)\n";
static char * piString     = 
                                "\n"                
                                "8b,dPPYba,  88\n"  
                                "88P'    \"8a 88\n"  
                                "88       d8 88\n"  
                                "88b,   ,a8\" 88\n"  
                                "88'YbbdP''  88\n"  
                                "88\n"              
                                "88            \n";
static char * holis = "holis";
static char * character = "( ͡°( ͡° ͜ʖ( ͡° ͜ʖ ͡°)ʖ ͡°) ͡°)";
char * quineF = "#include <stdio.h>\n#include <stdlib.h>\n\nint main()\n{\n\tchar c;\n\tFILE *file;\n\n\tfile = fopen(\"quine.c\", \"r\");\n\n\twhile((c = fgetc(file)) != EOF)\n\tprintf(\"%c\", c);\n\n\tfclose(file);\n\treturn 0;\n}";


char * filterString(char * string) {
    char * filtered = malloc(strlen(string));
    int i, length = 0;
    int stringLength = strlen(string);
    for(i = 0; i < stringLength; i++) {
        if(!isspace(string[i])) {
            if(string[i] >= 'A' && string[i] <= 'Z') {
                filtered[length++] = tolower(string[i]);
            } else {
                filtered[length++] = string[i];
            }
        }
    }
    return filtered;
}

int isCorrectAnswer(int challenge, char * answer) {
    char * filteredAnswer = filterString(answer);
    switch (challenge) {
        case 1: {
                    int ret = strcmp("estovaleunpuntomas", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        case 2: {
                    int ret = strcmp("#0854780*", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        case 3: {
                    int ret = strcmp("holaariel", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        case 4: {
                    int ret = strcmp("10", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        case 5: {
                    int ret = strcmp("easter_egg", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        case 6: {
                    int ret = strcmp(".whatami", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        case 7: {
                    int ret = strcmp("indeterminada", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        case 8: {
                    int ret = strcmp("pi", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        case 9: {
                    int ret = strcmp("hellothere", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        case 10: {                    
                    int ret = strcmp("unacertijo", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        case 11: {
                    int ret = strcmp("gdbinitafull", filteredAnswer);
                    free(filteredAnswer);
                    return ret;
        }
        default:
            free(filteredAnswer);
            break;
    }
}

void playGame(int socket) {
    understood(socket);
    numberPad(socket);
    morse(socket);
    EBADF(socket);
    easterEgg(socket);
    whatAmI(socket);
    indetermined(socket);
    pi(socket);
    helloThere(socket);
    quine(socket);
    gdbmeFunc(socket);
    endingGreeting();
    return;
}

void understood(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", character);
        printf("%s\n", greeting);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isCorrectAnswer(1, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
    free(answer);
}

void numberPad(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", numberPadString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isCorrectAnswer(2, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
        }
    }
    free(answer);
}

void morse(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", morseString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isCorrectAnswer(3, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
        }
    }
    free(answer);
}

void EBADF(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", EBADFString);
        write(5, string5, strlen(string5));
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isCorrectAnswer(4, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
        }
    }
    free(answer);
}

void easterEgg(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", easterEggString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isCorrectAnswer(5, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
        }
    }
    free(answer);
}

void whatAmI(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", whatAmIString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);
        if(isCorrectAnswer(6, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
        }
    }
    free(answer);
}

void indetermined(int socket) {
    char * answer = malloc(1024);
    int index = 0;
    int pick = 0;
    int dummyIndex = 0;
    int intStringLength = strlen(indeterminedString);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", mixedfdsString);
        
        while(index < intStringLength) {
            if(pick++ % 3 == 0) {
                write(1, indeterminedString + (index++), 1);
            } else {
                write(2, gibberish + (dummyIndex++), 1);
            }
        }
        printf("\n");

        recv(socket, answer, 1024, 0);

        if(isCorrectAnswer(7, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
        }
    }
    free(answer);
}

void pi(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", piString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isCorrectAnswer(8, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
        }
    }
    free(answer);
}

void helloThere(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", helloThereString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isCorrectAnswer(9, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
        }
    }
    free(answer);
}

void gdbme() {
    int magicNumber = 0;
    if(magicNumber == 0x12345) 
            printf("%s", magicNumberString);
    return;
}

void quine(int socket) {
    system("clear");
    printf("%s\n", challengeString);
    
    if(system("gcc quine.c -o quine") == 0) {
        printf("%s", quineString);
        if(system("bash -c \"diff <(./quine) <(cat quine.c)\"") == 0) {
            printf("%s", quineValidString);
        } else {
            printf("%s", incorrectAnswer);
        }
    } else {
        printf("%s", incorrectAnswer);
    }

    char * answer = malloc(1024);
    while(TRUE) {
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isCorrectAnswer(10, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
    free(answer);
}

void gdbmeFunc(int socket) {
    char * answer = malloc(1024);
    int magicNumber;

    while(TRUE) {
        magicNumber = 11111;    
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", gdbmeString);
        bzero(answer, sizeof(answer));
                
        recv(socket, answer, 1024, 0);

        if(isCorrectAnswer(11, answer) == 0) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            free(answer);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
        }
    }
    free(answer);
}

void endingGreeting() {
    printf("%s", endingString);
}