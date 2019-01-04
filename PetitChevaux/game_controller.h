#ifndef GAME_C_H
#define GAME_C_H

int lancerDe();
int demanderDeplacement(int *indJoueur);

void changerJoueur(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur);
void sortirCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur);
void avancerCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *val, int *indJoueur);
void mangerCheval();
void verifVictoire(int *nbJoueurs, joueur *joueur);
void afficherTour(joueur *joueur, int *indJoueur);
void afficherValeuDe(joueur *joueur, int *indJoueur, int *val);

/* DEBUG */
void debugPlateau(plateau *plateau);

#endif