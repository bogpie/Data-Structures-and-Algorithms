#include "Header.h"

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

void fInitQueue(Queue** adrQueue)
{
	Queue* queue = *adrQueue;
	queue = malloc(sizeof(Queue));
	queue->front = queue->rear = NULL;
	*adrQueue = queue;
}

void fPopulateQueue(Country* adrCountry1, Country* adrCountry2, Queue* queue)
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
