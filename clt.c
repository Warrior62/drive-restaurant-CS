//#include "lib/standard.h"
//#include "lib/repReq.h"
#include "lib/session.h"
#include "lib/data.h"

int fini = 0;

int main(){
    int cpt =0;
    param_thread_t params, params1, params2;
    CHECK_T(pthread_mutex_init(&mutexEcran,NULL),"Pb init mutexEcran");

    struct sigaction newact;
    void deroute(int);

    newact.sa_handler = deroute;
    CHECK(sigemptyset(&newact.sa_mask),"pb avec sigemptyset");
    newact.sa_flags = 0;
    CHECK(sigaction(SIGALRM, &newact, NULL), "pb avec sigaction");

    pthread_t tid[MAX_CLIENT+2];
    params.addr = ADDR_CLT_PAS;
    params.port = PORT_SRV_PAS;
    CHECK_T(pthread_create(&tid[MAX_CLIENT], NULL, (pf_t)clientServeur, (void *) &params), "erreur création thread client");

    params1.addr = ADDR_CLT_PAY;
    params1.port = PORT_SRV_PAY;
    CHECK_T(pthread_create(&tid[MAX_CLIENT+1], NULL, (pf_t)clientServeur, (void *) &params1), "erreur création thread client");

    params2.addr = ADDR_CLT_REC;
    params2.port = PORT_SRV_REC;
    CHECK_T(pthread_create(&tid[MAX_CLIENT+2], NULL, (pf_t)clientServeur, (void *) &params2), "erreur création thread client");

    sleep(5);

    for(cpt=0; cpt<MAX_CLIENT; cpt++){
        CHECK_T(pthread_create(&tid[cpt], NULL, (pf_t)client, NULL), "erreur création thread client");
    }


    for(cpt=0; cpt<MAX_CLIENT; cpt++)
        CHECK(pthread_join(tid[cpt], NULL), "pthread_join(client)");

    alarm(10);

    CHECK(pthread_join(tid[MAX_CLIENT], NULL), "pthread_join(client)");
    CHECK(pthread_join(tid[MAX_CLIENT+1], NULL), "pthread_join(client)");
    CHECK(pthread_join(tid[MAX_CLIENT+2], NULL), "pthread_join(client)");

    CHECK_T(pthread_mutex_destroy(&mutexEcran),"Pb destroy mutexEcran");
    return 0;
}

/**
 * @fn void client(void) 
 * @brief joue le rôle de thread client
 */ 
void client(){
    int prixCommande, numCommande;
    int sad;

    sad=sessionClt();
    connectSrv(sad, ADDR_SRV, PORT_SRV);
    reponse_t rep = senregistrer(sad,0);
    numCommande = rep.noCommande;

    //Passage de la commande
    sad=sessionClt();
    connectSrv(sad, ADDR_CLT_PAS, PORT_SRV_PAS);
    rep = passerCmd(sad, numCommande);
    prixCommande = atoi(rep.result);



    //Paiement de la commande;
    sad=sessionClt();
    connectSrv(sad, ADDR_CLT_PAY, PORT_SRV_PAY);

    effectuerPaiementCmd(numCommande, prixCommande, sad);


    //Recupération de la commande
    sad=sessionClt();
    connectSrv(sad, ADDR_CLT_REC, PORT_SRV_REC);

    demanderCmd(sad,numCommande);

    pthread_exit(EXIT_SUCCESS);


}

/**
 * @fn void clientServeur(param_thread_t *)
 * @brief crée un thread client faisant office de serveur pour être appelé 
 * @param param_thread_t datas à passer en argument de pthread_create()
 */ 
void clientServeur(param_thread_t * params){
    int sad;

    sad=sessionClt();
    connectSrv(sad, ADDR_SRV, PORT_SRV);
    senregistrer(sad, 1);

    int se /* écoute */, sd /* dialogue */;
    struct sockaddr_in clt;
    //printf("%d", getpid());
    se = sessionCltSrv(params->addr, params->port);
    while(1){
        sd = creerSocketDiscussion(&clt, se);
        dialClt2Clt(sd, &clt);
        //getchar();
        CHECK(shutdown(sd, SHUT_RDWR),"-- PB : shutdown()");
        CHECK(close(sd),"-- PB : close()");
    }
    CHECK(close(se), "--PB : close(se)");

}

/**
 * @fn int sessionClt(void)
 * @brief établit une session client en créant une socket d'appel et de dialogue
 * @return le numéro de la socket d'appel et de dialogue créée
 */ 
int sessionClt(void) {
	int sad;
	// Création d’une socket INET/STREAM d'appel et de dialogue
	CHECK(sad = socket(PF_INET, SOCK_STREAM, 0),"-- PB : socket()");
    CHECK_T(pthread_mutex_lock(&mutexEcran),"Pb lock mutexEcran");
	printf("[CLIENT]:Création de la socket d'appel et de dialogue [%d]\n", sad);
    CHECK_T(pthread_mutex_unlock(&mutexEcran),"Pb unlock mutexEcran");
	// Le client n'a pas besoin d'avoir une adresse mais il peut
	// ICI, Pas de préparation ni d'association
	return sad;
}

void deroute(int signal_number){
    switch(signal_number){
        case SIGALRM : exit(0);
            break;
        default : printf("Signal non traité !\n");
            break;
    }
}


