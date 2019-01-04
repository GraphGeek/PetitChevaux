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

void changerJoueur(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur) {
	debugPlateau(plateau);
	if(*indJoueur >= 0 && *indJoueur <= 2){
		(*indJoueur)++;
	}
	else if(*indJoueur == 3){
		*indJoueur = 0;
	}
	bool wait = false;
	char res;
	do {
		printf("\nEntrée pour passer au tour suivant (Il faut parfois le faire plusieurs fois [A revoir])\n");
		scanf("%c", &res);
		getchar();
		if(getchar() != '\n'){
			printf("Votre saisie n'est pas correcte\n");
		}
		else {
			wait = true;
			tour(plateau, nbJoueurs, joueur, indJoueur);
		}
	} while(!wait);
}

void sortirCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur) {
	//On identifie le joueur en cours par sa couleur
	//On vérifie que la sortie de l'écurie est libre
	int typeCase;
	//Si le joueur en cours est bleu
	if(joueur[*indJoueur].couleur == 0){
		if(plateau->chemin.rouge[0] == 1 || plateau->chemin.vert[0] == 1 || plateau->chemin.jaune[0] == 1){
			//Ici un cheval d'une autre couleur est présent sur la case de départ
			typeCase = 1;
		}
		else if(plateau->chemin.bleu[0] == 1){
			//Ici un cheval de la même couleur est présent sur la case de départ
			typeCase = 2;
		}
		else {
			//Ici la case de départ est vide
			typeCase = 0;
			//On fais sortir le cheval sur la case de départ
			plateau->chemin.bleu[0] = 1;
		}
	}
	//Si le joueur en cours est rouge
	if(joueur[*indJoueur].couleur == 1){
		if(plateau->chemin.bleu[0] == 1 || plateau->chemin.vert[0] == 1 || plateau->chemin.jaune[0] == 1){
			//Ici un cheval d'une autre couleur est présent sur la case de départ
			typeCase = 1;
		}
		else if(plateau->chemin.rouge[0] == 1){
			//Ici un cheval de la même couleur est présent sur la case de départ
			typeCase = 2;
		}
		else {
			//Ici la case de départ est vide
			typeCase = 0;
			//On fais sortir le cheval sur la case de départ
			plateau->chemin.rouge[0] = 1;
		}
	}
	//Si le joueur en cours est vert
	if(joueur[*indJoueur].couleur == 2){
		if(plateau->chemin.rouge[0] == 1 || plateau->chemin.bleu[0] == 1 || plateau->chemin.jaune[0] == 1){
			//Ici un cheval d'une autre couleur est présent sur la case de départ
			typeCase = 1;
		}
		else if(plateau->chemin.vert[0] == 1){
			//Ici un cheval de la même couleur est présent sur la case de départ
			typeCase = 2;
		}
		else {
			//Ici la case de départ est vide
			typeCase = 0;
			//On fais sortir le cheval sur la case de départ
			plateau->chemin.vert[0] = 1;
		}
	}
	//Si le joueur en cours est jaune
	if(joueur[*indJoueur].couleur == 3){
		if(plateau->chemin.rouge[0] == 1 || plateau->chemin.vert[0] == 1 || plateau->chemin.bleu[0] == 1){
			//Ici un cheval d'une autre couleur est présent sur la case de départ
			typeCase = 1;
		}
		else if(plateau->chemin.jaune[0] == 1){
			//Ici un cheval de la même couleur est présent sur la case de départ
			typeCase = 2;
		}
		else {
			//Ici la case de départ est vide
			typeCase = 0;
			//On fais sortir le cheval sur la case de départ
			plateau->chemin.jaune[0] = 1;
		}
	}
	//0 = Vide | 1 = Cheval d'une autre couleur | 2 = Cheval de la même couleur
	if(typeCase == 0){
		joueur[*indJoueur].statutJeu = 1; //Le joueur entre dans le jeu
		printf("Votre cheval est sorti de l'écurie, relancez le dé\n");
		printf("\n");
		//On relance un tour de jeu
		tour(plateau, nbJoueurs, joueur, indJoueur);
	}
	else if(typeCase == 1){
		int indCheval = 0; //Il faudra récupérer le numéro du cheval correspondant
		int coulCheval = 0; //Il faudra récupérer le numéro de couleur du cheval correspondant
		mangerCheval(joueur, indJoueur, &indCheval, &coulCheval);
	}
	else if(typeCase == 2){
		printf("Votre cheval est bloqué dans l'écurie, vous ne pouvez pas manger un cheval de même couleur !\n");
		printf("Vous passez votre tour\n");
		changerJoueur(plateau, nbJoueurs, joueur, indJoueur);
	}
	else {
		printf("Erreur\n");
	}
}

