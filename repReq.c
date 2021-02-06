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

/**
 * @fn reponse_t demanderCmd(int sad, int noCommande)
 * @brief permet au client de réclamer sa commande à la dernière borne
 * @param sad socket d'appel et de dialogue
 * @param noCommande numéro de la commande à réclamer
 * @return une réponse contenant le buffer
 */
reponse_t demanderCmd(int sad, int noCommande){
    requete_t req;
    req.noReq = noCommande;
    message_t buff;
    strcpy(req.action, "3");
    strcpy(req.params, "F");
    message_t msg;
    envoyerRequete(sad,req2str(&req, msg));
    memset(buff, 0, MAX_BUFF);
    CHECK(recv(sad, buff, MAX_BUFF, 0),"-- PB : recv()");
    CHECK_T(pthread_mutex_lock(&mutexEcran),"Pb lock mutexEcran");
    printf("\t[CLIENT]:Réception d'une réponse sur [%d]\n", sad);
    printf("\t\t[CLIENT]:Réponse reçue : ##%s##\n", buff);
    CHECK_T(pthread_mutex_unlock(&mutexEcran),"Pb unlock mutexEcran");
    reponse_t rep = str2rep(buff);
    return rep;
}

/**
 * @fn reponse_t senregistrer(int sad, int type)
 * @brief permet au client de s'enregistrer auprès du serveur d'enregistrement
 * @param sad socket d'appel et de dialogue
 * @param type numéro du type d'action à effectuer
 * @return une réponse d'acquittement de l'envoi d'une demande d'enregistrement 
 */
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

    // Nous créeons un nouveau fichier de commande
    // dont le nom correspond au numéro de la requête
    // passée en paramètre de la fonction, et nous le remplissons
    strcpy(newFileName, "db/");
    sprintf(numReq, "%hd", req.noReq);
    strcat(newFileName, numReq);
    strcat(newFileName, ".txt\0");
    creerFichierCmd(req, newFileName);

    // Dans le champ result de la réponse à renvoyer,
    // nous stockons le prix de la commande
    int prix = calculerPrixCmd(newFileName);
    char * prixStr = (char *)malloc(sizeof(char)*5);
    sprintf(prixStr, "%d", prix);
    strcpy(rep.result, prixStr);

    // Nous remplissons le buffer avec le prix de la commande
    printf("\t[SERVER]:Annonce du prix de la commande sur [%d]\n", sd);
    strcpy(buff, rep2str(&rep, buff));

    // Nous convertissons le prix de la commande en
    // une chaîne de caractère
    strcpy(copyBuff, buff);
    char *strPrixCmd = strtok(copyBuff, ":");
    strPrixCmd = strtok(NULL, ":");

    // Nous indiquons au client le prix de sa commande
    // pour qu'il puisse passer à la prochaine borne de service
    printf("--> PRIX COMMANDE : %s€\n", strPrixCmd);
    printf("Veuillez passer à la prochaine borne de commande !\n");
    CHECK(send(sd, buff, strlen(buff)+1, 0),"-- PB : send()");
}

/**
 * @fn void verifierPaiementCmd(int sd, requete_t req)
 * @brief vérifie que le prix passé en paramètre est bien celui calculé précédemment
 * @param int numéro de la socket de dialogue
 * @param requete_t requête envoyée par le client pour payer
 */ 
void verifierPaiementCmd(int sd, requete_t req){
    char newFileName[50], numReq[5];
    message_t buff;

    // Grâce à la requête passée en paramètre,
    // nous recalculons le prix de la commande 
    // passée à la borne précédente borne et le
    // comparons à celui passé en paramètre de la requête
    strcpy(newFileName, "db/");
    sprintf(numReq, "%hd", req.noReq);
    strcat(newFileName, numReq);
    strcat(newFileName, ".txt\0");
    int prix = calculerPrixCmd(newFileName);

    // Si les 2 prix sont identiques,
    // nous indiquons au client que sa commande est bien 
    // validée par l'envoi d'une requête contenant un 
    // message de validation de commande 
    if (atoi(req.params) == prix){
        reponse_t rep;
        rep.noCommande = req.noReq;
        strcpy(rep.result,"La commande est validée");
        strcpy(buff, rep2str(&rep, buff));
        CHECK(send(sd, buff, strlen(buff)+1, 0),"-- PB : send()");
    }
}

/**
 * @fn void donnerCmd(int sd, requete_t req)
 * @brief restitue la commande passée en borne°1 au client
 * @param int numéro de la socket de dialogue
 * @param requete_t requête envoyée par le client pour recevoir sa commande
 */ 
void donnerCmd(int sd, requete_t req){
    char newFileName[50], numReq[5];
    message_t buff;
    reponse_t rep;

    strcpy(newFileName, "db/");
    sprintf(numReq, "%hd", req.noReq);
    strcat(newFileName, numReq);
    strcat(newFileName, ".txt\0");
    // Une fois la commande donnée au client,
    // nous supprimons le fichier de commande associé
    remove(newFileName); 

    // Nous donnons la commande au client
    rep.noCommande = req.noReq;
    strcpy(rep.result,"Voila votre commande");
    strcpy(buff, rep2str(&rep, buff));
    CHECK(send(sd, buff, strlen(buff)+1, 0),"-- PB : send()");
}

/**
 * @fn void enregistrer(int sd, requete_t req)
 * @brief confirme ou non au client qu'il s'est bien enregistré auprès du serveur d'enregistrement
 * @param int numéro de la socket de dialogue
 * @param requete_t requête envoyée par le client pour demander son enregistrement auprès du serveur d'enregistrement
 */ 
void enregistrer(int sd, requete_t req){
    reponse_t rep;
    message_t buff;

    switch (req.noReq) {
        case 1 : // cas du client serveur
                 rep.noCommande = 0;
                 strcpy(rep.result, "Le client serveur est bien enregistré");
        break;
        case 0 : // cas du client normal
                 rep.noCommande = ++incNoCommande;
                 strcpy(rep.result, "Le client est enregistré");
        break;
    }

    strcpy(buff, rep2str(&rep, buff));
    CHECK(send(sd, buff, strlen(buff)+1, 0),"-- PB : send()");
}


