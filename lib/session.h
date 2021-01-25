#include "standard.h"

/******************************************************************/
/*                           CONSTANTES                           */
/******************************************************************/
#define ADDR_SRV	"127.0.0.1"
#define PORT_SRV    5000


/******************************************************************/
/*                           FONCTIONS                            */
/******************************************************************/
void accepterClt();
int creerSocketEcoute();
int creerSocketDiscussion(struct sockaddr_in *cltAdr, socklen_t lenCltAdr, int se);
int creerSocketAppel(void);
void envoyerRequete(int, char *);
void connecter(int, struct sockaddr_in *srvAdr);
void connectSrv(int sad);
void dialSrv2Clt(int sd, struct sockaddr_in *cltAdr);
void dialClt2Srv(int sad, const char * MSG);