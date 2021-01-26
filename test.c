#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/repReq.h"

int calculerPrixCmd(char *orderFilePath){
    FILE *fCmd, *fProducts;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fCmd = fopen(orderFilePath, "rt");
    fProducts = fopen("db/products.txt", "rt");
    char id[20], nom[20], prixUnitaire[20], data[100];
    char tabProducts[100][3];
    int i=0, j=0, prixFinal=0, tabCmd[100];
    
    //Stockage du contenu des produits dans un tableau tabProducts
    // while(fscanf(fProducts, "%s %s %s", id, nom, prixUnitaire) != EOF){
    //     tabProducts[i][0] = atoi(id);
    //     strcpy(&tabProducts[i][1], nom);
    //     tabProducts[i][2] = atoi(prixUnitaire);
    //     // printf("\t%d %s %d\n", tabProducts[i][0], &tabProducts[i][1], tabProducts[i][2]);
    //     i++;
    // }   

    // Stockage du contenu de la commande dans un tableau tabCmd
    printf("VOTRE COMMANDE\n");
    //while((read = getline(&line, &len, fCmd)) != -1){
        // tabCmd[j] = atoi(data);
        // printf("\t%d\n", tabCmd[j]);
        read = getline(&line, &len, fCmd);
        //char * strToken = strtok(line, " ");
        printf("//%s//", line);
      //  j++;
      
    //}

    // Calcul du prix de la commande
    // for(int k=0; k<j; k++)
    //     for(int l=0; l<i; l++)
    //         if(tabProducts[l][0] == tabCmd[k])
    //              prixFinal += tabProducts[l][2];
       
    // Fermeture des 2 fichiers
    fclose(fProducts);
    fclose(fCmd);

    return prixFinal;
}
int main(int argc, char **argv) {
	int test = calculerPrixCmd("db/orders.txt");
    printf("-->%d", test);
    return 0;	
}