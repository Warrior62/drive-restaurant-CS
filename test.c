#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/repReq.h"

char *numToASCII(int num) {
    /*
     * Use malloc to allocate an array in the heap, instead of using a
     * local array. The memory space of local array will be freed after
     * the invocation of numToASCII.
     */
    char *string = malloc(2);
    if (!string)
            return 0;
    string[0] = num;
    string[1] = 0;
    return string;
}

int calculerPrixCmd(char *orderFilePath){
    FILE *fCmd, *fProducts;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fCmd = fopen(orderFilePath, "rt");
    fProducts = fopen("db/products.txt", "rt");
    char id[20], nom[20], prixUnitaire[20], data[100];
    char tabProducts[100][3];
    int i=0, j=0, cpt=0, prixFinal=0, tabCmd[100];
    
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
    read = getline(&line, &len, fCmd);
    printf("len=%ld\n", len);
    while(read != -1){
        if(line[j] != 32){
            // tabCmd[j] = atoi((char *)line[j]);
            printf("-%s-", numToASCII(line[j]));
            cpt=0;
        }
        else cpt++;
        if(cpt >= 2) break;
        j++;
    }
    
        // read = getline(&line, &len, fCmd);
        //char * strToken = strtok(line, " ");
        // printf("//%d//", line[2]);
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