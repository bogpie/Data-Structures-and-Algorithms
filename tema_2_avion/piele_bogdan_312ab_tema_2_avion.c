#include "MainHeader.h"

int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	int nrIslands;

	Island* vIslands;
	fReadIslands(input, &nrIslands, &vIslands);

	GraphMat* graphMat;
	fReadConnections(input, nrIslands, &graphMat);

	while (1)
	{
		char query[NAMELENGTH];
		query[0] = '\0';
		fscanf(input, "%s", query);
		if (query[0] == '\0' || feof(input))
		{
			return 0; // testele 1->8
		}
		else if (query[0] >= '0' && query[0] <= '9')
		{
			nrIslands = atoi(query);
			break;
		}
		else if (!strcmp(query, "conexiune"))
		{
			fSolveConexiune(input, output, graphMat);
		}
		else if (!strcmp(query, "legatura"))
		{
			fSolveLegatura(input, output, graphMat);
		}
		else if (!strcmp(query, "adauga_zbor"))
		{
			fSolveAdaugaZbor(input, graphMat);
		}
		else if (!strcmp(query, "anulare_zbor"))
		{
			fSolveAnulareZbor(input, graphMat);
		}
		else if (!strcmp(query, "max_resurse"))
		{
			fSolveMaxResurse(input, output, nrIslands, vIslands);
		}
		else if (!strcmp(query, "max_cantitate"))
		{
			fSolveMaxCantitate(input, output, nrIslands, vIslands);
		}
		else if (!strcmp(query, "drum_zbor"))
		{
			fSolveDrumZbor(input, output, graphMat);
		}
		else if (!strcmp(query, "timp_zbor"))
		{
			fSolveTimpZbor(input, output, graphMat);
		}
		else if (!strcmp(query, "min_zbor"))
		{
			fSolveMinZbor(input, output, graphMat);
		}
		else
		{
			exit(2); // ar fi greseala la parsare
		}
	}
	// testele 9->14
	int tolerance;
	int totalPlanes = 0; //int oldnrislnads?
	short boolContinue = 0;
	fscanf(input, "%d", &tolerance);
	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		fscanf(input, "%d", &vIslands[idIsland].nrPlanes);
		vIslands[idIsland].tolerance = tolerance;
		int nrPlanes = vIslands[idIsland].nrPlanes;
		if (nrPlanes > tolerance)
		{
			boolContinue = 1;
		}
		totalPlanes += nrPlanes;
	}
	if (totalPlanes > tolerance* nrIslands)
	{
		fprintf(output, "Stack overflow!");
		return 0;
	}
	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		vIslands[idIsland].vPlanes = malloc(sizeof(int) * vIslands[idIsland].nrPlanes);
		for (int idPlane = 0; idPlane < vIslands[idIsland].nrPlanes; ++idPlane)
		{
			fscanf(input, "%d", &vIslands[idIsland].vPlanes[idPlane]);
		}
		vIslands[idIsland] = vIslands[idIsland];
	}
	if (!boolContinue)
	{
		for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
		{
			fprintf(output, "Island%d\n", idIsland);
			for (int idPlane = 0; idPlane < vIslands[idIsland].nrPlanes; ++idPlane)
			{
				fprintf(output, "%d ", vIslands[idIsland].vPlanes[idPlane]);
			}
			fprintf(output, "\n");
		}
		fprintf(output, "\n");
		return 0;
	}
	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		fCountSort(vIslands[idIsland].vPlanes, vIslands[idIsland].nrPlanes);
	}
	Heap** vHeap = malloc(sizeof(Heap*) * nrIslands);

	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		fInitHeap(&vHeap[idIsland], tolerance);
	}
	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		HeapNode* heapNode = malloc(sizeof(HeapNode));
		heapNode->dist = 0;
		heapNode->index = heapNode->dist;
		fInsertInHeap(vHeap[idIsland], heapNode);
	}
	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		Island island = vIslands[idIsland];
		if (island.nrPlanes > tolerance)
		{
			int excess = island.nrPlanes - tolerance;
			int* vExcess = malloc(sizeof(int) * excess);
			int idExcess = 0;
			for (int idPlane = excess + 1; idPlane < island.nrPlanes; ++idPlane)
			{
				//int plane = island.vPlanes[idPlane];
				vExcess[idExcess] = island.vPlanes[idPlane]; // vExcess[1] = 22
				++idExcess;
			}

			BackParam backParam;
			backParam.excess = excess;
			backParam.graphMat = graphMat;
			backParam.idIsland = idIsland;
			backParam.nrIslands = nrIslands;
			backParam.vIslands = vIslands;
			backParam.vHeap = vHeap;
			backParam.level = 0;
			backParam.vLevel = calloc(excess, sizeof(int));
			backParam.vAlready = calloc(nrIslands, sizeof(int));
			fBack(backParam);
			vHeap = backParam.vHeap;

			for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
			{
				if (vHeap[idIsland]->size <= 1) continue;
				fHeapSort(vHeap[idIsland]);
			}

			static int vPowers[] = { 1, 10, 100, 1000, 10000 };

			for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
			{
				printf("Island%d\n", idIsland);
				for (int idSolution = 0; idSolution < vHeap[idIsland]->size; ++idSolution)
				{
					for (int idPlane = 0; idPlane < vIslands[idIsland].nrPlanes; ++idPlane)
					{
						printf("%d ", vIslands[idIsland].vPlanes[idPlane]);
					}

					for (int idDigit = 0; idDigit < tolerance; ++idDigit)
					{
						int digit = (vHeap[idIsland]->arr[idDigit]->dist / vPowers[idDigit]) % 10;
						if (digit == 0) continue;
						else
						{
							printf("%d ", vExcess[digit]);
						}
					}
				}
			}
		}
	}
	return 0;
}