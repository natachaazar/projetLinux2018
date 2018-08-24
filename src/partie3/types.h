#define NB_CAMENEON 4
typedef int cameneon_id;
typedef enum {Bleu, Rouge, Jaune} couleur;
typedef struct {
    int cameneon_id;
    int maCouleur,autreCouleur;
    int enAttente;
    } Cameneon;