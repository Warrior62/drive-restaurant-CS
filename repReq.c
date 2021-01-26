// #include "lib/standard.h"
// #include "lib/repReq.h"
#include "lib/session.h"
#include "lib/data.h"

int incNoCommande = 0;
/******************************************************************/
/*                           REQUETES                             */
/******************************************************************/
void passerCmd(int sad){
    message_t buff, msg;
    char choix;
    int i = 0;
    requete_t req;
    req.noReq = 0;
    strcpy(req.action, "1");
    // int sad = creerSocketAppel();
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
}

// void demanderPaiementCmd(){}
// void demanderCmd(){}


/******************************************************************/
/*                           REPONSES                             */
/******************************************************************/

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

// void effectuerPaiement(){}
// void donnerCmd(){}



