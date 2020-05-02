#include "MainHeader.h"
#include "UtilHeader.h"

int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	int nrIslands;
	fscanf(input, "%d", &nrIslands);

	for (int idIsland = 0; idIsland < nrIslands; ++idIsland)
	{
		char vChar[NAMELENGTH];
		fscanf(input, "%s", &vChar);
		Island* island = malloc(sizeof(Island));
		fStrAlloc(&island->name, vChar);
		
		fscanf(input, "%d", &island->nrResources);
		island->vResources = malloc(sizeof(Resource) * island->nrResources);
		for (int idResource = 0; idResource < island->nrResources; ++idResource)
		{
			Resource resource = island->vResources[idResource]; // optional
			char vChar[NAMELENGTH];
			fscanf(input, "%s%d", vChar, resource.quantity);
			fStrAlloc(&resource.name, vChar);
			island->vResources[idResource] = resource;
		}
	}

	return 0;
}