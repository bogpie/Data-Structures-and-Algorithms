#include "MainHeader.h"

int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
	int nrIslands;
	Island* vIslands = NULL;
	fReadIslands(input, &nrIslands, &vIslands);
	GraphMat* graphMat = NULL;
	fReadConnections(input, nrIslands, &graphMat);
	int boolSkip=0;
	fSolvePart1(input, output, &nrIslands, vIslands, graphMat, &boolSkip);
	if (vIslands != NULL)
	{
		for (int idIsland = 1; idIsland <= graphMat->nrVertexes; ++idIsland)
		{
			if (vIslands[idIsland].vResources != NULL)
			{
				free(vIslands[idIsland].vResources);
				vIslands[idIsland].vResources = NULL;
			}
			//if (vIslands[idIsland].name != NULL) free(vIslands[idIsland].name);
		}
		free(vIslands);
		vIslands = NULL;
	}
	fEraseGraphMat(graphMat);
	graphMat = NULL;
	if (boolSkip)
	{
		fclose(input);
		fclose(output);
		return 0;
	}
	// testele 9->14
	vIslands = malloc(sizeof(Island) * (nrIslands + 1));
	int tolerance;
	int totalPlanes = 0; 
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
		fclose(input);
		fclose(output);
		return 0;
		//nrIslands = 0;
	}
	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		vIslands[idIsland].vPlanes = malloc(sizeof(int) * fMax(vIslands[idIsland].nrPlanes, tolerance));
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
		//nrIslands = 0;
		return 0;
	}
	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		fCountSort(vIslands[idIsland].vPlanes, vIslands[idIsland].nrPlanes);
	}
	Heap** vHeap = malloc(sizeof(Heap*) * (nrIslands + 1));

	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		fInitHeap(&vHeap[idIsland], 4);
	}

	fInitGraphMat(&graphMat, nrIslands, 0); // function
	for (int idLeft = 1; idLeft <= nrIslands; ++idLeft)
	{
		for (int idRight = 1; idRight <= nrIslands; ++idRight)
		{
			int cost;
			fscanf(input, "%d", &cost); // 0 || 1
			graphMat->mat[idLeft][idRight] = cost;
			graphMat->mat[idRight][idLeft] = cost;
			graphMat->nrEdges += 2;

		}
	}
	int chainTransfer = 0; // function !!
	for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
	{
		Island island = vIslands[idIsland];
		if (island.nrPlanes > tolerance)
		{
			int excess = island.nrPlanes - tolerance;
			int* vExcess = malloc(sizeof(int) * (excess + 1));
			int idExcess = 0;
			for (int idPlane = island.nrPlanes - excess; idPlane < island.nrPlanes; ++idPlane)
			{
				//int plane = island.vPlanes[idPlane];
				vExcess[idExcess] = island.vPlanes[idPlane]; // vExcess[1] = 22
				//should sort !!
				++idExcess;
			}

			int boolBreak = 1;
			for (int idNeighbour = 1; idNeighbour <= nrIslands; ++idNeighbour)
			{
				if (idNeighbour == idIsland || !fTestEdgeMat(graphMat, idIsland, idNeighbour)) continue;
				if (vIslands[idNeighbour].nrPlanes < tolerance)
				{
					boolBreak = 0;
					break;
				}
			}
			if (boolBreak)
			{
				chainTransfer = 1;
				break;
			}

			BackParam backParam;
			backParam.excess = excess;
			backParam.graphMat = graphMat;
			backParam.idIsland = idIsland;
			backParam.nrIslands = nrIslands;
			backParam.vIslands = vIslands;
			backParam.vHeap = vHeap;
			backParam.level = 0;
			int* vLevel = calloc(excess + 1, sizeof(int));
			backParam.vLevel = vLevel;
			int* vAlready = calloc(nrIslands + 1, sizeof(int));
			backParam.vAlready = vAlready;
			backParam.graphMat = graphMat;
			vIslands[idIsland].nrPlanes = tolerance;
			fBack(backParam);
			vHeap = backParam.vHeap;
			for (int idIsland2 = 1; idIsland2 <= nrIslands; ++idIsland2)
			{
				if (vHeap[idIsland2]->size <= 1) continue;
				int size = vHeap[idIsland2]->size;
				fHeapSort(vHeap[idIsland2]);
				vHeap[idIsland2]->size = size; // sortarea inseamna mereu "stergerea" minimului => decrementare continua de heap->size => reinitializam
			}
			const int vPowers[] = { 1, 10, 100, 1000, 10000 };
			for (int idIsland2 = 1; idIsland2 <= nrIslands; ++idIsland2)
			{
				fprintf(output, "Island%d\n", idIsland2);
				for (int idSolution = 0; idSolution < vHeap[idIsland2]->size; ++idSolution)
				{
					int solution = vHeap[idIsland2]->arr[idSolution]->dist;
					int solutionBak = solution;
					int nrDigits = 0;

					while (solution)
					{
						solution /= 10;
						++nrDigits;
					}

					solution = solutionBak;

					for (int idPlane = 0; idPlane < vIslands[idIsland2].nrPlanes; ++idPlane)
					{
						fprintf(output, "%d ", vIslands[idIsland2].vPlanes[idPlane]);
					}

					if (!solution)
					{
						fprintf(output, "\n");
						break;
					}

					for (int idDigit = 0; idDigit < nrDigits; ++idDigit)
					{
						int digit = (solution / vPowers[nrDigits - idDigit - 1]) % 10;
						if (digit == 0)
						{
							continue;
						}
						else
						{
							fprintf(output, "%d ", vExcess[digit - 1]);
						}
					}
					fprintf(output, "\n");

				}
			}
			if (vExcess != NULL) free(vExcess);
			if (vLevel != NULL) free(vLevel);
			if (backParam.vAlready != NULL) free(backParam.vAlready);
		}
	}
	if (chainTransfer) // transfer in lant
	{
		fChainTransfer(graphMat,vIslands, nrIslands, output);
	}
	fEraseGraphMat(graphMat);
	if (vHeap)
	{
		for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
		{
			if (vHeap[idIsland])
			{
				fEraseHeap(vHeap[idIsland]);
			}

		}
		free(vHeap);
	}
	if (vIslands != NULL)
	{
		for (int idIsland = 1; idIsland <= nrIslands; ++idIsland)
		{
			if (vIslands[idIsland].vPlanes != NULL)
			{
				free(vIslands[idIsland].vPlanes);
			}
		}
		free(vIslands);
	}
	fclose(input);
	fclose(output);
	return 0;
}