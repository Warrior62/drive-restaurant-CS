#include "lib/standard.h"

/******************************************************************/
/*                           REQUETES                             */
/******************************************************************/
void passerCmd(){
    message_t buff;
	int sad = creerSocketAppel();
<<<<<<< HEAD
    
=======

>>>>>>> dev
    affichageProduits();
    envoyerRequete(sad, "[CLIENT] Passage de la commande...");
    // Attente d'une réponse
	memset(buff, 0, MAX_BUFF);
	CHECK(recv(sad, buff, MAX_BUFF, 0),"-- PB : recv()");
	printf("\t[CLIENT]:Réception d'une réponse sur [%d]\n", sad);
	printf("\t\t[CLIENT]:Réponse reçue : ##%s##\n", buff);
}

void demanderPaiementCmd(){}
void demanderCmd(){}


/******************************************************************/
/*                           REPONSES                             */
/******************************************************************/
void annoncerPrixCmd(int sd, struct sockaddr_in *cltAdr){
<<<<<<< HEAD
	// Dialogue avec le client
	// Ici, lecture d'une reqête et envoi d'une réponse
	message_t buff;
	int req;	
=======
	// Ici, lecture d'une reqête et envoi d'une réponse
	message_t buff;
	int req;
	requete_t reqPrixCmd;	
	char newFileName[50];
	FILE *fCmd;

    // récupération du fichier de la commande dernièrement passée
    // calcul du prix final de la commande
    // envoi le prix de la commande sous forme de réponse 
>>>>>>> dev

	memset(buff, 0, MAX_BUFF);
	printf("\t[SERVER]: 1 - Attente de réception d'une commande\n");
	CHECK (recv(sd, buff, MAX_BUFF, 0), "--PB : recv() commande");
	printf("\t[SERVER]:Commande reçue : ##%s##\n", buff);
	printf("\t\t[SERVER]:du client d'adresse [%s:%d]\n",
			inet_ntoa(cltAdr->sin_addr), ntohs(cltAdr->sin_port));
	sscanf(buff,"%d",&req);

<<<<<<< HEAD
	switch(req){
		case 1 : printf("\t[SERVER]:Annonce du prix de la commande sur [%d]\n", sd);
				 CHECK(send(sd, REPONSE1, strlen(REPONSE1)+1, 0),"-- PB : send()");
				 printf("\t\t[SERVER]:réponse envoyée : ##%s##\n", REPONSE1);
				 break;
		case 2 : printf("\t[SERVER]:Envoi d'une réponse sur [%d]\n", sd);
				 CHECK(send(sd, REPONSE2, strlen(REPONSE2)+1, 0),"-- PB : send()");
				 printf("\t\t[SERVER]:réponse envoyée : ##%s##\n", REPONSE2);
				 break;
		case 3 : printf("\t[SERVER]:Envoi d'une réponse sur [%d]\n", sd);
				 CHECK(send(sd, REPONSE3, strlen(REPONSE3)+1, 0),"-- PB : send()");
				 printf("\t\t[SERVER]:réponse envoyée : ##%s##\n", REPONSE3);
				 break;
	}
=======
	// on stocke dans newFileName le chemin du nouveau fichier de cmd créé
	strcpy(newFileName, creerFichierCmd(fCmd, buff));
	
	// on annonce le prix de la commande au client
	printf("\t[SERVER]:Annonce du prix de la commande sur [%d]\n", sd);
	CHECK(send(sd, "Prix de la commande: " + calculerPrixCmd(newFileName), strlen(buff)+1, 0),"-- PB : send()");
>>>>>>> dev
	
	CHECK(shutdown(sd, SHUT_WR),"-- PB : shutdown()");
	sleep(1);
	// utiliser les getsockopts pour déterminer si le client a envoyé qq chose
}

void effectuerPaiement(){}
void donnerCmd(){}



