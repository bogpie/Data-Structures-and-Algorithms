#define _CRT_SECURE_NO_WARNINGS
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


typedef struct Node Node;
struct Node
{
    Player* adrPlayer;
    Node* next;
};

typedef struct Queue Queue;
struct Queue
{
    Node *front, * rear;
};

typedef struct StackNode StackNode;
struct StackNode
{
    char car;
    StackNode* next;
};

typedef struct Stack Stack;
struct Stack
{
    StackNode* top;
};


void fEnqueue(Queue* queue, Player * adrPlayer)
{
    Node* node = malloc(sizeof(Node));
    node->adrPlayer = adrPlayer;
    node->next = NULL;
    if (queue->rear == NULL)
    {
        queue->rear = node;
    }
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
    if (queue->front == NULL)
    {
        queue->front = queue->rear;
    }
}

void fCreateQueue(Queue** adrQueue)
{
    Queue* queue = malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    *adrQueue = queue;
}


int isEmpty(Queue* queue)
{
    if (queue->front == NULL)
    {
        return 1;
    }
    return 0;
}

Player fDeque(Queue* queue)
{
    if (isEmpty(queue)) exit(1);
    Node* dequed = queue->front;
    Player returned = *(dequed->adrPlayer);
    queue->front = queue->front->next;
    free(dequed);
    return  returned;
}


void fModify(Player * adrPlayer)
{
    (*adrPlayer).score = -1;
}

int main()
{
    Player * adrPlayer;
    Queue* queue;
    fCreateQueue(&queue);

    adrPlayer = malloc(sizeof(Player));
   
     adrPlayer->score = 123;


  
    fEnqueue(queue, adrPlayer);
    fEnqueue(queue, adrPlayer);
    fEnqueue(queue, adrPlayer);

    Player player;

    fModify(queue->front->adrPlayer);


    player = fDeque(queue);
    printf("%d ", adrPlayer->score);
    player = fDeque(queue);
    printf("%d ", adrPlayer->score);

    player = fDeque(queue);
    printf("%d ", adrPlayer->score);

   
    return 0;
}
