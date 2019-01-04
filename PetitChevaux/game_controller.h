#ifndef GAME_C_H
#define GAME_C_H

int lancerDe();
void changerJoueur(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur);
void sortirCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur);
int demanderDeplacement(int *indJoueur);
void avancerCheval(plateau *plateau, joueur *joueur, int *val);
void mangerCheval();
void verifValeur(plateau *plateau, int *nbJoueur, joueur *joueur, int *val, int *indJoueur);
void verifVictoire(int *nbJoueurs, joueur *joueur);
void afficherValeuDe(joueur *joueur, int *indJoueur, int *val);

#endif