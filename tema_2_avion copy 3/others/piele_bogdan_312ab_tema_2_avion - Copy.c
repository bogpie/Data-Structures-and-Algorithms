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
		if (query[0] == '\0')
		{
			break;
		}


		if (!strcmp(query, "conexiune"))
		{
			fSolveConexiune(input, output, graphMat);
		}
		else if (!strcmp(query, "legatura"))
		{
			fSolveLegatura(input, output,graphMat);
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
		else if (!strcmp(query, "max_cantiate_resurse"))
		{
			fSolveMaxCantitate(input, output, nrIslands, vIslands);
		}
		else if (!strcmp(query, "timp_zbor"))
		{
			fSolveTimpZbor(input, graphMat);
		}
		else if (!strcmp(query, "min_zbor"))
		{
			fSolveMinZbor(input, graphMat);
		}
		else exit(2); // ar fi greseala la parsare

	}
	return 0;
}