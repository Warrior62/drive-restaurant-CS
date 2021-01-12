#include "lib/standard.h"

int main(){
    printf("Test main srv.c\n");
    return 0;
}

void serveur(void){
    message_t buff;	
	int se /* écoute */, sd /* dialogue */;
	socklen_t lenClt;
	struct sockaddr_un mySockName, clt;
	
	// Déclaration & création d'une socket UNIX en mode STREAM
	CHECK(se = socket(PF_INET, SOCK_STREAM, 0), "socket 1");
	printf("N° de canal créé pour la socket %d\n", se);
	
	// Préparation de l'adressage de la socket
	mySockName.sun_family = PF_INET;
	strcpy(mySockName.sun_path, "./sokUnix");
	// Association la socket avec son adresse
	CHECK(bind(se, (struct sockaddr *)&mySockName, sizeof(mySockName)),"bind serveur");
	while (1) { // Boucle infinie : attente requête / traitement de la requête
		// attente de connexion : accept()
		lenClt = sizeof(clt);
		CHECK(sd=accept(se, (struct sockaddr *)&clt, &lenClt),"accept client");
		memset(&buff, MAX_BUFF, (0));
		printf("Attente de réception d'un message\n");
		CHECK (recv(sd, buff, MAX_BUFF, 0), "recv");
		printf("\tMessage reçu : ##%s## sur le canal %d\n", buff, sd);
		printf("\tpar le canal client : ##%s##\n\n", clt.sun_path);
		close(sd);
	}

	// fermeture de la socket
	close(se);
	// suppresion de la socket
	unlink(mySockName.sun_path);
}

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


