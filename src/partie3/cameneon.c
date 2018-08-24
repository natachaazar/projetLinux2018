#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "types.h"

const char* getCouleur(couleur coul){
    switch(coul){
        case Bleu: return "Bleu";
        case Jaune: return "Jaune";
        case Rouge: return "Rouge";
    }
}
int transformerCouleurEnInt(couleur c){
    int couleurInterne;
        if(c==Jaune) couleurInterne=0;
        else if(c==Bleu) couleurInterne=1;
        else couleurInterne=2;

        return couleurInterne;
}
couleur transformerIntEnCouleur(int couleurInterne){
    couleur coul;
        if(couleurInterne==0) coul=Jaune;
        else if(couleurInterne==1) coul=Bleu;
        else coul = Rouge;

        return coul;
}

int couleurComplementaire(int c1, int c2){
    if(c1 == c2){
        return c1;
    }else{
        return (3 - c1 - c2);
    }
}

void mutationCameneon(Cameneon demandeur,Cameneon recepteur){
   //printf("%d je suis %s et je mange du chevre feuille\n",demandeur.cameneon_id,getCouleur(transformerIntEnCouleur(demandeur.maCouleur)));
   //printf("%d je suis %s et je m'entraine\n",demandeur.cameneon_id,getCouleur(transformerIntEnCouleur(demandeur.maCouleur)));
   //printf("je suis %d et ma couleur est %s et je mange du chevre feuille\n",recepteur.cameneon_id,getCouleur(transformerIntEnCouleur(recepteur.maCouleur)));
   if(demandeur.enAttente==0){
      printf("%d je suis %s et je demande une mutation de %d qui est %s\n",demandeur.cameneon_id,getCouleur(transformerIntEnCouleur(demandeur.maCouleur)),
      recepteur.cameneon_id,getCouleur(transformerIntEnCouleur(recepteur.maCouleur))); 

      if(demandeur.enAttente==0){
      printf("%d je suis transforme en %s car ma  mutation avec %d est termine\n",demandeur.cameneon_id,getCouleur(transformerIntEnCouleur(demandeur.maCouleur)),
      recepteur.cameneon_id); 
   }
   } else{
        printf("%d j'ai deja depose une demande de mutation et j'attends que quelqu'un me demande\n",demandeur.cameneon_id);
   }
}

void Mutation(void *arguments){
   int r = rand() % 20;
    Cameneon demandeur = {};
    Cameneon recepteur = {};
    sscanf((char * ) arguments, "%d - %d - %d - %d - %d - %d",&demandeur.cameneon_id,&demandeur.maCouleur,&demandeur.enAttente,
    &recepteur.cameneon_id,&recepteur.maCouleur,&recepteur.enAttente);
    //while(1){
    for(int i=0;i<20;i++){
        sleep(r);
    
        mutationCameneon(demandeur,recepteur);
    }

}

int main(void){
    couleur couleurs[NB_CAMENEON]={Jaune,Bleu,Rouge,Bleu};
    Cameneon cameneons[NB_CAMENEON];
    pthread_t threads[20];
    char arguments[255][20];
    
    for(int j=0;j<NB_CAMENEON;j++){
        int index=j+1;
    
        while(index<NB_CAMENEON){
            sprintf(arguments[j],"%d - %d - %d - %d - %d - %d",j,transformerCouleurEnInt(couleurs[j]),0,index,transformerCouleurEnInt(couleurs[index]),0);
            sprintf(arguments[j+NB_CAMENEON],"%d - %d - %d - %d - %d - %d",index,transformerCouleurEnInt(couleurs[index]),0,j,transformerCouleurEnInt(couleurs[j]),0);
            pthread_create(&threads[j],NULL,(void *(*)())Mutation,&arguments[j]);
            pthread_create(&threads[j+NB_CAMENEON],NULL,(void *(*)())Mutation,&arguments[j+NB_CAMENEON]);
            index = index+1;
        } 
    }
    for(int i=0;i<NB_CAMENEON;i++){
        pthread_join(threads[i],NULL);
        pthread_join(threads[i+NB_CAMENEON],NULL);
    }
    return 0;
}