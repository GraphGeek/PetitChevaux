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

//Cette fonction permet de changer de joueur avant de relancer un tour de jeu
//Elle génère une boucle de jeu
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

//Cette fonction retourne le numéro d'un cheval d'un joueur
int indiceCheval(joueur *joueur, int *indJoueur){
	int indCheval;
	if(joueur[*indJoueur].nbChevaux == 3){
		indCheval = 0;
	}
	else if(joueur[*indJoueur].nbChevaux == 2){
		indCheval = 1;
	}
	else if(joueur[*indJoueur].nbChevaux == 1){
		indCheval = 2;
	}
	else if(joueur[*indJoueur].nbChevaux == 0){
		indCheval = 3;
	}
	return indCheval;
}

//Cette fonction retourne la couleur d'un cheval
int couleurCheval(plateau *plateau){
	int coulCheval;
	if(plateau->chemin.bleu[0] == 1){
		coulCheval = 0;
	}
	else if(plateau->chemin.rouge[0] == 1){
		coulCheval = 1;
	}
	else if(plateau->chemin.vert[0] == 1){
		coulCheval = 2;
	}
	else if(plateau->chemin.jaune[0] == 1){
		coulCheval = 3;
	}
	return coulCheval;
}

//Cette fonction permet de sortir un cheval sur la plateau
void sortirCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur) {
	int typeCase, indCheval, coulCheval;

	//On identifie le joueur en cours par sa couleur
	//On vérifie que la sortie de l'écurie est libre
	
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
			//On fait sortir le cheval sur la case de départ
			plateau->chemin.bleu[0] = 1;
		}
	}

	//Si le joueur en cours est rouge
	if(joueur[*indJoueur].couleur == 1){
		if(plateau->chemin.bleu[0] == 1 || plateau->chemin.vert[0] == 1 || plateau->chemin.jaune[0] == 1){
			typeCase = 1;
		}
		else if(plateau->chemin.rouge[0] == 1){
			typeCase = 2;
		}
		else {
			typeCase = 0;
			plateau->chemin.rouge[0] = 1;
		}
	}

	//Si le joueur en cours est vert
	if(joueur[*indJoueur].couleur == 2){
		if(plateau->chemin.rouge[0] == 1 || plateau->chemin.bleu[0] == 1 || plateau->chemin.jaune[0] == 1){
			typeCase = 1;
		}
		else if(plateau->chemin.vert[0] == 1){
			typeCase = 2;
		}
		else {
			typeCase = 0;
			plateau->chemin.vert[0] = 1;
		}
	}

	//Si le joueur en cours est jaune
	if(joueur[*indJoueur].couleur == 3){
		if(plateau->chemin.rouge[0] == 1 || plateau->chemin.vert[0] == 1 || plateau->chemin.bleu[0] == 1){
			typeCase = 1;
		}
		else if(plateau->chemin.jaune[0] == 1){
			typeCase = 2;
		}
		else {
			typeCase = 0;
			plateau->chemin.jaune[0] = 1;
		}
	}

	switch(typeCase) {

		case 0  : //La case de départ est vide
			joueur[*indJoueur].statutJeu = 1;
			joueur[*indJoueur].nbChevaux--;

			indCheval = indiceCheval(joueur, indJoueur);
			joueur[*indJoueur].cheval[indCheval].etat = 1;

			printf("Votre cheval est sorti de l'écurie, relancez le dé\n\n");

			tour(plateau, nbJoueurs, joueur, indJoueur);
			break;

		case 1 : //Un cheval d'une autre couleur est présent sur la case de départ
			indCheval = indiceCheval(joueur, indJoueur);
			joueur[*indJoueur].cheval[indCheval].etat = 1;
			coulCheval = couleurCheval(plateau);
			int caseArrivee = 0;
			mangerCheval(plateau, nbJoueurs, joueur, indJoueur, &indCheval, &coulCheval, &caseArrivee);
			break;

		case 2 : //Un cheval de la même couleur est présent sur la case de départ
			printf("Votre cheval est bloqué dans l'écurie, vous ne pouvez pas manger un cheval de même couleur !\n");
			printf("Vous passez votre tour\n");
			changerJoueur(plateau, nbJoueurs, joueur, indJoueur);
			break;
	}
}

