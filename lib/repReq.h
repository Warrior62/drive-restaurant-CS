#include "standard.h"

pthread_mutex_t mutexEcran;
pthread_mutex_t mutexClientPay;
/******************************************************************/
/*                           STRUCTURES                           */
/******************************************************************/
/**
 * @brief requête sous forme de structure
 * @param noReq  numéro de la commande
 * @param action code de la tâche attribuée à la requête
 * @param params liste des données à transmettre par la requête
 * @note  1 : passer la commande
 *        2 : demander le paiement de la commande
 *        3 : payer la commande
 *        4 : recevoir la commande
 */
typedef struct {
    short noReq;
    action_t action;
    message_t params;
} requete_t;


/**
 * @brief réponse sous forme de structure 
 * @param typeRep  numéro de la commande
 * @param result   message à envoyer au client
 * @note  1 : annoncer prix de la commande
 *        2 : effectuer le paiement de la commande
 *        3 : vérifier paiement de la commande
 *        4 : donner la commande
 */
typedef struct {
    short noCommande;
    message_t result;
} reponse_t;


/******************************************************************/
/*                           FONCTIONS REQUETES                   */
/******************************************************************/
/**
 * @fn reponse_t passerCmd(int sad)
 * @brief permet au client de donner les produits qu'il veut commander
 * @param sad socket de d'appel et de dialogue
 * @return une réponse reçue après annonce du prix de la commande
 */ 
reponse_t passerCmd(int sad);
// void demanderPaiementCmd();
reponse_t demanderCmd(int,int);


/******************************************************************/
/*                           FONCTIONS REPONSES                   */
/******************************************************************/
/**
 * @fn void annoncerPrixCmd(int sd, requete_t req)
 * @brief annonce au client le prix de sa commande
 * @param sd socket de dialogue
 * @param req requête au travers de laquelle le passage de commande s'est produit
 */ 
void annoncerPrixCmd(int sd, requete_t req);

/**
 * @fn reponse_t effectuerPaiementCmd(int, int, int)
 * @brief permet au client de payer sa commande
 * @param numCom numéro de la commande à payer
 * @param prix prix de la commande à payer
 * @param sad socket d'appel et de dialogue
 */ 
reponse_t effectuerPaiementCmd(int, int, int);
void verifierPaiementCmd(int , requete_t );
void donnerCmd();