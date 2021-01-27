//#include "lib/standard.h"
//#include "lib/repReq.h"
#include "lib/session.h"
#include "lib/data.h"


int main(){
    int cpt =0;
    param_thread_t params;
    CHECK_T(pthread_mutex_init(&mutexEcran,NULL),"Pb init mutexEcran");
    CHECK_T(pthread_mutex_init(&mutexClientPay,NULL),"Pb init mutexClientPay");
    pthread_t tid[MAX_CLIENT];
    for(cpt=0; cpt<MAX_CLIENT; cpt++){
        CHECK_T(pthread_create(&tid[cpt], NULL, (pf_t)client, NULL), "erreur création thread client");
    }

    params.addr = ADDR_CLT_PAY;
    params.port = PORT_SRV_PAY;

    CHECK_T(pthread_create(&tid[cpt+1], NULL, (pf_t)clientServeur, (void *) &params), "erreur création thread client");

    for(cpt=0; cpt<MAX_CLIENT; cpt++)
        CHECK(pthread_join(tid[cpt], NULL), "pthread_join(client)");

    CHECK_T(pthread_mutex_destroy(&mutexEcran),"Pb destroy mutexEcran");
    CHECK_T(pthread_mutex_destroy(&mutexClientPay),"Pb destroy mutexClientPay");
    return 0;
}

void client(){
    printf("je suis client\n");
    int prixCommande, numCommande;
    //printf("Test main clt.c\n");
    //fflush(stdout);
    int sad;
    printf("Lancement du client d'id = 0x%08lx\n", (long)pthread_self());
    //Passage de la commande
    sad=sessionClt();
    connectSrv(sad, ADDR_SRV, PORT_SRV);
    reponse_t rep = passerCmd(sad);
    prixCommande = atoi(rep.result);
    numCommande = rep.noCommande;

    sad=sessionClt();
    connectSrv(sad, ADDR_CLT_PAY, PORT_SRV_PAY);


    CHECK_T(pthread_mutex_lock(&mutexClientPay),"Pb lock mutexClientPay");
    effectuerPaiementCmd(numCommande, prixCommande, sad);
    CHECK_T(pthread_mutex_unlock(&mutexClientPay),"Pb unlock mutexClientPay");

    pthread_exit(EXIT_SUCCESS);
    //Paiement de la commande;



    //Recupération de la commande


}

void clientServeur(param_thread_t * params){
    int se /* écoute */, sd /* dialogue */;
    int fermer = 1;
    struct sockaddr_in clt;
    printf("%d", getpid());
    se = sessionSrv(params->addr, params->port);
    while(1){
        sd = creerSocketDiscussion(&clt, se);
        dialSrv2Clt(sd, &clt);
        getchar();
        CHECK(shutdown(sd, SHUT_RDWR),"-- PB : shutdown()");
        CHECK(close(sd),"-- PB : close()");
        printf("0 pour fermer le clientServeur\n");
        scanf("%d", &fermer);
        if(fermer == 0) break;
    }

}


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

