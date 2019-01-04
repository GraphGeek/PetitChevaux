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

void changerJoueur(plateau *plateau, int *nbJoueurs, joueur *joueur, int *i) {
	if(joueur->num == 0){
		*i = 1;
	}
	else if(joueur->num == 1){
		*i = 2;
	}
	else if(joueur->num == 2){
		*i = 3;
	}
	else if(joueur->num == 3){
		*i = 0;
	}
	tour(plateau, nbJoueurs, joueur, i);
}

void sortirCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *i) {
	joueur[*i].statutJeu = 1;
	if(joueur->couleur == 0){
		plateau->chemin.bleu[0] = 1;
	}
	else if(joueur->couleur == 1){
		plateau->chemin.rouge[0] = 1;
	}
	else if(joueur->couleur == 2){
		plateau->chemin.vert[0] = 1;
	}
	else if(joueur->couleur == 3){
		plateau->chemin.jaune[0] = 1;
	}
	printf("Cheval sorti, relancez le dé\n");
	tour(plateau, nbJoueurs, joueur, i);
}

int demanderDeplacement(int *i){
	int res;
	printf("Voulez vous déplacer le cheval à la case %d ? Oui (1) Non (0)", *i);
	scanf("%d", &res);
	if(res != 1 || res != 0){
		printf("Votre saisie n'est pas correcte\n");
	}
	return res;
}

void avancerCheval(plateau *plateau, joueur *joueur, int *val){
	int res;
	bool temp = false;
	if(joueur->couleur == 0){
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
	else if(joueur->couleur == 1){
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
	else if(joueur->couleur == 2){
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
	else if(joueur->couleur == 3){
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
}

void mangerCheval(){
	printf("Vous avez mangé le cheval de [Insérer nom du joueur]\n");
	//Gérer le fait de manger un cheval (son état passe de 1 à 0)
}

void verifValeur(plateau *plateau, int *nbJoueurs, joueur *joueur, int *val, int *i){
	/*
	On vérifie s'il y a des chevaux entre la position du cheval	et la position
	donnée par la valeur du dé.
	On récupère l'indice si c'est le cas, et la couleur du cheval correspondant
	*/
	int k, color, ind;
	bool b, r, v, j;
	bool stop = false;
	do {
		if(plateau->chemin.bleu[k] == 1){
			b = true;
			color = 0;
		} else if(plateau->chemin.rouge[k] == 1){
			r = true;
			color = 1;
		} else if(plateau->chemin.vert[k] == 1){
			v = true;
			color = 2;
		} else if(plateau->chemin.jaune[k] == 1){
			j = true;
			color = 3;
		}
		if(b == true || r == true || v == true || j == true){
			ind = *i;
			stop = true;
		}
		k++;
	} while(!stop && *i < *val);
	printf("Indice : %d, Couleur : %d", ind, color);
	int pos = 0; //A définir : Position du prochain cheval adverse
	if(*val < pos){
		avancerCheval(plateau, joueur, val);
		changerJoueur(plateau, nbJoueurs, joueur, i);
	} else if(*val == pos){
		mangerCheval();
		avancerCheval(plateau, joueur, val);
		changerJoueur(plateau, nbJoueurs, joueur, i);
	} else {
		changerJoueur(plateau, nbJoueurs, joueur, i);
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

void afficherValeurDe(joueur *joueur, int *i, int *val){
	if(joueur[*i].couleur == 0){
		printf(BRIGHT "\nAu tour de " COLOR_CYAN "%s\n\n" RESET, joueur[*i].pseudo);
		printf(COLOR_CYAN "%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[*i].pseudo, *val);
	} else if(joueur[*i].couleur == 1){
		printf(BRIGHT "\nAu tour de " COLOR_RED "%s\n\n" RESET, joueur[*i].pseudo);
		printf(COLOR_RED "%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[*i].pseudo, *val);
	} else if(joueur[*i].couleur == 2){
		printf(BRIGHT "\nAu tour de " COLOR_GREEN "%s\n\n" RESET, joueur[*i].pseudo);
		printf(COLOR_GREEN "%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[*i].pseudo, *val);
	} else if(joueur[*i].couleur == 3){
		printf(BRIGHT "\nAu tour de " COLOR_YELLOW "%s\n\n" RESET, joueur[*i].pseudo);				
		printf(COLOR_YELLOW "%s" RESET ", vous lancez le dé et obtenez un %d\n", joueur[*i].pseudo, *val);
	}
}

void tour(plateau *plateau, int *nbJoueurs, joueur *joueur, int *i) {
	//Variables temporaires
	bool premiereCaseLibre = true;
	bool premierTour;
	//for (int i = 0; i < *nbJoueurs; i++) {
		if(joueur[*i].statutJeu == 0){
			premierTour = true;
		} else {
			premierTour = false;
		}
		//effacerEcran();
		//afficherTitre();
		if(premierTour == true) {
			printf("PREMIER TOUR\n");
			int val = lancerDe();
			afficherValeurDe(joueur, i, &val);
			if(val == 6){
				if(premiereCaseLibre) {
					printf("Vous pouvez sortir un cheval\n");
					sortirCheval(plateau, nbJoueurs, joueur, i);
				} else {
					printf("La première case devant votre écurie est occupée, vous ne pouvez pas sortir de cheval !\n");
					changerJoueur(plateau, nbJoueurs, joueur, i);
				}
			} else {
				printf("Vous n'avez pas fait 6, vous passez votre tour\n");
				changerJoueur(plateau, nbJoueurs, joueur, i);
			}
		} 
		else {
			printf("TOUR NORMAL\n");
			int val = lancerDe();
			afficherValeurDe(joueur, i, &val);		
			if(val == 6){
				if(joueur->nbChevaux < 4){
					printf("TEST : Il faut sortir un cheval\n");
				}
				else {
					printf("TEST : Il faut sortir un cheval (== 6)\n");
					//avancerCheval(plateau, joueur, &val);
				}
			}
			else {
				printf("TEST : Il faut sortir un cheval (!= 6)\n");			
				//avancerCheval(plateau, joueur, &val);
			}
		}
	//}
};
