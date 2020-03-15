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
	Player* vPlayers;
};

typedef struct Node Node;
struct Node
{
	Node* prev;
	Country country;
	Node* next;
};

typedef struct StackNode StackNode;
struct StackNode
{
	Country country;
	StackNode* next;
};


typedef struct QueueNode QueueNode;
struct QueueNode
{
	Player* vPlayers;
	QueueNode* next;
};

typedef struct Queue Queue;
struct Queue
{
	QueueNode* front, * rear;
};


void fAdd(Node* start, Node* node, Node* prev,int iCountry,int nrCountries)
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
	strcpy(ptr, str);
	*adrPtr = ptr;
}

void fParseDate(FILE* dateIn,int * adrNrCountries,Node * start)
{	
	int score;

	int nrCountries;

	fscanf(dateIn, "%d", &nrCountries);
	*adrNrCountries = nrCountries;

	//vCountries = malloc(sizeof(Country) * nrCountries);

	Node* prev = start;
	start->next = start;
	start->prev = start;

	for (int iCountry = 0; iCountry < nrCountries; ++iCountry)
	{
		Country country;
		char countryName[NAMELENGTH];
		fscanf(dateIn, "%d%s" , &country.nrPlayers, countryName);
		country.name = malloc(sizeof(char) * strlen(countryName));
		strcpy(country.name, countryName);
		country.vPlayers = malloc(sizeof(Player) * country.nrPlayers);

		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player;
			char firstName[NAMELENGTH], lastName[NAMELENGTH];
			fscanf(dateIn, "%s%s%d", firstName, lastName, &player.score);
			fStrAlloc(&player.firstName, firstName);
			fStrAlloc(&player.lastName, lastName);
			country.vPlayers[iPlayer] = player;
		}

		Node* node = malloc(sizeof(Node));
		node->country = country;
		fAdd(start,node,prev,iCountry,nrCountries);
	
		prev = node;
	}

}

void fParseCerinte(FILE * cerinteIn,int vCerinte[5],Player vTwoPlayers[2])
{	
	for (int i = 0; i < 5; ++i)
	{
		fscanf(cerinteIn, "%d", &vCerinte[i]);
	}

	if (vCerinte[4] == 1)
	{
		char firstName[NAMELENGTH], lastName[NAMELENGTH];
		int score;

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
		Country country = node->country;
		printf("\ncountry name = %s", country.name);
		printf("\ncountry has %d players: ", country.nrPlayers);
		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = country.vPlayers[iPlayer];
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
		Country country = node->country;
		fprintf(rezultateOut,"%s\n", country.name);
		node = node->next;
	}
}

