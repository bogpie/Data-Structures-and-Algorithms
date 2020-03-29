#define _CRT_SECURE_NO_WARNINGS
#define NAMELENGTH 50
#define FLT_MAX 1e+10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Player Player;
struct Player
{
	char* lastName;
	char* firstName;
	int score;
};

typedef struct Country Country;
struct Country
{
	char* name;
	int nrPlayers;
	int globalScore;
	Player** vAdrPlayers;
};

typedef struct Node Node;
struct Node
{
	Node* prev;
	Country* adrCountry;
	Node* next;
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
	Player* adrPlayer1;
	Player* adrPlayer2;
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
	int size;
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

void fAdd(Node* start, Node* node, Node* prev, int iCountry, int nrCountries)
{
	prev->next = node;
	node->prev = prev;
	node->next = NULL;
	if (iCountry == nrCountries - 1)
	{
		node->next = start;
		start->prev = node;
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

void fParseDate(FILE* dateIn, int* adrNrCountries, Node* start)
{
	int nrCountries;

	fscanf(dateIn, "%d", &nrCountries);
	*adrNrCountries = nrCountries;


	Node* prev = start;
	start->next = start;
	start->prev = start;

	for (int iCountry = 0; iCountry < nrCountries; ++iCountry)
	{
		Country country;
		char countryName[NAMELENGTH];
		fscanf(dateIn, "%d%s", &country.nrPlayers, countryName);
		country.name = malloc(sizeof(char) * strlen(countryName));
		strcpy(country.name, countryName);

		country.vAdrPlayers = malloc(sizeof(Player*) * country.nrPlayers);

		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player;
			char firstName[NAMELENGTH], lastName[NAMELENGTH];
			fscanf(dateIn, "%s%s%d", firstName, lastName, &player.score);
			fStrAlloc(&player.firstName, firstName);
			fStrAlloc(&player.lastName, lastName);
			country.vAdrPlayers[iPlayer] = malloc(sizeof(Player));
			*country.vAdrPlayers[iPlayer] = player;
		}

		Node* node = malloc(sizeof(Node));
		country.globalScore = 0;

		node->adrCountry = malloc(sizeof(Country));
		*node->adrCountry = country;
		
		fAdd(start, node, prev, iCountry, nrCountries);

		prev = node;
	}

}

void fParseCerinte(FILE* cerinteIn, int vCerinte[5], Player vTwoPlayers[2])
{
	for (int i = 0; i < 5; ++i)
	{
		fscanf(cerinteIn, "%d", &vCerinte[i]);
	}

	if (vCerinte[4] == 1)
	{
		char firstName[NAMELENGTH], lastName[NAMELENGTH];

		for (int i = 0; i < 2; ++i)
		{
			fscanf(cerinteIn, "%s%s%d", firstName, lastName, &vTwoPlayers[i].score);

			fStrAlloc(&vTwoPlayers[i].firstName, firstName);
			fStrAlloc(&vTwoPlayers[i].lastName, lastName);
		}
	}
}

void fConsole(Node* start)
{
	Node* node = start->next;
	while (node != start)
	{
		Country country = *node->adrCountry;
		printf("\ncountry name = %s", country.name);
		printf("\ncountry has %d players: ", country.nrPlayers);
		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = *country.vAdrPlayers[iPlayer];
			printf("\n%s %s score %d", player.firstName, player.lastName, player.score);

		}
		printf("\n\n");
		node = node->next;
	}
}

void fPrint(Node* start, FILE* rezultateOut)
{
	Node* node = start->next;
	while (node != start)
	{
		Country country = *node->adrCountry;
		fprintf(rezultateOut, "%s", country.name);
		fprintf(rezultateOut, "\n");
		//if (node->next != start) fprintf(rezultateOut, "\n");
		

		node = node->next;
	}
	//fprintf(rezultateOut, "\n");
}



void fPrintLong(Node* start, FILE* rezultateOut)
{
	Node* node = start->next;
	while (node != start)
	{
		Country country = *node->adrCountry;
		printf("%s", country.name);
		printf("\ncountry has %d players: ", country.nrPlayers);
		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = *country.vAdrPlayers[iPlayer];
			printf("\n%s %s score %d", player.firstName, player.lastName, player.score);

		}
		printf("\n\n");
		node = node->next;
	}
}

void fFindMinim(Node* start, float* adrMinim)
{
	float minim = *adrMinim;
	Node* node = start->next;
	while (node != start)
	{
		Country country = *node->adrCountry;
		float init = 0;

		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = *country.vAdrPlayers[iPlayer];
			init += player.score;
		}
		init /= country.nrPlayers;
		if (init < minim)
		{
			minim = init;
		}
		node = node->next;
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

	int target;
	if (nrCountries == 1 << pwr)
	{
		return;
	}
	else
	{
		target = 1 << (pwr - 1);
	}
	*adrTarget = target;
}

void fDeleteNode(Node* node)
{
	Node* left = node->prev;
	Node* right = node->next;
	left->next = right;
	right->prev = left;
	free(node);
}

