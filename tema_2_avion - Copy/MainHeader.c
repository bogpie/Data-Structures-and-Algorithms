#include "MainHeader.h"

void fReadIslands(FILE* input, int* adrNrIslands, Island* vIslands)
{
	int nrIslands = 0;
	fscanf(input, "%d", &nrIslands);

	for (int idIsland = 0; idIsland < nrIslands; ++idIsland)
	{
		char vChar[NAMELENGTH];
		Island island;

		fscanf(input, "%s", &vChar);
		fStrAlloc(&island.name, vChar);

		fscanf(input, "%d", &island.nrResources);
		island.vResources = malloc(sizeof(Resource) * island.nrResources);
		for (int idResource = 0; idResource < island.nrResources; ++idResource)
		{
			Resource resource;// optional
			char vChar[NAMELENGTH];
			fscanf(input, "%s%d", vChar, &resource.quantity);
			fStrAlloc(&resource.name, vChar);
			island.vResources[idResource] = resource;
		}

		vIslands[idIsland] = island;
	}
	*adrNrIslands = nrIslands;

}

void fReadConnections(FILE* input, int nrIslands, GraphMat** adrGraphMat)
{
	GraphMat* graphMat;
	int nrEdges;
	fscanf(input, "%d", &nrEdges);
	fInitGraphMat(&graphMat, nrIslands, nrEdges);
	fCreateGraphMat(graphMat, input);
	*adrGraphMat = graphMat;
}

void fSolveConexiune(FILE* input, GraphMat* graphMat)
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	fscanf(input, "%s%s", leftName, rightName);
	int leftIndex = leftName[strlen(leftName) - 1] - '0';
	int rightIndex = rightName[strlen(rightName) - 1] - '0';
	if (fTestEdgeMat(graphMat, leftIndex, rightIndex))
	{
		fprintf(input, "OK");
	}
	else
	{
		fprintf(input, "NO");
	}
}

void fSolveLegatura(FILE* input, GraphMat* graphMat)
{
	char islandName[NAMELENGTH];
	fscanf(input, "%s", islandName);
	int islandIndex = islandName[strlen(islandName) - 1] - '0';
	fprintf(input, "\n");
	fFindNeighbourMat(graphMat, islandIndex);
}

void fSolveMaxResurse(FILE* input, int nrIslands, Island* vIslands)
{
	TrieNode* trieRoot;
	fInitTrieNode(&trieRoot);

	for (int idIsland = 0; idIsland < nrIslands; ++idIsland)
	{
		Island island = vIslands[idIsland];
		for (int idResource = 0; idResource < island.nrResources; ++idResource)
		{
			Resource resource = island.vResources[idResource];
			fInsertInTrie(resource.name, trieRoot);
		}
	}
	char* word = NULL;
	int nrResources = 0;
	fprintf(input, "\n");
	fPrintTrie(trieRoot, word, 0, nrResources);
}

void fSolveAdaugaZbor(FILE* input, GraphMat* graphMat) //move to graphheader??
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	int cost;
	fscanf(input, "%s%s%d", leftName, rightName, &cost);
	int leftIndex = leftName[strlen(leftName) - 1] - '0';
	int rightIndex = rightName[strlen(rightName) - 1] - '0';
	graphMat->mat[leftIndex][rightIndex] = graphMat->mat[rightIndex][leftIndex] = cost;
}

void fSolveAnulareZbor(FILE* input, GraphMat* graphMat)
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	int cost;
	fscanf(input, "%s%s%d", leftName, rightName, &cost);
	int leftIndex = leftName[strlen(leftName) - 1] - '0';
	int rightIndex = rightName[strlen(rightName) - 1] - '0';
	graphMat->mat[leftIndex][rightIndex] = graphMat->mat[rightIndex][leftIndex] = 0;
}

void fSolveMaxCantitate(FILE* input, int nrIslands, Island* vIslands)
{
	char searched[NAMELENGTH];
	int maxim = -1;
	fscanf(input, "%s", searched);
	fprintf(input, "\n");
	for (int idIsland = 0; idIsland < nrIslands; ++idIsland)
	{
		Island island = vIslands[idIsland];

		int idResource;
		for (idResource = 0; idResource < island.nrResources; ++idResource)
		{
			Resource resource = island.vResources[idResource];
			if (!strcmp(resource.name, searched))
			{
				if (resource.quantity > maxim)
				{
					maxim = resource.quantity;
				}
			}
		}
	}
	for (int idIsland = 0; idIsland < nrIslands; ++idIsland)
	{
		Island island = vIslands[idIsland];

		int idResource;
		for (idResource = 0; idResource < island.nrResources; ++idResource)
		{
			Resource resource = island.vResources[idResource];
			if (!strcmp(resource.name, searched))
			{
				if (resource.quantity == maxim)
				{
					fprintf(input, "%s ", island.name);
					break;
				}
			}
		}
	}

}

void fSolveTimpZbor(FILE* input, GraphMat* graphMat)
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	int cost;
	fscanf(input, "%s%s%d", leftName, rightName, &cost);
	int leftIndex = leftName[strlen(leftName) - 1] - '0';
	int rightIndex = rightName[strlen(rightName) - 1] - '0';
	int time;

	fDijkstra(graphMat, leftIndex, rightIndex, &time,0);
}

void fSolveMinZbor(FILE* input, GraphMat* graphMat)
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	int cost;
	fscanf(input, "%s%s%d", leftName, rightName, &cost);
	int leftIndex = leftName[strlen(leftName) - 1] - '0';
	int rightIndex = rightName[strlen(rightName) - 1] - '0';
	int time;

	fDijkstra(graphMat, leftIndex, rightIndex, &time,15);
}