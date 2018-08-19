#include <semaphore.h>
#include "types.h"

sem_t seulement_deux;
sem_t mutex;
sem_t semPrivee;

int premierAppel = 1;
couleur couleurA;
couleur couleurB;

couleur mutation(cameneon_id id, couleur c){
    couleur resultat;
    int valeur;

    sem_wait(&seulement_deux);
    sem_wait(&mutex);

    if(premierAppel){
        couleurA = c;
        premierAppel = 0;
        sem_post(&mutex);
        sem_wait(&semPrivee);

        resultat = couleurB;
        sem_post(&mutex);
        sem_post(&seulement_deux);
        sem_post(&seulement_deux);
    }
    else{
        premierAppel = 1;
        couleurB = c;
        resultat = couleurA;
        sem_post(&semPrivee);
    }
    return resultat;
}

void initMutation(void){
    sem_init(&seulement_deux,0,2);
    sem_init(&mutex,0,1);
    sem_init(&semPrivee,0,0);

}