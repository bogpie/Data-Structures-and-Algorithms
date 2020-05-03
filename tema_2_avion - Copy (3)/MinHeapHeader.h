#pragma once

#ifndef MINHEAPHEADER

#define MINHEAPHEADER


typedef struct HeapNode HeapNode;
struct HeapNode
{
	int index;
	int dist;
};

typedef struct Heap Heap;
struct Heap
{
	int size, capacity;
	HeapNode **arr;
};


void fInitHeap(Heap** adrHeap, int capacity);

void fResize(Heap* heap);

void fErase(Heap** adrHeap);

void fPrint(Heap* heap);

void fParent(Heap* heap, int child, int* adrParent);

void fLeftChild(Heap* heap, int parent, int* adrLeftChild);

void fRightChild(Heap* heap, int parent, int* adrRightChild);

void fFindMinim(Heap* heap, int* adrMinim);

void fSwap(HeapNode** adrA, HeapNode** adrB);

void fHeapifyDown(Heap* heap, int pos);

void fHeapifyUp(Heap* heap, int pos);

void fInsertInHeap(Heap* heap, HeapNode* heapNode);

void fDeleteNode(Heap* heap, int pos);

void fHeapSort(Heap* heap);

void fFindInHeap(Heap* heap, int searchedIndex, int* adrFoundPosition,int *adrCrtTime);

#endif