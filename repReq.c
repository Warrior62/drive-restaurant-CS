// #include "lib/standard.h"
// #include "lib/repReq.h"
#include "lib/session.h"
#include "lib/data.h"
/******************************************************************/
/*                           REQUETES                             */
/******************************************************************/
void passerCmd(int sad){
    message_t buff;
    char choix;
    int i = 0;
    requete_t req;
    req.noReq = 0;
    strcpy(req.action, "1");
    // int sad = creerSocketAppel();
    affichageProduits();
    printf("Que voulez vous commander ? 0 pour valider\n");
    do{
        scanf("%c", &choix);
        printf("%c", choix);
        if(choix != 48) req.params[i] = choix;
        i++;
    }while(choix != 48);
    envoyerRequete(sad, req2str(&req, buff));
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
    message_t buff;
    char newFileName[50], numReq[5];
    strcpy(newFileName, creerFichierCmd(req));

    // on annonce le prix de la commande au client
    printf("\t[SERVER]:Annonce du prix de la commande sur [%d]\n", sd);
    CHECK(send(sd, "Prix de la commande: " + calculerPrixCmd(newFileName), strlen(buff)+1, 0),"-- PB : send()");

    CHECK(shutdown(sd, SHUT_WR),"-- PB : shutdown()");
    sleep(1);
    // utiliser les getsockopts pour déterminer si le client a envoyé qq chose
}

// void effectuerPaiement(){}
// void donnerCmd(){}



