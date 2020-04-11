#define _CRT_SECURE_NO_WARNINGS
#define NAMELENGTH 50
#define FLT_MAX 1e+10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player Player;
struct Player
{
	char* prenume;
	char* numeFamilie;
	int score;
};

typedef struct Country Country;
struct Country
{
	char* name;
	int nrPlayers;
	int globalScore;
	Player* vPlayers;
};

typedef struct ListNode ListNode;
struct ListNode
{
	ListNode* prev;
	Country* adrCountry; // sunt alocate dinamic, dorim sincronizarea punctajelor si deci folosim adrese la tari
	ListNode* next;
};

typedef struct StackNode StackNode;
struct StackNode
{
	Country* adrCountry;
	StackNode* next;
};

typedef struct QueueNode QueueNode;
struct QueueNode
{
	Player* adrPlayer; // alocare dinamica pentru sincronizarea punctajelor
	QueueNode* next;
};

typedef struct Queue Queue;
struct Queue
{
	QueueNode* front, * rear;
};

typedef struct Stack Stack;
struct Stack
{
	StackNode* top;
	int size;
};

typedef struct TreeNode TreeNode;
struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	Player player;
};

typedef struct Tree Tree;
struct Tree
{
	TreeNode* root;
};

int fMin(int a, int b)
{
	//calcularea minimului
	if (a < b) return a;
	return b;
}

int fMax(int a, int b)
{
	//calcularea maximului
	if (a > b) return a;
	return b;
}

void fEraseStack(Stack* stack)
{
	//stergerea stivei
	StackNode* stackNode = stack->top;
	while (stackNode != NULL)
	{
		StackNode* freed = stackNode;
		stackNode = stackNode->next;
		free(freed);
	}
	free(stack);
}

void fEraseQueue(Queue* queue)
{
	//stergerea cozii
	QueueNode* queueNode = queue->front;
	while (queueNode != NULL)
	{
		QueueNode* freed = queueNode;
		queueNode = queueNode->next;
		free(freed);
	}
	free(queue);
}

void fErase(ListNode* start, Player* vTwoPlayers, int* vCerinte)
{
	//eliberarea de memorie pentru structurile: lista, vector al celor 2 jucatori din cerinte.in, vector de cerinte
	ListNode* listNode = start->next;

	while (listNode != start)
	{
		Country* adrCountry = listNode->adrCountry;
		free(adrCountry);
		listNode = listNode->next;
	}
	free(start);
	free(vTwoPlayers);
	free(vCerinte);
}

void fDeque(Queue* queue)
{
	//scoaterea din coada
	QueueNode* dequedNode = queue->front;
	queue->front = (queue->front)->next;
	free(dequedNode);
}

void fEnqueue(Queue* queue, Player* adrPlayer)
{
	//introducerea in coada
	QueueNode* queueNode = malloc(sizeof(QueueNode));
	queueNode->adrPlayer = adrPlayer;
	queueNode->next = NULL;
	if (queue->rear == NULL)
	{
		queue->rear = queueNode;
	}
	else
	{
		(queue->rear)->next = queueNode;
		queue->rear = queueNode;
	}
	if (queue->front == NULL)
	{
		queue->front = queue->rear;
	}
}

void fQueueMatches(Country* adrCountry1, Country* adrCountry2, Queue* queue)
{
	//introducerea in coada a meciurilor pentru 2 tari
	int iPlayer, jPlayer;
	for (iPlayer = 0; iPlayer < adrCountry1->nrPlayers; ++iPlayer)
	{
		for (jPlayer = 0; jPlayer < adrCountry2->nrPlayers; ++jPlayer)
		{
			fEnqueue(queue, &(adrCountry1->vPlayers[iPlayer]));
			fEnqueue(queue, &(adrCountry2->vPlayers[jPlayer]));
		}
	}
}

void fPush(Stack** adrStack, Country* adrCountry)
{
	//impingere in stiva
	Stack* stack = *adrStack;
	StackNode* stackNode = malloc(sizeof(StackNode));
	stackNode->adrCountry = adrCountry;
	stackNode->next = stack->top;
	stack->top = stackNode;
	++stack->size;
	*adrStack = stack;
}

void fPop(Stack** adrStack)
{
	//scoatere din stiva
	Stack* stack = *adrStack;
	if (stack->top != NULL)
	{
		StackNode* poppedNode = stack->top;
		//Country poppedCountry = *poppedNode->adrCountry;
		stack->top = stack->top->next;
		free(poppedNode);
		*adrStack = stack;
		--stack->size;
	}
	else
	{
		exit(1);
	}

}

