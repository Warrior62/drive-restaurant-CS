// #include "lib/standard.h"
// #include "lib/repReq.h"
#include "lib/session.h"
#include "lib/data.h"

int incNoCommande = 0;
/******************************************************************/
/*                           REQUETES                             */
/******************************************************************/
/**
 * @fn reponse_t passerCmd(int sad)
 * @brief permet au client de donner les produits qu'il veut commander
 * @param sad socket de d'appel et de dialogue
 * @return une réponse reçue après annonce du prix de la commande
 */ 
reponse_t passerCmd(int sad, int noCommande){
    message_t buff, msg;
    char choix;
    int i = 0;
    requete_t req;
    req.noReq = noCommande;
    strcpy(req.action, "1");
    CHECK_T(pthread_mutex_lock(&mutexEcran),"Pb lock mutexEcran");
    affichageProduits();
    printf("Que voulez vous commander ? 0 pour valider\n");
    do{
        fflush(stdin);
        scanf("%c", &choix);
        if(choix != 48 && choix != 10) req.params[i] = choix;
        i++;
    }while(choix != 48);
    req.params[i] = 70;
    envoyerRequete(sad, req2str(&req, msg));
    // Attente d'une réponse
	memset(buff, 0, MAX_BUFF);
	CHECK(recv(sad, buff, MAX_BUFF, 0),"-- PB : recv() -- passerCmd()");

	printf("\t[CLIENT]:Réception d'une réponse sur [%d]\n", sad);
	printf("\t\t[CLIENT]:Réponse reçue : ##%s##\n", buff);
    CHECK_T(pthread_mutex_unlock(&mutexEcran),"Pb unlock mutexEcran");
	reponse_t rep = str2rep(buff);
	return rep;
}

/**
 * @fn reponse_t effectuerPaiementCmd(int, int, int)
 * @brief permet au client de payer sa commande
 * @param numCom numéro de la commande à payer
 * @param prix prix de la commande à payer
 * @param sad socket d'appel et de dialogue
 */
reponse_t effectuerPaiementCmd(int numCom, int prix, int sad){
    requete_t req;
    message_t buff;
    req.noReq = numCom;
    strcpy(req.action, "2");
    sprintf(req.params, "%d", prix);
    strcat(req.params, "F");
    message_t msg;
    envoyerRequete(sad,req2str(&req, msg));
    memset(buff, 0, MAX_BUFF);
    CHECK(recv(sad, buff, MAX_BUFF, 0),"-- PB : recv() -- passerCmd()");
    CHECK_T(pthread_mutex_lock(&mutexEcran),"Pb lock mutexEcran");
    printf("\t[CLIENT]:Réception d'une réponse sur [%d]\n", sad);
    printf("\t\t[CLIENT]:Réponse reçue : ##%s##\n", buff);
    CHECK_T(pthread_mutex_unlock(&mutexEcran),"Pb unlock mutexEcran");
    reponse_t rep = str2rep(buff);
    return rep;
}
reponse_t demanderCmd(int sad, int noCommande){
    requete_t req;
    req.noReq = noCommande;
    message_t buff;
    strcpy(req.action, "3");
    strcpy(req.params, "F");
    message_t msg;
    envoyerRequete(sad,req2str(&req, msg));
    memset(buff, 0, MAX_BUFF);
    CHECK(recv(sad, buff, MAX_BUFF, 0),"-- PB : recv() -- passerCmd()");
    CHECK_T(pthread_mutex_lock(&mutexEcran),"Pb lock mutexEcran");
    printf("\t[CLIENT]:Réception d'une réponse sur [%d]\n", sad);
    printf("\t\t[CLIENT]:Réponse reçue : ##%s##\n", buff);
    CHECK_T(pthread_mutex_unlock(&mutexEcran),"Pb unlock mutexEcran");
    reponse_t rep = str2rep(buff);
    return rep;

}

