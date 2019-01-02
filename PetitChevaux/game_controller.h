#ifndef GAME_C_H
#define GAME_C_H

int lancerDe();
void changerJoueur();
void sortirCheval(joueur *joueur);
void avancerCheval(int *val);
void mangerCheval();
void verifValeur(plateau *plateau, int *val);
void verifVictoire(int *nbJoueurs, joueur *joueur);

#endif