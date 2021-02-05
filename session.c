#include "./lib/session.h"
#include "./lib/data.h"

/**
 * @fn int sessionSrv(char *, int)
 * @brief établit une session serveur en créant une socket d'écoute
 * @param addr adresse IP à attribuer au serveur
 * @param port numéro du port à attribuer au serveur
 * @return le numéro de la socket d'écoute créée
 */ 
int sessionSrv(char * addr, int port) {
    int se /*socket écoute*/;
    struct sockaddr_in seAdr;

    // Création d’une socket INET/STREAM : nécessite une connexion
    CHECK(se = socket(PF_INET, SOCK_STREAM, 0),"-- PB : socket()");
    printf("[SERVER]:Création de la socket d'écoute [%d]\n", se);
    // Préparation d’un adressage pour une socket INET
    seAdr.sin_family = PF_INET;
    seAdr.sin_port = htons(port);				// htons() : network order
    seAdr.sin_addr.s_addr = inet_addr(addr);	// adresse effective
    memset(&(seAdr.sin_zero), 0, 8);
    // Association de la socket d'écoute avec l’adresse d'écoute
    CHECK(bind(se, (struct sockaddr *)&seAdr, sizeof(seAdr)),"-- PB : bind() -- sessionSrv()");
    printf("[SERVER]:Association de la socket [%d] avec l'adresse [%s:%d]\n", se, inet_ntoa(seAdr.sin_addr), ntohs(seAdr.sin_port));
    // Mise de la socket à l'écoute
    CHECK(listen(se, 3), "--PB : listen()");	// 5 est le nb de clients mis en attente
    // Boucle permanente (1 serveur est un daemon)
    printf("[SERVER]:Ecoute de demande de connexion (3 max) sur le canal [%d] d'adresse [%s:%d]\n", se, inet_ntoa(seAdr.sin_addr), ntohs(seAdr.sin_port));
    return se;
}

int sessionCltSrv(char * addr, int port) {
    int se /*socket écoute*/;
    struct sockaddr_in seAdr;

    // Création d’une socket INET/STREAM : nécessite une connexion
    CHECK(se = socket(PF_INET, SOCK_STREAM, 0),"-- PB : socket()");
    printf("[CLIENTSERVER]:Création de la socket d'écoute [%d]\n", se);
    // Préparation d’un adressage pour une socket INET
    seAdr.sin_family = PF_INET;
    seAdr.sin_port = htons(port);				// htons() : network order
    seAdr.sin_addr.s_addr = inet_addr(addr);	// adresse effective
    memset(&(seAdr.sin_zero), 0, 8);
    // Association de la socket d'écoute avec l’adresse d'écoute
    CHECK(bind(se, (struct sockaddr *)&seAdr, sizeof(seAdr)),"-- PB : bind() -- sessionSrv()");
    printf("[CLIENTSERVER]:Association de la socket [%d] avec l'adresse [%s:%d]\n", se, inet_ntoa(seAdr.sin_addr), ntohs(seAdr.sin_port));
    // Mise de la socket à l'écoute
    CHECK(listen(se, 3), "--PB : listen()");	// 5 est le nb de clients mis en attente
    // Boucle permanente (1 serveur est un daemon)
    printf("[CLIENTSERVER]:Ecoute de demande de connexion (3 max) sur le canal [%d] d'adresse [%s:%d]\n", se, inet_ntoa(seAdr.sin_addr), ntohs(seAdr.sin_port));
    return se;
}

/**
 * @fn int creerSocketDiscussion(struct sockaddr_in *cltAdr, int se)
 * @brief crée une socket de discussion
 * @param cltAdr structure d'adressage du client
 * @param se socket d'écoute
 * @return le numéro de la socket de discussion créée
 */ 