void fPrintLong(Node* start,FILE * rezultateOut)
{
	Node* node = start->next;
	while (node != start)
	{
		Country country = node->country;
		printf("%s", country.name);
		printf("\ncountry has %d players: ", country.nrPlayers);
		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = country.vPlayers[iPlayer];
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
		Country country = node->country;
		float init = 0;

		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = country.vPlayers[iPlayer];
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
	int pwr = 0, nrCountriesBak=nrCountries;
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
	Node* stanga = node->prev;
	Node* dreapta = node->next;
	stanga->next = dreapta;
	dreapta->prev = stanga;
	free(node);
}

void fDeleteMinim(Node* start,int nrCountries,float minim)
{
	Node* node = start->next;
	while (node != start)
	{
		Country country = node->country;
		float init = 0;

		for (int iPlayer = 0; iPlayer < country.nrPlayers; ++iPlayer)
		{
			Player player = country.vPlayers[iPlayer];
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

void fEliminate(Node* start,int* adrNrCountries)
{
	int nrCountries = *adrNrCountries,target;
	fFindTarget(nrCountries, &target);

	while (nrCountries != target)
	{
		float minim = FLT_MAX;
		fFindMinim(start, &minim);
		fDeleteMinim(start, nrCountries,minim);
		--nrCountries;
	}
	*adrNrCountries = nrCountries;

	
}


void fPush(StackNode** adrStackTop, Country country)
{
	StackNode* stackTop;
	stackTop = *adrStackTop;

	StackNode* stackNode = malloc(sizeof(StackNode));
	stackNode->country = country;
	stackNode->next = stackTop;
	stackTop = stackNode;

	*adrStackTop = stackTop;
}

void fPop(StackNode** adrStackTop)
{
	StackNode* stackTop = *adrStackTop;

	if (stackTop!=NULL)
	{
		Node* poppedNode = stackTop;
		Country poppedCountry = poppedNode->country;

		stackTop = stackTop->next;
		free(poppedNode);

		*adrStackTop = stackTop;

		return poppedCountry;
	}
	else
	{
		exit(1);
	}
	
}


void fStack(Node* start,StackNode** adrStackTop)
{
	StackNode* stackTop = NULL;

	Node* node = start->next;
	
	while (node != start)
	{
		fPush(&stackTop, node->country);
		node = node->next;
	}
	*adrStackTop = stackTop;
}

void fDeque(Queue* queue)
{
	Player* dequeuedNode = queue->front;
	//Player* returned = (queue->front)->vPlayers;
	queue->front = (queue->front)->next;
	free(dequeuedNode);
}

void fEnqeue(Queue* queue,Player* vPlayers)
{
	QueueNode* queueNode = malloc(sizeof(QueueNode));
	queueNode->vPlayers = vPlayers;
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

void fQueue(Country* vCountries, int* vLocal, Queue* queue)
{
	Country country1 = vCountries[0];
	Country country2 = vCountries[1];

	Player* vPlayers = malloc(sizeof(Player) * 2);
	for (int iPlayer = 0; iPlayer < country1.nrPlayers; ++iPlayer)
	{
		for (int jPlayer = 0; jPlayer < country2.nrPlayers; ++jPlayer)
		{
			vPlayers[0] = country1.vPlayers[iPlayer];
			vPlayers[1] = country2.vPlayers[jPlayer];
			fEnqueue(queue,vPlayers);
		}
	}
}


void fTournament(StackNode* stackTop)
{

	StackNode* winnerTop;

	while (stackTop!=NULL)
	{
		int* vLocal = malloc(sizeof(int) * 2); 
		vLocal[0] = vLocal[1] = 0;
		Country* vCountries = malloc(sizeof(Country) * 2);
		QueueNode* queueNode = malloc(sizeof(QueueNode));

		for (int i = 0; i < 2; ++i)
		{
			vCountries[i]= stackTop->country;
			fPop(&stackTop);
		}

		Queue* queue;
		queue = malloc(sizeof(Queue));
		queue->front = queue->rear = NULL;

		fQueue(vCountries,vLocal, queue);
		
		while (queue->front != NULL)
		{
			Player* vPlayers=queue->front;
			Player player1 = vPlayers[0], player2 = vPlayers[1];

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

			fDeque(queue);
		}

		vCountries[0].globalScore += vLocal[0];
		vCountries[1].globalScore += vLocal[1];


		if (vLocal[0] > vLocal[1])
		{
			fPush(&winnerTop, vCountries[0]);
		}
		else if (vLocal[1] > vLocal[0])
		{
			fPush(&winnerTop, vCountries[1]);
		}
		
	}

}

int main()
{
	FILE* cerinteOut = fopen("date.out", "w");
	FILE* rezultateOut = fopen("rezultate.out", "w");
	FILE* dateIn = fopen("date.in", "r");

	Node* start = malloc(sizeof(Node));
	int nrCountries;
	fParseDate(dateIn,&nrCountries,start);

	FILE* cerinteIn = fopen("cerinte.in", "r");
	int vCerinte[5];
	Player vTwoPlayers[2];
	fParseCerinte(cerinteIn, vCerinte, vTwoPlayers);

	if (vCerinte[1] == 1)
	{
		fEliminate(start, &nrCountries);
	}

	fPrint(start, rezultateOut);

	if (vCerinte[2] == 0) return 0;

	StackNode* stackTop = NULL;
	fStack(start,&stackTop);
	fTournament(stackTop);

	return 0;
}
