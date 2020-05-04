#include "MainHeader.h"

void fReadIslands(FILE* input, int* adrNrIslands, Island** adrVectorIslands)
{
	int nrIslands = 0;
	fscanf(input, "%d", &nrIslands);
	*adrNrIslands = nrIslands;

	Island* vIslands = malloc(sizeof(Island) * (nrIslands + 1)); //indexarea insulelor in input e de al 1




	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		char vChar[NAMELENGTH];
		Island island;

		fscanf(input, "%s", vChar);



		fStrAlloc(&island.name, vChar);

		//fscanf(input, "%s", vChar);island.nrResources = atoi(vChar);
		fscanf(input, "%d", &island.nrResources);

		island.vResources = malloc(sizeof(Resource) * island.nrResources);
		for (int idResource = 0; idResource < island.nrResources; ++idResource)
		{
			Resource resource;
			fscanf(input, "%s", vChar);
			fStrAlloc(&resource.name, vChar);
			//fscanf(input, "%s", vChar); resource.quantity = atoi(vChar);
			fscanf(input, "%d", &resource.quantity);
			island.vResources[idResource] = resource;

		}

		vIslands[idIsland] = island;
	}
	*adrNrIslands = nrIslands;
	*adrVectorIslands = vIslands;

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

void fSolveConexiune(FILE* input, FILE* output, GraphMat* graphMat)
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	fscanf(input, "%s", leftName);
	fscanf(input, "%s", rightName);
	int leftIndex, rightIndex;
	fNameToIndex(leftName, &leftIndex);
	fNameToIndex(rightName, &rightIndex);
	if (fTestEdgeMat(graphMat, leftIndex, rightIndex))
	{
		fprintf(output, "OK\n");
	}
	else
	{
		fprintf(output, "NO\n");
	}
}

void fSolveLegatura(FILE* input, FILE* output, GraphMat* graphMat)
{
	char islandName[NAMELENGTH];
	fscanf(input, "%s", islandName);
	int islandIndex = islandName[strlen(islandName) - 1] - '0';
	fFindNeighbourMat(output, graphMat, islandIndex);
}

void fSolveMaxResurse(FILE* input, FILE* output, int nrIslands, Island* vIslands)
{
	TrieNode* trieRoot;
	fInitTrieNode(&trieRoot);

	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		Island island = vIslands[idIsland];
		for (int idResource = 0; idResource < island.nrResources; ++idResource)
		{
			Resource resource = island.vResources[idResource];
			fInsertInTrie(resource.name, trieRoot);
		}
	}
	char* word = malloc(NAMELENGTH);
	int nrResources = 0;
	fCountTrie(trieRoot, 0, &nrResources);
	fprintf(output, "%d ", nrResources);
	fPrintTrie(output, trieRoot, word, 0);
	fprintf(output, "\n");
}

void fSolveAdaugaZbor(FILE* input, GraphMat* graphMat) //move to graphheader??
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	int cost;
	fscanf(input, "%s%s%d", leftName, rightName, &cost);
	int leftIndex, rightIndex;
	fNameToIndex(leftName, &leftIndex);
	fNameToIndex(rightName, &rightIndex);
	graphMat->mat[leftIndex][rightIndex] = graphMat->mat[rightIndex][leftIndex] = cost;
	graphMat->nrEdges++;
}

void fSolveAnulareZbor(FILE* input, GraphMat* graphMat)
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	int cost;
	fscanf(input, "%s%s%d", leftName, rightName, &cost);
	int leftIndex, rightIndex;
	fNameToIndex(leftName, &leftIndex);
	fNameToIndex(rightName, &rightIndex);
	graphMat->mat[leftIndex][rightIndex] = graphMat->mat[rightIndex][leftIndex] = 0;
}

void fSolveMaxCantitate(FILE* input, FILE* output, int nrIslands, Island* vIslands)
{
	char searched[NAMELENGTH];
	int maxim = -1;
	fscanf(input, "%s", searched);
	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
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
	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
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
					fprintf(output, "%s ", island.name);
					break;
				}
			}
		}
	}
	fprintf(output, "\n");
}

void fSolveDrumZbor(FILE* input, FILE* output, GraphMat* graphMat) /// lipeste !!
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	fscanf(input, "%s%s", leftName, rightName);
	int leftIndex, rightIndex;
	fNameToIndex(leftName, &leftIndex);
	fNameToIndex(rightName, &rightIndex);
	int time = INT_MAX;
	int* vPrev = malloc(sizeof(int) * (graphMat->nrVertexes + 1));
	fDijkstra(graphMat, leftIndex, rightIndex, &time, vPrev, 0);
	//printf("\nde la nodul sursa %d la nodurile:", source);
	if (time != INT_MAX)
	{
		fPrintPath(output, vPrev, leftIndex, rightIndex);
	}
	else
	{
		fprintf(output, "NO");
	}
	fprintf(output, "\n");
}

void fSolveTimpZbor(FILE* input, FILE* output, GraphMat* graphMat)
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	fscanf(input, "%s%s", leftName, rightName);
	int leftIndex, rightIndex;
	fNameToIndex(leftName, &leftIndex);
	fNameToIndex(rightName, &rightIndex);
	int time = INT_MAX;
	int* vPrev = malloc(sizeof(int) * (graphMat->nrVertexes + 1));
	fDijkstra(graphMat, leftIndex, rightIndex, &time, vPrev, 0);

	if (time == INT_MAX)
	{
		fprintf(output, "INF\n");

	}
	else
	{
		fprintf(output, "%d\n", time);
	}
}

void fSolveMinZbor(FILE* input, FILE* output, GraphMat* graphMat)
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	fscanf(input, "%s%s", leftName, rightName);
	int leftIndex, rightIndex;
	fNameToIndex(leftName, &leftIndex);
	fNameToIndex(rightName, &rightIndex);
	int time;
	int* vPrev = malloc(sizeof(int) * (graphMat->nrVertexes + 1));
	fDijkstra(graphMat, leftIndex, rightIndex, &time, vPrev, 15);
	fprintf(output, "%d\n", time);
}

void fNameToIndex(char* name, int* adrIndex)
{
	int firstDigit = name[strlen(name) - 2] - '0';
	int secondDigit = name[strlen(name) - 1] - '0';
	*adrIndex = firstDigit * (firstDigit > 0 && firstDigit < 9) * 10 + secondDigit;
}