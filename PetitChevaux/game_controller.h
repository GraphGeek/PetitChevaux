#ifndef GAME_C_H
#define GAME_C_H

int lancerDe();

//int demanderDeplacement(int *i, int *val);

void demanderDeplacement(plateau *plateau, joueur * joueur, int *indJoueur, int *i, int *val, int *couleur, bool *tmp);

void changerJoueur(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur);
void sortirCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur);
void avancerCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *val, int *indJoueur);
void mangerCheval(plateau *plateau, joueur *joueur, int *indJoueur, int *indCheval, int *coulCheval, int *i, int *val);
void verifVictoire(int *nbJoueurs, joueur *joueur);
void afficherTour(joueur *joueur, int *indJoueur);
void afficherValeuDe(joueur *joueur, int *indJoueur, int *val);

/* DEBUG */
void debugPlateau(plateau *plateau);

#endif