/******************************************************************/
/*                           INCLUDE                              */
/******************************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sendfile.h>



/******************************************************************/
/*                           CONSTANTES                           */
/******************************************************************/
#define MAX_BUFF	512


/******************************************************************/
/*                           TYPEDEF                              */
/******************************************************************/
typedef char message_t[MAX_BUFF];
typedef char action_t[MAX_BUFF];


/******************************************************************/
/*                        MACRO-FONCTIONS                         */
/******************************************************************/
#define CHECK(sts, msg) if ((sts)==-1) {perror(msg); exit(-1);}


/******************************************************************/
/*                           FONCTIONS                            */
/******************************************************************/
void serveur(void);
int sessionSrv(void);