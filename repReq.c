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
reponse_t passerCmd(int sad){
    message_t buff, msg;
    char choix;
    int i = 0;
    requete_t req;
    req.noReq = 0;
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
    CHECK_T(pthread_mutex_unlock(&mutexEcran),"Pb unlock mutexEcran");
    envoyerRequete(sad, req2str(&req, msg));
    // Attente d'une réponse
	memset(buff, 0, MAX_BUFF);
	CHECK(recv(sad, buff, MAX_BUFF, 0),"-- PB : recv() -- passerCmd()");
    CHECK_T(pthread_mutex_lock(&mutexEcran),"Pb lock mutexEcran");
	printf("\t[CLIENT]:Réception d'une réponse sur [%d]\n", sad);
	printf("\t\t[CLIENT]:Réponse reçue : ##%s##\n", buff);
    CHECK_T(pthread_mutex_unlock(&mutexEcran),"Pb unlock mutexEcran");
	reponse_t rep = str2rep(buff);
	return rep;
}

// void demanderPaiementCmd(){}
// void demanderCmd(){}


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
    // Ici, lecture d'une reqête et envoi d'une réponse
    message_t buff, copyBuff;

    //memset(buff, 0, MAX_BUFF);

    char newFileName[50], numReq[5];

    reponse_t rep;
    rep.noCommande = ++incNoCommande;
    req.noReq = rep.noCommande;

    strcpy(newFileName, "db/");
    // strcpy(numReq, "");
    sprintf(numReq, "%hd", req.noReq);
    strcat(newFileName, numReq);
    strcat(newFileName, ".txt\0");
    printf("**%s**\n", newFileName);
    creerFichierCmd(req, newFileName);

    printf("on lance calculer prix cmd\n");
    int prix = calculerPrixCmd(newFileName);
    char * prixStr = (char *)malloc(sizeof(char)*5);
    // strcpy(prixStr, "");
    sprintf(prixStr, "%d", prix);
    strcpy(rep.result, prixStr);


    printf("\t[SERVER]:Annonce du prix de la commande sur [%d]\n", sd);
    strcpy(buff, rep2str(&rep, buff));

    // je crée une copie du buffer pour ne pas le modifier 
    strcpy(copyBuff, buff);
    char *strPrixCmd = strtok(copyBuff, ":");
    strPrixCmd = strtok(NULL, ":");

    printf("--> PRIX COMMANDE : %s€\n", strPrixCmd);
    printf("Veuillez passer à la prochaine borne de commande !\n");
    CHECK(send(sd, buff, strlen(buff)+1, 0),"-- PB : send()");

    CHECK(shutdown(sd, SHUT_WR),"-- PB : shutdown()");
    sleep(1);
    // utiliser les getsockopts pour déterminer si le client a envoyé qq chose
}

/**
 * @fn void effectuerPaiementCmd(int, int, int)
 * @brief permet au client de payer sa commande
 * @param numCom numéro de la commande à payer
 * @param prix prix de la commande à payer
 * @param sad socket d'appel et de dialogue
 */ 
void effectuerPaiementCmd(int numCom, int prix, int sad){
    requete_t req;
    req.noReq = numCom;
    req.action[0] = 2;
    sprintf(req.params, "%d", prix);
    message_t msg;
    envoyerRequete(sad,req2str(&req, msg));

}
// void donnerCmd(){}



