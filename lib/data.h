#include "repReq.h"

void affichageProduits();
int calculerPrixCmd(char *orderFilePath);
void creerFichierCmd(requete_t, char *);

requete_t str2req(char * str);
reponse_t str2rep(char * str);

char * req2str(const requete_t *, message_t);
char * rep2str(const reponse_t *, message_t );

typedef struct {
    int id;
    char * nom;
    int prixUnit;
} produit_t;