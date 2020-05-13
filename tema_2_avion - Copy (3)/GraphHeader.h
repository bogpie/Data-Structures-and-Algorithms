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
void fCreateGraphMatOld(GraphMat* graphMat, int orientat);
void fCreateGraphMat(GraphMat* graphMat, FILE* input);
void fInsertEdge(GraphList* graphList, int i, int j);
void fInitGraphList(GraphList** adrGraphList, int nrVertexes, int nrEdges);
void fMatToList(GraphMat* graphMat, GraphList** adrGraphList);
void fListToMat(GraphList* graphList, GraphMat** adrGraphMat);
void fEraseGraphMat(GraphMat* graphMat);
void fPrintGraphList(GraphList* graphList);
void fPrintGraphMat(GraphMat* graphMat);
void fFindNeighbourList(GraphList* graphList, int x);
void fFindNeighbourMat(FILE* output,GraphMat* graphMat, int x);
void fInitGraphMat(GraphMat** adrGraphMat, int nrVertexes, int nrEdges);
void fEraseGraphList(GraphList* graphList);
int fTestEdgeMat(GraphMat* graphMat, int x, int y);
void fTestEdgeList(GraphList* graphList, int x, int y);
void fCopyMat(int** sourceMat, int*** adrDestMat, int nrVertexes);

#endif