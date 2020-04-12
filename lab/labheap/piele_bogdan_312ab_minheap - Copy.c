#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Heap Heap;
struct Heap
{
	int size, capacity, * arr;
};

void fCreateHeap(Heap** adrHeap,int capacity)
{
	Heap* heap = malloc(sizeof(Heap));

	if (heap == NULL)
	{
		exit(1);
	}

	heap->size = 0;
	heap->capacity = capacity;
	heap->arr = malloc(sizeof(int) * capacity);

	*adrHeap = heap;
}

void fResize(Heap* heap)
{
	heap->capacity *= 2;
	int * arr = malloc(sizeof(heap->capacity));
	if (heap->arr==NULL)
	{
		printf("no more memory left");
		return;
	}
	heap->arr = arr;
}

void fErase(Heap** adrHeap)
{
	Heap* heap = *adrHeap;
	if (heap== NULL) return;
	if (heap->arr == NULL) return;
	free(heap->arr);
	free(heap);
	heap = NULL;
	*adrHeap = heap;
}

void fPrint(Heap* heap)
{
	int i;
	for (int i = 0; i < heap->size; ++i)
	{
		printf("%d ", (*heap).arr[i]);
	}
}

void fParent(Heap* heap, int child, int* adrParent)
{
	if (child >= heap->size)
	{
		*adrParent = -1;
		return;
	}
	*adrParent = (child-1)/2;
}

void fLeftChild(Heap* heap, int parent, int* adrLeftChild)
{
	int leftChild=-1;
	if (leftChild < heap->size && parent >= 0)
	{
		leftChild = 2 * parent + 1;

	}
	*adrLeftChild = leftChild;
}

void fRightChild(Heap* heap, int parent, int* adrRightChild)
{
	int rightChild=-1;
	if (rightChild < heap->size && parent >= 0)
	{
		rightChild = 2 * parent + 2;

	}
	*adrRightChild = rightChild;
}

void fFindMinim(Heap* heap,int* adrMinim)
{
	if (heap->size == 0)
	{
		*adrMinim = INT_MAX;
	}
	*adrMinim = heap->arr[0];
}

void fSwap(int* adrA, int* adrB)
{
	int aux = *adrA;
	*adrA = *adrB;
	*adrB = aux;
}

void fHeapifyDown(Heap* heap,int pos)
{
	int isHeapified = 0;
	int leftChild, rightChild, posMin = pos;

	while (!isHeapified)
	{
		isHeapified = 1;
		posMin = pos;
		fLeftChild(heap, pos, &leftChild);
		fRightChild(heap, pos, &rightChild);
		if (leftChild == -1 || rightChild == -1)
		{
			return;
		}
		int* arr = heap->arr;
		if (leftChild != -1)
		{
			if (arr[leftChild] < arr[posMin])
			{
				posMin = leftChild;
			}
		}
		if (rightChild != -1)
		{
			if (arr[rightChild] < arr[posMin])
			{
				posMin = rightChild;
			}
		}
		if (posMin != pos)
		{
			fSwap(&heap->arr[pos], &heap->arr[posMin]);
			isHeapified = 0;
			pos = posMin;
		}
	}

	
}
void fHeapifyUp(Heap* heap,int pos)
{
	int isHeapified = 0;
	int parent, posMin = pos;

	while (!isHeapified)
	{
		isHeapified = 1;
		posMin = pos;
		fParent(heap, pos, &parent);
		if (parent == -1)
		{
			return;
		}
		int* arr = heap->arr;
			
		if (arr[parent] < arr[posMin])
		{
			posMin = parent;
		}
		
		if (posMin != pos)
		{
			fSwap(&heap->arr[pos], &heap->arr[posMin]);
			isHeapified = 0;
			pos = posMin;
		}
	}

	
}

int main()
{
	Heap* heap = NULL;
	int capacity;
	printf("capacitatea : ");
	scanf("%d", &capacity);
	fCreateHeap(&heap, capacity);
	fResize(heap);
	
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
