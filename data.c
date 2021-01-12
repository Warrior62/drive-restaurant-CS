#include "./lib/data.h"


char * req2str (const requete_t *req, message_t msg) {
    // serialization d'une requête (structure) sous forme d'une chaîne de caractères
    // c-à-d une suite d'octets
    memset(msg, 0, MAX_BUFF);
    sprintf(msg,"%hd:%s:%s", req->noReq, req->action, req->params);
    return msg;
}
