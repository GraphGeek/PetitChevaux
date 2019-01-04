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
	bool sortieLibre;
	if(joueur->couleur == 0){
		if(plateau->chemin.bleu[0] == 0){
			sortieLibre = true;
			plateau->chemin.bleu[0] = 1;
		}
		else {
			sortieLibre = false;
		}
	}
	else if(joueur->couleur == 1){
		if(plateau->chemin.bleu[0] == 0){
			sortieLibre = true;
			plateau->chemin.rouge[0] = 1;
		}
		else {
			sortieLibre = false;
		}
	}
	else if(joueur->couleur == 2){
		if(plateau->chemin.bleu[0] == 0){
			sortieLibre = true;
			plateau->chemin.vert[0] = 1;
		}
		else {
			sortieLibre = false;
		}
	}
	else if(joueur->couleur == 3){
		if(plateau->chemin.bleu[0] == 0){
			sortieLibre = true;
			plateau->chemin.jaune[0] = 1;
		}
		else {
			sortieLibre = false;
		}
	}
	if(sortieLibre == true){
		//Le cheval peut sortir de l'écurie
		joueur[*indJoueur].statutJeu = 1;
		printf("Votre cheval est sorti de l'écurie, relancez le dé\n");
		printf("\n");
		//Ajouter l'état du cheval (en fonction de son numéro) (Voir structure cheval)
		//On relance un tour de jeu
		tour(plateau, nbJoueurs, joueur, indJoueur);
	} else {
		//Le cheval est bloqué dans l'écurie
		joueur[*indJoueur].statutJeu = 0;
		mangerCheval();
	}
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

void mangerCheval(){
	printf("Vous avez mangé le cheval de [Insérer nom du joueur]\n");
	//Gérer le fait de manger un cheval (son état passe de 1 à 0)
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
				printf("TEST : Il faut sortir un cheval\n");
				sortirCheval(plateau, nbJoueurs, joueur, indJoueur);
			}
			else {
				printf("TEST : Il faut avancer un cheval (== 6)\n");
				avancerCheval(plateau, nbJoueurs, joueur, &val, indJoueur);
			}
		}
		else {
			printf("TEST : Il faut avancer un cheval (!= 6)\n");			
			//avancerCheval(plateau, nbJoueurs, joueur, &val, indJoueur);
			//ERREUR DE SEGMENTATION ICI -> A VOIR
			changerJoueur(plateau, nbJoueurs, joueur, indJoueur);
		}
	}
};
