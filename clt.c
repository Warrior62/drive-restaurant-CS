//#include "lib/standard.h"
//#include "lib/repReq.h"
#include "lib/session.h"
#include "lib/data.h"

int main(){
    int choix = 1;
    printf("Test main clt.c\n");
    int sad;
    sad=sessionClt();
     while(choix){
         printf("Que voulez vous faire?\n");
         printf("1 - Commander\n");
         printf("2 - Payer\n");
         printf("3 - Récuperer une commande\n");
         printf("0 - Partir\n\n");
         printf("Votre choix: ");
         scanf("%d", &choix);
         switch(choix){
             case 1 :
                 connectSrv(sad);
                 passerCmd(sad);
             break;
             case 2 : //payer
             break;
             case 3 : //Recuperer
             break;
         }
    }
    return 0;
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

