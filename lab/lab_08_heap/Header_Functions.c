#include "Header.h"
#include <limits.h>

void fCreateHeap(Heap** adrHeap, int capacity)
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
	int* arr = realloc(heap->arr,sizeof(int)*heap->capacity);
	if (heap->arr == NULL)
	{
		printf("no more memory left");
		return;
	}
	heap->arr = arr;
}

void fErase(Heap** adrHeap)
{
	Heap* heap = *adrHeap;
	if (heap == NULL) return;
	if (heap->arr == NULL) return;
	free(heap->arr);
	free(heap);
	heap = NULL;
	*adrHeap = heap;
}

void fPrint(Heap* heap)
{
	int i;
	for (i = 0; i < heap->size; ++i)
	{
		printf("%d ", (*heap).arr[i]);
	}
}

void fParent(Heap* heap, int child, int* adrParent)
{
	if (child >= heap->size || child == 0)
	{
		*adrParent = -1;
		return;
	}
	*adrParent = (child - 1) / 2;
}

void fLeftChild(Heap* heap, int parent, int* adrLeftChild)
{
	int leftChild = -1;
	if (parent < heap->size && parent >= 0)
	{
		leftChild = 2 * parent + 1;
	}
	if (leftChild >= heap->size)
	{
		leftChild = -1; // pozitia este in afara arborelui, nodul este frunza
	}

	*adrLeftChild = leftChild;
}

void fRightChild(Heap* heap, int parent, int* adrRightChild)
{
	int rightChild = -1;
	if (parent < heap->size && parent >= 0)
	{
		rightChild = 2 * parent + 2;

	}
	if (rightChild >= heap->size)
	{
		rightChild = -1; // pozitia este in afara arborelui, nodul este frunza
	}
	*adrRightChild = rightChild;
}

void fFindMinim(Heap* heap, int* adrMinim)
{
	if (heap->size == 0)
	{
		*adrMinim = INT_MAX; 
	}
	*adrMinim = heap->arr[0];
}

void fSwap(int* adrA, int* adrB)
{
	//interschimbare
	int aux = *adrA;
	*adrA = *adrB;
	*adrB = aux;
}

void fHeapifyDown(Heap* heap, int pos)
{
	//cernere in jos iterativa
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

void fHeapifyUp(Heap* heap, int pos)
{
	// cernere in sus iterativa
	int isHeapified = 0;
	int parent, posMax = pos;

	while (!isHeapified)
	{
		isHeapified = 1;
		posMax = pos; // (re)initializam pozitia nodului mai mare 
		fParent(heap, pos, &parent);
		if (parent == -1)
		{
			break;
		}
		int* arr = heap->arr;

		if (arr[parent] > arr[posMax])
		{
			posMax = parent;
		}

		if (posMax != pos)
		{
			fSwap(&heap->arr[pos], &heap->arr[posMax]);
			isHeapified = 0;
			pos = posMax;
		}
	}
	return;
}

void fInsert(Heap* heap, int key)
{
	int pos;
	if (heap->size == heap->capacity)
	{
		fResize(heap);
	}

	pos = heap->size++;
	heap->arr[pos] = key;

	fHeapifyUp(heap,pos);
	
}

void fDeleteNode(Heap* heap, int pos)
{
	int lastPos= heap->size - 1;
	fSwap(&heap->arr[lastPos], &heap->arr[pos]); // pt pastrarea proprietatii de arbore complet

	int parent;
	fParent(heap, pos, &parent);

	heap->arr[--heap->size] = 0;

	if (heap->arr[pos] < heap->arr[parent])
	{
		fHeapifyUp(heap, pos);
	}
	else
	{
		fHeapifyDown(heap, pos);
	}
}

void fHeapSort(Heap* heap)
{
	int n = heap->size;	

	/// verificare ca proprietatile heapului sunt in regula definite
	while (n > heap->capacity) 
	{ 
		fResize(heap) ; 
	}	
	for (int i = (n - 1) / 2 - 1; i >= 0; --i)
	{
		fHeapifyDown(heap,i);
	}
	///

	for (int i = n - 1; i >= 0; --i)
	{
		fSwap(&heap->arr[0], &heap->arr[i]); // in 0 mereu minim;
		fHeapifyDown(heap, 0);
	}
}