void mangerCheval(joueur *joueur, int *indJoueur, int *indCheval, int *coulCheval){
	printf("Vous avez mangé le cheval [Insérer numéro] de [%s]\n", joueur[*indJoueur].pseudo);
	//Gérer le fait de manger un cheval (son état passe de 1 à 0)
	joueur[*indJoueur].cheval[*indCheval].etat = 0;
}

int demanderDeplacement(int *indJoueur){
	int res;
	printf("Voulez vous déplacer le cheval à la case %d ? Oui (1) Non (0)", *indJoueur);
	scanf("%d", &res);
	if(res != 1 || res != 0){
		printf("Votre saisie n'est pas correcte\n");
	}
	return res;
}

void avancerCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *val, int *indJoueur){
	int res;
	bool temp = false;
	//Si le joueur est Bleu
	if(joueur[*indJoueur].couleur == 0){
		for(int i; i < 55; i++){
			if(plateau->chemin.bleu[i] == 1 && temp == false){
				do {
					res = demanderDeplacement(&i);
					if(res == 1){
						plateau->chemin.bleu[i] = 0;
						plateau->chemin.bleu[i + *val] = 1;
						temp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
					//Sinon il faut changer de joueur ?
				} while(res != 1 || res != 0);
			}
		}
	}
	//Si le joueur est Rouge
	else if(joueur[*indJoueur].couleur == 1){
		for(int i; i < 55; i++){
			if(plateau->chemin.rouge[i] == 1 && temp == false){
				do{
					res = demanderDeplacement(&i);
					if(res == 1){
						plateau->chemin.rouge[i] = 0;
						plateau->chemin.rouge[i + *val] = 1;
						temp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
				}while(res != 1 || res != 0);
			}
		}
	}
	//Si le joueur est Vert
	else if(joueur[*indJoueur].couleur == 2){
		for(int i; i < 55; i++){
			if(plateau->chemin.vert[i] == 1 && temp == false){
				do{
					res = demanderDeplacement(&i);
					if(res == 1){
						plateau->chemin.vert[i] = 0;
						plateau->chemin.vert[i + *val] = 1;
						temp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
				}while(res != 1 || res != 0);
			}
		}
	}
	//Si le joueur est Jaune
	else if(joueur[*indJoueur].couleur == 3){
		for(int i; i < 55; i++){
			if(plateau->chemin.jaune[i] == 1 && temp == false){
				do{
					res = demanderDeplacement(&i);
					if(res == 1){
						plateau->chemin.jaune[i] = 0;
						plateau->chemin.jaune[i + *val] = 1;
						temp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
				}while(res != 1 || res != 0);
			}
		}
	}
	changerJoueur(plateau, nbJoueurs, joueur, indJoueur);
}

//Fonction à revoir
void verifVictoire(int *nbJoueurs, joueur *joueur){
	for (int i = 0; i < *nbJoueurs; i++) {
		do {
			if(joueur[i].victoire == true){
				printf("%s a gagné la partie\n", joueur[i].pseudo);
			}
		} while (joueur[i].victoire == false);
	}
}

void afficherTour(joueur *joueur, int *indJoueur){
	if(joueur[*indJoueur].couleur == 0){
		printf(BRIGHT "\nAu tour de " COLOR_CYAN "%s\n\n" RESET, joueur[*indJoueur].pseudo);
	} else if(joueur[*indJoueur].couleur == 1){
		printf(BRIGHT "\nAu tour de " COLOR_RED "%s\n\n" RESET, joueur[*indJoueur].pseudo);
	} else if(joueur[*indJoueur].couleur == 2){
		printf(BRIGHT "\nAu tour de " COLOR_GREEN "%s\n\n" RESET, joueur[*indJoueur].pseudo);
	} else if(joueur[*indJoueur].couleur == 3){
		printf(BRIGHT "\nAu tour de " COLOR_YELLOW "%s\n\n" RESET, joueur[*indJoueur].pseudo);				
	}
}


void afficherValeurDe(joueur *joueur, int *indJoueur, int *val){
	if(joueur[*indJoueur].couleur == 0){
		printf(COLOR_CYAN "%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[*indJoueur].pseudo, *val);
	} else if(joueur[*indJoueur].couleur == 1){
		printf(COLOR_RED "%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[*indJoueur].pseudo, *val);
	} else if(joueur[*indJoueur].couleur == 2){
		printf(COLOR_GREEN "%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[*indJoueur].pseudo, *val);
	} else if(joueur[*indJoueur].couleur == 3){
		printf(COLOR_YELLOW "%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[*indJoueur].pseudo, *val);
	}
}

void tour(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur) {
	effacerEcran();
	afficherTitre();
	printf("\n%s commence la partie !\n", joueur[*indJoueur].pseudo);
	afficherTour(joueur, indJoueur);
	bool premierTour;
	if(joueur->statutJeu == 0){
		premierTour = true;
	} else {
		premierTour = false;
	}
	if(premierTour == true) {
		int val = lancerDe();
		afficherValeurDe(joueur, indJoueur, &val);
		if(val == 6){
			sortirCheval(plateau, nbJoueurs, joueur, indJoueur);
		}
		else {
			printf("Vous n'avez pas fait 6, vous passez votre tour\n");
			changerJoueur(plateau, nbJoueurs, joueur, indJoueur);
		}
	} 
	else {
		int val = lancerDe();
		afficherValeurDe(joueur, indJoueur, &val);		
		if(val == 6){
			if(joueur[*indJoueur].nbChevaux < 4){
				int res;
				printf("Voulez-vous sortir un cheval de l'écurie ? Oui (1) Non (0)");
				scanf("%d", &res);
				if(res != 1 || res != 0){
					printf("Votre saisie n'est pas correcte\n");
				}
				else if(res == 1){
					sortirCheval(plateau, nbJoueurs, joueur, indJoueur);
				}
				else {
					printf("TEST : Il faut avancer un cheval (== 6)\n");
					avancerCheval(plateau, nbJoueurs, joueur, &val, indJoueur);
				}
			}
			else {
				printf("TEST : Il faut avancer un cheval (== 6)\n");
				avancerCheval(plateau, nbJoueurs, joueur, &val, indJoueur);
			}
		}
		else {
			printf("TEST : Il faut avancer un cheval (!= 6)\n");			
			avancerCheval(plateau, nbJoueurs, joueur, &val, indJoueur);
			//ERREUR DE SEGMENTATION ICI -> A VOIR
		}
	}
};

/* DEBUG */

void debugPlateau(plateau *plateau){
	int x;
	//int y;
	printf("\n\nDEBUG PLATEAU\n");
	for(x = 0; x < 15; x++){
		/*
		for(y = 0; y < 15; y++){
			printf("%d", plateau->plateau[x][y]);			
		}
		printf("\n");
		*/
	}
	//Chemins des joueurs
	for(x = 0; x < 55; x++){
		printf(COLOR_CYAN "%d" RESET, plateau->chemin.bleu[x]);
	}
	printf("\n");
	for(x = 0; x < 55; x++){
		printf(COLOR_RED "%d" RESET, plateau->chemin.rouge[x]);
	}
	printf("\n");
	for(x = 0; x < 55; x++){
		printf(COLOR_GREEN "%d" RESET, plateau->chemin.vert[x]);
	}
	printf("\n");
	for(x = 0; x < 55; x++){
		printf(COLOR_YELLOW "%d" RESET, plateau->chemin.jaune[x]);
	}
	printf("\n");
}