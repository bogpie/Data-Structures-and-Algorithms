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
	Country* adrCountry; // sunt alocate dinamic
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
	Player* adrPlayer;
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
	if (a < b) return a;
	return b;
}

int fMax(int a, int b)
{
	if (a > b) return a;
	return b;
}

void fEraseStack(Stack* stack)
{
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
	ListNode* listNode = start->next;

	while (listNode != start)
	{
		Country* adrCountry = listNode->adrCountry;
		free(adrCountry);
		listNode = listNode->next;
	}
	free(start);

	/*
	for (int iPlayer = 0; iPlayer < 2; ++iPlayer)
	{
		free(vTwoPlayers[iPlayer].numeFamilie);
		free(vTwoPlayers[iPlayer].prenume);
	}
	*/

	free(vTwoPlayers);
	free(vCerinte);
}

void fDeque(Queue* queue)
{
	QueueNode* dequedNode = queue->front;
	queue->front = (queue->front)->next;
	free(dequedNode);
}

void fEnqueue(Queue* queue, Player* adrPlayer)
{
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
	Stack* stack = *adrStack;

	ListNode* listNode = start->next;

	while (listNode != start)
	{
		fPush(&stack, listNode->adrCountry);
		listNode = listNode->next;
	}
	*adrStack = stack;
}

void fAdd(ListNode* start, ListNode* listNode, ListNode* prev, int iCountry, int nrCountries)
{
	prev->next = listNode;
	listNode->prev = prev;
	listNode->next = NULL;
	if (iCountry == nrCountries - 1)
	{
		listNode->next = start;
		start->prev = listNode;
	}

}

void fStrAlloc(char** adrPtr, char str[])
{
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

void fPrint(ListNode* start, FILE* rezultateOut)
{
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
	float minim = *adrMinim;
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
	int pwr = 0, nrCountriesBak = nrCountries;
	while (nrCountries)
	{
		nrCountries /= 2;
		++pwr;
	}
	nrCountries = nrCountriesBak;

	if (nrCountries == 1 << pwr)
	{
		*adrTarget = nrCountries;
		return;
	}
	else
	{
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
			return;
		}
		listNode = listNode->next;
	}

}

void fEliminate(ListNode* start, int* adrNrCountries)
{
	int nrCountries = *adrNrCountries, target;
	fFindTarget(nrCountries, &target);

	while (nrCountries != target)
	{
		float minim = FLT_MAX;
		fFindMinim(start, &minim);
		fDeleteMinim(start, nrCountries, minim);
		--nrCountries;
	}
	*adrNrCountries = nrCountries;


}

void fPrintStack(Stack* stack, FILE* rezultateOut)
{
	StackNode* stackNode = stack->top;
	while (stackNode != NULL)
	{
		Country country = *stackNode->adrCountry;
		fprintf(rezultateOut, "%s --- %d\n", country.name, country.globalScore);
		stackNode = stackNode->next;
	}
	//fprintf(rezultateOut, "\n");
}

void fCopyStack(Stack** adrDestination, Stack* source)
{
	Stack* destination = *adrDestination;
	//Stack* source = *adrSource;

	StackNode* stackNode = source->top;
	while (stackNode != NULL)
	{
		fPush(&destination, stackNode->adrCountry);
		stackNode = stackNode->next;
	}
	//destination->size = source->size;
	*adrDestination = destination;
	//*adrSource = source;
}

