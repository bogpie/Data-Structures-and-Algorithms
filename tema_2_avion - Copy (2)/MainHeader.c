#include "MainHeader.h"

void fReadIslands(FILE* input, int* adrNrIslands, Island** adrVectorIslands)
{
	int nrIslands = 0;
	Island* vIslands = malloc(sizeof(Island) * nrIslands + 1); //indexarea insulelor in input e de al 1

	fscanf(input, "%d", &nrIslands);

	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		char vChar[NAMELENGTH];
		Island island;

		fgets(vChar, NAMELENGTH, input);
		while (vChar[0] != '\n');

		while (vChar[0] != 'I')
		{
			fscanf(input, "%s", vChar);
		}

		fStrAlloc(&island.name, vChar);

		fscanf(input, "%d", &island.nrResources);
		island.vResources = malloc(sizeof(Resource) * island.nrResources);
		for (int idResource = 0; idResource < island.nrResources; ++idResource)
		{
			Resource resource;// optional
			//char vChar[NAMELENGTH];
			fscanf(input, "%s%d", vChar, &resource.quantity);
			fStrAlloc(&resource.name, vChar);
			island.vResources[idResource] = resource;
		}
		char breakLine;
		
		fscanf(input, "%c", &breakLine);
		if (breakLine != '\n')
		{
			fscanf(input, "%c", &breakLine);
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
	fFindNeighbourMat(output,graphMat, islandIndex);
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
	char* word = NULL;
	int nrResources = 0;
	fprintf(output, "\n");
	fPrintTrie(output,trieRoot, word, 0, &nrResources);
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

void fSolveMaxCantitate(FILE* input, FILE* output, int nrIslands, Island* vIslands)
{
	char searched[NAMELENGTH];
	int maxim = -1;
	fscanf(input, "%s", searched);
	fprintf(output, "\n");
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

}

void fSolveTimpZbor(FILE* input, GraphMat* graphMat)
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	int cost;
	fscanf(input, "%s%s%d", leftName, rightName, &cost);
	int leftIndex, rightIndex;
	fNameToIndex(leftName, &leftIndex);
	fNameToIndex(rightName, &rightIndex);
	int time;

	fDijkstra(graphMat, leftIndex, rightIndex, &time, 0);
}

void fSolveMinZbor(FILE* input, GraphMat* graphMat)
{
	char leftName[NAMELENGTH], rightName[NAMELENGTH];
	int cost;
	fscanf(input, "%s%s%d", leftName, rightName, &cost);
	int leftIndex, rightIndex;
	fNameToIndex(leftName, &leftIndex);
	fNameToIndex(rightName, &rightIndex);
	int time;

	fDijkstra(graphMat, leftIndex, rightIndex, &time, 15);
}

void fNameToIndex(char* name, int* adrIndex)
{
	int firstDigit = name[strlen(name) - 2] - '0';
	int secondDigit = name[strlen(name) - 1] - '0';
	*adrIndex = firstDigit * (firstDigit > 0 && firstDigit < 9) * 10 + secondDigit;
}