#include "repReq.h"

void affichageProduits();
int calculerPrixCmd(char *orderFilePath);
char * creerFichierCmd(requete_t reqPrixCmd);
requete_t str2req(char * str);
char * req2str (const requete_t *, message_t);