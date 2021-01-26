#include "./lib/data.h"


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

    printf("\n******************************\n");
    printf("NOTRE CARTE:\n");
    printf("------------\n");
    // Je récupére l'ensemble du contenu du fichier f
    while(fscanf(f, "%s %s %s", id,nom,prix) != EOF){
        strcpy(&tabId[i], id);
        strcpy(&tabNom[i], nom);
        strcpy(&tabPrix[i], prix);
        printf("\t%s %s %s€\n", &tabId[i], &tabNom[i], &tabPrix[i]);
        i++;
    }        
    printf("******************************\n");
    fclose(f);
}


/**
 * @fn      int calculerPrixCmd(char *orderFilePath)
 * @brief   calcule le prix total de la commande dont le fichier associé est passé en paramètre
 * @param   orderFilePath   chemin du fichier associé à la commande
 * @return  prix total de la commande
 */ 
int calculerPrixCmd(char *orderFilePath){
    FILE *fCmd, *fProducts;
    fCmd = fopen(orderFilePath, "rt");
    fProducts = fopen("db/products.txt", "rt");
    char id[20], nom[20], prixUnitaire[20], data[100];
    produit_t tabProducts[100];
    int i=0, j=0, prixFinal=0, tabCmd[100];
    printf("premiere trace\n");
    //Stockage du contenu des produits dans un tableau tabProducts
    while(fscanf(fProducts, "%s %s %s", id, nom, prixUnitaire) != EOF){
        tabProducts[i].id = atoi(id);
        //strcpy(tabProducts[i].nom, nom);
        tabProducts[i].prixUnit = atoi(prixUnitaire);
        //printf("-->%d\n", tabProducts[i].prixUnit);
        i++;
    }   

    // Stockage du contenu de la commande dans un tableau tabCmd
    printf("VOTRE COMMANDE\n");
    while(fscanf(fCmd, "%s", data) != EOF){
        if(atoi(data) != 0){
            if(atoi(data) != 0){
                tabCmd[j] = atoi(data);
                printf("\t%d\n", tabCmd[j]);
                j++;
            }
        }
    }
    fflush(stdin);

    // Calcul du prix de la commande
    for(int k=0; k<j; k++) 
        for (int l = 0; l < i; l++) 
            if (tabProducts[l].id == tabCmd[k]) 
                prixFinal += tabProducts[l].prixUnit;
          
        
    
       
    // Fermeture des 2 fichiers
    fclose(fProducts);
    fclose(fCmd);

    return prixFinal;
}


char * req2str (const requete_t *req, message_t msg) {
    // serialization d'une requête (structure) sous forme d'une chaîne de caractères
    // c-à-d une suite d'octets
    memset(msg, 0, MAX_BUFF);
    int i = 0;
    char str[50] = "";
    while(req->params[i] != 70){
        strncat(str, &req->params[i], 1);
        strcat(str, " ");
        i++;
    }
    strncat(str, &req->params[i], 1);
    sprintf(msg,"%hd:%s:%s", req->noReq, req->action, str);
    return msg;
}

// requete_t *str2req (const message_t msg) {
//     requete_t *req = (requete_t *) malloc(sizeof(requete_t));
//     // dé-serialization d'une chaîne de caractères en requête (structure)
//     sscanf(msg,"%hd:%[^:]:%[^\n]", &req->noReq, req->action, req->params);
//     return req;
// }

/**
 * @fn  void creerFichierCmd(requete_t reqPrixCmd)
 * @brief créer le fichier de commande et le remplir avec les produits commandés
 * @param reqPrixCmd requête envoyée par le client pour passer sa commande
 * @note le nom du fichier de commande créé correspond au numéro de commande.txt
 */ 
void creerFichierCmd(requete_t reqPrixCmd, char * newFileName){
    //char numeroReq[50];

    // on crée un fichier de commande 
    // dont le nom est le numéro de la commande

    // on insére les données de params dans le fichier de commande
    int i=0;
    FILE *fCmd = fopen(newFileName, "w");
    while(reqPrixCmd.params[i] != 70)
	{
        //printf("%c", reqPrixCmd.params[i]);
        if(reqPrixCmd.params[i] != 13 && reqPrixCmd.params[i] != 10 && reqPrixCmd.params[i] != 48) {
            fwrite(&reqPrixCmd.params[i], sizeof(reqPrixCmd.params[i]), 1, fCmd);
            fputs(" ", fCmd);
        }
        i++;
	}
    // on ferme le fichier de commande
    fclose(fCmd);
    /**
    char * strReturn = (char *) malloc(sizeof(char) * 10);
    strcpy(strReturn, newFileName);
    return strReturn;*/
}

requete_t str2req(char * str){
	requete_t req;
	char * strToken = strtok(str,":");
	req.noReq = atoi(strToken);
	
	strToken = strtok(NULL,":");
	strcpy(req.action, strToken);
	
	strToken = strtok(NULL,":");
    int i = 0, j = 0;
	while (strToken[j] != 70) {
	    if(strToken[j] != 32) {
	        req.params[i] = strToken[j];
	        i++;
	    }
	    j++;

    }
	req.params[i] = 70;
    return req;
}

char * rep2str(const reponse_t * rep, message_t msg){
    memset(msg, 0, MAX_BUFF);
    sprintf(msg,"%hd:%s", rep->noCommande, rep->result);
    return msg;
}

reponse_t str2rep(char * str){
    reponse_t rep;
    char * strToken = strtok(str,":");
    rep.noCommande = atoi(strToken);

    strToken = strtok(NULL,":");
    strcpy(rep.result, strToken);

    return rep;
}
