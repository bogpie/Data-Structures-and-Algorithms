#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct element ELEMENT;

struct element
{
	int data;
	ELEMENT* next;
};

void initSorted(int n, ELEMENT* start, ELEMENT* finish)
{
	int x;
	printf("\nx=");
	scanf("%d", &x);
	ELEMENT* crt = malloc(sizeof(ELEMENT*));
	start->next = crt;
	crt->data = x;
	crt->next = finish;

	ELEMENT* prev = start;

	for (int i = 1; i < n; ++i)
	{
		printf("\nx=");
		scanf("%d", &x);

		ELEMENT* crt = start;

		while (crt != NULL)
		{
			if (x > crt->data)
			{
				prev = crt;
				crt = crt->next;
			}
			else
			{
				ELEMENT* newElem = malloc(sizeof(ELEMENT*));
				newElem->data = x;
				newElem->next = crt;
				prev->next = newElem;
				break;
			}
		}
	}

}

void initList(ELEMENT* start, ELEMENT* finish)
{
	start->next = finish;
	start->data = INT_MIN;
	finish->next = NULL;
	finish->data = INT_MAX;
}

void printList(ELEMENT* start, ELEMENT* finish)
{
	ELEMENT* crt = start->next;

	printf("\n");
	while (crt != finish)
	{
		printf("%d ", crt->data);
		crt = crt->next;
	}
}

int countElem(ELEMENT* start, ELEMENT* finish)
{
	ELEMENT* crt = start->next;
	int sol = 0;
	while (crt != finish)
	{
		++sol;
		crt = crt->next;
	}
	return sol;
}

void reverseList(ELEMENT** adrStart, ELEMENT** adrFinish)
{
	ELEMENT* start = *adrStart;
	ELEMENT* finish= *adrFinish;

	ELEMENT* newFinish = start;
	ELEMENT* crt = start->next;
	ELEMENT* prev = start;

	while (crt != NULL)
	{
		ELEMENT* newCrt=crt->next;
		crt->next = prev;
		prev = crt;
		crt = newCrt;
	}

	start = finish;
	finish = newFinish;
	finish->next = NULL;

	*adrStart= start;
	*adrFinish= finish;
}

int main()
{
	int n;
	printf("n=");
	scanf("%d", &n);
	if (n <= 0) return -1;

	ELEMENT* start= malloc(sizeof(ELEMENT*));
	ELEMENT* finish = malloc(sizeof(ELEMENT*));
	
	initList(start, finish);
	initSorted(n, start, finish);
	printf("\n%d elemente: ",countElem(start, finish));
	printList(start, finish);

	reverseList(&start, &finish);
	printf("\nlista elemente inversate : ");
	printList(start, finish);


	return 0;
}