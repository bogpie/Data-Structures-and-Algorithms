#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>

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

		while (crt != finish)
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


int main()
{
	int n;
	printf("n=");
	scanf("%d", &n);

	ELEMENT* start= malloc(sizeof(ELEMENT*));
	ELEMENT* finish = malloc(sizeof(ELEMENT*));
	
	initList(start, finish);
	initSorted(n, start, finish);
	printList(start, finish);
	//count(start, finish);



	return 0;
}