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

/**
 * @fn void serveur(void)
 * @brief joue le rôle de serveur d'enregistrement
 */ 
void serveur(void){
    int se /* écoute */, sd /* dialogue */;
    struct sockaddr_in clt;
    printf("%d", getpid());
    se = sessionSrv(ADDR_SRV, PORT_SRV);
	while (1) {
		sd = creerSocketDiscussion(&clt, se);
		dialSrv2Clt(sd, &clt);
		CHECK(close(sd),"-- PB : close()");
	}
	CHECK(close(se), "--PB : close(se)");

}



