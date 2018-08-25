#define NB_CAMENEON 4
typedef int cameneon_id;
typedef enum {Bleu, Rouge, Jaune} couleur;
typedef struct strucure1{
    int cameneon_id;
    int maCouleur,autreCouleur;
    int enAttente;
    pthread_mutex_t lock;
    } Cameneon;