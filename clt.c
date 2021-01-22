#include "lib/standard.h"
#include "lib/repReq.h"
#include "lib/session.h"
#include "lib/data.h"

int main(){
    printf("Test main clt.c\n");
    int choix;
    while(choix){
        printf("Que voulez vous faire?\n");
        printf("1-Commander\n");
        printf("2-Payer\n");
        printf("3-Récuperer une commande\n");
        printf("0-Partir\n");
        scanf("%d", &choix);
        switch(choix){
            case 1 : //passerCommande
            break;
            case 2 : //Payer
            break;
            case 3 : //Recuperer
            break;

        }

    }
    return 0;
}