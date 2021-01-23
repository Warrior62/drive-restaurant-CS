// #include "lib/standard.h"
// #include "repReq.c"
#include "./lib/repReq.h"
#include "./lib/session.h"

int main(){
    printf("Test main srv.c\n");
	serveur();
    return 0;
}

void serveur(void){
	//message_t buff;	
	int se /* écoute */, sd /* dialogue */;
	struct sockaddr_in clt;
	socklen_t lenClt=sizeof(clt);

	// Déclaration & création d'une socket UNIX en mode STREAM
	se = creerSocketEcoute();
	// Préparation de l'adressage de la socket
	// mySockName.sin_family = PF_INET;
	// strcpy(mySockName.sin_path, "./sockUnix");
	// Association la socket avec son adresse
	// CHECK(bind(se, (struct sockaddr *)&mySockName, sizeof(mySockName)),"bind serveur");
	
	// Mettre en place une socket d'écoute prête à la réception des connexions	
	se = sessionSrv();
	// Boucle infinie : attente requête / traitement de la requête
	while (1) { 
		// attente de connexion d'un client et création d'une socket de dialogue
		sd = creerSocketDiscussion(&clt, lenClt, se);
		// dialogue avec le client connecté
		dialSrv2Clt(sd, &clt);
		// Fermeture de la socket de dialogue
		getchar();
		CHECK(close(sd),"-- PB : close()");
	}
	// fermeture de la socket
	CHECK(close(se), "--PB : close(se)");
	// suppresion de la socket
	// unlink(mySockName.sun_path);
}

int sessionSrv(void) {
	int se /*socket écoute*/;
	struct sockaddr_in seAdr;

	// Création d’une socket INET/STREAM : nécessite une connexion
	CHECK(se = socket(PF_INET, SOCK_STREAM, 0),"-- PB : socket()");
	printf("[SERVER]:Création de la socket d'écoute [%d]\n", se);
	// Préparation d’un adressage pour une socket INET
	seAdr.sin_family = PF_INET;
	seAdr.sin_port = htons(PORT_SRV);				// htons() : network order	
	seAdr.sin_addr.s_addr = inet_addr(ADDR_SRV);	// adresse effective
	memset(&(seAdr.sin_zero), 0, 8);
	// Association de la socket d'écoute avec l’adresse d'écoute
	CHECK(bind(se, (struct sockaddr *)&seAdr, sizeof(seAdr)),"-- PB : bind() -- sessionSrv()");
	printf("[SERVER]:Association de la socket [%d] avec l'adresse [%s:%d]\n", se,
				inet_ntoa(seAdr.sin_addr), ntohs(seAdr.sin_port));
	// Mise de la socket à l'écoute
	CHECK(listen(se, 5), "--PB : listen()");	// 5 est le nb de clients mis en attente
	// Boucle permanente (1 serveur est un daemon)
	printf("[SERVER]:Ecoute de demande de connexion (5 max) sur le canal [%d] d'adresse [%s:%d]\n", se, inet_ntoa(seAdr.sin_addr), ntohs(seAdr.sin_port));
	return se;
}

