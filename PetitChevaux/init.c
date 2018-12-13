//Ce fichier contient toutes les fonctions d'initialisation du jeu
#include "header.h"

void initJeu() {
	int nbJoueurs = 4;
	joueur joueur[4];
	printf(BRIGHT "|LE JEU DES PETITS CHEVAUX|\n" RESET);
	//initPlateau();
	/////////////////////////////////////////////////////////
	//En attendant de faire passer la matrice par la fonction
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
	/////////////////////////////////////////////////////////
	initJoueurs(&nbJoueurs, &joueur);
	afficherPlateau(matrice_jeu, &joueur);
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
	//A voir pour retourner une matrice (malloc)
}

void initJoueurs(int *nbJoueurs, joueur *joueur) {
	int couleur_num = 0;
	int verif[] = { 0,0,0,0 };
	/*
	Pour le moment le nombre de joueur est forcément 4
	do
	{
		printf("Nombre de Joueur pour la Partie (1 a 4 joueurs) : ");
		scanf("%d", nbJoueurs);
		if ((*nbJoueurs < 0) || (*nbJoueurs > 4)) {
			printf("Veuillez choisir un nombre de joueurs compris entre 1 et 4 !\n");
		}
	} while ((*nbJoueurs < 0) || (*nbJoueurs > 4));
	*/
	for (int i = 0; i < *nbJoueurs; i++) {
		//Enregistrement du pseudo
		printf("\n");

		printf("Joueur %d, choisissez un pseudo : ", i + 1);
		scanf("%s", joueur[i].pseudo);
		joueur[i].num = i + 1;

		printf("\n");

		//Enregistrement des couleurs
		do {
			if (verif[0] == 0) {
				printf(COLOR_CYAN "BLEU (1) " RESET);
			}
			if (verif[1] == 0) {
				printf(COLOR_RED "ROUGE (2) " RESET);
			}
			if (verif[2] == 0) {
				printf(COLOR_GREEN "VERT (3) " RESET);
			}
			if (verif[3] == 0) {
				printf(COLOR_YELLOW "JAUNE (4)" RESET);
			}

			printf("\n\n");

			printf("%s, quelle couleur voulez-vous : ", joueur[i].pseudo);
			scanf("%d", &couleur_num);
			
			if (verif[couleur_num - 1] == 1)
			{
				printf("\nErreur : Cette couleur est deja utilisee !\n\n");
			}

			if ((couleur_num < 0) || (couleur_num > 4)) {
				printf("\nErreur : Cette couleur n'existe pas !\n\n");
			}

		} while ((verif[couleur_num - 1] != 0) || ((couleur_num < 0) || (couleur_num > 4)));
		//On verrouille la couleur saisie
		verif[couleur_num - 1] = 1;
		//On attribue la couleur au joueur
		joueur[i].couleur = couleur_num - 1;

		//On attribue les chevaux au joueur
		joueur[i].nb_chevaux = 4;
	}

	//On teste
	for (int i = 0; i < 4; i++) {
		printf("Joueur %d | NumJoueur %d | Pseudo : %s | Couleur : %d | Nombre de chevaux : %d\n", i + 1, joueur[i].num, joueur[i].pseudo, joueur[i].couleur, joueur[i].nb_chevaux);
	}
}