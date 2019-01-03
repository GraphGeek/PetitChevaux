#ifndef GAME_C_H
#define GAME_C_H

int lancerDe();
void changerJoueur();
void sortirCheval(plateau *plateau, joueur *joueur);
void avancerCheval(plateau *plateau, joueur *joueur, int *val);
void mangerCheval();
void verifValeur(plateau *plateau, joueur *joueur, int *val);
void verifVictoire(int *nbJoueurs, joueur *joueur);

#endif