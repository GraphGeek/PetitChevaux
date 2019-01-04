#include "main.h"

void effacerEcran(){
	system("clear");
}

void afficherTitre(){
	printf(BRIGHT CHEVAL " LE JEU DES PETITS CHEVAUX " CHEVAL "\n" RESET);
}

void enterToContinue(){
	printf("\nEntrée pour continuer...\n");
	while (true){
		int c = getchar();
		if (c == '\n' || c == EOF) break;
	}
}

int main() {
	srand(time(NULL));
	//On initialise le jeu
	initJeu();
}