int creerSocketDiscussion(struct sockaddr_in *cltAdr, int se){
	int sd;
	socklen_t lenClt=sizeof(cltAdr);
	CHECK(sd=accept(se, (struct sockaddr *)cltAdr, &lenClt),"-- PB : accept()");
	printf("[SERVER]:Acceptation de connexion du client [%s:%d]\n", inet_ntoa(cltAdr->sin_addr), ntohs(cltAdr->sin_port));
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

/**
 * @fn void envoyerRequete(int, char *)
 * @brief envoie une requête au serveur d'enregistrement
 * @param sad socket d'appel et de dialogue
 * @param msg message string à envoyer par la socket
 */ 
void envoyerRequete(int sad, char *msg){
	CHECK(send(sad, msg, strlen(msg)+1, 0),"-- PB : send()");
}

/**
 * @fn void connecter(int, struct sockaddr_in *srvAdr)
 * @brief permet la connexion au serveur
 * @param sad socket d'appel et de dialogue
 * @param srvAdr structure d'adressage du serveur
 */ 
void connecter(int sad, struct sockaddr_in * srvAdr){
	CHECK(connect(sad, (struct sockaddr *)&srvAdr, sizeof(srvAdr)),"-- PB : connect()");
	printf("[CLIENT]:Connexion effectuée avec le serveur [%s:%d] par le canal [%d]\n", inet_ntoa(srvAdr->sin_addr), ntohs(srvAdr->sin_port), sad);	
}

/**
 * @fn void dialSrv2Clt(int sd, struct sockaddr_in *cltAdr)
 * @brief permet le communication du serveur vers le client 
 * @param sd socket de dialogue
 * @param cltAdr structure d'adressage du client
 * @note selon l'action à effectuer, le switch déclenche les réponses à envoyer
 */ 
void dialSrv2Clt(int sd, struct sockaddr_in *cltAdr) {
	// Dialogue avec le client
	// Ici, lecture d'une reqête et envoi d'une réponse
	message_t buff;
	memset(buff, 0, MAX_BUFF);
	printf("\t[SERVER]:Attente de réception d'une requête\n");
	CHECK(recv(sd, buff, MAX_BUFF, 0), "PB-- recv()");
	printf("\t[SERVER]:Requête reçue : ##%s##\n", buff);
	printf("\t\t[SERVER]:du client d'adresse [%s:%d]\n", inet_ntoa(cltAdr->sin_addr), ntohs(cltAdr->sin_port));
	
	requete_t req = str2req(buff);
    /**
	printf("Je dois faire %s\n", req.action);
	printf("Il a commandé %s", req.params);
    */

	switch(atoi(req.action)){
        case 0 :
            switch(req.noReq) {
                case 0 : printf("Un client pour le drive vient de s'enregistrer\n");
                break;
                case 1 : printf("Une de mes bornes vient de s'enregistrer\n");
                break;
            }
            enregistrer(sd,req);
        break;
	}

	CHECK(shutdown(sd, SHUT_WR),"-- PB : shutdown()");
	sleep(1);
	// utiliser les getsockopts pour déterminer si le client a envoyé qq chose
}

void dialClt2Clt(int sd, struct sockaddr_in *cltAdr) {
	// Dialogue avec le client
	// Ici, lecture d'une reqête et envoi d'une réponse
	message_t buff;
	
	memset(buff, 0, MAX_BUFF);
	printf("\t[CLIENTSERVER]:Attente de réception d'une requête\n");
	CHECK(recv(sd, buff, MAX_BUFF, 0), "PB-- recv()");
	printf("\t[CLIENTSERVER]:Requête reçue : ##%s##\n", buff);
	printf("\t\t[CLIENTSERVER]:du client d'adresse [%s:%d]\n", inet_ntoa(cltAdr->sin_addr), ntohs(cltAdr->sin_port));
	
	requete_t req = str2req(buff);

	switch(atoi(req.action)){
        case 1 : annoncerPrixCmd(sd, req);
        break;
		case 2 : //paiement de la commande
		    verifierPaiementCmd(sd, req);
		break;
		case 3 : //demande de recupération de commande
            donnerCmd(sd, req);
		break;
	}

	CHECK(shutdown(sd, SHUT_WR),"-- PB : shutdown()");
	sleep(1);
}

/**
 * @fn void connectSrv(int sad, char *, int)
 * @brief permet la connexion au serveur
 * @param sad socket d'appel et de dialogue
 * @param addr adresse IP à attribuer au serveur
 * @param port numéro du port à attribuer au serveur
 */ 
void connectSrv(int sad, char * addr, int port) {
	struct sockaddr_in srvAdr;
	// le client doit fournir l'adresse du serveur
	srvAdr.sin_family = PF_INET;
	srvAdr.sin_port = htons(port);
	srvAdr.sin_addr.s_addr = inet_addr(addr);
	memset(&(srvAdr.sin_zero), 0, 8);
	// demande connexion 
	CHECK(connect(sad, (struct sockaddr *)&srvAdr, sizeof(srvAdr)),"-- PB : connect()");
    //CHECK_T(pthread_mutex_lock(&mutexEcran),"Pb lock mutexEcran");
    printf("[CLIENT]:Connexion effectuée avec le serveur [%s:%d] par le canal [%d]\n", inet_ntoa(srvAdr.sin_addr), ntohs(srvAdr.sin_port), sad);
    //CHECK_T(pthread_mutex_unlock(&mutexEcran),"Pb unlock mutexEcran");
}








