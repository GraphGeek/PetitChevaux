#include "main.h"

void effacerEcran(){
	system("clear");
}

void afficherTitre(){
	printf(BRIGHT "|" CHEVAL " LE JEU DES PETITS CHEVAUX " CHEVAL "|\n" RESET);
}

int main() {
	srand(time(NULL));
	//On initialise le jeu
	initJeu();
}