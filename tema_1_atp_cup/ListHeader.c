#include "Header.h"

void fPrintList(ListNode* start, FILE* rezultateOut)
{
	//afisarea iterativa a elementelor listei
	ListNode* listNode = start->next;
	while (listNode != start)
	{
		Country country = *listNode->adrCountry;
		fprintf(rezultateOut, "%s", country.name);
		fprintf(rezultateOut, "\n");
		listNode = listNode->next;
	}
}

void fDeleteListNode(ListNode* listNode)
{
	ListNode* left = listNode->prev;
	ListNode* right = listNode->next;
	left->next = right;
	right->prev = left;
	free(listNode);
}

void fAddInList(ListNode* start, ListNode* listNode, ListNode* prev, int iCountry, int nrCountries)
{
	//adaugam in lista un nou nod
	//parametrii: nodul de start, nodul de adaugat, nodul anterior, indicele de tara, nr de tari

	prev->next = listNode;
	listNode->prev = prev;
	listNode->next = NULL;
	if (iCountry == nrCountries - 1)
	{
		//daca am ajuns la finalul listei, asiguram caracterul circular al listei
		listNode->next = start;
		start->prev = listNode;
	}

}

void fInitList(ListNode** adrStart)
{
	//initializam nodul de start al listei transmis prin referinta
	ListNode* start = malloc(sizeof(ListNode));
	start->next = start;
	start->prev = start;
	*adrStart = start;
}

void fFindMinim(ListNode* start, float* adrMinim)
{
	//gasirea scorului initial minim intre tarile din lista
	float minim = *adrMinim;
	ListNode* listNode = start->next;
	while (listNode != start)
	{
		//insumam scorurile jucatorilor pentru calcularea scorului initial
		float init = 0;
		Country country = *listNode->adrCountry;
		int iPlayer;
		for (iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = country.vPlayers[iPlayer];
			init += player.score;
		}
		//apoi impartim scorul insumat la numarul de jucatori
		init /= country.nrPlayers;
		if (init < minim)
		{
			minim = init;
		}
		listNode = listNode->next;
	}
	*adrMinim = minim;
}

void fEraseList(ListNode* start)
{
	ListNode* listNode = start->next;
	while (listNode != start)
	{
		Country* adrCountry = listNode->adrCountry;
		free(adrCountry);
		listNode = listNode->next;
	}
	free(start);
}

void fEliminateUntilTarget(ListNode* start, int* adrNrCountries)
{
	//eliminam tari din lista
	//parametrii: nodul de start, nr de tari (urmeaza a fi modificat!)

	//nr de tari scade pana atinge o tinta, pe care o aflam
	int nrCountries = *adrNrCountries, target;
	fFindTarget(nrCountries, &target);

	//stergem tari pana la atingerea tintei
	while (nrCountries != target)
	{
		//gasim scorul minim intre tari si stergem tara cu scorul respectiv
		float minim = FLT_MAX;
		fFindMinim(start, &minim);
		fDeleteMinim(start, nrCountries, minim);
		--nrCountries;
	}
	*adrNrCountries = nrCountries;


}

void fDeleteMinim(ListNode* start, int nrCountries, float minim)
{
	//stergem tara cu scorul initial minim
	//recalculam scorul initial si comparam cu scorul minim gasit
	ListNode* listNode = start->next;
	while (listNode != start)
	{
		Country country = *listNode->adrCountry;
		float init = 0;

		int iPlayer;
		for (iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = country.vPlayers[iPlayer];
			init += player.score;
		}
		init /= country.nrPlayers;
		if (init == minim)
		{
			fDeleteListNode(listNode);
			//avem grija sa stergem o singura tara, deci iesim din functie
			return;
		}
		listNode = listNode->next;
	}

}