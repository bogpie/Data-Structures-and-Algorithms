#include "MainHeader.h"


void fCreateGraphMat(GraphMat* graphMat, FILE* input)
{
	int iEdge;
	for (iEdge = 0; iEdge < graphMat->nrEdges; ++iEdge)
	{
		char leftName[NAMELENGTH], rightName[NAMELENGTH];
		int leftIndex, rightIndex, cost;
		char aux[3];
		fscanf(input, "%s%s%s%d", leftName, aux, rightName, &cost);
		fNameToIndex(leftName, &leftIndex);
		fNameToIndex(rightName, &rightIndex);
		graphMat->mat[leftIndex][rightIndex] = cost;
		graphMat->mat[rightIndex][leftIndex] = cost;
	}
}

void fCreateGraphMatOld(GraphMat* graphMat, int orientat)
{
	printf("\nnr noduri:");
	int nrVertexes = graphMat->nrVertexes;

	graphMat->nrEdges = 0;
	int i;
	for (i = 0; i < nrVertexes; ++i)
	{
		int j;
		for (j = 0; j < nrVertexes; ++j)
		{
			if (i == j || graphMat->mat[i][j] == 1 || (orientat == 0 && i > j))
			{
				continue;
			}
			printf("\narc de la %d la %d ( valoare boolean ) : ", i, j);
			scanf("%d", &graphMat->mat[i][j]);
			if (graphMat->mat[i][j])
			{
				++graphMat->nrEdges;
			}

			if (!orientat)
			{
				graphMat->mat[j][i] = graphMat->mat[i][j];
				++graphMat->nrEdges;
			}
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

void fInitGraphList(GraphList** adrGraphList, int nrVertexes, int nrEdges)
{
	GraphList* graphList = *adrGraphList;
	graphList = malloc(sizeof(GraphList));
	graphList->nrEdges = 0;
	graphList->nrVertexes = nrVertexes;
	graphList->vLists = malloc(sizeof(ListNode*) * nrVertexes + 1);
	*adrGraphList = graphList;

	int i;
	for (i = 0; i < nrVertexes; ++i)
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

	int nrVertexes = graphList->nrVertexes = graphMat->nrVertexes;
	graphList->nrEdges = graphMat->nrEdges;
	int i;
	for (i = 0; i < nrVertexes; ++i)
	{
		int j;
		for (j = 0; j < nrVertexes; ++j)
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
	int i;
	for (i = 0; i < nrVertexes; ++i)
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
	int i;
	for (i = 0; i < graphMat->nrVertexes; ++i)
	{
		int j;
		for (j = 0; j < graphMat->nrVertexes; ++j)
		{
			graphMat->mat[i][j] = 0;
		}
		if (graphMat->mat[i] != NULL)
		{
			free(graphMat->mat[i]);
		}
	}
	graphMat->nrEdges = 0;
	graphMat->nrVertexes = 0;
	free(graphMat);

}

void fPrintGraphList(GraphList* graphList)
{
	int i;
	for (i = 0; i < graphList->nrVertexes; ++i)
	{
		ListNode* listNode = graphList->vLists[i];
		printf("\nincidente cu %d: ", graphList->vLists[i]->index);

		if (listNode == NULL)
		{
			continue;
		}

		listNode = listNode->next;
		while (listNode != NULL)
		{
			printf("%d ", listNode->index);
			listNode = listNode->next;
		}
	}
}

void fPrintGraphMat(GraphMat* graphMat)
{
	int nrVertexes = graphMat->nrVertexes;
	int i;
	for (i = 0; i < nrVertexes; ++i)
	{
		printf("\nincidente cu %d: ", i);
		int j;
		for (j = 0; j < nrVertexes; ++j)
		{
			if (graphMat->mat[i][j] == 1)
			{
				printf("%d ", j);
			}
		}
	}
}

void fFindNeighbourList(GraphList* graphList, int x)
{
	ListNode* listNode = graphList->vLists[x];
	printf("\nincidente cu %d: ", graphList->vLists[x]->index);
	listNode = listNode->next;
	while (listNode != NULL)
	{
		printf("%d ", listNode->index);
		listNode = listNode->next;
	}
}

void fFindNeighbourMat(FILE* output,GraphMat* graphMat, int x)
{
	int nrVertexes = graphMat->nrVertexes;
	//printf("\nincidente cu %d: ", x);
	int j;
	for (j = 1; j <= nrVertexes; ++j)
	{
		if (graphMat->mat[x][j] != 0)
		{
			fprintf(output, "Island%d ", j);
		}
	}
	fprintf(output, "\n");
}

void fInitGraphMat(GraphMat** adrGraphMat, int nrVertexes, int nrEdges)
{
	GraphMat* graphMat = malloc(sizeof(GraphMat));
	fPointerTest(graphMat);
	*adrGraphMat = graphMat;
	graphMat->mat = calloc(nrVertexes + 1, sizeof(int*)); // indexare in input de la 1
	graphMat->nrVertexes = nrVertexes;
	graphMat->nrEdges = nrEdges;
	int i;
	for (i = 1; i <= nrVertexes; ++i) // indexare in input de la 1
	{
		graphMat->mat[i] = calloc(nrVertexes + 1, sizeof(int));
	}

	fPointerTest(graphMat->mat);
}

void fEraseGraphList(GraphList* graphList)
{
	int i;
	for (i = 0; i < graphList->nrVertexes; ++i)
	{
		ListNode* listNode = graphList->vLists[i];
		while (listNode != NULL)
		{
			ListNode* oldNode = listNode;
			listNode = oldNode->next;
			if (oldNode != NULL)
			{
				oldNode->index = 0;
				oldNode = NULL;
				free(oldNode);
			}
		}
	}
	if (graphList->vLists != NULL)
	{
		free(graphList->vLists);
	}

	graphList->nrEdges = graphList->nrVertexes = 0;
	free(graphList);
}

int fTestEdgeMat(GraphMat* graphMat, int x, int y)
{
	//printf("\ntest pe graficul cu matrice: ");
	if (graphMat->mat[x][y] && graphMat->mat[y][x])
	{
		return 1;
	}
	return 0;
}

void fTestEdgeList(GraphList* graphList, int x, int y)
{
	printf("\ntest pe graficul cu lista: ");
	int i;
	for (i = 0; i < graphList->nrVertexes; ++i)
	{
		int index1 = graphList->vLists[i]->index;
		if (index1 == x)
		{
			ListNode* listNode = graphList->vLists[i];
			while (listNode)
			{
				if (listNode->index == y)
				{
					printf(" exista muchie");
					return;
				}
				listNode = listNode->next;
			}
			break;
		}
	}
	printf(" nu exista muchie");
	return;
}

void fCopyMat(int** sourceMat, int*** adrDestMat, int nrVertexes)
{
	int** destMat = *adrDestMat;
	int i;
	for (i = 0; i < nrVertexes; ++i)
	{
		int j;
		for (j = 0; j < nrVertexes; ++j)
		{
			destMat[i][j] = sourceMat[i][j];
		}
	}
	*adrDestMat = destMat;
}

void fRoy(GraphMat* graphMat, int nrVertexes)
{
	int** pathMat;
	pathMat = calloc(nrVertexes, sizeof(int*));
	int i;
	for (i = 0; i < nrVertexes; ++i)
	{
		pathMat[i] = calloc(nrVertexes, sizeof(int));
	}
	fCopyMat(graphMat->mat, &pathMat, nrVertexes);
	int index1;
	for (index1 = 0; index1 < nrVertexes; ++index1)
	{
		int index2;
		for (index2 = 0; index2 < nrVertexes; ++index2)
		{
			if (index1 == index2) continue;
			int intermediar;
			for (intermediar = 0; intermediar < nrVertexes; ++intermediar)
			{
				if (pathMat[index1][index2]) continue;
				if (pathMat[index1][intermediar] == 1 && pathMat[intermediar][index2] == 1)
				{
					pathMat[index1][index2] = 1;
				}
			}
		}
	}

	for (index1 = 0; index1 < nrVertexes; ++index1)
	{
		printf("\nexista drum de la %d la : ", index1);
		int index2;
		for (index2 = 0; index2 < nrVertexes; ++index2)
		{
			if (pathMat[index1][index2])
			{
				printf("%d ", index2);
			}
		}
	}
}
