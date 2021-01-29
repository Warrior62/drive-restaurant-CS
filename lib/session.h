#include "standard.h"

/******************************************************************/
/*                           CONSTANTES                           */
/******************************************************************/
#define ADDR_SRV	"127.0.0.1"
#define PORT_SRV    5000
#define ADDR_CLT_PAY "127.0.0.2"
#define PORT_SRV_PAY    5001
#define ADDR_CLT_REC "127.0.0.3"
#define PORT_SRV_REC    5002

/******************************************************************/
/*                           FONCTIONS                            */
/******************************************************************/
/**
 * @fn int creerSocketDiscussion(struct sockaddr_in *cltAdr, int se)
 * @brief crée une socket de discussion
 * @param cltAdr structure d'adressage du client
 * @param se socket d'écoute
 * @return le numéro de la socket de discussion créée
 */ 
int creerSocketDiscussion(struct sockaddr_in *cltAdr, int se);

/**
 * @fn      int creerSocketAppel(void);  
 * @brief   crée une socket d'appel
 * @note    pas d'association de la socket d'appel avec une structure d'adressage de socket
 * @return  le numéro de la socket d'appel créée
 */
int creerSocketAppel(void);

/**
 * @fn void envoyerRequete(int, char *)
 * @brief envoie une requête au serveur d'enregistrement
 * @param sad socket d'appel et de dialogue
 * @param msg message string à envoyer par la socket
 */ 
void envoyerRequete(int, char *);

/**
 * @fn void connecter(int, struct sockaddr_in *srvAdr)
 * @brief permet la connexion au serveur
 * @param sad socket d'appel et de dialogue
 * @param srvAdr structure d'adressage du serveur
 */ 
void connecter(int, struct sockaddr_in *srvAdr);

/**
 * @fn void connectSrv(int sad, char *, int)
 * @brief permet la connexion au serveur
 * @param sad socket d'appel et de dialogue
 * @param addr adresse IP à attribuer au serveur
 * @param port numéro du port à attribuer au serveur
 */ 
void connectSrv(int sad, char *, int);

/**
 * @fn void dialSrv2Clt(int sd, struct sockaddr_in *cltAdr)
 * @brief permet le communication du serveur vers le client 
 * @param sd socket de dialogue
 * @param cltAdr structure d'adressage du client
 * @note selon l'action à effectuer, le switch déclenche les réponses à envoyer
 */ 
void dialSrv2Clt(int sd, struct sockaddr_in *cltAdr);

/**
 * @fn void dialClt2Srv(int sad, const char * MSG)
 * @brief permet le communication du client vers le serveur 
 * @param sad socket d'appel et de dialogue
 * @param MSG message à envoyer au serveur lors d'une requête client
*/ 
void dialClt2Srv(int sad, const char * MSG);

void dialClt2Clt(int sd, struct sockaddr_in *cltAdr);