//Cette fonction permet d'effectuer les opérations utiles lorsqu'un cheval est mangé par un autre
void effectuerManger(plateau *plateau, joueur *joueur, int *indJoueur, int *indCheval, int *coulCheval, int *caseArrivee, int *numJoueur){
	joueur[*numJoueur].cheval[*indCheval].etat = 0;
	joueur[*numJoueur].nbChevaux++;

	if(*coulCheval == 0){
		plateau->chemin.bleu[*caseArrivee] = 0;
	}
	else if(*coulCheval == 1){
		plateau->chemin.rouge[*caseArrivee] = 0;
	}
	else if(*coulCheval == 2){
		plateau->chemin.vert[*caseArrivee] = 0;
	}
	else if(*coulCheval == 3){
		plateau->chemin.jaune[*caseArrivee] = 0;
	}

	if(joueur[*indJoueur].couleur == 0){
		plateau->chemin.bleu[*caseArrivee] = 1;
	}
	else if(joueur[*indJoueur].couleur == 1){
		plateau->chemin.rouge[*caseArrivee] = 1;
	}
	else if(joueur[*indJoueur].couleur == 2){
		plateau->chemin.vert[*caseArrivee] = 1;
	}
	else if(joueur[*indJoueur].couleur == 3){
		plateau->chemin.jaune[*caseArrivee] = 1;
	}
}

void mangerCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur, int *indCheval, int *coulCheval, int *caseArrivee){
	int numJoueur;

	if(joueur[*indJoueur].couleur != *coulCheval){
		if(joueur[0].couleur == *coulCheval){
			numJoueur = 0;
			effectuerManger(plateau, joueur, indJoueur, indCheval, coulCheval, caseArrivee, &numJoueur);
		}
		else if(joueur[1].couleur == *coulCheval){
			numJoueur = 0;
			effectuerManger(plateau, joueur, indJoueur, indCheval, coulCheval, caseArrivee, &numJoueur);
		}
		else if(joueur[2].couleur == *coulCheval){
			numJoueur = 0;
			effectuerManger(plateau, joueur, indJoueur, indCheval, coulCheval, caseArrivee, &numJoueur);
		}
		else if(joueur[3].couleur == *coulCheval){
			numJoueur = 0;
			effectuerManger(plateau, joueur, indJoueur, indCheval, coulCheval, caseArrivee, &numJoueur);
		}
		printf("Vous avez mangé le cheval et pris sa place\n");
	}
	else {
		printf("Vous ne pouvez pas manger votre popre cheval !\n");
	}
	changerJoueur(plateau, nbJoueurs, joueur, indJoueur);
}

