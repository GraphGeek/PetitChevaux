#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "PetitsChevaux.h"

#define Joueur 4

int lancerDe() {
	srand(time(NULL));
	int R = rand() % 7; //Modulo 7 car 6 + 1
	printf("Valeur du lancer : %i\n", R);
}

void afficherPlateau(char matrice_jeu[][42]) {
	int x, y;
	//Affichage de la matrice caractère par caractère et coloration (Il faudra en faire une fonction)
	printf(COLOR_YELLOW "JOUEUR 1" COLOR_WHITE "     (4) CHEVAUX (4)     " COLOR_CYAN "JOUEUR 2" RESET);
	printf("\n");
	printf("\n");
	for (x = 0; x < 16 + 1; x++) {
		for (y = 0; y < 41; y++) {
			//Couleur de fond des écuries
			if (x >= 0 && x < 7 && y >= 0 && y < 16) {
				printf(COLOR_YELLOW BG_YELLOW "%c" RESET, matrice_jeu[x][y]);
			}
			else if (x >= 0 && x < 7 && y >= 25 && y < 41) {
				printf(COLOR_CYAN BG_CYAN "%c" RESET, matrice_jeu[x][y]);
			}
			else if (x >= 10 && x < 17 && y >= 0 && y < 16) {
				printf(COLOR_GREEN BG_GREEN "%c" RESET, matrice_jeu[x][y]);
			}
			else if (x >= 10 && x < 17 && y >= 25 && y < 41) {
				printf(COLOR_RED BG_RED "%c" RESET, matrice_jeu[x][y]);
			}
			//Couleur de fond de la croix centrale
			else if ((x >= 2 && x <= 7) && (y >= 19 && y <= 21)) {
				printf(BG_CYAN BRIGHT "%c" RESET, matrice_jeu[x][y]);
			}
			else if ((x >= 9 && x <= 14) && (y >= 19 && y <= 21)) {
				printf(BG_GREEN BRIGHT "%c" RESET, matrice_jeu[x][y]);
			}
			else if ((x == 8) && (y >= 1 && y <= 18)) {
				printf(BG_YELLOW BRIGHT "%c" RESET, matrice_jeu[x][y]);
			}
			else if ((x == 8) && (y >= 22 && y <= 39)) {
				printf(BG_RED BRIGHT "%c" RESET, matrice_jeu[x][y]);
			}
			//Couleur des chemins
			else if (((x >= 1 && x <= 7) && (y >= 22 && y <= 24)) || ((x == 7) && (y >= 25 && y <= 40)) || (x == 1 && y == 20)) {
				printf(COLOR_CYAN "%c" RESET, matrice_jeu[x][y]);
			}
			else if (((x == 9) && (y >= 0 && y <= 17)) || ((x >= 10 && x <= 15) && (y == 17)) || (x == 15 && y == 20)) {
				printf(COLOR_GREEN "%c" RESET, matrice_jeu[x][y]);
			}
			else if (((x == 7) && (y >= 0 && y <= 17)) || ((x >= 1 && x <= 7) && (y == 17)) || (x == 8 && y == 0)) {
				printf(COLOR_YELLOW "%c" RESET, matrice_jeu[x][y]);
			}
			else if (((x >= 9 && x <= 15) && (y >= 22 && y <= 24)) || ((x == 9) && (y >= 25 && y <= 40)) || (x == 8 && y == 40)) {
				printf(COLOR_RED "%c" RESET, matrice_jeu[x][y]);
			}
			//Croisement
			else if ((x == 8) && (y >= 19 && y <= 21)) {
				printf(COLOR_BLACK BG_WHITE "%c" RESET, matrice_jeu[x][y]);
			}
			//Accentuation des cases de départ des écuries
			else if ((x == 1 && y == 23) || (x == 7 && y == 0) || (x == 9 && y == 40) || (x == 15 && y == 17)) {
				printf(BRIGHT "%c" RESET, matrice_jeu[x][y]);
			}
			//Affichage des autres éléments
			else {
				printf("%c", matrice_jeu[x][y]);
			}
		}
		printf("\n");
	}
	printf("\n");
	printf(COLOR_GREEN "JOUEUR 3" COLOR_WHITE "     (4) CHEVAUX (4)     " COLOR_RED "JOUEUR 4" RESET);
	printf("\n");
};

