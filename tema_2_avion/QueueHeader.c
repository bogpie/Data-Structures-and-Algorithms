#include "MainHeader.h"

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

void fEnqueue(Queue* queue, int idIsland)
{
	//introducerea in coada
	QueueNode* queueNode = malloc(sizeof(QueueNode));
	queueNode->idIsland = idIsland;
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