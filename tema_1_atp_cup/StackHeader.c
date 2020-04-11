#include "Header.h"

void fEraseStack(Stack* stack)
{
	//stergerea stivei
	StackNode* stackNode = stack->top;
	while (stackNode != NULL)
	{
		StackNode* freed = stackNode;
		stackNode = stackNode->next;
		free(freed);
	}
	free(stack);
}


void fInitStack(Stack** adrStack)
{
	Stack* stack = *adrStack;
	stack = malloc(sizeof(Stack));
	stack->top = NULL;
	stack->size = 0;
	*adrStack = stack;
}

void fCopyStack(Stack** adrDestination, Stack* source)
{
	//functie de copiere a unei stive intr-alta
	Stack* destination = *adrDestination;

	StackNode* stackNode = source->top;
	while (stackNode != NULL)
	{
		fPush(&destination, stackNode->adrCountry);
		stackNode = stackNode->next;
	}
	*adrDestination = destination;
}

void fPrintStack(Stack* stack, FILE* rezultateOut)
{
	//afisarea stivei
	StackNode* stackNode = stack->top;
	while (stackNode != NULL)
	{
		Country country = *stackNode->adrCountry;
		fprintf(rezultateOut, "%s --- %d\n", country.name, country.globalScore);
		stackNode = stackNode->next;
	}
}

void fPush(Stack** adrStack, Country* adrCountry)
{
	//impingere in stiva
	Stack* stack = *adrStack;
	StackNode* stackNode = malloc(sizeof(StackNode));
	stackNode->adrCountry = adrCountry;
	stackNode->next = stack->top;
	stack->top = stackNode;
	++stack->size;
	*adrStack = stack;
}

void fPop(Stack** adrStack)
{
	//scoatere din stiva
	Stack* stack = *adrStack;
	if (stack->top != NULL)
	{
		StackNode* poppedNode = stack->top;
		//Country poppedCountry = *poppedNode->adrCountry;
		stack->top = stack->top->next;
		free(poppedNode);
		*adrStack = stack;
		--stack->size;
	}
	else
	{
		exit(1);
	}

}

void fPopulateStack(ListNode* start, Stack** adrStack)
{
	//stivuim tarile folosind lista circulara
	Stack* stack = *adrStack;
	ListNode* listNode = start->next;
	while (listNode != start)
	{
		fPush(&stack, listNode->adrCountry);
		listNode = listNode->next;
	}
	*adrStack = stack;
}
