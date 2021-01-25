//#include "lib/standard.h"
//#include "lib/repReq.h"
#include "lib/session.h"
#include "lib/data.h"

int main(){
    int choix;
    printf("Test main clt.c\n");
     while(choix){
         printf("Que voulez vous faire?\n");
         printf("1 - Commander\n");
         printf("2 - Payer\n");
         printf("3 - Récuperer une commande\n");
         printf("0 - Partir\n\n");
         printf("Votre choix: ");
         scanf("%d", &choix);
         switch(choix){
             case 1 : client("Passage de commande souhaité !", 1);
             break;
             case 2 : client("Paiement de commande souhaité!", 2);
             break;
             case 3 : //Recuperer
             break;
         }
    }
    return 0;
}

void client(const char * MSG, int action) {
	int sad /*socket appel et dialogue*/;

	// Mise en place du socket d'appel PF_INET/STREAM adressée ou non
	sad=sessionClt();
	// Connexion avec un serveur
	// la socket d'appel devient une socket de dialogue (connectée)
	connectSrv(sad);
	// Dialogue du client avec le serveur
	// dialClt2Srv(sad, MSG);
    switch (action)
    {
    case 1:
        passerCmd(sad);
        break;
    
    default:
        break;
    }
	// Fermeture de la socket de dialogue
	getchar();
	CHECK(close(sad),"-- PB : close()");	
}

int sessionClt(void) {
	int sad;
	// Création d’une socket INET/STREAM d'appel et de dialogue
	CHECK(sad = socket(PF_INET, SOCK_STREAM, 0),"-- PB : socket()");
	printf("[CLIENT]:Création de la socket d'appel et de dialogue [%d]\n", sad);		
	// Le client n'a pas besoin d'avoir une adresse mais il peut
	// ICI, Pas de préparation ni d'association
	return sad;
}