int InitJoueurs() {

}

int main() {
	//Création du plateau sous forme de matrice, les valeurs indiquées autour permettent de connaître la coresspondance
	//des cases du plateau avec leurs coordonnées dans la matrice

	//Tableau[Ligne][Colonne]

	//Cases du plateau			  1 2  3  4  5  6  7  8  9  10 11 12 13 1415
	//Coordonnées matrice  (x)    0 2  5  8  11 14 17 20 23 26 29 32 35 3840   //	y

	char matrice_jeu[17][42] = { {"[][][][][][][][]         [][][][][][][][]"}, //	0
								{"[][][][][][][][] O  O  0 [][][][][][][][]"}, //	1
								{"[][][][][][][][] O [1] O [][][][][][][][]"}, //	2
								{"[][][][][][][][] O [2] O [][][][][][][][]"}, //	3
								{"[][][][][][][][] O [3] O [][][][][][][][]"}, //	4
								{"[][][][][][][][] O [4] O [][][][][][][][]"}, //	5
								{"[][][][][][][][] O [5] O [][][][][][][][]"}, //	6
								{"0 O  O  O  O  O  O [6] O  O  O  O  O  O O"}, //	7
								{"O[1][2][3][4][5][6][X][6][5][4][3][2][1]O"}, //	8
								{"O O  O  O  O  O  O [6] O  O  O  O  O  O 0"}, //	9
								{"[][][][][][][][] O [2] O [][][][][][][][]"}, //	10
								{"[][][][][][][][] O [3] O [][][][][][][][]"}, //	11
								{"[][][][][][][][] O [4] O [][][][][][][][]"}, //	12
								{"[][][][][][][][] O [5] O [][][][][][][][]"}, //	13
								{"[][][][][][][][] O [1] O [][][][][][][][]"}, //	14
								{"[][][][][][][][] 0  O  O [][][][][][][][]"}, //	15
								{"[][][][][][][][]         [][][][][][][][]"}  //	16
	};

	//On sauvegarde une copie du plateau, cela sera utile lorsqu'on voudra effectuer des modifications
	char copie_matrice = matrice_jeu;

	afficherPlateau(matrice_jeu);

	int verif[Joueur] = {0,0,0,0};
	char couleur_[Joueur] ; 
	char couleur[Joueur] = {'J','B','V','R'};
	char pseudo[Joueur][15];
	char col; 

	for (int i = 0; i < Joueur; i++) {
		int j = 0; 
		do {
			if (verif[0] == 0) {
				printf(COLOR_YELLOW "Jaune (J)\n" RESET);
			}
			if (verif[1] == 0) {
				printf(COLOR_CYAN "Bleu (B)\n" RESET);
			}
			if (verif[2] == 0) {
				printf(COLOR_GREEN "Vert (V)\n" RESET);
			}
			if (verif[3] == 0) {
				printf(COLOR_RED "Rouge (R)\n" RESET);
			}
			printf("i:%d", i); 
			printf("\nJoueur %d quelle couleur voulez vous ? ", i + 1);
			scanf("%c", &col); getchar();
			printf("\n");
			while ((j < Joueur) && (couleur[j] != col)) j++;


			if ( j >= Joueur || verif[j] == 1) {
				printf("Cette couleur n'est pas disponible\n\n");
				/*couleur_[i] = col;
				verif[j] = 1;
				res = true;*/
			}
			else
				verif[j] = 1; 
			/*if (couleur[i] == 'J') {
				verif[0] = 1;
			}
			if (couleur[i] == 'B') {
				verif[1] = 1;
			}
			if (couleur[i] == 'V') {
				verif[2] = 1;
			}
			if (couleur[i] == 'R') {
				verif[3] = 1;
			}*/
			/*if (couleur[i] != 'J' && couleur[i] != 'B' && couleur[i] != 'V' && couleur[i] != 'R') {
				printf("Cette couleur n'est pas disponible\n\n");
			}
			printf("Comment vous appelez-vous ? ");
			scanf("%s", &pseudo[i]); getchar();
			printf("\nVous avez choisi %s\n\n", pseudo[i]);*/
		} while (verif[j] != 0);//while (couleur[i] != 'J' && couleur[i] != 'B' && couleur[i] != 'V' && couleur[i] != 'R');
		couleur_[i] = col;
		//verif[j] = 1;
	}
}