#include "standard.h"

/**
 * @brief requête sous forme de structure des
 * @params noReq  numéro de la requête
 * @params action description de la tâche attribuée à la requête
 * @params params liste d'arguments supplémentaires pour la requête
 */
typedef struct {
    short noReq;
    action_t action;
    message_t params;
} requete_t;