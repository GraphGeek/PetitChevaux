#ifndef GAME_C_H
#define GAME_C_H

int lancerDe();

//int demanderDeplacement(int *i, int *val);

void demanderDeplacement(plateau *plateau, int *nbJoueurs, joueur * joueur, int *indJoueur, int *i, int *val, int *couleur, bool *tmp);
void changerJoueur(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur);
int indiceCheval(joueur *joueur, int *numJoueur);
int indiceChevalJoueurEnCours(joueur *joueur, int *indJoueur);
int couleurCheval(plateau *plateau);
void sortirCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur);
void avancerCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *val, int *indJoueur);
void effectuerManger(plateau *plateau, joueur *joueur, int *indJoueur, int *indCheval, int *coulCheval, int *caseArrivee, int *numJoueur);
void mangerCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur, int *indCheval, int *coulCheval, int *caseArrivee);
void verifVictoire(int *nbJoueurs, joueur *joueur);
void afficherTour(joueur *joueur, int *indJoueur);
void afficherValeuDe(joueur *joueur, int *indJoueur, int *val);
void affichPlateau(plateau *plateau);

int identifierJoueur(joueur *joueur, int *indJoueur, int *coulCheval);

/* DEBUG */
void debugPlateau(plateau *plateau);

#endif