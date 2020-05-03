#include "MainHeader.h"

int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	int nrIslands;
	Island* vIslands = malloc(sizeof(Island) * nrIslands);
	fReadIslands(input, &nrIslands, vIslands);
	GraphMat* graphMat;
	fReadConnections(input, nrIslands, &graphMat);


	while (!feof(input))
	{
		char query[NAMELENGTH];
		fscanf(input, "%s", query);

		if (!strcmp(query, "conexiune"))
		{
			fSolveConexiune(input, graphMat);
		}
		else if (!strcmp(query, "legatura"))
		{
			fSolveLegatura(input, graphMat);
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
			fSolveMaxResurse(input, nrIslands, vIslands);
		}
		else if (!strcmp(query, "max_cantiate_resurse"))
		{
			fSolveMaxCantitate(input, nrIslands, vIslands);
		}
		else if (!strcmp(query, "timp_zbor"))
		{
			fSolveTimpZbor(input, graphMat);
		}
		else if (!strcmp(query, "min_zbor"))
		{
			fSolveMinZbor(input, graphMat);
		}
		else exit(1); // ar fi greseala la parsare

	}
	return 0;
}