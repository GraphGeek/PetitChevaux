//Ce fichier contient toutes les fonctions utiles lors d'un tour de jeu
#include "main.h"
#include "game_controller.h"

int lancerDe() {
	srand(time(NULL));
	int R = rand() % 7; //Modulo 7 car 6 + 1
	printf("Valeur du lancer : %i\n", R);
}

void afficherPlateau(char matrice_jeu[][42], joueur *joueur) {
	int x, y;
	//Affichage de la matrice caractère par caractère et coloration
	printf(COLOR_YELLOW "JOUEUR 1" "     (%d)" COLOR_WHITE " CHEVAUX " COLOR_CYAN "(%d)     " "JOUEUR 2" RESET, joueur[0].nb_chevaux, joueur[1].nb_chevaux);
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
	printf(COLOR_GREEN "JOUEUR 3" "     (%d)" COLOR_WHITE " CHEVAUX " COLOR_RED "(%d)     " "JOUEUR 4" RESET, joueur[2].nb_chevaux, joueur[3].nb_chevaux);
	printf("\n");
};