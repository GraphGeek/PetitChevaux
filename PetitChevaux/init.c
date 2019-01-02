//Ce fichier contient toutes les fonctions d'initialisation du jeu
#include "main.h"
#include "init.h"

void initJeu() {
	int nbJoueurs = 4;
	joueur joueur[4];
	printf(BRIGHT "|" CHEVAL " LE JEU DES PETITS CHEVAUX |\n" RESET);
	//initPlateau();
	//initJoueurs(&nbJoueurs, joueur);
	tour(joueur);
}

void initPlateau() {
	plateau plateau;
	int x, y;
	//Initialisation à zéro
	for(x = 0; x < 15; x++){
		for(y = 0; y < 15; y++){
			plateau.plateau[x][y] = 0;
		}
	}
	for(x = 0; x < 55; x++){
		plateau.chemin.bleu[x] = 0;
		plateau.chemin.rouge[x] = 0;
		plateau.chemin.vert[x] = 0;
		plateau.chemin.jaune[x] = 0;
	}
	//Affichage
	for(x = 0; x < 15; x++){
		for(y = 0; y < 15; y++){
			printf("%d", plateau.plateau[x][y]);			
		}
		printf("\n");
	}
	for(x = 0; x < 55; x++){
		printf(COLOR_CYAN "%d" RESET, plateau.chemin.bleu[x]);
	}
	printf("\n");
	for(x = 0; x < 55; x++){
		printf(COLOR_RED "%d" RESET, plateau.chemin.rouge[x]);
	}
	printf("\n");
	for(x = 0; x < 55; x++){
		printf(COLOR_GREEN "%d" RESET, plateau.chemin.vert[x]);
	}
	printf("\n");
	for(x = 0; x < 55; x++){
		printf(COLOR_YELLOW "%d" RESET, plateau.chemin.jaune[x]);
	}
	printf("\n");
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
		joueur[i].nbChevaux = 4;
		for(int j = 0; j < 4; j++){
			joueur[i].cheval[j].etat = 1;
			joueur[i].cheval[j].couleur = couleur_num - 1;
		}
	}
}