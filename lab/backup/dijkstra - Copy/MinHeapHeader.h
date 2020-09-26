#pragma once

#ifndef MINHEAPHEADER

#define _CRT_SECURE_NO_WARNINGS
#define MINHEAPHEADER
#include<stdio.h>
#include<stdlib.h>

typedef struct Heap Heap;
struct Heap
{
	int size, capacity, * arr;
};

typedef struct HeapNode HeapNode;
struct HeapNode
{
	int index;
	int dist;
};

void fInitHeap(Heap** adrHeap, int capacity);

void fResize(Heap* heap);

void fErase(Heap** adrHeap);

void fPrint(Heap* heap);

void fParent(Heap* heap, int child, int* adrParent);

void fLeftChild(Heap* heap, int parent, int* adrLeftChild);

void fRightChild(Heap* heap, int parent, int* adrRightChild);

void fFindMinim(Heap* heap, int* adrMinim);

void fSwap(int* adrA, int* adrB);

void fHeapifyDown(Heap* heap, int pos);

void fHeapifyUp(Heap* heap, int pos);

void fInsertKeyInHeap(Heap* heap, int key);

void fDeleteNode(Heap* heap, int pos);

void fHeapSort(Heap* heap);

#endif