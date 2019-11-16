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
static char * easterEggString    = "respuesta = strings[FALTA NUMERITO]";
static char * whatAmIString      = ".data .bss .comment ? .shstrtab .symtab .strtab\n";
static char * mixedfdsString     = "Mixed File Descriptors\n";
static char * indeterminedString = "La respuesta a este acertijo es indeterminada\n";
static char * gibberish          = "fdnfkjsdnfsfdkjnsfkjdnfjksdnflsdkjcnsigjfdpoihgjfdgsopbñfoigjbofsibmdivmfoivdmsñoifvsdjnfpaokdpasodkpaosjfdpifjnñsddskfñaoisnfvoisnvcsoinvcñsoicnsovkñasigfdaopgjñvfoimapñodivmdofvinñsoivndopvñdsfovnfinmvmfvposdñvoijsopvmsdvaofniaifnmasddfoimdc\n";
static char * helloThereString   = "Hotel Echo Lima Lima Oscar Tango Hotel Echo Romeo Echo\n";
static char * quineString        = "¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde:\n";
static char * quineValidString   = "La respuesta al acertijo es un acertijo\n";
static char * gdbmeString        = "b gdbme y encontrá el valor mágico\n";
static char * magicNumberString  = "La respuesta a este acertijo es gdbinit a full\n";
static char * endingString       = "Felicitaciones por terminar el juego! Ahora a aprobar al grupo 5 :)\n";
static char * piString     = "	char"
							    "3141592654[3141"
	  "],__3141[3141];_314159[31415],_3141[31415];hey(){register char*"
      "_3_141,*_3_1415, *_3__1415; register int _314,_31415,__31415,*_31,"
    "_3_14159,__3_1415;*_3141592654=__31415=2,_3141592654[0][_3141592654"
   "-1]=1[__3141]=5;__3_1415=1;do{_3_14159=_314=0,__31415++;for( _31415"
  "=0;_31415<(3,14-4)*__31415;_31415++)_31415[_3141]=_314159[_31415]= -"
"1;_3141[*_314159=_3_14159]=_314;_3_141=_3141592654+__3_1415;_3_1415="
"__3_1415    +__3141;for			(_31415 = 3141-"
	   "__3_1415  ;			_31415;_31415--"
	   ",_3_141 ++,			_3_1415++){_314"
	   "+=_314<<2 ;			_314<<=1;_314+="
	  "*_3_1415;_31			 =_314159+_314;"
	  "if(!(*_31+1)			 )* _31 =_314 /"
	  "__31415,_314			 [_3141]=_314 &"
	  "__31415 ;* (			 _3__1415=_3_141"
	 ")+= *_3_1415			  = *_31;while(*"
	 "_3__1415 >=			  31415/3141 ) *"
	 "_3__1415+= -			  10,(*--_3__1415"
	")++;_314=_314			  [_3141]; if ( !"
	"_3_14159 && *			  _3_1415)_3_14159"
	"=1,__3_1415 =			  3141-_31415;}if("
	"_314+(__31415			   >>1)>=__31415 )"
	"while ( ++ *			   _3_141==3141/314"
       ")*_3_141--=0			   ;}while(_3_14159"
       ") ; { char *			   __3_14= '3.1415';"
       "write((3,1),			   (--*__3_14,__3_14"
       "),(_3_14159			    ++,++_3_14159))+"
      "3.1415926; }			    for ( _31415 = 1;"
     "_31415<3141-			    1;_31415++)write("
    "31415& 314-(			    3,14),_3141592654["
  "_31415    ] +				   '0123456789','31'"
  "[ 3]+1)-_314;				   puts((*_3141592654=0"
",_3141592654))				    ;_314= '3.141592';}'";


char * filterString(char * string) {
    char * filtered = malloc(strlen(string));
    int i, length = 0;
    for(i = 0 ; i < strlen(string) ; i++) {
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

int isAnswerCorrect(int challenge, char * answer) {
    char * filteredAnswer = filterString(answer);
    switch (challenge) {
        case 1:
            return strcmp("estovaleunpuntomas\n", filteredAnswer);
        case 2:
            return strcmp("#0854780*\n", filteredAnswer);
        case 3:
            return strcmp("holaariel\n", filteredAnswer);
        case 4:
            return strcmp("10\n", filteredAnswer);
        case 5:
            return strcmp("easter_egg\n", filteredAnswer);
        case 6:
            return strcmp(".whatAmI\n", filteredAnswer);
        case 7:
            return strcmp("indeterminada\n", filteredAnswer);
        case 8:
            return strcmp("pi\n", filteredAnswer);
        case 9:
            return strcmp("hellothere\n", filteredAnswer);
        case 10:
            return strcmp("unacertijo\n", filteredAnswer);
        case 11:
            return strcmp("gdbinitafull\n", filteredAnswer);
        default:
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
    gdbme(socket);
    endingGreeting();
    return;
}

void understood(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", greeting);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isAnswerCorrect(1, answer)) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
}

void numberPad(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", numberPadString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isAnswerCorrect(2, answer)) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
}

void morse(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", morseString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isAnswerCorrect(3, answer)) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
}

void EBADF(int socket) {
    char * answer = malloc(1024);
    write(5, string5, strlen(string5));
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", EBADFString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isAnswerCorrect(4, answer)) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
}

void easterEgg(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", easterEggString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isAnswerCorrect(5, answer)) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
}

void whatAmI(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", whatAmIString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isAnswerCorrect(6, answer)) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
}

void indetermined(int socket) {
    char * answer = malloc(1024);
    int index = 0;
    int pick = 0;
    int dummyIndex = 0;
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", mixedfdsString);
        
        while(index < strlen(indeterminedString)) {
            if(pick++ % 3 == 0) {
                write(1, indeterminedString + (index++), 1);
            } else {
                write(2, gibberish + (dummyIndex++), 1);
            }
        }
        printf("\n");

        recv(socket, answer, 1024, 0);

        if(isAnswerCorrect(7, answer)) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
}

void pi(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", piString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isAnswerCorrect(8, answer)) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
}

void helloThere(int socket) {
    char * answer = malloc(1024);
    while(TRUE) {
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", helloThereString);
        bzero(answer, sizeof(answer));
        recv(socket, answer, 1024, 0);

        if(isAnswerCorrect(9, answer)) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
}

void quine(int socket) {
    system("clear");
    printf("%s\n", challengeString);
    
    if(system("gcc quine.c -o quine") == 0) {
        printf("%s", quineString);
        if(system("./quine | diff -quine.c") == 0) {
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

            if(isAnswerCorrect(10, answer)) {
                printf("%s%s\n", correctAnswer, answer);
                sleep(1);
                return;
            } else {
                printf("%s%s\n", incorrectAnswer, answer);
                sleep(1);
                system("clear");
            }
        }

}

void gdbme(int socket) {
    char * answer = malloc(1024);
    int magicNumber;

    while(TRUE) {
        magicNumber = 11111;    
        system("clear");
        printf("%s\n", challengeString);
        printf("%s\n", gdbmeString);
        bzero(answer, sizeof(answer));
        
        if(magicNumber == 0) 
            printf("%s", magicNumberString);
        
        recv(socket, answer, 1024, 0);

        if(isAnswerCorrect(9, answer)) {
            printf("%s%s\n", correctAnswer, answer);
            sleep(1);
            return;
        } else {
            printf("%s%s\n", incorrectAnswer, answer);
            sleep(1);
            system("clear");
        }
    }
}

void endingGreeting() {
    printf("%s", endingString);
}