// #include "./lib/standard.h"
// #include "./lib/repReq.h"
#include "./lib/session.h"
#include "./lib/data.h"

/**
 * @fn      int creerSocketEcoute(int se, struct sockaddr_in seAdr);  
 * @brief   crée une socket à l'écoute de requête(s) client(s)
 * @note    associe aussi la socket d'écoute se à la structure d'adressage seAdr
 * @return  le numéro de la socket d'écoute créée
 */ 
int creerSocketEcoute()
{
    int se;
	struct sockaddr_in seAdr;

	CHECK(se = socket(PF_INET, SOCK_STREAM, 0),"-- PB : socket()");
	printf("[SERVER]:Création de la socket d'écoute [%d]\n", se);
	// Préparation d’un adressage pour une socket INET
	seAdr.sin_family = PF_INET;
	seAdr.sin_port = htons(ADDR_SRV);				// htons() : network order	
	seAdr.sin_addr.s_addr = inet_addr(ADDR_SRV);	// adresse effective
	memset(&(seAdr.sin_zero), 0, 8);
	// Association de la socket d'écoute avec l’adresse d'écoute
	CHECK(bind(se, (struct sockaddr *)&seAdr, sizeof(seAdr)),"-- PB : bind() - creerSocketEcoute()");
	CHECK(listen(se, 0), "--PB : listen()");

    return se;
}


int creerSocketDiscussion(struct sockaddr_in *cltAdr, socklen_t lenCltAdr, int se){
	int sd;
	CHECK(sd=accept(se, (struct sockaddr *)&cltAdr, &lenCltAdr),"-- PB : accept()");
	printf("[SERVER]:Accepation de connexion du client [%s:%d]\n", inet_ntoa(cltAdr->sin_addr), ntohs(cltAdr->sin_port));
	return sd;
}


/**
 * @fn      int creerSocketAppel(void);  
 * @brief   crée une socket d'appel
 * @note    pas d'association de la socket d'appel avec une structure d'adressage de socket
 * @return  le numéro de la socket d'appel créée
 */ 
int creerSocketAppel(void)
{
    int sad;
	CHECK(sad = socket(PF_INET, SOCK_STREAM, 0),"-- PB : socket()");
	printf("[CLIENT]:Création de la socket d'appel et de dialogue [%d]\n", sad);		
	// Le client n'a pas besoin d'avoir une adresse
	// ICI, Pas de préparation ni d'association
	return sad;
}

void envoyerRequete(int sad, char *msg){
	CHECK(send(sad, msg, strlen(msg)+1, 0),"-- PB : send()");

}

void connecter(int sad, struct sockaddr_in * srvAdr){
	CHECK(connect(sad, (struct sockaddr *)&srvAdr, sizeof(srvAdr)),"-- PB : connect()");
	printf("[CLIENT]:Connexion effectuée avec le serveur [%s:%d] par le canal [%d]\n", inet_ntoa(srvAdr->sin_addr), ntohs(srvAdr->sin_port), sad);	
}

void dialSrv2Clt(int sd, struct sockaddr_in *cltAdr) {
	// Dialogue avec le client
	// Ici, lecture d'une reqête et envoi d'une réponse
	message_t buff;
	
	memset(buff, 0, MAX_BUFF);
	printf("\t[SERVER]:Attente de réception d'une requête\n");
	CHECK (recv(sd, buff, MAX_BUFF, 0), "PB-- recv()");
	printf("\t[SERVER]:Requête reçue : ##%s##\n", buff);
	printf("\t\t[SERVER]:du client d'adresse [%s:%d]\n",
			inet_ntoa(cltAdr->sin_addr), ntohs(cltAdr->sin_port));
	
	requete_t req = str2req(buff);
	switch(req.noReq){
		case 1 : //passer commande
				annoncerPrixCmd(sd, req);
		break;
		case 2 : //demande de paiment
		break;
		case 3 : //paiement de la commande
		break;
		case 4: //demande de recupération de commande
		break;
	}

	CHECK(shutdown(sd, SHUT_WR),"-- PB : shutdown()");
	sleep(1);
	// utiliser les getsockopts pour déterminer si le client a envoyé qq chose
}





