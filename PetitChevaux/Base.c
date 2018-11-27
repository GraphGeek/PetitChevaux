#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COLOR_RED "\x1b[31m" /*Couleur rouge*/
#define COLOR_GREEN "\x1b[32m" /*Couleur verte*/
#define COLOR_YELLOW "\x1b[33m" /*Couleur jaune*/
#define COLOR_BLUE "\x1b[34m" /*Couleur bleu*/
#define COLOR_RESET "\x1b[0m"/*Couleur blanche*/
#define Joueur 4

int lancerDe() {
	srand(time(NULL));
	int De = rand() % 7; /*modulo 7 car 6+1*/
	printf("Valeur = %d\n", De);
}

int Couleur() {
	char couleur[Joueur];
	printf("Joueur 1 quelle couleur voulez vous ?\n\n");
	printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
	printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
	printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
	printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
	scanf("%c", &couleur[0]); getchar();
	if (couleur[0] == 'R') {
		printf("Joueur 2 quelle couleur voulez vous ?\n\n");
		printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
		printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
		printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
		scanf("%c", &couleur[1]); getchar();
		if (couleur[1] == 'V') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
			printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'J') {
				couleur[3] = 'B';
				printf("\nJoueur 4:" COLOR_BLUE "Bleu\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'J';
				printf("\nJoueur 4:" COLOR_YELLOW "Jaune\n" COLOR_RESET);
			}
		}
		else if (couleur[1] == 'J') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
			printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'V') {
				couleur[3] = 'B';
				printf("\nJoueur 4:" COLOR_BLUE "Bleu\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'V';
				printf("\nJoueur 4:" COLOR_GREEN "Vert\n" COLOR_RESET);
			}
		}
		else if (couleur[1] == 'B') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
			printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'J') {
				couleur[3] = 'V';
				printf("\nJoueur 4:" COLOR_GREEN "Vert\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'J';
				printf("\nJoueur 4:" COLOR_YELLOW "Jaune\n" COLOR_RESET);
			}
		}
		else {
			printf("Couleur invalide!\n");
		}
	}
	else if (couleur[0] == 'V') {
		printf("Joueur 2 quelle couleur voulez vous ?\n\n");
		printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
		printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
		printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
		scanf("%c", &couleur[1]); getchar();
		if (couleur[1] == 'R') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
			printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'J') {
				couleur[3] = 'B';
				printf("\nJoueur 4:" COLOR_BLUE "Bleu\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'J';
				printf("\nJoueur 4:" COLOR_YELLOW "Jaune\n" COLOR_RESET);
			}
		}
		else if (couleur[1] == 'J') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
			printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'R') {
				couleur[3] = 'B';
				printf("\nJoueur 4:" COLOR_BLUE "Bleu\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'R';
				printf("\nJoueur 4:" COLOR_RED "Rouge\n" COLOR_RESET);
			}
		}
		else if (couleur[1] == 'B') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
			printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'J') {
				couleur[3] = 'R';
				printf("\nJoueur 4:" COLOR_RED "Rouge\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'J';
				printf("\nJoueur 4:" COLOR_YELLOW "Jaune\n" COLOR_RESET);
			}
		}
		else {
			printf("Couleur invalide!\n");
		}
	}
	else if (couleur[0] == 'J') {
		printf("Joueur 2 quelle couleur voulez vous ?\n\n");
		printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
		printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
		printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
		scanf("%c", &couleur[1]); getchar();
		if (couleur[1] == 'V') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
			printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'R') {
				couleur[3] = 'B';
				printf("\nJoueur 4:" COLOR_BLUE "Bleu\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'R';
				printf("\nJoueur 4:" COLOR_RED "Rouge\n" COLOR_RESET);
			}
		}
		else if (couleur[1] == 'R') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
			printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'V') {
				couleur[3] = 'B';
				printf("\nJoueur 4:" COLOR_BLUE "Bleu\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'V';
				printf("\nJoueur 4:" COLOR_GREEN "Vert\n" COLOR_RESET);
			}
		}
		else if (couleur[1] == 'B') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
			printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'R') {
				couleur[3] = 'V';
				printf("\nJoueur 4:" COLOR_GREEN "Vert\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'R';
				printf("\nJoueur 4:" COLOR_RED "Rouge\n" COLOR_RESET);
			}
		}
		else {
			printf("Couleur invalide!\n");
		}
	}
	else if (couleur[0] == 'B') {
		printf("Joueur 2 quelle couleur voulez vous ?\n\n");
		printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
		printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
		printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
		scanf("%c", &couleur[1]); getchar();
		if (couleur[1] == 'V') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
			printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'J') {
				couleur[3] = 'R';
				printf("\nJoueur 4:" COLOR_RED "Rouge\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'J';
				printf("\nJoueur 4:" COLOR_YELLOW "Jaune\n" COLOR_RESET);
			}
		}
		else if (couleur[1] == 'J') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
			printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'V') {
				couleur[3] = 'R';
				printf("\nJoueur 4:" COLOR_RED "Rouge\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'V';
				printf("\nJoueur 4:" COLOR_GREEN "Vert\n" COLOR_RESET);
			}
		}
		else if (couleur[1] == 'R') {
			printf("Joueur 3 quelle couleur voulez vous ?\n\n");
			printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
			printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
			scanf("%c", &couleur[2]); getchar();
			if (couleur[2] == 'J') {
				couleur[3] = 'V';
				printf("\nJoueur 4:" COLOR_GREEN "Vert\n" COLOR_RESET);
			}
			else {
				couleur[3] = 'J';
				printf("\nJoueur 4:" COLOR_YELLOW "Jaune\n" COLOR_RESET);
			}
		}
		else {
			printf("Couleur invalide!\n");
		}
	}
	else {
		printf("Couleur invalide!\n");
	}
}
int main() {
	char Verification[Joueur] = { 0,0,0,0 };
	char couleur[][10] = { "Rouge","Vert","Jaune","Bleu" };
	for (int i = 0; i < Joueur; i++) {
		do {
			printf("Joueur %d quelle couleur voulez vous ?\n\n", i+1);
			if (Verification[0] == 0) {
				printf(COLOR_RED "Rouge\n" COLOR_RESET "(R)\n");
			}
			if (Verification[1] == 0) {
				printf(COLOR_GREEN "Vert\n" COLOR_RESET "(V)\n");
			}
			if (Verification[2] == 0) {
				printf(COLOR_YELLOW "Jaune\n" COLOR_RESET "(J)\n");
			}
			if (Verification[3] == 0) {
				printf(COLOR_BLUE "Bleu\n" COLOR_RESET "(B)\n");
			}
			scanf("%c", &couleur[i]); getchar();
			if (couleur[i] == 'R') {
				Verification[0] = 1;
			}
		} while (couleur[i] != 'R' || couleur[i] != 'V' || couleur[i] != 'J' || couleur[i] != 'B' && couleur[i] != couleur[i-1]);
	}
}