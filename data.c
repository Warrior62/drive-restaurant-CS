#include "./lib/data.h"
#include "./lib/repReq.h"


/**
 * @fn      void affichageProduits(); 
 * @brief   lis le fichier db/products.txt et affiche son contenu
 * @note    affiche les produits qui peuvent être commandés par le client
 */ 
void affichageProduits(){
	FILE *f;
    f = fopen("db/products.txt", "rt");
    char id[20], nom[20], prix[20], tabId[100], tabNom[100], tabPrix[100];
    int i=0;

	printf("NOTRE CARTE:\n");
    // Je récupére l'ensemble du contenu du fichier f
    while(fscanf(f, "%s %s %s", id,nom,prix) != EOF){
        strcpy(&tabId[i], id);
        strcpy(&tabNom[i], nom);
        strcpy(&tabPrix[i], prix);
        printf("\t%s %s %s\n", &tabId[i], &tabNom[i], &tabPrix[i]);
        i++;
    }        
    fclose(f);
}


int calculerPrixCmd(){
    FILE *f;
    f = fopen("db/orders.txt", "rt");
    char id[20], quantite[20], prix[20], tabId[100], tabQuantite[100], tabPrix[100];
    int i=0, prixFinal=0;
    printf("VOTRE COMMANDE\n");
    while(fscanf(f, "%s %s %s", id, prix, quantite) != EOF){
        strcpy(&tabId[i], id);
        tabQuantite[i] = atoi(quantite);
        tabPrix[i] = atoi(prix);
        printf("\t%s %d %d\n", &tabId[i], tabQuantite[i], tabPrix[i]);
        i++;
    }   
    fclose(f);

    for(int j=0; j<(sizeof(tabQuantite)/sizeof(int)); j++)
        prixFinal += (tabQuantite[j] * tabPrix[j]); 
    
    return prixFinal;
}

char * req2str (const requete_t *req, message_t msg) {
    // serialization d'une requête (structure) sous forme d'une chaîne de caractères
    // c-à-d une suite d'octets
    memset(msg, 0, MAX_BUFF);
    sprintf(msg,"%hd:%s:%s", req->noReq, req->action, req->params);
    return msg;
}
