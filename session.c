#include "./lib/standard.h"
#include "./lib/session.h"

/**
 * @fn      int creerSocketEcoute(int se, struct sockaddr_in seAdr);  
 * @brief   crée une socket à l'écoute de requête(s) client(s)
 * @param   seAdr structure d'adressage de la socket d'écoute à créer
 * @note    associe aussi la socket d'écoute se à la structure d'adressage seAdr
 * @return  le numéro de la socket d'écoute créée
 */ 
int creerSocketEcoute(struct sockaddr_in seAdr)
{
    int se;

	CHECK(se = socket(PF_INET, SOCK_STREAM, 0),"-- PB : socket()");
	printf("[SERVER]:Création de la socket d'écoute [%d]\n", se);
	// Préparation d’un adressage pour une socket INET
	seAdr.sin_family = PF_INET;
	seAdr.sin_port = htons(ADDR_SRV);				// htons() : network order	
	seAdr.sin_addr.s_addr = inet_addr(ADDR_SRV);	// adresse effective
	memset(&(seAdr.sin_zero), 0, 8);
	// Association de la socket d'écoute avec l’adresse d'écoute
	CHECK(bind(se, (struct sockaddr *)&seAdr, sizeof(seAdr)),"-- PB : bind()");

    return se;
}


/**
 * @fn      int creerSocketAppel(void);  
 * @brief   crée une socket d'appel
 * @note    pas d'association de la socket d'appel avec une structure d'adressage de socket
 * @return  le numéro de la socket d'appel créée
 */ 
int creerSocketAppel(void)
{
    int sad;
	CHECK(sad = socket(PF_INET, SOCK_STREAM, 0),"-- PB : socket()");
	printf("[CLIENT]:Création de la socket d'appel et de dialogue [%d]\n", sad);		
	// Le client n'a pas besoin d'avoir une adresse
	// ICI, Pas de préparation ni d'association
	return sad;
}
