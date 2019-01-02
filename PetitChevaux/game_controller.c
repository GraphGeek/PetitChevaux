//Ce fichier contient toutes les fonctions utiles lors d'un tour de jeu
#include <stdbool.h>
#include "main.h"
#include "game_controller.h"

int lancerDe() {
	int r = 0;
	do { 
		r = rand() % 7; //Modulo 7 car 6 + 1
	} while (r == 0);
	return r;
}

void changerJoueur() {
	printf("Joueur suivant\n");
	//Gérer le changement de joueur à partir de la structure joueur
}

void sortirCheval() {
	printf("Cheval sorti, relancez le dé\n");
	//Gérer la sortie d'un cheval
	//Le joueur doit rejouer
}

void avancerCheval(int *val){
	printf("Le cheval avance de %d cases\n", *val);
	//Gérer le déplacement d'un cheval
}

void mangerCheval(){
	printf("Vous avez mangé le cheval de [Insérer nom du joueur]\n");
	//Gérer le fait de manger un cheval (son état passe de 1 à 0)
}

void verifValeur(int *val){
	int pos = 0; //A définir : Position du prochain cheval adverse
	if(*val < pos){
		avancerCheval(val);
		changerJoueur();
	} else if(*val == pos){
		mangerCheval();
		avancerCheval(val);
		changerJoueur();
	} else {
		changerJoueur();
	}
}

void verifVictoire(int *nbJoueurs, joueur *joueur){
	for (int i = 0; i < *nbJoueurs; i++) {
		do {
			if(joueur[i].victoire == true){
				printf("%s a gagné la partie\n", joueur[i].pseudo);
			}
		} while (joueur[i].victoire == false);
	}
}

void tour(int *nbJoueurs, joueur *joueur) {
	//Variables temporaires
	bool premierTour = false;
	bool premiereCaseLibre = true;

	for (int i = 0; i < *nbJoueurs; i++) {
		//effacerEcran();
		//afficherTitre();
		if(premierTour) {
			int val = lancerDe();
			if(joueur[i].couleur == 0){
				printf("\nAu tour de " COLOR_CYAN "%s\n\n", joueur[i].pseudo);
				printf("%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[i].pseudo, val);
			} else if(joueur[i].couleur == 1){
				printf("\nAu tour de " COLOR_RED "%s\n\n", joueur[i].pseudo);
				printf("%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[i].pseudo, val);
			} else if(joueur[i].couleur == 2){
				printf("\nAu tour de " COLOR_GREEN "%s\n\n", joueur[i].pseudo);
				printf("%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[i].pseudo, val);
			} else if(joueur[i].couleur == 3){
				printf("\nAu tour de " COLOR_YELLOW "%s\n\n", joueur[i].pseudo);				
				printf("%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[i].pseudo, val);
			}
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
					verifValeur(&val);
				}
			verifValeur(&val);
			}
		}
	}
};
