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
void accepterClt();
int creerSocketDiscussion(struct sockaddr_in *cltAdr, int se);
int creerSocketAppel(void);
void envoyerRequete(int, char *);
void connecter(int, struct sockaddr_in *srvAdr);
void connectSrv(int sad, char *, int);
void dialSrv2Clt(int sd, struct sockaddr_in *cltAdr);
void dialClt2Srv(int sad, const char * MSG);
