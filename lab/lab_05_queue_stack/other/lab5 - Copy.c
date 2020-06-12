#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node Node;
struct Node
{
    char* text;
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
    // poate nu am nevoie de size idk
};


void fEnqueue(Queue* queue, char* text)
{
    Node* node = malloc(sizeof(Node));
    node->text = text;
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

void fPush(Stack** adrStack, char car)
{
    Stack* stack = *adrStack;

    StackNode* stackNode = malloc(sizeof(StackNode));
    stackNode->car = car;
    stackNode->next = stack->top;
    stack->top = stackNode;

    *adrStack = stack;
}

char fPop(Stack** adrStack)
{
    Stack* stack = *adrStack;
    
    if (isEmpty(stack)) exit(1);

    StackNode* popped = stack->top;
    char returned = stack->top->car;  
    stack->top = stack->top->next;

    free(popped);
    return returned;
}


void fCreateStack(Stack** adrStack)
{
    Stack* stack = malloc(sizeof(Stack));
    stack->top =NULL;
    *adrStack = stack;
}

int isEmpty(Queue* queue)
{
    if (queue->front == NULL)
    {
        return 1;
    }
    return 0;
}

char* fDeque(Queue* queue)
{
    if (isEmpty(queue)) exit(1);
    Node* dequed = queue->front;
    char* returned = dequed->text;
    queue->front = queue->front->next;
    free(dequed);
    return  returned;
}

void fBackWards(char** adrText,Stack ** adrStack)
{
    char* text = *adrText;
    Stack* stack = *adrStack;

    int lg = strlen(text);
    for (int i = 0; i <= lg; ++i)
    {
        char car = text[i];
        fPush(&stack, car);
    }
    char car = fPop(&stack); // \0;
    for (int i = 0; i < lg; ++i)
    {
        char car = fPop(&stack);
        text[i] = car;
    }
    text[lg] = '\0';

    *adrText = text;
    *adrStack = stack;
}
 

int main()
{
    char sir[100];
    char* text;
    Queue* queue;
    fCreateQueue(&queue);

   

    while (scanf("%s", sir))
    {
        if (!strcmp(sir, "stop"))
        {
            break;
        }
        text = malloc(sizeof(char) * strlen(sir));
        strcpy(text, sir);
        fEnqueue(queue, text);
    }


    Stack* stack;
    fCreateStack(&stack);

    while (1)
    {
        if (isEmpty(queue))
        {
            break;
        }

        text = malloc(sizeof(char) * strlen(queue->front->text));
        text = fDeque(queue);
        fBackWards(&text,&stack);       
        printf("%s\n", text);
    }

    return 0;
}
