
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QueueNode QueueNode; // structura pentru nod de coada
struct QueueNode
{
    char* text;
    QueueNode* next;
};

typedef struct Queue Queue; // structura pentru coada
struct Queue
{
    QueueNode* front;
    QueueNode* rear;
};

typedef struct StackNode StackNode; // nod de stiva
struct StackNode
{
    char car;
    StackNode* next;
};

typedef struct Stack Stack; // stiva
struct Stack
{
    StackNode* top;
};


void fEnqueue(Queue* queue, char* text) // functie de introducere in coada a unui text
{
    QueueNode* queueNode = malloc(sizeof(QueueNode));
    queueNode->text = text;
    queueNode->next = NULL; 
    if (queue->rear == NULL)  // daca coada nu are niciun element 
    {
        queue->rear = queueNode;
    }
    else
    {
        queue->rear->next = queueNode; 
        queue->rear = queueNode; //noul capat de final al cozii e elementul adaugat
    }
    if (queue->front == NULL) 
    {
        queue->front = queue->rear;
        // trebuie actualizat si capatul de inceput al cozii 
        // daca coada are acum un element
        // acel element e atat capatul de final, cat si cel de inceput al cozii
    }
}

char* fDeque(Queue* queue) // functie de scoatere din coada
{
    if (isEmpty(queue)) exit(1);
    QueueNode* dequed = queue->front;
    char* returned = dequed->text;
    queue->front = queue->front->next;
    free(dequed);
    return  returned;
}
//returneaza un pointer la char care corespunde unui sir de caractere alocat dinamic


void fCreateQueue(Queue** adrQueue) // functie de initializare a cozii
{
    Queue* queue = malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    *adrQueue = queue;
}

void fPush(Stack** adrStack, char car) // functie de introdus in stiva
{
    Stack* stack = *adrStack;

    StackNode* stackNode = malloc(sizeof(StackNode));
    stackNode->car = car;
    stackNode->next = stack->top;
    stack->top = stackNode;

    *adrStack = stack;
}

char fPop(Stack** adrStack) // functie de scos din stiva, returneaza un caracter
{
    Stack* stack = *adrStack;

    if (isEmpty(stack)) exit(1);

    StackNode* popped = stack->top;
    char returned = stack->top->car;  
    stack->top = stack->top->next;

    free(popped);
    return returned;
}


void fCreateStack(Stack** adrStack) // initializarea stivei
{
    Stack* stack = malloc(sizeof(Stack));
    stack->top =NULL;
    *adrStack = stack;
}

int isEmpty(Queue* queue) // returneaza 1 in cazul in care coada este goala, 0 altfel
{
    if (queue->front == NULL)
    {
        return 1;
    }
    return 0;
}



void fBackWards(char** adrText,Stack ** adrStack) // functie de inversat un text folosind stiva 
{
    char* text = *adrText;
    Stack* stack = *adrStack;

    int lg = strlen(text);
    int i;
    for (i = 0; i <= lg; ++i)
    {
        char car = text[i];
        fPush(&stack, car); 
        // impingem caracter cu caracter de la primul element pana la '\0'
        // atunci, caracterele vor fi scoase in ordinea dorita (sirul inversat)
    }
    // problema cere introducerea caracterelor pana la '\0'
    // asadar '\0' este aflat la inceputul sirului si trebuie scos
    char car = fPop(&stack);

    for (i = 0; i < lg; ++i)
    {
        char car = fPop(&stack);
        text[i] = car;
    }
    text[lg] = '\0'; // pentru ca sirul sa poata fi afisat cu printf("%s",text);

    *adrText = text;
    *adrStack = stack; 
    // folosim parametrii prin referinta, asadar adresele-parametrii din functie trebuie sa corespunda acum la valorile (variabilele) dorite
}
 

int main()
{
    char sir[100]; // sirul auxiliar, lungimea lui dupa citire va fi nr de biti char alocati dinamic
    char* text;
    Queue* queue;
    fCreateQueue(&queue); // initializam coada

    while (scanf("%s", sir)) // citim sirul pe fiecare iteratie a buclei
    {
        if (!strcmp(sir, "stop")) // daca am gasit caracterul stop
        { 
            break; // iesi din bucla
        }
        text = malloc(sizeof(char) * strlen(sir)); // alocam dinamic textul
        strcpy(text, sir); // copiem din sirul citit in text 
        fEnqueue(queue, text); // introducem in coada textul
    }


    Stack* stack;
    fCreateStack(&stack); // initializam stiva

    while (!isEmpty(queue)) // cat timp avem elemente in coada
    {
        text = malloc(sizeof(char) * strlen(queue->front->text)); 
        // alocam un numar de biti de caractere egal cu lungimea primului element al cozii
        text = fDeque(queue); // scoatem din coada primul element
        fBackWards(&text,&stack);  // il inversam
        printf("%s\n", text); // il afisam
    }

    return 0;
}
