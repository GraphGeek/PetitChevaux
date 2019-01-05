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
	enterToContinue();
	effacerEcran();
	afficherTitre();
	tour(plateau, nbJoueurs, joueur, indJoueur);
}

void sortirCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur) {
	//On identifie le joueur en cours par sa couleur
	//On vérifie que la sortie de l'écurie est libre
	int typeCase;
	//Si le joueur en cours est bleu
	if(joueur[*indJoueur].couleur == 0){
		/*
		if(){
			//Ici un cheval d'une autre couleur est présent sur la case de départ
			typeCase = 1;
		}
		else
		*/
		if(plateau->chemin.bleu[0] == 1){
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
		/*
		if(){
			//Ici un cheval d'une autre couleur est présent sur la case de départ
			typeCase = 1;
		}
		else
		*/
		if(plateau->chemin.rouge[0] == 1){
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
		/*
		if(){
			//Ici un cheval d'une autre couleur est présent sur la case de départ
			typeCase = 1;
		}
		else
		*/
		 if(plateau->chemin.vert[0] == 1){
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
		/*
		if(){
			//Ici un cheval d'une autre couleur est présent sur la case de départ
			typeCase = 1;
		}
		else
		*/
		if(plateau->chemin.jaune[0] == 1){
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
		joueur[*indJoueur].nbChevaux--;
		printf("Votre cheval est sorti de l'écurie, relancez le dé\n");
		printf("\n");
		//On relance un tour de jeu
		tour(plateau, nbJoueurs, joueur, indJoueur);
	}
	else if(typeCase == 1){
		int indCheval = 0; //Il faudra récupérer le numéro du cheval correspondant
		mangerCheval(joueur, indJoueur, &indCheval);
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

//Fonction à revoir
void mangerCheval(joueur *joueur, int *indJoueur, int *indCheval){
	printf("Vous avez mangé le cheval [Insérer numéro] de [%s]\n", joueur[*indJoueur].pseudo);
	//Gérer le fait de manger un cheval (son état passe de 1 à 0)
	joueur[*indJoueur].cheval[*indCheval].etat = 0;
}

void demanderDeplacement(plateau *plateau, int *i, int *val, int *couleur, bool *tmp){
	int res;
	do {
		printf("Voulez vous déplacer le cheval à la case %d ? Oui (1) Non (0) : ", *i + *val);
		scanf("%d", &res);
		if(res == 1){
			switch(*couleur) {
			case 0  :
				plateau->chemin.bleu[*i] = 0;
				plateau->chemin.bleu[*i + *val] = 1;
				break;
				
			case 1  :
				plateau->chemin.rouge[*i] = 0;
				plateau->chemin.rouge[*i + *val] = 1;
				break;

			case 2  :
				plateau->chemin.vert[*i] = 0;
				plateau->chemin.vert[*i + *val] = 1;
				break;

			case 3  :
				plateau->chemin.jaune[*i] = 0;
				plateau->chemin.jaune[*i + *val] = 1;
				break;
			}
			*tmp = true;
			printf("Le cheval avance de %d cases\n", *val);
		}
		else if(res == 0){
			//On fait quoi ici ?
		}
		else {
			//Et ici ?
		}
	} while(res != 1 && res != 0);
}


void avancerCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *val, int *indJoueur){
	bool tmp = false;
	int couleur = -1;
	//Si le joueur en cours est bleu
	if(joueur[*indJoueur].couleur == 0){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.bleu[i] == 1 && tmp == false){
				couleur = 0;
				demanderDeplacement(plateau, &i, val, &couleur, &tmp);
			}
		}
	}
	//Si le joueur en cours est rouge
	else if(joueur[*indJoueur].couleur == 1){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.rouge[i] == 1 && tmp == false){
				couleur = 1;
				demanderDeplacement(plateau, &i, val, &couleur, &tmp);
			}
		}
	}
	//Si le joueur en cours est vert
	else if(joueur[*indJoueur].couleur == 2){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.vert[i] == 1 && tmp == false){
				couleur = 2;
				demanderDeplacement(plateau, &i, val, &couleur, &tmp);
			}
		}
	}
	//Si le joueur en cours est jaune
	else if(joueur[*indJoueur].couleur == 3){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.rouge[i] == 1 && tmp == false){
				couleur = 3;
				demanderDeplacement(plateau, &i, val, &couleur, &tmp);
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
	debugPlateau(plateau);
	afficherTour(joueur, indJoueur);
	if(joueur[*indJoueur].statutJeu == 0) {
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
				printf("Voulez-vous sortir un cheval de l'écurie ? Oui (1) Non (0) : ");
				scanf("%d", &res);
				if(res != 1 && res != 0){
					printf("Votre saisie n'est pas correcte\n");
				}
				else if(res == 1){
					sortirCheval(plateau, nbJoueurs, joueur, indJoueur);
					//Penser à ajouter la vérification de superposition
				}
				else {
					avancerCheval(plateau, nbJoueurs, joueur, &val, indJoueur);
				}
			}
			else {
				avancerCheval(plateau, nbJoueurs, joueur, &val, indJoueur);
			}
		}
		else {
			avancerCheval(plateau, nbJoueurs, joueur, &val, indJoueur);
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