#include <stdio.h>
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
   printf("je suisDDDDDDDD %d et ma couleur est %s et je mange du chevre feuille\n",demandeur.cameneon_id,getCouleur(demandeur.maCouleur));
   printf("je suisRRRRRRRR %d et ma couleur est %s et je mange du chevre feuille\n",recepteur.cameneon_id,getCouleur(recepteur.maCouleur));
}

void Mutation(Cameneon *args){
    Cameneon demandeur=args[0];
    Cameneon recepteur=args[1];
    //Random random = new Random();
    //int sec = random.Next(3,10)*1000;
    while(1){
        //System.Threading.Thread.Sleep(sec);
        mutationCameneon(demandeur,recepteur);
    }

}

int main(void){
    couleur couleurs[NB_CAMENEON]={Jaune,Bleu,Rouge,Bleu};
    Cameneon cameneons[NB_CAMENEON];
    pthread_t threads[20];
    int i;

    for(int i=0;i<NB_CAMENEON;i++){
        cameneons[i]=new Cameneon();
        cameneons[i].cameneon_id=i;
        cameneons[i].maCouleur = transformerCouleurEnInt(couleurs[i]);
    }
    for(int j=0;i<NB_CAMENEON;j++){
        int index=j+1;
        Cameneon arguments[2];
        Cameneon arguments2[2];
        while(index<NB_CAMENEON){
            arguments[0]=cameneons[j];
            arguments[1]=cameneons[index];
            arguments2[0]=arguments[1];
            arguments2[1]=arguments[0];
            pthread_create(&threads[j],Mutation,&arguments);
            pthread_create(&threads[j+NB_CAMENEON],Mutation,&arguments2);
        } 
    }
    for(int i=0;i<NB_CAMENEON;i++){
        pthread_join(threads[i],NULL);
        pthread_join(threads[i+NB_CAMENEON],NULL);
    }
    return 0;
}