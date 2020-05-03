#include "MainHeader.h"

void fReadIslands(FILE* input,int* adrNrIslands, Island* vIslands)
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