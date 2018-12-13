#include "PetitsChevaux.h"

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

void initJeu() {
	int nbJoueurs = 0;
	printf(BRIGHT "BIENVENUE DANS LE JEU DES PETITS CHEVAUX\n\n" RESET);
	initPlateau();
	initJoueurs(&nbJoueurs);
}

void initPlateau() {
	//Création du plateau sous forme de matrice, les valeurs indiquées autour permettent de connaître la coresspondance
	//des cases du plateau avec leurs coordonnées dans la matrice

	//Tableau[Ligne][Colonne]

	//Cases du plateau			  1 2  3  4  5  6  7  8  9  10 11 12 13 1415
	//Coordonnées matrice  (x)    0 2  5  8  11 14 17 20 23 26 29 32 35 3840   //	y

	char matrice_jeu[17][42] = {
		{"[][][][][][][][]         [][][][][][][][]"}, //	0
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
	//afficherPlateau(matrice_jeu); //Temporaire -> A voir pour retourner une matrice (malloc)
}

void initJoueurs(int *nbJoueurs) {
	joueur joueur[4];
	int couleur_num = 0;
	int verif[] = { 0,0,0,0 };
	do
	{
		printf("Nombre de Joueur pour la Partie (1 a 4 joueurs) : ");
		scanf("%d", nbJoueurs);
		if ((*nbJoueurs < 0) || (*nbJoueurs > 4)) {
			printf("Veuillez choisir un nombre de joueurs compris entre 1 et 4 !\n");
		}
	} while ((*nbJoueurs < 0) || (*nbJoueurs > 4));
	for (int i = 0; i < *nbJoueurs; i++) {
		//Enregistrement du pseudo
		printf("\nJoueur %d, choisissez un pseudo : ", i + 1);
		scanf("%s", joueur[i].pseudo);
		joueur[i].num = i + 1;

		//Enregistrement des couleurs
		do {
			printf("\n%s, quelle couleur voulez-vous :\n\n", joueur[i].pseudo);
			if (verif[0] == 0) {
				printf(COLOR_CYAN "BLEU (1)\n" RESET);
			}
			if (verif[1] == 0) {
				printf(COLOR_RED "ROUGE (2)\n" RESET);
			}
			if (verif[2] == 0) {
				printf(COLOR_GREEN "VERT (3)\n" RESET);
			}
			if (verif[3] == 0) {
				printf(COLOR_YELLOW "JAUNE (4)\n" RESET);
			}
			scanf("%d", &couleur_num);

			if (verif[couleur_num - 1] == 1)
			{
				printf("\nErreur : Cette couleur est deja utilisee !\n\n");
			}

			if ((couleur_num < 0) || (couleur_num > 4)) {
				printf("\nErreur : Cette couleur n'existe pas !\n\n");
			}

		} while ((verif[couleur_num - 1] != 0) || ((couleur_num < 0) || (couleur_num > 4)));
		//On bloque la couleur
		verif[couleur_num - 1] = 1;
		//On attribue la couleur au joueur
		joueur[i].couleur = couleur_num - 1;
	}
}

int main() {
	initJeu();
}