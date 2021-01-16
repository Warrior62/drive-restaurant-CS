#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calculerPrixCmd(char *orderFilePath){
    FILE *f;
    f = fopen(orderFilePath, "rt");
    char id[20], quantite[20], prix[20], tabId[100], tabQuantite[100], tabPrix[100];
    int i=0, prixFinal=0;
    
    printf("VOTRE COMMANDE\n");
    while(fscanf(f, "%s %s %s", id, prix, quantite) != EOF){
        strcpy(&tabId[i], id);
        tabQuantite[i] = atoi(quantite);
        tabPrix[i] = atoi(prix);
        printf("\t%s %d %d\n", &tabId[i], tabQuantite[i], tabPrix[i]);
        i++;
    }   
    fclose(f);

    for(int j=0; j<(sizeof(tabQuantite)/sizeof(int)); j++)
        prixFinal += (tabQuantite[j] * tabPrix[j]); 
    
    return prixFinal;
}

int main(int argc, char **argv) {
	

    int prix;
    char cheminFichier[100];
    strcpy(cheminFichier, "db/orders.txt");
    prix=calculerPrixCmd(cheminFichier);
    printf("PRIX TOTAL : %d\n", prix);

    return 0;	
}