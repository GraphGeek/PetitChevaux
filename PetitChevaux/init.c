//Ce fichier contient toutes les fonctions d'initialisation du jeu
#include "main.h"
#include "init.h"

void initJeu() {
	effacerEcran();
	int nbJoueurs = 4;
	joueur joueur[nbJoueurs]; //On initialise un tableau de structure de type joueur pour les 4 joueurs
	plateau plateau; //On initialise un plateau de type plateau
	initPlateau(&plateau);
	initJoueurs(&nbJoueurs, joueur);
	int indJoueur = premierJoueur();
	effacerEcran();
	afficherTitre();
	printf("\n%s commence la partie !\n", joueur[indJoueur].pseudo);
	tour(&plateau, &nbJoueurs, joueur, &indJoueur);
}

int premierJoueur() {
	return(rand() % 4); //Modulo 4 car 3 + 1 (Incluant 0)
}

void initPlateau(plateau *plateau) {
	int x, y;
	//Initialisation à zéro
	//Initialisation du plateau
	for(x = 0; x < 15; x++){
		for(y = 0; y < 15; y++){
			plateau->plateau[x][y] = 0;
		}
	}
	//Initialisation des chemins des joueurs
	for(x = 0; x < 55; x++){
		plateau->chemin.bleu[x] = 0;
		plateau->chemin.rouge[x] = 0;
		plateau->chemin.vert[x] = 0;
		plateau->chemin.jaune[x] = 0;
	}
}

void initJoueurs(int *nbJoueurs, joueur *joueur) {
	int couleur_num = 0;
	int verif[] = { 0,0,0,0 };
	for (int i = 0; i < *nbJoueurs; i++) {
		afficherTitre();
		//Enregistrement du pseudo
		printf("\n");

		printf("Joueur %d, choisissez un pseudo : ", i + 1);
		scanf("%s", joueur[i].pseudo);
		joueur[i].num = i + 1;

		printf("\n");

		//Enregistrement des couleurs
		do {
			if (verif[0] == 0) {
				printf(BRIGHT COLOR_CYAN "BLEU (1) " RESET);
			}
			if (verif[1] == 0) {
				printf(BRIGHT COLOR_RED "ROUGE (2) " RESET);
			}
			if (verif[2] == 0) {
				printf(BRIGHT COLOR_GREEN "VERT (3) " RESET);
			}
			if (verif[3] == 0) {
				printf(BRIGHT COLOR_YELLOW "JAUNE (4)" RESET);
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
			joueur[i].cheval[j].etat = 0;
			joueur[i].cheval[j].couleur = couleur_num - 1;
		}

		joueur[i].victoire = false;
		effacerEcran();
	}
}