#include "MainHeader.h"

void fInitHeap(Heap** adrHeap, int capacity)
{
	Heap* heap = malloc(sizeof(Heap));
	if (heap == NULL)
	{
		exit(1);
	}
	heap->size = 0;
	capacity = 30;
	heap->capacity = capacity;
	heap->arr = malloc(capacity*sizeof(int));
	*adrHeap = heap;
}

void fResize(Heap* heap)
{
	heap->capacity *= 2;
	HeapNode** arr = realloc(heap->arr, heap->capacity * sizeof(HeapNode*));
	if (arr == NULL)
	{
		printf("no more memory left");
		free(arr);
		exit(1);
	}
	else
	{
		heap->arr = arr;

	}
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
		printf("%d ", (*heap).arr[i]->index);
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
	*adrMinim = heap->arr[0]->index;
}

void fSwap(HeapNode** adrA, HeapNode** adrB)
{
	//interschimbare
	HeapNode* aux = *adrA;
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
		if (leftChild == -1 && rightChild == -1)
		{
			return;
		}
		HeapNode** arr = heap->arr;
		if (leftChild != -1)
		{
			if (arr[leftChild]->dist < arr[posMin]->dist)
			{
				posMin = leftChild;
			}
		}
		if (rightChild != -1)
		{
			if (arr[rightChild]->dist < arr[posMin]->dist)
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
		HeapNode** arr = heap->arr;

		if (arr[parent]->dist > arr[posMax]->dist)
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

void fInsertInHeap(Heap* heap, HeapNode* heapNode)
{
	int pos;
	if (heap->size >= heap->capacity)
	{
		fResize(heap);
	}

	pos = heap->size++;
	heap->arr[pos] = heapNode;

	fHeapifyUp(heap, pos);
}

void fDeleteNode(Heap* heap, int pos)
{
	int lastPos = heap->size - 1;
	fSwap(&heap->arr[lastPos], &heap->arr[pos]); // pt pastrarea proprietatii de arbore complet

	int parent;
	fParent(heap, pos, &parent);

	heap->arr[heap->size - 1]->dist = heap->arr[heap->size - 1]->index = 0;
	--heap->size;

	if (heap->arr[pos] < heap->arr[parent])
	{
		fHeapifyUp(heap, pos);
	}
	else
	{
		fHeapifyDown(heap, pos);
	}
}

void fFindInHeap(Heap* heap, int searchedIndex, int* adrFoundPosition, int* adrCrtTime)
{
	int i;

	for (i = 0; i < heap->size; ++i)
	{
		if (heap->arr[i]->index == searchedIndex)
		{
			*adrCrtTime = heap->arr[i]->dist;
			*adrFoundPosition = i;
			return;
		}
	}
	*adrFoundPosition = -1;
	return;
}

void fHeapSort(Heap* heap)
{
	int n = heap->size;
	while (n > heap->capacity)
	{
		fResize(heap);
	}
	int i;
	for (i = (n - 1) / 2; i >= 0; --i)
	{
		fHeapifyDown(heap, i);
	}
	// a fost verificata proprietatea de minheap
	// se ignora frunzele in cernerea in jos (nu au subarbori => subarborii de un singur element deja respecta proprietatea)

	while (heap->size > 0)
	{
		n = heap->size;
		int poppedIndex = heap->arr[0]->index;
		int poppedDist = heap->arr[0]->dist;
		fDeleteNode(heap, 0); // care modifica si heap->size

		heap->arr[heap->size]->index = poppedIndex;
		heap->arr[heap->size]->dist = poppedDist;
		// stergerea presupune in functia mea decrementarea size-ului heap-ului si modificarea valorii de sters cu 0
		// asa ca, pentru o eventuala afisare sortata, trebuie resetata valoarea ultimului nod de la 0 la valoarea gasita (nu vrem sa se piarda)
		// ea va fi ignorata la urmatoarele operatii pe arbore (pentru ca heap->size tocmai a fost decrementat)

		fHeapifyDown(heap, 0);
	}

}

void fEraseHeap(Heap* heap)
{
	if (heap->arr)
	{
		for (int i = 0; i < heap->size; ++i)
		{
			if (heap->arr[i])
			{
				free(heap->arr[i]);
			}
		}
		free(heap->arr);
	}
	free(heap);

}