void demanderDeplacement(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur, int *i, int *val, int *couleur, bool *tmp){
	int res, coulCheval, indCheval;
	int cpt = 0;
	int numCase = *i + *val + 1;
	int caseArrivee = *i + *val;
	bool bloq;

	do {
		printf("Voulez vous déplacer le cheval à la case %d ? Oui (1) Non (0) : ", numCase);
		scanf("%d", &res);

		if(res == 1){
			switch(*couleur) {

			case 0  :
				//On bloque si la case d'arrivée est occupée par un cheval d'une autre couleur
				if(plateau->chemin.rouge[caseArrivee] == 1){
					bloq = true;
					coulCheval = 1;
				}
				else if(plateau->chemin.vert[caseArrivee] == 1){
					bloq = true;
					coulCheval = 2;
				}
				else if(plateau->chemin.jaune[caseArrivee] == 1){
					bloq = true;
					coulCheval = 3;
				}
				//On bloque si la case d'arrivée est occupée par un cheval de même couleur
				else if(plateau->chemin.bleu[caseArrivee] == 1){
					bloq = true;
				}
				else {
					bloq = false;
				}

				//Si la case d'arrivée n'est pas occupée
				if(bloq == false){
					//Si toutes les cases entre la case actuelle et la case d'arrivée valent 0				
					for(int k = *i + 1; k < (caseArrivee); k++){
						if(plateau->chemin.bleu[k] == 0 && plateau->chemin.rouge[k] == 0 && plateau->chemin.vert[k] == 0 && plateau->chemin.jaune[k] == 0){
							cpt++;
						}
					}

					if(cpt + 1 == *val){
						plateau->chemin.bleu[*i] = 0;
						plateau->chemin.bleu[caseArrivee] = 1;
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
					plateau->chemin.bleu[caseArrivee] = 1;
					*tmp = true;

					printf("Le cheval avance de %d cases\n", *val);

					indCheval = indiceCheval(joueur, indJoueur);

					mangerCheval(plateau, nbJoueurs, joueur, indJoueur, &indCheval, &coulCheval, &caseArrivee);
				}
				break;				

			case 1  :
				if(plateau->chemin.bleu[caseArrivee] == 1){
					bloq = true;
					coulCheval = 0;
				}
				else if(plateau->chemin.vert[caseArrivee] == 1){
					bloq = true;
					coulCheval = 2;
				}
				else if(plateau->chemin.jaune[caseArrivee] == 1){
					bloq = true;
					coulCheval = 3;
				}
				else if(plateau->chemin.rouge[caseArrivee] == 1){
					bloq = true;
				}
				else {
					bloq = false;
				}

				if(bloq == false){
					for(int k = *i + 1; k < (caseArrivee); k++){
						if(plateau->chemin.bleu[k] == 0 && plateau->chemin.rouge[k] == 0 && plateau->chemin.vert[k] == 0 && plateau->chemin.jaune[k] == 0){
							cpt++;
						}
					}

					if(cpt + 1 == *val){
						plateau->chemin.rouge[*i] = 0;
						plateau->chemin.rouge[caseArrivee] = 1;
						*tmp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
					else {
						printf("Vous ne pouvez pas passer par dessus un autre cheval !\n");
					}
				}
				else {
					plateau->chemin.rouge[*i] = 0;
					plateau->chemin.rouge[caseArrivee] = 1;
					*tmp = true;

					printf("Le cheval avance de %d cases\n", *val);

					int indCheval = indiceCheval(joueur, indJoueur);

					mangerCheval(plateau, nbJoueurs, joueur, indJoueur, &indCheval, &coulCheval, &caseArrivee);
				}
				break;

			case 2  :
				if(plateau->chemin.rouge[caseArrivee] == 1){
					bloq = true;
					coulCheval = 1;
				}
				else if(plateau->chemin.bleu[caseArrivee] == 1){
					bloq = true;
					coulCheval = 0;
				}
				else if(plateau->chemin.jaune[caseArrivee] == 1){
					bloq = true;
					coulCheval = 3;
				}
				else if(plateau->chemin.vert[caseArrivee] == 1){
					bloq = true;
				}
				else {
					bloq = false;
				}

				if(bloq == false){
					for(int k = *i + 1; k < (caseArrivee); k++){
						if(plateau->chemin.bleu[k] == 0 && plateau->chemin.rouge[k] == 0 && plateau->chemin.vert[k] == 0 && plateau->chemin.jaune[k] == 0){
							cpt++;
						}
					}

					if(cpt + 1 == *val){
						plateau->chemin.vert[*i] = 0;
						plateau->chemin.vert[caseArrivee] = 1;
						*tmp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
					else {
						printf("Vous ne pouvez pas passer par dessus un autre cheval !\n");
					}
				}
				else {
					plateau->chemin.vert[*i] = 0;
					plateau->chemin.vert[caseArrivee] = 1;
					*tmp = true;

					printf("Le cheval avance de %d cases\n", *val);

					int indCheval = indiceCheval(joueur, indJoueur);

					mangerCheval(plateau, nbJoueurs, joueur, indJoueur, &indCheval, &coulCheval, &caseArrivee);
				}
				break;

			case 3 :
				if(plateau->chemin.rouge[caseArrivee] == 1){
					bloq = true;
					coulCheval = 1;
				}
				else if(plateau->chemin.vert[caseArrivee] == 1){
					bloq = true;
					coulCheval = 2;
				}
				else if(plateau->chemin.bleu[caseArrivee] == 1){
					bloq = true;
					coulCheval = 0;
				}
				else if(plateau->chemin.jaune[caseArrivee] == 1){
					bloq = true;
				}
				else {
					bloq = false;
				}

				if(bloq == false){
					for(int k = *i + 1; k < (caseArrivee); k++){
						if(plateau->chemin.bleu[k] == 0 && plateau->chemin.rouge[k] == 0 && plateau->chemin.vert[k] == 0 && plateau->chemin.jaune[k] == 0){
							cpt++;
						}
					}

					if(cpt + 1 == *val){
						plateau->chemin.jaune[*i] = 0;
						plateau->chemin.jaune[caseArrivee] = 1;
						*tmp = true;
						printf("Le cheval avance de %d cases\n", *val);
					}
					else {
						printf("Vous ne pouvez pas passer par dessus un autre cheval !\n");
					}
				}
				else {
					plateau->chemin.jaune[*i] = 0;
					plateau->chemin.jaune[caseArrivee] = 1;
					*tmp = true;

					printf("Le cheval avance de %d cases\n", *val);

					int indCheval = indiceCheval(joueur, indJoueur);

					mangerCheval(plateau, nbJoueurs, joueur, indJoueur, &indCheval, &coulCheval, &caseArrivee);
				}
				break;
			}
		}
	} while(res != 1 && res != 0);
}


void avancerCheval(plateau *plateau, int *nbJoueurs, joueur *joueur, int *val, int *indJoueur){
	bool tmp = false;
	int couleur;

	//Si le joueur en cours est bleu
	if(joueur[*indJoueur].couleur == 0){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.bleu[i] == 1 && tmp == false){
				couleur = 0;
				demanderDeplacement(plateau, nbJoueurs, joueur, indJoueur, &i, val, &couleur, &tmp);
			}
		}
	}
	//Si le joueur en cours est rouge
	else if(joueur[*indJoueur].couleur == 1){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.rouge[i] == 1 && tmp == false){
				couleur = 1;
				demanderDeplacement(plateau, nbJoueurs, joueur, indJoueur, &i, val, &couleur, &tmp);
			}
		}
	}
	//Si le joueur en cours est vert
	else if(joueur[*indJoueur].couleur == 2){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.vert[i] == 1 && tmp == false){
				couleur = 2;
				demanderDeplacement(plateau, nbJoueurs, joueur, indJoueur, &i, val, &couleur, &tmp);
			}
		}
	}
	//Si le joueur en cours est jaune
	else if(joueur[*indJoueur].couleur == 3){
		for(int i = 0; i < 55; i++){
			if(plateau->chemin.jaune[i] == 1 && tmp == false){
				couleur = 3;
				demanderDeplacement(plateau, nbJoueurs, joueur, indJoueur, &i, val, &couleur, &tmp);
			}
		}
	}

	changerJoueur(plateau, nbJoueurs, joueur, indJoueur);
}


