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
	strcpy(ptr, str);
	*adrPtr = ptr;
}

void fParseDate(FILE* dateIn, int* adrNrCountries, Node* start)
{
	int score;

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
	Node* stanga = node->prev;
	Node* dreapta = node->next;
	stanga->next = dreapta;
	dreapta->prev = stanga;
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


void fPush(StackNode** adrStackTop, Country* adrCountry)
{
	StackNode* stackTop;
	stackTop = *adrStackTop;

	StackNode* stackNode = malloc(sizeof(StackNode));

	stackNode->adrCountry = adrCountry;
	stackNode->next = stackTop;
	stackTop = stackNode;

	*adrStackTop = stackTop;
}

void fPop(StackNode** adrStackTop)
{
	StackNode* stackTop = *adrStackTop;

	if (stackTop != NULL)
	{
		StackNode* poppedNode = stackTop;
		//Country poppedCountry = *poppedNode->adrCountry;

		stackTop = stackTop->next;
		free(poppedNode);

		*adrStackTop = stackTop;

	}
	else
	{
		exit(1);
	}

}


void fStack(Node* start, StackNode** adrStackTop)
{
	StackNode* stackTop = NULL;

	Node* node = start->next;

	while (node != start)
	{
		fPush(&stackTop, node->adrCountry);
		//node->country.globalScore = 0;
		node = node->next;
	}
	*adrStackTop = stackTop;
}

void fDeque(Queue* queue)
{
	QueueNode* dequedNode = queue->front;
	queue->front = (queue->front)->next;
	free(dequedNode);
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
void fPrintStack(StackNode* stackTop, FILE* rezultateOut)
{
	StackNode* stackNode = stackTop;
	while (stackNode != NULL)
	{
		Country country = *stackNode->adrCountry;
 		fprintf(rezultateOut, "%s --- %d\n", country.name,country.globalScore);
		stackNode = stackNode->next;
	}
	//fprintf(rezultateOut, "\n");
}

void fDeleteStack(StackNode* stackTop, FILE* rezultateOut)
{
	while (stackTop != NULL)
	{
		fPop(&stackTop);
	}
}

void fCopyStack(StackNode** adrStackTop, StackNode** adrWinnerTop)
{
	StackNode* stackTop = *adrStackTop;
	StackNode* winnerTop = *adrWinnerTop;

	while (winnerTop!= NULL)
	{
		fPush(&stackTop, winnerTop->adrCountry);
		fPop(&winnerTop);
	}
	*adrStackTop = stackTop;
	*adrWinnerTop = winnerTop;
}

void fTournament(StackNode* stackTop,FILE* rezultateOut)
{
	StackNode* winnerTop=NULL;
	
	int idEtapa = 1;


	while (stackTop->next!=NULL)
	{
		if(idEtapa==1) fprintf(rezultateOut, "\n");

		fprintf(rezultateOut, "====== ETAPA %d ======\n\n",idEtapa);

		while (stackTop != NULL)
		{

			int* vLocal = malloc(sizeof(int) * 2);
			QueueNode* queueNode = malloc(sizeof(QueueNode));

			Country * adrCountry1 = NULL, * adrCountry2 = NULL;

			for (int i = 0; i < 2; ++i)
			{
				if (i == 0)
				{
					adrCountry1 = stackTop->adrCountry;
					fprintf(rezultateOut, "%s %d", adrCountry1->name, adrCountry1->globalScore);
				}
				else
				{
					adrCountry2 = stackTop->adrCountry;
					fprintf(rezultateOut, " ----- ");
					fprintf(rezultateOut, "%s %d", adrCountry2->name, adrCountry2->globalScore);

				}
				
				fPop(&stackTop);
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
				fPush(&winnerTop, adrCountry1);
			}
			else if (vLocal[1] > vLocal[0])
			{
				fPush(&winnerTop, adrCountry2);
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
						fPush(&winnerTop, adrCountry2);
						pushed = 1;
						break;
					}
				}
				if (!pushed)
				{
					fPush(&winnerTop, adrCountry1);

				}
			}

			fprintf(rezultateOut, "\n");

		}

		fprintf(rezultateOut, "=== WINNER ===\n");
		
		//*adrWinnerTop = winnerTop;
		

		fPrintStack(winnerTop, rezultateOut);
		
		
		fCopyStack(&stackTop, &winnerTop);

		if (stackTop->next != NULL)
		{
			fprintf(rezultateOut, "\n");

		}

		++idEtapa;
	}
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
	Player vTwoPlayers[2];
	fParseCerinte(cerinteIn, vCerinte, vTwoPlayers);

	if (vCerinte[1] == 1)
	{
		fEliminate(start, &nrCountries);
	}

	fPrint(start, rezultateOut);

	if (vCerinte[2] == 0) return 0;

	StackNode* stackTop = NULL;
	fStack(start, &stackTop);

	// StackNode* winnerTop = NULL;
	fTournament(stackTop,rezultateOut);

	if (vCerinte[3] == 0) return 0;

	return 0;
}
