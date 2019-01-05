#ifndef PETIT_CHEVAUX_H
#define PETIT_CHEVAUX_H

//Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

//Mises en forme

#define RESET			"\x1b[0m" //Réinitialise la mise en forme

#define BRIGHT			"\x1b[1m"

//Couleurs
#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_YELLOW	"\x1b[33m"
#define COLOR_CYAN		"\x1b[36m"

//Couleurs de fond
#define BG_RED			"\x1b[41m"
#define BG_GREEN		"\x1b[42m"
#define BG_YELLOW		"\x1b[43m"
#define BG_CYAN			"\x1b[46m"

//Emoji Cheval
#define CHEVAL			"\u265E"

#define ENTER			"\n"

//Structures

typedef enum {BLEU, ROUGE, VERT, JAUNE} couleur;

typedef struct {
	bool etat; //0 = Dans l'écurie | 1 = Sur le plateau
	couleur couleur;
} cheval;

typedef struct {
	char pseudo[15];
	int num;
	couleur couleur;
	int nbChevaux;
	cheval cheval[4];
	bool cheminFinal[6];
	bool victoire;
	bool statutJeu; //0 = Pas de chevaux sortis | 1 = Au moins un cheval en jeu
} joueur;

typedef struct {
	int bleu[55];
	int rouge[55];
	int vert[55];
	int jaune[55];
} chemin;

typedef struct {
	int plateau[15][15];
	chemin chemin;
} plateau;

typedef struct {
	int x;
	int y;
} cellule;

//Fonctions

void effacerEcran();
void afficherTitre();
void viderBuffer();
void enterToContinue();
void initJeu();
void tour(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur);

#endif