// #include "lib/standard.h"
// #include "repReq.c"
#include "./lib/repReq.h"
#include "./lib/session.h"

int main(){
    printf("Test main srv.c\n");
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    CHECK_T(pthread_create(&tid, &attr, (pf_t)serveur, NULL), "erreur création thread serveur");
    pthread_exit(EXIT_SUCCESS);
    return 0;
}

void serveur(void){
	//message_t buff;	
	int se /* écoute */, sd /* dialogue */;
	struct sockaddr_in clt;
    printf("%d", getpid());
	se = sessionSrv();
	while (1) {
		sd = creerSocketDiscussion(&clt, se);
		dialSrv2Clt(sd, &clt);
		getchar();
		CHECK(close(sd),"-- PB : close()");
	}
	CHECK(close(se), "--PB : close(se)");
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
	printf("[SERVER]:Association de la socket [%d] avec l'adresse [%s:%d]\n", se, inet_ntoa(seAdr.sin_addr), ntohs(seAdr.sin_port));
	// Mise de la socket à l'écoute
	CHECK(listen(se, 3), "--PB : listen()");	// 5 est le nb de clients mis en attente
	// Boucle permanente (1 serveur est un daemon)
	printf("[SERVER]:Ecoute de demande de connexion (3 max) sur le canal [%d] d'adresse [%s:%d]\n", se, inet_ntoa(seAdr.sin_addr), ntohs(seAdr.sin_port));
	return se;
}

