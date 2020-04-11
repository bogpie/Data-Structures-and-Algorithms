#include "Header.h"


void fPlayMatch(Player* adrPlayer1, Player* adrPlayer2, int* vLocal)
{
	//simularea unui meci intre doi jucatori cu actualizarea scorurilor locale pentru cele 2 tari corespunzatoare
	Player player1 = *adrPlayer1, player2 = *adrPlayer2;

	if (player1.score > player2.score)
	{
		player1.score += 5;
		vLocal[0] += 3;
	}
	else if (player1.score < player2.score)
	{
		player2.score += 5;
		vLocal[1] += 3;
	}
	else
	{
		player1.score += 2;
		player2.score += 2;
		++vLocal[0];
		++vLocal[1];

	}
	adrPlayer1->score = player1.score;
	adrPlayer2->score = player2.score;
}

void fTournament(Stack* stack, FILE* rezultateOut, Stack** adrFourStack)
{
	//simulam turneul
	Stack* winner;
	fInitStack(&winner);
	Stack* fourStack = *adrFourStack;
	int idEtapa = 1;
	while (stack->size > 1)
	{
		fprintf(rezultateOut, "\n====== ETAPA %d ======\n\n", idEtapa);

		while (stack->top != NULL)
		{
			//scoatem cele 2 tari din stiva
			Country* adrCountry1 = NULL, * adrCountry2 = NULL;
			adrCountry1 = (stack->top)->adrCountry;
			fprintf(rezultateOut, "%s %d", adrCountry1->name, adrCountry1->globalScore);
			fPop(&stack);
			adrCountry2 = (stack->top)->adrCountry;
			fprintf(rezultateOut, " ----- ");
			fprintf(rezultateOut, "%s %d", adrCountry2->name, adrCountry2->globalScore);
			fPop(&stack);
			fprintf(rezultateOut, "\n");

			//realizam coada de meciuri
			Queue* queue;
			fInitQueue(&queue);
			fPopulateQueue(adrCountry1, adrCountry2, queue);

			//simulam meciurile
			int* vLocal = malloc(sizeof(int) * 2);
			vLocal[0] = vLocal[1] = 0;
			while (queue->front != NULL)
			{
				Player* adrPlayer1 = queue->front->adrPlayer;
				Player* adrPlayer2 = queue->front->next->adrPlayer;
				fprintf(rezultateOut, "%s %s %d ", adrPlayer1->numeFamilie, adrPlayer1->prenume, adrPlayer1->score);
				fprintf(rezultateOut, "vs %s %s %d\n", adrPlayer2->numeFamilie, adrPlayer2->prenume, adrPlayer2->score);
				fPlayMatch(adrPlayer1, adrPlayer2, vLocal);
				fDeque(queue);
				fDeque(queue);
			}

			//impingem in stiva winner tara castigatoare
			adrCountry1->globalScore += vLocal[0];
			adrCountry2->globalScore += vLocal[1];
			if (vLocal[0] > vLocal[1])
			{
				fPush(&winner, adrCountry1);
			}
			else if (vLocal[1] > vLocal[0])
			{
				fPush(&winner, adrCountry2);
			}
			else
			{
				//la egalitatea scorurilor locale, aflam jucatorul cu scorul maxim. tara lui va fi introdusa in stiva.
				int pushed = 0;
				int maxim = -1;
				Country country = *adrCountry1;
				int iPlayer;
				for (iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
				{
					Player player = country.vPlayers[iPlayer];
					if (player.score > maxim) maxim = player.score;
				}
				country = *adrCountry2;
				for (iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
				{
					Player player = country.vPlayers[iPlayer];
					if (player.score > maxim)
					{
						//daca vreun jucator din tara 2 are un scor ce deapaseste maximul calculat pentru tara 1, introducem tara 2 si iesim din bucla
						fPush(&winner, adrCountry2);
						pushed = 1;
						break;
					}
				}
				if (!pushed)
				{
					//daca nu am introdus in stiva winner nicio tara, inseamna ca niciun jucator din tara 2 nu a depasit ca scor maximul => tara 1 este castigatoare
					fPush(&winner, adrCountry1);
				}
			}
			fprintf(rezultateOut, "\n");
			free(vLocal);
			fEraseQueue(queue);
		}


		fprintf(rezultateOut, "=== WINNER ===\n");
		fPrintStack(winner, rezultateOut);

		fCopyStack(&stack, winner);
		winner->top = NULL;
		winner->size = 0;

		if (stack->size == 4)
		{
			fCopyStack(&fourStack, stack);
		}

		++idEtapa;
	}

	*adrFourStack = fourStack;
}

void fRanking(FILE* rezultateOut, Stack* fourStack, Tree* tree)
{
	//realizam clasamentul
	fprintf(rezultateOut, "\n====== CLASAMENT JUCATORI ======\n");
	//intai populam bst-ul
	fPopulateTree(fourStack, tree);
	//apoi il afisam
	fPrintTree(tree->root, rezultateOut);
}

void fParseDate(FILE* dateIn, int* adrNrCountries, ListNode* start)
{
	//parsam fisierul date.in
	//parametrii: fisierul, nr de tari (referinta), nodul de start-santinela al listei circulare

	//citim numarul de tari
	int nrCountries;
	fscanf(dateIn, "%d", &nrCountries);
	*adrNrCountries = nrCountries;

	//primul nod anterior in parcurgerea pentru crearea elementelor listei este chiar nodul de start
	ListNode* prev = start;

	//cream fiecare tara
	int iCountry;
	for (iCountry = 0; iCountry < nrCountries; ++iCountry)
	{
		//citim numarul de jucatori, numele tarii, alocand atatia biti char cat avem nevoie
		Country country;
		char countryName[NAMELENGTH];
		fscanf(dateIn, "%d%s", &country.nrPlayers, countryName);
		fStrAlloc(&country.name, countryName);

		//citim jucatorii
		country.vPlayers = malloc(sizeof(Player) * country.nrPlayers);
		int iPlayer;
		for (iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			//le citim numele de familie, prenumele si scorul. alocam in acelasi mod sirurile de caractere.
			Player player;
			char numeFamilie[NAMELENGTH], prenume[NAMELENGTH];
			fscanf(dateIn, "%s%s%d", numeFamilie, prenume, &player.score);
			fStrAlloc(&player.numeFamilie, numeFamilie);
			fStrAlloc(&player.prenume, prenume);
			//memoram in structura de tara fiecare jucator
			country.vPlayers[iPlayer] = player;
		}

		//alocam nodul de lista caruia ii atribuim tara creata
		ListNode* listNode = malloc(sizeof(ListNode));
		country.globalScore = 0;
		listNode->adrCountry = malloc(sizeof(Country));
		*listNode->adrCountry = country;

		//adaugam nodul de lista si reinitializam nodul anterior
		fAddInList(start, listNode, prev, iCountry, nrCountries);
		prev = listNode;
	}

}

void fParseCerinte(FILE* cerinteIn, int* vCerinte, Player* vTwoPlayers)
{
	//parsam fisierul de cerinte
	//memorand cerintele de rezolvat si cei doi jucatori

	//citirea cerintelor
	int i;
	for (i = 0; i < 5; ++i)
	{
		fscanf(cerinteIn, "%d", &vCerinte[i]);
	}

	//citirea jucatorilor pentru cerinta 5
	if (vCerinte[4] == 1)
	{
		char numeFamilie[NAMELENGTH], prenume[NAMELENGTH];

		for (i = 0; i < 2; ++i)
		{
			fscanf(cerinteIn, "%s%s%d", numeFamilie, prenume, &vTwoPlayers[i].score);

			fStrAlloc(&vTwoPlayers[i].numeFamilie, numeFamilie);
			fStrAlloc(&vTwoPlayers[i].prenume, prenume);
		}
	}
}

void fOpenAllCommandLine(FILE** adrCerinteIn, FILE** adrDateIn, FILE** adrRezultateOut, int argc, char* argv[])
{
	//parametrii: adresele fisierelor (referinta), numarul argumentelor din linia de comanda, argumentele 

	*adrCerinteIn = fopen(argv[1], "r");
	if (*adrCerinteIn == NULL) // daca alocarea nu este facuta cu succes
	{
		exit(1);
	}
	*adrDateIn = fopen(argv[2], "r");
	if (*adrDateIn == NULL)
	{
		exit(1);
	}
	*adrRezultateOut = fopen(argv[3], "w");
	if (*adrRezultateOut == NULL)
	{
		exit(1);
	}
}