void fDeleteMinim(Node* start, int nrCountries, float minim)
{
	Node* node = start->next;
	while (node != start)
	{
		Country country = *node->adrCountry;
		float init = 0;

		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = *country.vAdrPlayers[iPlayer];
			init += player.score;
		}
		init /= country.nrPlayers;
		if (init == minim)
		{
			fDeleteNode(node);
			return;
		}
		node = node->next;
	}

}

void fEliminate(Node* start, int* adrNrCountries)
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


void fPush(Stack** adrStack, Country* adrCountry)
{
	Stack* stack=*adrStack;

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
		//free(poppedNode);
		*adrStack = stack;
		--stack->size;
	}
	else
	{
		exit(1);
	}

}


void fStack(Node* start, Stack** adrStack)
{
	Stack* stack = *adrStack;

	Node* node = start->next;

	while (node != start)
	{
		fPush(&stack, node->adrCountry);
		//node->country.globalScore = 0;
		node = node->next;
	}
	*adrStack = stack;
}

void fDeque(Queue* queue)
{
	QueueNode* dequedNode = queue->front;
	queue->front = (queue->front)->next;
	//free(dequedNode);
}

void fEnqueue(Queue* queue, Player* adrPlayer1,Player* adrPlayer2)
{
	QueueNode* queueNode = malloc(sizeof(QueueNode));
	queueNode->adrPlayer1 = adrPlayer1;
	queueNode->adrPlayer2 = adrPlayer2;
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

void fQueue(Country* adrCountry1, Country* adrCountry2, Queue* queue)
{
	Country country1 = *adrCountry1;
	Country country2 = *adrCountry2;

	Player* adrPlayer1 = NULL;
	Player* adrPlayer2 = NULL;

	for (int iPlayer = 0; iPlayer < country1.nrPlayers; ++iPlayer)
	{
		adrPlayer1 = malloc(sizeof(Player));
		adrPlayer1 = country1.vAdrPlayers[iPlayer];

		for (int jPlayer = 0; jPlayer < country2.nrPlayers; ++jPlayer)
		{
			adrPlayer2 = malloc(sizeof(Player));
			adrPlayer2 = country2.vAdrPlayers[jPlayer];
			fEnqueue(queue, adrPlayer1,adrPlayer2);
		
		}
	}
}
void fPrintStack(Stack* stack, FILE* rezultateOut)
{
	StackNode* stackNode = stack->top;
	while (stackNode != NULL)
	{
		Country country = *stackNode->adrCountry;
 		fprintf(rezultateOut, "%s --- %d\n", country.name,country.globalScore);
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

void fTournament(Stack* stack,FILE* rezultateOut,Stack** adrFourStack)
{
	Stack* winner = malloc(sizeof(Stack));
	Stack* fourStack = *adrFourStack;
	winner->top = NULL;
	winner->size = 0;

	int idEtapa = 1;


	while (stack->size>1)
	{
		fprintf(rezultateOut, "\n====== ETAPA %d ======\n\n",idEtapa);


		while (stack->top != NULL)
		{
			int* vLocal = malloc(sizeof(int) * 2);
			QueueNode* queueNode = malloc(sizeof(QueueNode));

			Country * adrCountry1 = NULL, * adrCountry2 = NULL;

			for (int i = 0; i < 2; ++i)
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
			queue = malloc(sizeof(Queue));
			queue->front = queue->rear = NULL;

			fQueue(adrCountry1,adrCountry2, queue);

			vLocal[0] = vLocal[1] = 0;
			while (queue->front != NULL)
			{
				QueueNode* queueNode = queue->front;
				Player* adrPlayer1 = queueNode->adrPlayer1;
				Player* adrPlayer2 = queueNode->adrPlayer2;
				Player player1 = *adrPlayer1, player2 = *adrPlayer2;

				fprintf(rezultateOut, "%s %s %d ", player1.firstName, player1.lastName, player1.score);
				fprintf(rezultateOut, "vs %s %s %d\n", player2.firstName, player2.lastName, player2.score);

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
				for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
				{
					Player player = *country.vAdrPlayers[iPlayer];
					if (player.score > maxim) maxim = player.score;
				}
				country = *adrCountry2;
				for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
				{
					Player player = *country.vAdrPlayers[iPlayer];
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

void fOpenAll(FILE** adrCerinteIn, FILE** adrDateIn, FILE** adrRezultateOut)
{
	*adrCerinteIn = fopen("cerinte.in", "r");
	*adrDateIn = fopen("date.in", "r");
	*adrRezultateOut = fopen("rezultate.out", "w");
}

void fOpenAllCommandLine(FILE** adrCerinteIn, FILE** adrDateIn, FILE** adrRezultateOut, int argc, char* argv[])
{
	*adrCerinteIn = fopen(argv[1], "r");
	*adrDateIn = fopen(argv[2], "r");
	*adrRezultateOut = fopen(argv[3], "w");
}

void alocNode(TreeNode** adrTreeNode)
{
	TreeNode* treeNode;
	treeNode = malloc(sizeof(TreeNode));
	treeNode->left = treeNode->right = NULL;
	*adrTreeNode = treeNode;
}

void fInsert(Player player, Tree* tree)
{
	if (tree->size == 0)
	{
		(tree->root)->player = player;
	}
	else
	{
		TreeNode* treeNode = tree->root;

		while (1)
		{
			Player nodePlayer = treeNode->player;

			if (player.score > nodePlayer.score)
			{
				if (treeNode->right == NULL)
				{
					alocNode(&treeNode->right);
					(treeNode->right)->player = player;
					break;
				}
				treeNode = treeNode->right;
			}
			else if (player.score < nodePlayer.score)
			{
				if (treeNode->left == NULL)
				{
					alocNode(&treeNode->left);
					(treeNode->left)->player = player;
					break;
				}
				treeNode = treeNode->left;
			}
			else
			{
				if (strcmp(player.firstName, nodePlayer.firstName) < 1)
				{
					treeNode->player = player;
					break;
				}
				else if (strcmp(player.firstName, nodePlayer.firstName) == 0)
				{
					if (strcmp(player.lastName, nodePlayer.lastName) == -1)
					{
						treeNode->player = player;
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
	}
	++tree->size;
		
		
}
	
void fTree(Stack* fourStack, Tree* tree)
{
	while (fourStack->top != NULL)
	{
		Country* adrCountry = (fourStack->top)->adrCountry;
		Country country = *adrCountry;

		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = *country.vAdrPlayers[iPlayer];

			fInsert(player, tree);
		}

		fPop(&fourStack);

	}
}

void fDFS(TreeNode* treeNode,int* vExists,int* adrNrBetween,Player* vTwoPlayers,FILE* rezultateOut)
{
	if (treeNode == NULL) return;
	Player player = treeNode->player;


	fDFS(treeNode->right, vExists, adrNrBetween,vTwoPlayers,rezultateOut);

	for (int iPlayer = 0; iPlayer < 2; ++iPlayer)
	{
		if (strcmp(vTwoPlayers[iPlayer].firstName, player.firstName) == 0)
		{
			if (strcmp(vTwoPlayers[iPlayer].lastName, player.lastName) == 0)
			{
				++vExists[iPlayer];
				break;
			}
		}
	}

	int minScore = fMin(vTwoPlayers[0].score, vTwoPlayers[1].score);
	int maxScore = fMax(vTwoPlayers[0].score, vTwoPlayers[1].score);
	if (player.score > minScore&& player.score < maxScore) ++*adrNrBetween;

	fprintf(rezultateOut, "%s %s %d\n", player.firstName, player.lastName, player.score);
	
	fDFS(treeNode->left, vExists,adrNrBetween,vTwoPlayers,rezultateOut);
}


void fRanking(FILE* rezultateOut,Stack* fourStack, Tree* tree, int vCerinte[] )
{
	fprintf(rezultateOut, "\n====== CLASAMENT JUCATORI ======\n");
	fTree(fourStack, tree);
	int *vExists = malloc(sizeof(int) * 2), nrBetween = 0;
	vExists[0] = vExists[1] = 0;
	fDFS(tree->root, vExists,&nrBetween,vTwoPlayers,rezultateOut);
	
	if (vCerinte[4] == 0) return;

	if (vExists[0] && vExists[1])
	{
		fprintf(rezultateOut, "%d", nrBetween);
	}
	else if (!vExists[0])
	{
		fprintf(rezultateOut,"%s %s nu poate fi identificat!\n", vTwoPlayers[0].firstName, vTwoPlayers[0].lastName);
	}
	else
	{
		fprintf(rezultateOut,"%s %s nu poate fi identificat!\n", vTwoPlayers[1].firstName, vTwoPlayers[1].lastName);
	}
	
}

int main(int argc, char* argv[])
{
	//date.out??	

	FILE* cerinteIn=NULL;
	FILE* rezultateOut=NULL;
	FILE* dateIn=NULL;

	//fOpenAll(&cerinteIn, &dateIn,&rezultateOut);
	fOpenAllCommandLine(&cerinteIn, &dateIn, &rezultateOut,argc,argv);
	
	Node* start = malloc(sizeof(Node));
	int nrCountries;
	fParseDate(dateIn, &nrCountries, start);

	int vCerinte[5];
	Player* vTwoPlayers=malloc(sizeof(Player)*2);
	fParseCerinte(cerinteIn, vCerinte, vTwoPlayers);

	if (vCerinte[1] == 1)
	{
		fEliminate(start, &nrCountries);
	}

	fPrint(start, rezultateOut);

	if (vCerinte[2] == 0) return 0;


	Stack* stack=malloc(sizeof(Stack));
	stack->top = NULL;
	stack->size = 0;

	fStack(start, &stack);

	// StackNode* winnerTop = NULL;

	Stack* fourStack = malloc(sizeof(Stack));
	fourStack->top = NULL;
	fourStack->size = 0;
	fTournament(stack,rezultateOut,&fourStack);

	
	//fPrintStack(fourStack,rezultateOut);

	Tree* tree = malloc(sizeof(tree));
	tree->size = 0;

	alocNode(&tree->root);
	
	
	if (vCerinte[3] == 0) return 0;

	fRanking(rezultateOut,fourStack, tree);

	
 
	return 0;
}
