#include <stdio.h>
#include <pthread.h>
#include "agora.c"

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

void CameneonVie(void *arguments){
    cameneon_id id;
    couleur maCouleur, couleurAncienne,autreCouleur;
    int maCouleurInterne;

    sscanf((char * ) arguments, "%d - %d",&id,&maCouleurInterne);
    maCouleur=transformerIntEnCouleur(maCouleurInterne);

    while(1){
        printf("je suis %d et ma couleur est %s et je mange du chevre feuille\n",id,getCouleur(maCouleur));
        printf("je suis %d et ma couleur est %s et je m'entraine\n",id,getCouleur(maCouleur));
        printf("je suis %d et ma couleur est %s et je vais pour une mutation vers agora\n",id,getCouleur(maCouleur));
        autreCouleur = mutation(id,maCouleur);
        couleurAncienne = maCouleur;
        maCouleur = transformerIntEnCouleur(couleurComplementaire(transformerCouleurEnInt(maCouleur),
        transformerCouleurEnInt(autreCouleur)));
        printf("je suis %d et ma couleur est %s et ma mutation est terminee\n",id,getCouleur(maCouleur));
    }

}

int main(void){
    couleur couleurs[NB_CAMENEON]={Jaune,Bleu,Rouge,Bleu};
    char arguments[255][NB_CAMENEON];
    pthread_t threads[NB_CAMENEON];
    int i;

    initMutation();
    for(int i=0;i<NB_CAMENEON;i++){
        sprintf(arguments[i],"%d - %d",i,transformerCouleurEnInt(couleurs[i]));
        pthread_create(&threads[i],NULL,(void *(*)())CameneonVie,arguments[i]);
    }
    for(int i=0;i<NB_CAMENEON;i++){
        pthread_join(threads[i],NULL);
    }
    return 0;
}