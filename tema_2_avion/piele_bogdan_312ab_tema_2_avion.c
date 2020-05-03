#include "MainHeader.h"

int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	int nrIslands;
	Island* vIslands = malloc(sizeof(Island) * nrIslands);
	fReadIslands(input, &nrIslands, vIslands);
	GraphMat* graphMat;
	fReadConnecions(input, nrIslands, &graphMat);

	TrieNode* trieRoot;
	fInitTrieNode(&trieRoot);
	while (!feof(input))
	{
		char query[NAMELENGTH];
		fscanf(input, "%s", query);
		if (query[2] == 'x') // max_resurse
		{
			for (int idIsland = 0; idIsland < nrIslands; ++idIsland)
			{
				Island island = vIslands[idIsland];
				for (int idResource = 0; idResource < island.nrResources; ++idResource)
				{
					Resource resource = island.vResources[idResource];
					fInsertInTrie(resource.name, trieRoot);
				}
			}
		}
		char* word = NULL;
		fCountTrie(trieRoot,word,0 )
	}
	return 0;
}