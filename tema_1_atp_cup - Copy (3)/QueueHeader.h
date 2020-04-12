#pragma once

#ifndef QUEUEHEADER
	#define QUEUEHEADER
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
	void fInitQueue(Queue** adrQueue);
	void fEraseQueue(Queue* queue);
	void fEnqueue(Queue* queue, Player* adrPlayer);
	void fDeque(Queue* queue);
	void fPopulateQueue(Country* adrCountry1, Country* adrCountry2, Queue* queue);
#endif