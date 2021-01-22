/******************************************************************/
/*                           CONSTANTES                           */
/******************************************************************/
#define ADDR_SRV	"172.20.30.13"


/******************************************************************/
/*                           FONCTIONS                            */
/******************************************************************/
void accepterClt();
int creerSocketEcoute(struct sockaddr_in );
int creerSocketDiscussion(struct sockaddr_in *, int * , int );
int creerSocketAppel(void);
void envoyerRequete(int, char *);
void connecter(int, struct sockaddr_in *);