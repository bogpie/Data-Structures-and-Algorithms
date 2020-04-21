#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Header.h"

//min heap
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

	printf("\nvectorul heap-ului : ");
	fPrint(heap);

	int parent,child,minim;

	printf("\ndaca nodul fiu se afla la pozitia : ");
	scanf("%d", &child);
	fParent(heap, child, &parent);
	if (parent == -1)
	{
		printf("\natunci nodul este radacina");
	}
	else
	{
		printf("\natunci nodul parinte se afla la pozitia %d", parent);

	}

	int leftChild, rightChild;
	printf("\ndaca nodul parinte se afla la pozitia : ");
	scanf("%d", &parent);
	fLeftChild(heap, parent, &leftChild);
	fRightChild(heap, parent, &rightChild);

	printf("\natunci copilul stang ");
	if (leftChild == -1)
	{
		printf("nu exista ");
	}
	else
	{
		printf("este la pozitia %d ", leftChild);
	}
	printf("si copilul drept ");
	if (rightChild == -1)
	{
		printf("nu exista ");
	}
	else
	{
		printf("este la pozitia %d ", rightChild);
	}

	fFindMinim(heap, &minim);
	printf("\nminimul heapului este %d", minim);

	int pos;
	printf("\npozitia nodului de sters : "); scanf("%d", &pos);
	fDeleteNode(heap, pos); 
	--nrKeys;
	printf("\nvectorul heap-ului este acum: ");
	fPrint(heap);

	printf("\nam populat vectorul din heap. acum sortam elementele lui descrescator (minheap!): ");
	//int* vSorted = malloc(sizeof(int) * nrKeys);
	fHeapSort(heap);
	heap->size = nrKeys;
	for (int i = 0; i < nrKeys; ++i)
	{
		printf("%d ", heap->arr[i]);
	}

	fErase(&heap);
	printf("\nheapul a fost sters");
}
