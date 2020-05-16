#pragma once

#ifndef QUEUEHEADER
	#define QUEUEHEADER
	typedef struct QueueNode QueueNode;
	struct QueueNode
	{
		int idIsland;
		QueueNode* next;
	};

	typedef struct Queue Queue;
	struct Queue
	{
		QueueNode* front, * rear;
	};
	void fInitQueue(Queue** adrQueue);
	void fEraseQueue(Queue* queue);
	void fEnqueue(Queue* queue, int idIsland);
	void fDeque(Queue* queue);
#endif