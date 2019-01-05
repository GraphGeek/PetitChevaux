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
		int coulCheval = 0; //Il faudra récupérer la couleur du cheval correspondant
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

//Fonction à revoir
void mangerCheval(joueur *joueur, int *indJoueur, int *indCheval, int *coulCheval){
	//Il faut passer l'état du cheval à 0 : Utiliser la fonction mangerCheval()
	//Il faudra identifier le joueur à l'aide de sa couleur et de la variable coulCheval
	printf("Vous avez mangé le cheval et pris sa place\n");
}

void demanderDeplacement(plateau *plateau, joueur *joueur, int *indJoueur, int *i, int *val, int *couleur, bool *tmp){
	int res, coulCheval, indCheval;
	int cpt = 0;
	bool bloq;
	do {
		printf("Voulez vous déplacer le cheval à la case %d ? Oui (1) Non (0) : ", *i + *val + 1);
		scanf("%d", &res);
		if(res == 1){
			switch(*couleur) {

			case 0  :
				for(int k = *i + 1; k < (*i + *val); k++){
					if(plateau->chemin.bleu[k] == 0 && plateau->chemin.rouge[k] == 0 && plateau->chemin.vert[k] == 0 && plateau->chemin.jaune[k] == 0){
						cpt++;
					}
				}
				//Si la case d'arrivée n'est pas occupée par un cheval d'une autre couleur
				if(plateau->chemin.rouge[*i + *val] == 1){
					bloq = true;
					coulCheval = 1;
				}
				else if(plateau->chemin.vert[*i + *val] == 1){
					bloq = true;
					coulCheval = 2;
				}
				else if(plateau->chemin.jaune[*i + *val] == 1){
					bloq = true;
					coulCheval = 3;
				}
				//Si la case d'arrivée n'est pas occupée par un cheval de même couleur
				else if(plateau->chemin.bleu[*i + *val] == 0){
					bloq = false;
				}
				if(bloq == false){
					//Si toutes les cases entre la case actuelle et précédent la case d'arrivée valent 0				
					if(cpt + 1 == *val){
						plateau->chemin.bleu[*i] = 0;
						plateau->chemin.bleu[*i + *val] = 1;
						*tmp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
					//Sinon on affiche une erreur
					else {
						printf("Vous ne pouvez pas passer par dessus un autre cheval !\n");
					}
				}
				//Sinon on mange le cheval adverse
				else {
					plateau->chemin.bleu[*i] = 0;
					plateau->chemin.bleu[*i + *val] = 1;
					*tmp = true;
					printf("Le cheval avance de %d cases\n", *val);
					indCheval = *i + *val;
					mangerCheval(joueur, indJoueur, &indCheval, &coulCheval);
				}
				break;				

			case 1  :
				for(int k = *i + 1; k < (*i + *val); k++){
					if(plateau->chemin.bleu[k] == 0 && plateau->chemin.rouge[k] == 0 && plateau->chemin.vert[k] == 0 && plateau->chemin.jaune[k] == 0){
						cpt++;
					}
				}
				//Si la case d'arrivée n'est pas occupée par un cheval d'une autre couleur
				if(plateau->chemin.bleu[*i + *val] == 1){
					bloq = true;
					coulCheval = 1;
				}
				else if(plateau->chemin.vert[*i + *val] == 1){
					bloq = true;
					coulCheval = 2;
				}
				else if(plateau->chemin.jaune[*i + *val] == 1){
					bloq = true;
					coulCheval = 3;
				}
				//Si la case d'arrivée n'est pas occupée par un cheval de même couleur
				else if(plateau->chemin.rouge[*i + *val] == 0){
					bloq = false;
				}
				if(bloq == false){
					//Si toutes les cases entre la case actuelle et précédent la case d'arrivée valent 0				
					if(cpt + 1 == *val){
						plateau->chemin.rouge[*i] = 0;
						plateau->chemin.rouge[*i + *val] = 1;
						*tmp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
					//Sinon on affiche une erreur
					else {
						printf("Vous ne pouvez pas passer par dessus un autre cheval !\n");
					}
				}
				//Sinon on mange le cheval adverse
				else {
					plateau->chemin.rouge[*i] = 0;
					plateau->chemin.rouge[*i + *val] = 1;
					*tmp = true;
					printf("Le cheval avance de %d cases\n", *val);
					indCheval = *i + *val;
					mangerCheval(joueur, indJoueur, &indCheval, &coulCheval);
				}
				break;

			case 2  :
				for(int k = *i + 1; k < (*i + *val); k++){
					if(plateau->chemin.bleu[k] == 0 && plateau->chemin.rouge[k] == 0 && plateau->chemin.vert[k] == 0 && plateau->chemin.jaune[k] == 0){
						cpt++;
					}
				}
				//Si la case d'arrivée n'est pas occupée par un cheval d'une autre couleur
				if(plateau->chemin.rouge[*i + *val] == 1){
					bloq = true;
					coulCheval = 1;
				}
				else if(plateau->chemin.bleu[*i + *val] == 1){
					bloq = true;
					coulCheval = 2;
				}
				else if(plateau->chemin.jaune[*i + *val] == 1){
					bloq = true;
					coulCheval = 3;
				}
				//Si la case d'arrivée n'est pas occupée par un cheval de même couleur
				else if(plateau->chemin.vert[*i + *val] == 0){
					bloq = false;
				}
				if(bloq == false){
					//Si toutes les cases entre la case actuelle et précédent la case d'arrivée valent 0				
					if(cpt + 1 == *val){
						plateau->chemin.vert[*i] = 0;
						plateau->chemin.vert[*i + *val] = 1;
						*tmp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
					//Sinon on affiche une erreur
					else {
						printf("Vous ne pouvez pas passer par dessus un autre cheval !\n");
					}
				}
				//Sinon on mange le cheval adverse
				else {
					plateau->chemin.vert[*i] = 0;
					plateau->chemin.vert[*i + *val] = 1;
					*tmp = true;
					printf("Le cheval avance de %d cases\n", *val);
					indCheval = *i + *val;
					mangerCheval(joueur, indJoueur, &indCheval, &coulCheval);
				}
				break;

			case 3 :
				for(int k = *i + 1; k < (*i + *val); k++){
					if(plateau->chemin.bleu[k] == 0 && plateau->chemin.rouge[k] == 0 && plateau->chemin.vert[k] == 0 && plateau->chemin.jaune[k] == 0){
						cpt++;
					}
				}
				//Si la case d'arrivée n'est pas occupée par un cheval d'une autre couleur
				if(plateau->chemin.rouge[*i + *val] == 1){
					bloq = true;
					coulCheval = 1;
				}
				else if(plateau->chemin.vert[*i + *val] == 1){
					bloq = true;
					coulCheval = 2;
				}
				else if(plateau->chemin.bleu[*i + *val] == 1){
					bloq = true;
					coulCheval = 3;
				}
				//Si la case d'arrivée n'est pas occupée par un cheval de même couleur
				else if(plateau->chemin.jaune[*i + *val] == 0){
					bloq = false;
				}
				if(bloq == false){
					//Si toutes les cases entre la case actuelle et précédent la case d'arrivée valent 0				
					if(cpt + 1 == *val){
						plateau->chemin.jaune[*i] = 0;
						plateau->chemin.jaune[*i + *val] = 1;
						*tmp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
					//Sinon on affiche une erreur
					else {
						printf("Vous ne pouvez pas passer par dessus un autre cheval !\n");
					}
				}
				//Sinon on mange le cheval adverse
				else {
					plateau->chemin.jaune[*i] = 0;
					plateau->chemin.jaune[*i + *val] = 1;
					*tmp = true;
					printf("Le cheval avance de %d cases\n", *val);
					indCheval = *i + *val;
					mangerCheval(joueur, indJoueur, &indCheval, &coulCheval);
				}
				break;
			}
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
				demanderDeplacement(plateau, joueur, indJoueur, &i, val, &couleur, &tmp);
			}
		}
	}
	//Si le joueur en cours est rouge
	else if(joueur[*indJoueur].couleur == 1){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.rouge[i] == 1 && tmp == false){
				couleur = 1;
				demanderDeplacement(plateau, joueur, indJoueur, &i, val, &couleur, &tmp);
			}
		}
	}
	//Si le joueur en cours est vert
	else if(joueur[*indJoueur].couleur == 2){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.vert[i] == 1 && tmp == false){
				couleur = 2;
				demanderDeplacement(plateau, joueur, indJoueur, &i, val, &couleur, &tmp);
			}
		}
	}
	//Si le joueur en cours est jaune
	else if(joueur[*indJoueur].couleur == 3){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.jaune[i] == 1 && tmp == false){
				couleur = 3;
				demanderDeplacement(plateau, joueur, indJoueur, &i, val, &couleur, &tmp);
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
	printf(COLOR_CYAN "|" RESET);
	for(x = 0; x < 55; x++){
		if(plateau->chemin.bleu[x] == 1){
			printf(COLOR_CYAN CHEVAL "|" RESET);
		}
		else {
			printf(COLOR_CYAN "o|" RESET);
		}
	}
	printf("\n");
	printf(COLOR_RED "|" RESET);
	for(x = 0; x < 55; x++){
		if(plateau->chemin.rouge[x] == 1){
			printf(COLOR_RED CHEVAL "|" RESET);
		}
		else {
			printf(COLOR_RED "o|" RESET);
		}
	}
	printf("\n");
	printf(COLOR_GREEN "|" RESET);
	for(x = 0; x < 55; x++){
		if(plateau->chemin.vert[x] == 1){
			printf(COLOR_GREEN CHEVAL "|" RESET);
		}
		else {
			printf(COLOR_GREEN "o|" RESET);
		}
	}
	printf("\n");
	printf(COLOR_YELLOW "|" RESET);
	for(x = 0; x < 55; x++){
		if(plateau->chemin.jaune[x] == 1){
			printf(COLOR_YELLOW CHEVAL "|" RESET);
		}
		else {
			printf(COLOR_YELLOW "o|" RESET);
		}
	}
	printf("\n");
}