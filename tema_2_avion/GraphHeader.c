#include "MainHeader.h"


void fCreateGraphMat(GraphMat* graphMat, FILE* input)
{
	int iEdge;
	for (iEdge = 0; iEdge < graphMat->nrEdges; ++iEdge)
	{
		char leftName[NAMELENGTH], rightName[NAMELENGTH];
		int idLeft, idRight, cost;
		char aux[3];
		fscanf(input, "%s%s%s%d", leftName, aux, rightName, &cost);
		fNameToIndex(leftName, &idLeft);
		fNameToIndex(rightName, &idRight);
		graphMat->mat[idLeft][idRight] = cost;
		graphMat->mat[idRight][idLeft] = cost;
	}
}

void fEraseGraphMat(GraphMat* graphMat)
{
	int i;
	for (i = 1; i <= graphMat->nrVertexes; ++i)
	{
		if (graphMat->mat[i] == NULL) continue;
		//int j; for (j = 1; j <= graphMat->nrVertexes; ++j) graphMat->mat[i][j] = 0;
		free(graphMat->mat[i]);
	}
	//graphMat->nrEdges = 0; graphMat->nrVertexes = 0;
	if (graphMat != NULL) free(graphMat);
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

void fFindNeighbourMat(FILE* output, GraphMat* graphMat, int x)
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
	graphMat->mat = calloc(nrVertexes + 1, sizeof(int*)); // indexare in input de la 1
	graphMat->nrVertexes = nrVertexes;
	graphMat->nrEdges = nrEdges;
	int i;
	for (i = 1; i <= nrVertexes; ++i) // indexare in input de la 1
	{
		graphMat->mat[i] = calloc(nrVertexes + 1, sizeof(int));
	}

	fPointerTest(graphMat->mat);
	*adrGraphMat = graphMat;
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

