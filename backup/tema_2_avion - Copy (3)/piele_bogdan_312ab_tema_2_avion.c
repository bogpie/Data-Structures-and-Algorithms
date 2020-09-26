#include "MainHeader.h"

int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	int nrIslands = -1;
	fSolvePart1(input, output, &nrIslands); // la o eventual modificare a numarului de insule, programul va executa si partea a doua a problemei
	if (nrIslands != -1) 		
	{
		// testele 9->14, se rezolva partea a doua 
		fSolvePart2(input, output, nrIslands);	
	}

	fclose(input);
	fclose(output);
	return 0;
}