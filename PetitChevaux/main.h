#ifndef PETIT_CHEVAUX_H
#define PETIT_CHEVAUX_H

//Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define RESET			"\x1b[0m" //Réinitialise la mise en forme

//Mises en forme
#define BRIGHT			"\x1b[1m" //Gras
#define DIM				"\x1b[2m" //Normal
#define UNDERSCORE		"\x1b[4m" //Souligné
#define BLINK			"\x1b[5m" //Clignotant
#define REVERSE			"\x1b[7m" //Couleur inversée
#define HIDDEN			"\x1b[8m" //Caché

//Couleurs
#define COLOR_BLACK		"\x1b[30m"
#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_YELLOW	"\x1b[33m"
#define COLOR_BLUE		"\x1b[34m"
#define COLOR_MAGENTA	"\x1b[35m"
#define COLOR_CYAN		"\x1b[36m"
#define COLOR_WHITE		"\x1b[37m"

//Couleurs de fond
#define BG_BLACK		"\x1b[40m"
#define BG_RED			"\x1b[41m"
#define BG_GREEN		"\x1b[42m"
#define BG_YELLOW		"\x1b[43m"
#define BG_BLUE			"\x1b[44m"
#define BG_MAGENTA		"\x1b[45m"
#define BG_CYAN			"\x1b[46m"
#define BG_WHITE		"\x1b[47m"

//Emoji Cheval
#define CHEVAL			"\u265E"

#define ENTER			"\n"

typedef enum {BLEU, ROUGE, VERT, JAUNE} couleur;

typedef struct {
	bool etat; //0 = Dans l'écurie | 1 = Sur le plateau
	couleur couleur;
	int pos; //Position du cheval sur un chemin (0 à 55) | -1 = Pas sur le chemin
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

void effacerEcran();
void afficherTitre();
void initJeu();
void tour(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur);

#endif