#include "main.h"

void effacerEcran(){
	system("clear");
}

void afficherTitre(){
	printf(BRIGHT CHEVAL " LE JEU DES PETITS CHEVAUX " CHEVAL "\n" RESET);
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void enterToContinue(){
	viderBuffer();
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