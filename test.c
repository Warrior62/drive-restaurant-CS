#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.c"



int main(int argc, char **argv) {
	
    affichageProduits();
    int prix;
    prix=calculerPrixCmd();
    printf("PRIX TOTAL : %d\n", prix);
    printf("***************************************\n");
    return 0;	
}