void fStackCountries(ListNode* start, Stack** adrStack)
{
	//stivuim tarile folosind lista circulara
	Stack* stack = *adrStack;
	ListNode* listNode = start->next;
	while (listNode != start)
	{
		fPush(&stack, listNode->adrCountry);
		listNode = listNode->next;
	}
	*adrStack = stack;
}

void fStrAlloc(char** adrPtr, char str[])
{
	//daca citim direct intr-o variabila alocata dinamic un sir de caractere exista riscul sa fi alocat prea putin
	//asa ca folosim un string str[] pentru memorarea sirului de caractere, pe care il copiem intr-un vector din heap, folosindu-ne de lungimea sirului
	char* ptr = *adrPtr;
	ptr = malloc(sizeof(char) * strlen(str));
	if (ptr != 0)
	{
		strcpy(ptr, str);
	}
	else
	{
		exit(1);
	}
	*adrPtr = ptr;
}

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

void fFindTarget(int nrCountries, int* adrTarget)
{
	//gasim noul numar de tari ce trebuie atins (tinta)
	//parametrii: nr de tari, tinta (referinta)

	int pwr = 0, nrCountriesBak = nrCountries;

	//aflam cea mai mare putere a lui 2 mai mica sau egala cu numarul de tari
	//adica impartim numarul de tari la 2 cat timp nu e nul si, in acelasi timp, incrementam puterea
	while (nrCountries)
	{
		nrCountries /= 2;
		++pwr;
	}
	nrCountries = nrCountriesBak;

	if (nrCountries == 1 << pwr)
	{
		//daca numarul e deja putere a lui 2, nu mai trebuie eliminate tari
		//tinta e chiar numarul de tari deja existent
		*adrTarget = nrCountries;
		return;
	}
	else
	{
		//altfel tinta este 2^(puterea-1)
		*adrTarget = 1 << (pwr - 1);
	}
}

void fDeleteNode(ListNode* listNode)
{
	ListNode* left = listNode->prev;
	ListNode* right = listNode->next;
	left->next = right;
	right->prev = left;
	free(listNode);
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
			fDeleteNode(listNode);
			//avem grija sa stergem o singura tara, deci iesim din functie
			return;
		}
		listNode = listNode->next;
	}

}

void fEliminateFromList(ListNode* start, int* adrNrCountries)
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

void fPrintStack(Stack* stack, FILE* rezultateOut)
{
	//afisarea stivei
	StackNode* stackNode = stack->top;
	while (stackNode != NULL)
	{
		Country country = *stackNode->adrCountry;
		fprintf(rezultateOut, "%s --- %d\n", country.name, country.globalScore);
		stackNode = stackNode->next;
	}
}

void fCopyStack(Stack** adrDestination, Stack* source)
{
	//functie de copiere a unei stive intr-alta
	Stack* destination = *adrDestination;

	StackNode* stackNode = source->top;
	while (stackNode != NULL)
	{
		fPush(&destination, stackNode->adrCountry);
		stackNode = stackNode->next;
	}
	*adrDestination = destination;
}

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

void fInitTree(Tree** adrTree)
{
	Tree* tree = *adrTree;
	tree = malloc(sizeof(tree));
	tree->root = NULL;
	*adrTree = tree;
}

void fInitStack(Stack** adrStack)
{
	Stack* stack = *adrStack;
	stack = malloc(sizeof(Stack));
	stack->top = NULL;
	stack->size = 0;
	*adrStack = stack;
}

