#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct GraphMat GraphMat;
struct GraphMat
{
	int nrVertexes;
	int nrEdges;
	int** mat;
};

typedef struct Node Node;
struct Node
{
	int index;
	struct Node* next;
};

typedef struct GraphList GraphList;
struct GraphList
{
	int nrVertexes;
	int nrEdges;
	Node** vLists;
};

void fPointerTest(void* ptr)
{
	if (ptr == NULL)
	{
		exit(1);
	}
}

void fCreateGraphMat(GraphMat** adrGraphMat)
{
	GraphMat* graphMat = malloc(sizeof(GraphMat));
	fPointerTest(graphMat);
	printf("\nnr noduri:");
	scanf("%d", &graphMat->nrVertexes);
	int nrVertexes = graphMat->nrVertexes;
	graphMat->mat = calloc(nrVertexes , sizeof(int*));

	for (int i = 0; i < nrVertexes; ++i)
	{
		graphMat->mat[i] = calloc(nrVertexes , sizeof(int));
	}

	fPointerTest(graphMat->mat);
	graphMat->nrEdges = 0;
	for (int i = 0; i < nrVertexes; ++i)
	{
		for (int j = i + 1; j < nrVertexes; ++j)
		{
			printf("\n arc de la %d la %d ( valoare boolean ) : ",i,j);
			scanf("%d", &graphMat->mat[i][j]);
			if (graphMat->mat[i][j])
			{
				graphMat->nrEdges += 2;
			}
			graphMat->mat[j][i] = graphMat->mat[i][j];
		}
	}
	*adrGraphMat = graphMat;
}

void fInsertEdge(GraphList* graphList, int i, int j)
{
	Node* newNode = malloc(sizeof(newNode));
	newNode->next = NULL;
	newNode->index = j;
	Node* oldNext = graphList->vLists[i]->next;
	graphList->vLists[i]->next = newNode;
	newNode->next = oldNext;
	
}


void fInitGraphList(GraphList** adrGraphList,int nrVertexes)
{
	GraphList* graphList = *adrGraphList;
	graphList = malloc(sizeof(GraphList));
	graphList->nrEdges = 0;
	graphList->nrVertexes= 0;
	graphList->vLists = malloc(sizeof(Node*)*nrVertexes);
	*adrGraphList = graphList;

	for (int i = 0; i < nrVertexes; ++i)
	{
		graphList->vLists[i] = malloc(sizeof(Node*));
		graphList->vLists[i]->index = i;
		graphList->vLists[i]->next = NULL;
	}
	*adrGraphList = graphList;
}

void fTransform(GraphMat* graphMat, GraphList** adrGraphList)
{
	GraphList* graphList=*adrGraphList;

	int nrVertexes = graphMat->nrVertexes;
	for (int i = 0; i < nrVertexes; ++i)
	{
		for (int j = 0; j < nrVertexes; ++j)
		{
			if (graphMat->mat[i][j]) //exista arc i--j
			{
				fInsertEdge(graphList, i, j);
			}
		}
	}
	*adrGraphList = graphList;
}


int main()
{
	printf("%d", atoi("-1123"));
	printf("se vor crea grafuri neorientate cu noduri de la 0 la nr de noduri-1");
	GraphMat* graphMat =NULL;
	GraphList* graphList=NULL;	// le initializez in functiile de jos
	fCreateGraphMat(&graphMat);
	fInitGraphList(&graphList,graphMat->nrVertexes);
	fTransform(graphMat, &graphList);
	return 0;
}