//Fonction qui n'a pas encore été implémentée
void verifVictoire(int *nbJoueurs, joueur *joueur){
	for (int i = 0; i < *nbJoueurs; i++) {
		do {
			if(joueur[i].victoire == true){
				printf("%s a gagné la partie\n", joueur[i].pseudo);
			}
		} while (joueur[i].victoire == false);
	}
}

//Permet d'afficher le pseudo du joueur à chaque tour
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

//Permet d'afficher la valeur du dé à chaque tour
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

//Fonction qui permet de gérer un tour de jeu
void tour(plateau *plateau, int *nbJoueurs, joueur *joueur, int *indJoueur) {

	affichPlateau(plateau);
	afficherTour(joueur, indJoueur);

	//Si le joueur n'a aucun cheval de sorti
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
	//Si le joueur à au moins un cheval de sorti
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

//Cette fonction permet d'afficher une version minimaliste des cases du plateau pour
//avoir un premier aperçu en jeu
void affichPlateau(plateau *plateau){
	printf("\n");
	printf("|");
	for(int x = 0; x < 55; x++){
		if(plateau->chemin.bleu[x] == 1){
			printf(COLOR_CYAN CHEVAL "|" RESET);
		}
		else if(plateau->chemin.rouge[x] == 1){
			printf(COLOR_RED CHEVAL RESET "|");
		}
		else if(plateau->chemin.vert[x] == 1){
			printf(COLOR_GREEN CHEVAL RESET"|");
		}
		else if(plateau->chemin.jaune[x] == 1){
			printf(COLOR_YELLOW CHEVAL RESET"|");
		}
		else {
			printf("o|");
		}
	}
	printf("\n");
}

/* DEBUG */
//Cette fonction nous a servi au cours du développement
void debugPlateau(plateau *plateau){
	int x;
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