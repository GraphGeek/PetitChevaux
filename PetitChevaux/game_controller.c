//Ce fichier contient toutes les fonctions utiles lors d'un tour de jeu
#include <stdbool.h>
#include "main.h"
#include "game_controller.h"

bool victoire;

int lancerDe() {
	int r = 0;
	do { 
		r = rand() % 7; //Modulo 7 car 6 + 1
	} while (r == 0);
	return r;
}

void afficherPlateau(char matrice_jeu[][42], joueur *joueur) {
	int x, y;
	//Affichage de la matrice caractère par caractère et coloration
	printf(COLOR_YELLOW "JOUEUR 1" "     (%d)" COLOR_WHITE " CHEVAUX " COLOR_CYAN "(%d)     " "JOUEUR 2" RESET, joueur[0].nbChevaux, joueur[1].nbChevaux);
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
	printf(COLOR_GREEN "JOUEUR 3" "     (%d)" COLOR_WHITE " CHEVAUX " COLOR_RED "(%d)     " "JOUEUR 4" RESET, joueur[2].nbChevaux, joueur[3].nbChevaux);
	printf("\n");
};

void changerJoueur() {
	printf("Joueur suivant\n");
}

void sortirCheval() {
	printf("Cheval sorti, relancez le dé\n");
}

void avancerCheval(int *val){
	printf("Le cheval avance de %d cases\n", val);
}

void mangerCheval(){
	printf("Vous avez mangé le cheval de [Insérer joueur]\n");
}

void verifValeur(int *val){
	int pos; //A définir : Position du prochain cheval adverse
	if(val < pos){
		avancerCheval(val);
		changerJoueur();
	} else if(val == pos){
		mangerCheval();
		avancerCheval(val);
		changerJoueur();
	} else {
		changerJoueur();
	}
}

void tour(joueur *joueur) {
	bool premierTour = true;
	bool premiereCaseLibre = true;
	if(premierTour) {
		printf("Premier tour de jeu\n");
		int val = lancerDe();
		printf("Vous avez obtenu un %d\n", val);
		if(val == 6){
			if(premiereCaseLibre) {
				printf("Vous pouvez sortir un cheval\n");
				sortirCheval();
			} else {
				printf("La première case devant votre écurie est occupée, vous ne pouvez pas sortir de cheval !\n");
				changerJoueur();
			}
		} else {
			printf("Vous n'avez pas fait 6, vous passez votre tour\n");
			changerJoueur();
		}
	} else {
		int val = lancerDe();
		if(val == 6){
			if(joueur->nbChevaux < 4){
				int res;
				do {
					printf("Voulez-vous sortir un cheval ? Oui (1) Non (0)\n");
					scanf("%d", &res);
					if(res != 1 || res != 0){
						printf("Votre saisie n'est pas correcte\n");
					}
				} while (res != 1 || res != 0);
			} else {
				verifValeur(val);
			}
		verifValeur(val);
		}
	}
};