reponse_t senregistrer(int sad, int type){
    requete_t req;
    message_t msg, buff;
    req.noReq = type;
    strcpy(req.action, "0");
    strcpy(req.params, "F");
    envoyerRequete(sad,req2str(&req,msg));

    memset(buff, 0, MAX_BUFF);
    CHECK(recv(sad, buff, MAX_BUFF, 0),"-- PB : recv()");
    reponse_t rep = str2rep(buff);
    CHECK_T(pthread_mutex_lock(&mutexEcran),"Pb lock mutexEcran");
    printf("\t[ENREGISTREMENT]:Réception d'une réponse sur [%d]\n", sad);
    printf("\t\t[ENREGISTREMENT]:Réponse reçue : %s\n", rep.result);
    CHECK_T(pthread_mutex_unlock(&mutexEcran),"Pb unlock mutexEcran");
    return rep;

}
/******************************************************************/
/*                           REPONSES                             */
/******************************************************************/
/**
 * @fn void annoncerPrixCmd(int sd, requete_t req)
 * @brief annonce au client le prix de sa commande
 * @param sd socket de dialogue
 * @param req requête au travers de laquelle le passage de commande s'est produit
 */
void annoncerPrixCmd(int sd, requete_t req){
    message_t buff, copyBuff;


    char newFileName[50], numReq[5];

    reponse_t rep;
    rep.noCommande = req.noReq;

    strcpy(newFileName, "db/");
    sprintf(numReq, "%hd", req.noReq);
    strcat(newFileName, numReq);
    strcat(newFileName, ".txt\0");
    creerFichierCmd(req, newFileName);

    int prix = calculerPrixCmd(newFileName);
    char * prixStr = (char *)malloc(sizeof(char)*5);
    sprintf(prixStr, "%d", prix);
    strcpy(rep.result, prixStr);


    printf("\t[SERVER]:Annonce du prix de la commande sur [%d]\n", sd);
    strcpy(buff, rep2str(&rep, buff));

    strcpy(copyBuff, buff);
    char *strPrixCmd = strtok(copyBuff, ":");
    strPrixCmd = strtok(NULL, ":");

    printf("--> PRIX COMMANDE : %s€\n", strPrixCmd);
    printf("Veuillez passer à la prochaine borne de commande !\n");
    CHECK(send(sd, buff, strlen(buff)+1, 0),"-- PB : send()");
}

void verifierPaiementCmd(int sd, requete_t req){
    char newFileName[50], numReq[5];
    message_t buff;
    strcpy(newFileName, "db/");
    sprintf(numReq, "%hd", req.noReq);
    strcat(newFileName, numReq);
    strcat(newFileName, ".txt\0");
    int prix = calculerPrixCmd(newFileName);
    if (atoi(req.params) == prix){
        //printf("Le prix est bon\n");
        reponse_t rep;
        rep.noCommande = req.noReq;
        strcpy(rep.result,"La commande est validée");
        strcpy(buff, rep2str(&rep, buff));
        CHECK(send(sd, buff, strlen(buff)+1, 0),"-- PB : send()");
    }
}
void donnerCmd(int sd, requete_t req){
    char newFileName[50], numReq[5];
    message_t buff;
    strcpy(newFileName, "db/");
    sprintf(numReq, "%hd", req.noReq);
    strcat(newFileName, numReq);
    strcat(newFileName, ".txt\0");
    remove(newFileName);

    reponse_t rep;
    rep.noCommande = req.noReq;
    strcpy(rep.result,"Voila votre commande");
    strcpy(buff, rep2str(&rep, buff));
    CHECK(send(sd, buff, strlen(buff)+1, 0),"-- PB : send()");
}

void enregistrer(int sd, requete_t req){
    reponse_t rep;
    message_t buff;
    switch (req.noReq) {
        case 1 : rep.noCommande = 0;
        strcpy(rep.result, "Le client serveur est bien enregistré");
        break;
        case 0 : rep.noCommande = ++incNoCommande;
        strcpy(rep.result, "Le client est enregistré");
        break;

    }
    strcpy(buff, rep2str(&rep, buff));
    CHECK(send(sd, buff, strlen(buff)+1, 0),"-- PB : send()");
}


