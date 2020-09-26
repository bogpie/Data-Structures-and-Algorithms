#pragma once

#ifndef GRAPHHEADER
#define GRAPHHEADER


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
void fCreateGraphMat(GraphMat* graphMat, FILE* input);
void fEraseGraphMat(GraphMat* graphMat);
void fPrintGraphMat(GraphMat* graphMat);
void fFindNeighbourMat(FILE* output,GraphMat* graphMat, int x);
void fInitGraphMat(GraphMat** adrGraphMat, int nrVertexes, int nrEdges);
int fTestEdgeMat(GraphMat* graphMat, int x, int y);

#endif