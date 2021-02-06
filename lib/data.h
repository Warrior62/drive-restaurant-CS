/******************************************************************/
/*                           INCLUDE                              */
/******************************************************************/
#include "repReq.h"


/******************************************************************/
/*                           TYPEDEF                              */
/******************************************************************/
/**
 * @brief structure passée en paramètre de pthread_create pour renseigner l'adresse et le port du client
 */
typedef struct{
    char * addr;
    int port;
}param_thread_t;


/******************************************************************/
/*                           FONCTIONS                            */
/******************************************************************/
/**
 * @fn      void affichageProduits(); 
 * @brief   lis le fichier db/products.txt et affiche son contenu
 * @note    affiche les produits qui peuvent être commandés par le client
 */ 
void affichageProduits();

/**
 * @fn      int calculerPrixCmd(char *orderFilePath)
 * @brief   calcule le prix total de la commande dont le fichier associé est passé en paramètre
 * @param   orderFilePath   chemin du fichier associé à la commande
 * @return  prix total de la commande
 */
int calculerPrixCmd(char *orderFilePath);

/**
 * @fn  void creerFichierCmd(requete_t reqPrixCmd)
 * @brief créer le fichier de commande et le remplir avec les produits commandés
 * @param reqPrixCmd requête envoyée par le client pour passer sa commande
 * @param newFileName nom du fichier à créer
 * @note le nom du fichier de commande créé correspond au numéro de commande.txt
 */ 
void creerFichierCmd(requete_t, char *);

/**
 * @fn requete_t str2req(char * str)
 * @brief convertit une chaîne de caractère contenant la requête en une requête
 * @param str chaîne à convertir
 * @return une requête de type requete_t
 */ 
requete_t str2req(char * str);

/**
 * @fn reponse_t str2rep(char * str)
 * @brief convertit une chaîne de caractère contenant la réponse en une réponse
 * @param str chaîne à convertir
 * @return une réponse de type reponse_t
 */ 
reponse_t str2rep(char * str);

/**
 * @fn char * req2str(const requete_t *, message_t)
 * @brief convertit une requête en une chaîne de caractère 
 * @param requete_t requête à convertir
 * @param message_t message à transmettre au travers de la requête
 * @return une chaîne de caractère
 */ 
char * req2str(const requete_t *, message_t);

/**
 * @fn char * rep2str(const reponse_t *, message_t)
 * @brief convertit une réponse en une chaîne de caractère 
 * @param reponse_t réponse à convertir
 * @param message_t message à transmettre au travers de la réponse
 * @return une chaîne de caractère
 */ 
char * rep2str(const reponse_t *, message_t );

/**
 * @fn void clientServeur(param_thread_t *)
 * @brief crée un thread client faisant office de serveur pour être appelé 
 * @param param_thread_t datas à passer en argument de pthread_create()
 */ 
void clientServeur(param_thread_t *);

/**
 * @fn void clientServeur(param_thread_t *)
 * @brief crée un thread client faisant office de serveur pour être appelé 
 * @param param_thread_t datas à passer en argument de pthread_create()
 */ 
void deroute(int signal_number);

/**
 * @brief structure contenant les informations d'un produit commandé par le client
 */
typedef struct {
    int id;
    char * nom;
    int prixUnit;
} produit_t;

