#ifndef GAME_C_H
#define GAME_C_H

int lancerDe();
void changerJoueur();
void sortirCheval();
void avancerCheval(int *val);
void mangerCheval();
void verifValeur(int *val);
void verifVictoire(int *nbJoueurs, joueur *joueur);

#endif