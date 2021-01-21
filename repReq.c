/******************************************************************/
/*                           REQUETES                             */
/******************************************************************/
void passerCmd(){
    message_t buff;
	int sad = creerSocketAppel();
    
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
	// Dialogue avec le client
	// Ici, lecture d'une reqête et envoi d'une réponse
	message_t buff;
	int req;	

	memset(buff, 0, MAX_BUFF);
	printf("\t[SERVER]: 1 - Attente de réception d'une commande\n");
	CHECK (recv(sd, buff, MAX_BUFF, 0), "--PB : recv() commande");
	printf("\t[SERVER]:Commande reçue : ##%s##\n", buff);
	printf("\t\t[SERVER]:du client d'adresse [%s:%d]\n",
			inet_ntoa(cltAdr->sin_addr), ntohs(cltAdr->sin_port));
	sscanf(buff,"%d",&req);

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
	
	CHECK(shutdown(sd, SHUT_WR),"-- PB : shutdown()");
	sleep(1);
	// utiliser les getsockopts pour déterminer si le client a envoyé qq chose
}

void effectuerPaiement(){}
void donnerCmd(){}


