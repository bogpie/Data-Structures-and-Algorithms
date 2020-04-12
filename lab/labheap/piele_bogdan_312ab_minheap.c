#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Header.h"

int main()
{
	Heap* heap = NULL;
	int capacity;
	printf("capacitatea : ");
	scanf("%d", &capacity);
	fCreateHeap(&heap, capacity);



	int nrKeys;
	printf("\nnr elemente : ");
	scanf("%d", &nrKeys);
	
	for (int i = 0; i < nrKeys; ++i)
	{
		int key;
		printf("\nelement cu cheia : ");
		scanf("%d", &key);
		fInsert(heap,key);
	}

	fPrint(heap);

	int parent,child,minim;

	printf("child ( nodul fiu ) : ");
	scanf("%d", &child);
	fParent(heap, child, &parent);
	

	int leftChild, rightChild;
	printf("nodul parinte : ");
	printf("\nparent position : ");
	scanf("%d", &parent);
	fLeftChild(heap, parent, &leftChild);
	fRightChild(heap, parent, &rightChild);
	fFindMinim(heap,&minim);

	int position;
	printf("\nposition : "); scanf("%d", &position);
	fHeapifyDown(heap,position);
	fHeapifyUp(heap,position);



	fErase(&heap);
}
