#include "Header.h"

int main(int argc, char* argv[])
{
	//initializam toate pointerele la fisiere cu NULL
	FILE* cerinteIn = NULL;
	FILE* rezultateOut = NULL;
	FILE* dateIn = NULL;

	//le deschidem
	fOpenAllCommandLine(&cerinteIn, &dateIn, &rezultateOut, argc, argv);

	//initializam lista circulara, nr de tari, vectorul de cerinte (vCerinte[i]=1 <=> cerinta i+1 se rezolva - numerotarea incepe de la 0)
	ListNode* start;
	fInitList(&start);

	int nrCountries, * vCerinte = malloc(sizeof(int) * 5);

	//parsam fisierul de date
	fParseDate(dateIn, &nrCountries, start);

	//parsam fisierul de cerinte, memorand in vTwoPlayers cei doi jucatori de care avem nevoie pentru cerinta 5
	Player* vTwoPlayers = malloc(sizeof(Player) * 2);
	fParseCerinte(cerinteIn, vCerinte, vTwoPlayers);

	if (vCerinte[1] == 1) // se rezolva cerinta 2?
	{
		fEliminateUntilTarget(start, &nrCountries); // eliminam tari
	}
	fPrintList(start, rezultateOut); // afiseaza tarile (ramase)

	if (vCerinte[2] == 1) // se rezolva si cerinta 3?
	{
		//initializam stiva stack pentru tarile ramase si o stiva fourStack pentru tarile clasate pe locurile 1->4
		Stack* stack, * fourStack;
		fInitStack(&stack);
		fPopulateStack(start, &stack);
		fInitStack(&fourStack);

		//simulam turneul
		fTournament(stack, rezultateOut, &fourStack);

		//initializam BST-ul jucatorilor ultimelor 4 tari ramase in turneu
		Tree* tree;
		fInitTree(&tree);

		if (vCerinte[3] == 1) // se rezolva si cerinta 4?
		{
			//realizam un clasament populand BST-ul
			fRanking(rezultateOut, fourStack, tree);
			if (vCerinte[4] == 1) // se rezolva si cerinta 5 ?
			{
				//identificam si numaram jucatorii aflati intre cei 2 jucatori mentionati in cerinte.in
				fIdentifyAndCount(rezultateOut, vTwoPlayers, tree);
			}
		}
		//stergem stiva
		fEraseStack(stack);
	}
	//stergem celelalte structuri de date alocate dinamic
	fEraseList(start);
	free(vTwoPlayers);
	free(vCerinte);
	fclose(dateIn);
	fclose(cerinteIn);
	fclose(rezultateOut);
	return 0;
}
