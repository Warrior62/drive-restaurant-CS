#include "standard.h"

/******************************************************************/
/*                           FONCTIONS REQUETES                   */
/******************************************************************/
void passerCmd(){}
void demanderPaiementCmd(){}
void demanderCmd(){}


/******************************************************************/
/*                           FONCTIONS REPONSES                   */
/******************************************************************/
void annoncerPrixCmd(){}
void effectuerPaiementCmd(){}
void verifierPaiementCmd(){}
void donnerCmd(){}


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
    short typeRep;
    message_t result;
} reponse_t;