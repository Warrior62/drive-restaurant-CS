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
#include <pthread.h>


/******************************************************************/
/*                           CONSTANTES                           */
/******************************************************************/
#define MAX_BUFF	512
#define MAX_CLIENT  1

/******************************************************************/
/*                           TYPEDEF                              */
/******************************************************************/
typedef char message_t[MAX_BUFF];
typedef char action_t[MAX_BUFF];
typedef void * (*pf_t)(void *);

/******************************************************************/
/*                        MACRO-FONCTIONS                         */
/******************************************************************/
#define CHECK(sts, msg) if ((sts)==-1) {perror(msg); exit(-1);}
#define CHECK_T(sts, msg) if ((sts)!=0) {perror(msg); exit(-1);}

/******************************************************************/
/*                           FONCTIONS                            */
/******************************************************************/
/**
 * @fn void serveur(void)
 * @brief joue le rôle de serveur d'enregistrement ou de thread serveur
 */ 
void serveur(void);

/**
 * @fn int sessionSrv(char *, int)
 * @brief établit une session serveur en créant une socket d'écoute
 * @param addr adresse IP à attribuer au serveur
 * @param port numéro du port à attribuer au serveur
 * @return le numéro de la socket d'écoute créée
 */ 
int sessionSrv(char *, int);

/**
 * @fn void client(void) 
 * @brief joue le rôle de thread client
 */ 
void client(void);

/**
 * @fn int sessionClt(void)
 * @brief établit une session client en créant une socket d'appel et de dialogue
 * @return le numéro de la socket d'appel et de dialogue créée
 */ 
int sessionClt(void);

int sessionCltSrv(char * addr, int port);