void fPlayMatch(Player* adrPlayer1,Player* adrPlayer2,int* vLocal)
{
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
	Stack* winner;
	fInitStack(&winner);
	Stack* fourStack = *adrFourStack;
	int idEtapa = 1;

	while (stack->size > 1)
	{
		fprintf(rezultateOut, "\n====== ETAPA %d ======\n\n", idEtapa);

		while (stack->top != NULL)
		{
			int* vLocal = malloc(sizeof(int) * 2);
			Country * adrCountry1 = NULL, * adrCountry2 = NULL;
			int i;
			for (i = 0; i < 2; ++i)
			{
				if (i == 0)
				{
					adrCountry1 = (stack->top)->adrCountry;
					fprintf(rezultateOut, "%s %d", adrCountry1->name, adrCountry1->globalScore);
				}
				else
				{
					adrCountry2 = (stack->top)->adrCountry;
					fprintf(rezultateOut, " ----- ");
					fprintf(rezultateOut, "%s %d", adrCountry2->name, adrCountry2->globalScore);

				}

				fPop(&stack);
			}
			fprintf(rezultateOut, "\n");

			Queue* queue;
			fInitQueue(&queue);
			fQueueMatches(adrCountry1, adrCountry2, queue);

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
				int pushed = 0;
				int maxim = -1;
				Country country = *adrCountry1;
				int iPlayer;
				for ( iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
				{
					Player player = country.vPlayers[iPlayer];
					if (player.score > maxim) maxim = player.score;
				}
				country = *adrCountry2;
				for ( iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
				{
					Player player = country.vPlayers[iPlayer];
					if (player.score > maxim)
					{
						fPush(&winner, adrCountry2);
						pushed = 1;
						break;
					}
				}
				if (!pushed)
				{
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

void fOpenAllCommandLine(FILE** adrCerinteIn, FILE** adrDateIn, FILE** adrRezultateOut, int argc, char* argv[])
{
	*adrCerinteIn = fopen(argv[1], "r");

	if (*adrCerinteIn == NULL)
	{
		exit(1);
		//*adrCerinteIn = fopen("cerinte.in", "r");
	}

	*adrDateIn = fopen(argv[2], "r");

	if (*adrDateIn == NULL)
	{
		exit(1);
		//*adrDateIn = fopen("date.in", "r");
	}

	*adrRezultateOut = fopen(argv[3], "w");

	if (*adrRezultateOut == NULL)
	{
		exit(1);
		//*adrRezultateOut = fopen("rezultate.out", "w");
	}
}

void alocTreeNode(TreeNode** adrTreeNode)
{
	TreeNode* treeNode;
	treeNode = malloc(sizeof(TreeNode));
	treeNode->left = treeNode->right = NULL;
	*adrTreeNode = treeNode;
}

void fInsert(Player player, TreeNode** adrTreeNode)
{
	TreeNode* treeNode = *adrTreeNode;

	if (!strcmp(player.prenume, "Marco"))
	{
		int breakpoint = 1;
	}

	if (treeNode == NULL)
	{
		alocTreeNode(&treeNode);
		treeNode->player = player;
		*adrTreeNode = treeNode;
		return;
	}

	Player nodePlayer = treeNode->player;
	if (player.score > nodePlayer.score)
	{
		fInsert(player, &treeNode->right);
	}
	else if (player.score < nodePlayer.score)
	{
		fInsert(player, &treeNode->left);

	}
	else
	{
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

void fTree(Stack* fourStack, Tree* tree)
{
	while (fourStack->top != NULL)
	{
		Country* adrCountry = (fourStack->top)->adrCountry;
		Country country = *adrCountry;
		int iPlayer = 0;
		for (iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = country.vPlayers[iPlayer];
			fInsert(player, &tree->root);
		}

		fPop(&fourStack);

	}
}

void fDFS(TreeNode* treeNode, FILE* rezultateOut)
{
	if (treeNode == NULL) return;
	Player player = treeNode->player;
	fDFS(treeNode->right, rezultateOut);
	fprintf(rezultateOut, "%s %s %d\n", player.numeFamilie, player.prenume, player.score);
	fDFS(treeNode->left, rezultateOut);
}

void fSearch(Player searched, TreeNode* treeNode, int* adrFound)
{
	if (treeNode == NULL) return;
	Player player = treeNode->player;

	if (searched.score > player.score)
	{
		fSearch(searched, treeNode->right, adrFound);
	}
	else if (searched.score < player.score)
	{
		fSearch(searched, treeNode->left, adrFound);
	}
	else
	{
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
	fprintf(rezultateOut, "\n====== CLASAMENT JUCATORI ======\n");
	fTree(fourStack, tree);
	fDFS(tree->root, rezultateOut);
}

void fCount(int minScore, int maxScore, TreeNode* treeNode, int* adrNrBetween)
{
	if (treeNode == NULL) return;
	Player player = treeNode->player;

	if (player.score > minScore&& player.score < maxScore)
	{
		++* adrNrBetween;
	}

	if (player.score > minScore)
	{
		fCount(minScore, maxScore, treeNode->left, adrNrBetween);
	}
	if (player.score < maxScore)
	{
		fCount(minScore, maxScore, treeNode->right, adrNrBetween);
	}



}

void fIdentifyAndCount(FILE* rezultateOut, Player* vTwoPlayers, Tree* tree)
{
	int iPlayer;
	for (iPlayer = 0; iPlayer < 2; ++iPlayer)
	{
		int found = 0;
		Player searched = vTwoPlayers[iPlayer];
		fSearch(searched, tree->root, &found);
		if (found == 0)
		{
			fprintf(rezultateOut, "\n%s %s nu poate fi identificat!\n", searched.numeFamilie, searched.prenume);
			return;
		}
	}
	int minScore = fMin(vTwoPlayers[0].score, vTwoPlayers[1].score);
	int maxScore = fMax(vTwoPlayers[0].score, vTwoPlayers[1].score);
	int nrBetween = 0;
	fCount(minScore, maxScore, tree->root, &nrBetween);
	fprintf(rezultateOut, "\n%d", nrBetween);
}

void fParseDate(FILE* dateIn, int* adrNrCountries, ListNode* start)
{
	int nrCountries;

	fscanf(dateIn, "%d", &nrCountries);
	*adrNrCountries = nrCountries;


	ListNode* prev = start;
	start->next = start;
	start->prev = start;

	int iCountry;
	for (iCountry = 0; iCountry < nrCountries; ++iCountry)
	{
		Country country;
		char countryName[NAMELENGTH];
		fscanf(dateIn, "%d%s", &country.nrPlayers, countryName);
		country.name = malloc(sizeof(char) * strlen(countryName));
		strcpy(country.name, countryName);

		country.vPlayers = malloc(sizeof(Player) * country.nrPlayers); 
		
		int iPlayer;
		for (iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player;
			char numeFamilie[NAMELENGTH], prenume[NAMELENGTH];
			fscanf(dateIn, "%s%s%d", numeFamilie, prenume, &player.score);
			fStrAlloc(&player.numeFamilie, numeFamilie);
			fStrAlloc(&player.prenume, prenume);
			//country.vAdrPlayers[iPlayer] = malloc(sizeof(Player));
			country.vPlayers[iPlayer] = player;
		}

		ListNode* listNode = malloc(sizeof(ListNode));
		country.globalScore = 0;
		listNode->adrCountry = malloc(sizeof(Country));
		*listNode->adrCountry = country;
		fAdd(start, listNode, prev, iCountry, nrCountries);
		prev = listNode;
	}

}

void fParseCerinte(FILE* cerinteIn, int vCerinte[5], Player vTwoPlayers[2])
{
	int i;
	for (i = 0; i < 5; ++i)
	{
		fscanf(cerinteIn, "%d", &vCerinte[i]);
	}

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

int main(int argc, char* argv[])
{
	FILE* cerinteIn = NULL;
	FILE* rezultateOut = NULL;
	FILE* dateIn = NULL;
	//fOpenAll(&cerinteIn, &dateIn,&rezultateOut);
	fOpenAllCommandLine(&cerinteIn, &dateIn, &rezultateOut, argc, argv);

	ListNode* start = malloc(sizeof(ListNode));
	int nrCountries, * vCerinte = malloc(sizeof(int) * 5);
	fParseDate(dateIn, &nrCountries, start);
	Player* vTwoPlayers = malloc(sizeof(Player) * 2);
	fParseCerinte(cerinteIn, vCerinte, vTwoPlayers);

	if (vCerinte[1] == 1)
	{
		fEliminate(start, &nrCountries);
	}
	fPrint(start, rezultateOut);

	if (vCerinte[2] == 1)
	{
		Stack* stack, * fourStack;
		fInitStack(&stack);
		fStackCountries(start, &stack);
		fInitStack(&fourStack);
		fTournament(stack, rezultateOut, &fourStack);
		Tree* tree;
		fInitTree(&tree);

		if (vCerinte[3] == 1)
		{
			fRanking(rezultateOut, fourStack, tree);
			if (vCerinte[4] == 1)
			{
				fIdentifyAndCount(rezultateOut, vTwoPlayers, tree);
			}
		}
		fEraseStack(stack);
	}
	fErase(start, vTwoPlayers, vCerinte);

	return 0;
}