void fInitQueue(Queue** adrQueue)
{
	Queue* queue = *adrQueue;
	queue = malloc(sizeof(Queue));
	queue->front = queue->rear = NULL;
	*adrQueue = queue;
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
			fQueueMatches(adrCountry1, adrCountry2, queue);

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

void fAlocTreeNode(TreeNode** adrTreeNode)
{
	//alocarea unui nod de BST
	TreeNode* treeNode;
	treeNode = malloc(sizeof(TreeNode));
	treeNode->left = treeNode->right = NULL;
	*adrTreeNode = treeNode;
}

void fInsertInTree(Player player, TreeNode** adrTreeNode)
{
	//inseram in BST un jucator, parcurgerea recursiva se face in functie de scor
	TreeNode* treeNode = *adrTreeNode;

	if (treeNode == NULL)
	{
		//nodul unde trebuie facuta inserarea, il alocam
		fAlocTreeNode(&treeNode);
		treeNode->player = player;
		*adrTreeNode = treeNode;
		return;
	}

	Player nodePlayer = treeNode->player;
	if (player.score > nodePlayer.score)
	{
		fInsertInTree(player, &treeNode->right);
	}
	else if (player.score < nodePlayer.score)
	{
		fInsertInTree(player, &treeNode->left);

	}
	else
	{
		//exista deja un jucator cu acelasi scor
		//efectuam comparatiile de nume si inlocuim, daca e cazul, nodul
		int numeFamilieCmp = strcmp(player.numeFamilie, nodePlayer.numeFamilie);
		if (numeFamilieCmp <= -1)
		{
			treeNode->player = player;
			*adrTreeNode = treeNode;
		}
		else if (numeFamilieCmp == 0)
		{
			if (strcmp(player.prenume, nodePlayer.prenume) <= -1)
			{
				treeNode->player = player;
				*adrTreeNode = treeNode;
			}
		}
	}
	return;

}

void fPopulateTree(Stack* fourStack, Tree* tree)
{
	//populam BST-ul, iterand prin stiva celor 4 tari
	while (fourStack->top != NULL)
	{
		Country* adrCountry = (fourStack->top)->adrCountry;
		Country country = *adrCountry;
		int iPlayer = 0;
		for (iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = country.vPlayers[iPlayer];
			fInsertInTree(player, &tree->root);
		}
		fPop(&fourStack);
	}
}

void fPrintTree(TreeNode* treeNode, FILE* rezultateOut)
{
	//parcurgere inorder
	if (treeNode == NULL) return;
	fPrintTree(treeNode->right, rezultateOut);
	fprintf(rezultateOut, "%s %s %d\n", treeNode->player.numeFamilie, treeNode->player.prenume, treeNode->player.score);
	fPrintTree(treeNode->left, rezultateOut);
}

void fSearchInTree(Player searched, TreeNode* treeNode, int* adrFound)
{
	//cautam in BST un jucator, reinitializand de fiecare data radacina BST-ului in functie de scor
	if (treeNode == NULL) return;
	Player player = treeNode->player;

	if (searched.score > player.score)
	{
		fSearchInTree(searched, treeNode->right, adrFound);
	}
	else if (searched.score < player.score)
	{
		fSearchInTree(searched, treeNode->left, adrFound);
	}
	else
	{
		//am gasit un jucator cu scor egal. are si acelasi nume ? (este acelasi jucator?) 
		int foundNume = !strcmp(searched.numeFamilie, player.numeFamilie);
		int foundPrenume = !strcmp(searched.prenume, player.prenume);
		if (foundNume && foundPrenume)
		{
			*adrFound = 1;
			return;
		}
		else
		{
			*adrFound = 0;
			return;
		}

	}

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

void fCount(int minScore, int maxScore, TreeNode* treeNode, int* adrNrBetween)
{
	//numararea jucatorilor se face printr-o parcurgere preorder
	//daca jucatorul este intre cele 2 scoruri, incrementam solutia, cautam in stanga nodului corespunzator si in dreapta
	if (treeNode == NULL) return;
	if (treeNode->player.score > minScore && treeNode->player.score < maxScore)
	{
		++* adrNrBetween;
	}
	fCount(minScore, maxScore, treeNode->left, adrNrBetween);
	fCount(minScore, maxScore, treeNode->right, adrNrBetween);
}

void fIdentifyAndCount(FILE* rezultateOut, Player* vTwoPlayers, Tree* tree)
{
	//identificam si numaram cati sportivi se afla in BST intre cei doi jucatori din cerinte.in

	//intai vedem daca exista jucatorii in BST
	int iPlayer;
	for (iPlayer = 0; iPlayer < 2; ++iPlayer)
	{
		int found = 0;
		fSearchInTree(vTwoPlayers[iPlayer], tree->root, &found);
		if (found == 0)
		{
			fprintf(rezultateOut, "\n%s %s nu poate fi identificat!\n", vTwoPlayers[iPlayer].numeFamilie, vTwoPlayers[iPlayer].prenume);
			return;
		}
	}
	int minScore = fMin(vTwoPlayers[0].score, vTwoPlayers[1].score);
	int maxScore = fMax(vTwoPlayers[0].score, vTwoPlayers[1].score);
	int nrBetween = 0;
	//numaram in variabila nrBetween jucatorii dintre scorurile minim si maxim ale celor 2 jucatori
	fCount(minScore, maxScore, tree->root, &nrBetween);
	fprintf(rezultateOut, "\n%d", nrBetween);
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
		fEliminateFromList(start, &nrCountries); // eliminam tari
	}
	fPrintList(start, rezultateOut); // afiseaza tarile (ramase)

	if (vCerinte[2] == 1) // se rezolva si cerinta 3?
	{
		//initializam stiva stack pentru tarile ramase si o stiva fourStack pentru tarile clasate pe locurile 1->4
		Stack* stack, * fourStack;
		fInitStack(&stack);
		fStackCountries(start, &stack);
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
	fErase(start, vTwoPlayers, vCerinte);

	return 0;
}
