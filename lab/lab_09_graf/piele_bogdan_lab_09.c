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

void fPointerTest(void* ptr)
{
	if (ptr == NULL)
	{
		exit(1);
	}
}

void fCreateGraphMat(GraphMat* graphMat)
{
	printf("\nnr noduri:");
	int nrVertexes = graphMat->nrVertexes;
	
	graphMat->nrEdges = 0;
	for (int i = 0; i < nrVertexes; ++i)
	{
		for (int j = i + 1; j < nrVertexes; ++j)
		{
			printf("\n arc de la %d la %d ( valoare boolean ) : ", i, j);
			scanf("%d", &graphMat->mat[i][j]);
			if (graphMat->mat[i][j])
			{
				graphMat->nrEdges += 2;
			}
			graphMat->mat[j][i] = graphMat->mat[i][j];
		}
	}
}

void fInsertEdge(GraphList* graphList, int i, int j)
{
	ListNode* newListNode = malloc(sizeof(newListNode));
	newListNode->next = NULL;
	newListNode->index = j;
	ListNode* oldNext = graphList->vLists[i]->next;
	graphList->vLists[i]->next = newListNode;
	newListNode->next = oldNext;

}


void fInitGraphList(GraphList** adrGraphList, int nrVertexes)
{
	GraphList* graphList = *adrGraphList;
	graphList = malloc(sizeof(GraphList));
	graphList->nrEdges = 0;
	graphList->nrVertexes = 0;
	graphList->vLists = malloc(sizeof(ListNode*) * nrVertexes);
	*adrGraphList = graphList;

	for (int i = 0; i < nrVertexes; ++i)
	{
		graphList->vLists[i] = malloc(sizeof(ListNode*));
		graphList->vLists[i]->index = i;
		graphList->vLists[i]->next = NULL;
	}
	*adrGraphList = graphList;
}

void fMatToList(GraphMat* graphMat, GraphList** adrGraphList)
{
	GraphList* graphList = *adrGraphList;

	int nrVertexes = graphList->nrVertexes=graphMat->nrVertexes;
	graphList->nrEdges = graphMat->nrEdges;
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

void fListToMat(GraphList* graphList, GraphMat** adrGraphMat)
{
	GraphMat* graphMat = *adrGraphMat;
	int nrVertexes = graphMat->nrVertexes = graphList->nrVertexes;
	graphMat->nrEdges = graphMat->nrEdges;
	for (int i = 0; i < nrVertexes; ++i)
	{
		int index1 = graphList->vLists[i]->index;
		ListNode* listNode = graphList->vLists[i]->next;
		while (listNode)
		{
			int index2 = listNode->index;
			graphMat->mat[index1][index2] = 1;
			listNode = listNode->next;
		}
	}
}

void fEraseGraphMat(GraphMat* graphMat)
{
	for (int i = 0; i < graphMat->nrVertexes; ++i)
	{
		int j;
		for (j = 0; j < graphMat->nrVertexes; ++j);
		{
			graphMat->mat[i][j] = 0;
		}
		/*
		if (graphMat->mat[i] != NULL)
		{
			free(graphMat->mat[i]);
		}
		*/
	}
	free(graphMat);
	graphMat->nrEdges = 0;
	graphMat->nrVertexes = 0;
}

void fPrintGraphList(GraphList* graphList)
{
	for (int i = 0; i < graphList->nrVertexes; ++i)
	{
		ListNode* listNode = graphList->vLists[i];
		printf("\n%d: ",graphList->vLists[i]->index);
		listNode = listNode->next;
		while (listNode!=NULL)
		{
			printf("%d ", listNode->index);
			listNode = listNode->next;
		}
		printf("\n");
	}
}

void fPrintGraphMat(GraphMat* graphMat)
{
	int nrVertexes = graphMat->nrVertexes;
	for (int i = 0; i < nrVertexes; ++i)
	{
		for (int j = 0; j < nrVertexes; ++j)
		{
			printf("%d ",graphMat->mat[i][j]);
		}
		printf("\n");
	}
}

void fInitGraphMat(GraphMat** adrGraphMat,int nrVertexes)
{
	GraphMat* graphMat = malloc(sizeof(GraphMat));
	fPointerTest(graphMat);
	*adrGraphMat = graphMat;
	graphMat->mat = calloc(nrVertexes, sizeof(int*));

	for (int i = 0; i < nrVertexes; ++i)
	{
		graphMat->mat[i] = calloc(nrVertexes, sizeof(int));
	}

	fPointerTest(graphMat->mat);
}

int main()
{
	printf("se vor crea grafuri neorientate cu noduri de la 0 la nr de noduri-1");
	GraphMat* graphMat = NULL;
	GraphList* graphList = NULL;	// le initializez in functiile de jos
	int nrVertexes;
	printf("\nnr de noduri:");
	scanf("%d", &nrVertexes);
	fInitGraphMat(&graphMat, nrVertexes);

	fCreateGraphMat(graphMat);
	fInitGraphList(&graphList, graphMat->nrVertexes);
	fMatToList(graphMat, &graphList);
	printf("\nam creat graful cu liste din graful cu matrice (de adiacenta):\n");
	fPrintGraphList(graphList);

	fEraseGraphMat(graphMat);
	fInitGraphMat(&graphMat,nrVertexes);
	fListToMat(graphList, &graphMat);
	printf("\nam creat graful cu matrice din graful cu liste:\n");
	fPrintGraphMat(graphMat);

	return 0;
}