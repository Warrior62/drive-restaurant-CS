#include "lib/standard.h"

/******************************************************************/
/*                           REQUETES                             */
/******************************************************************/
void passerCmd(){
    // envoi d'une requête pour commander
    CHECK(sendfile(), "--PB: sendfile()");
    // création du fichier de commande
    system("touch db/0.txt");
}
void demanderPaiementCmd(){}
void demanderCmd(){}


/******************************************************************/
/*                           REPONSES                             */
/******************************************************************/

void annoncerPrixCmd(int sd, struct sockaddr_in *cltAdr){
	// Ici, lecture d'une reqête et envoi d'une réponse
	message_t buff;
	int req;	

    // récupération du fichier de la commande dernièrement passée
    // calcul du prix final de la commande
    // envoi le prix de la commande sous forme de réponse 

	memset(buff, 0, MAX_BUFF);
	printf("\t[SERVER]: 1 - Attente de réception d'une commande\n");
	CHECK (recv(sd, buff, MAX_BUFF, 0), "--PB : recv() commande");
	printf("\t[SERVER]:Commande reçue : ##%s##\n", buff);
	printf("\t\t[SERVER]:du client d'adresse [%s:%d]\n",
			inet_ntoa(cltAdr->sin_addr), ntohs(cltAdr->sin_port));
	sscanf(buff,"%d",&req);

	switch(req){
		case 1 : 
				 char db[4];
				 strcpy(db, "db/");
				 
				 printf("\t[SERVER]:Annonce du prix de la commande sur [%d]\n", sd);
				 CHECK(send(sd, "Prix de la commande: " + calculerPrixCmd(), strlen(REPONSE1)+1, 0),"-- PB : send()");
				 printf("\t\t[SERVER]:réponse envoyée : ##%s##\n", REPONSE1);
				 break;
	}
	
	CHECK(shutdown(sd, SHUT_WR),"-- PB : shutdown()");
	sleep(1);
	// utiliser les getsockopts pour déterminer si le client a envoyé qq chose
}

void effectuerPaiement(){}
void donnerCmd(){}



