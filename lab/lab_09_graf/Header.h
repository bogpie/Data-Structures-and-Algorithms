#pragma once


#ifndef HEADER
#define HEADER

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct GraphMat GraphMat;
struct GraphMat
{
	int nrVertexes;
	int nrEdges;
	int** mat;
};

typedef struct ListNode ListNode;
struct ListNode
{
	int index;
	struct ListNode* next;
};

typedef struct GraphList GraphList;
struct GraphList
{
	int nrVertexes;
	int nrEdges;
	ListNode** vLists;
};

void fPointerTest(void* ptr);
void fCreateGraphMat(GraphMat* graphMat, int orientat);
void fInsertEdge(GraphList* graphList, int i, int j);
void fInitGraphList(GraphList** adrGraphList, int nrVertexes);
void fMatToList(GraphMat* graphMat, GraphList** adrGraphList);
void fListToMat(GraphList* graphList, GraphMat** adrGraphMat);
void fEraseGraphMat(GraphMat* graphMat);
void fPrintGraphList(GraphList* graphList);
void fPrintGraphMat(GraphMat* graphMat);
void fFindNeighbourList(GraphList* graphList, int x);
void fFindNeighbourMat(GraphMat* graphMat, int x);
void fInitGraphMat(GraphMat** adrGraphMat, int nrVertexes);
void fEraseGraphList(GraphList* graphList);
void fTestEdgeMat(GraphMat* graphMat, int x, int y);
void fTestEdgeList(GraphList* graphList, int x, int y);
void fCopyMat(int** sourceMat, int*** adrDestMat, int nrVertexes);
void fRoy(GraphMat* graphMat, int nrVertexes);

#endif