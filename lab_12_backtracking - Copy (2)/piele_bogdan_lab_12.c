#include "MainHeader.h"

int main(int argc, char* argv[])
{
	// bibliografie pentru teste input https://www.infoarena.ro/problema/rucsac?action=attach-list

	char* fileName = malloc(10);

	strcpy(fileName, argv[1]);
	strcpy(fileName, "input4.in");

	FILE* input = fopen(fileName, "r");
	//output in consola 

	printf("sunt descrise diferite situatii in fisierele de input");
	int nObjects, maxWeight;
	fscanf(input, "%d%d", &nObjects, &maxWeight);
	printf("\nconform input.in sunt %d obiecte, rucsacul poate tine greutatea %d", nObjects, maxWeight);
	printf("\niar obiectele (indexate de la 0) sunt:\n");
	Object* vObjects = malloc(sizeof(Object) * nObjects);
	for (int iObject = 0; iObject < nObjects; ++iObject)
	{
		fscanf(input, "%d%d", &vObjects[iObject].weight, &vObjects[iObject].cost);
		//vObjects[iObject].index = iObject;
		printf("%d : greutate = %d , cost = %d\n",
			iObject, vObjects[iObject].weight, vObjects[iObject].cost);
	}

	int* vSol = malloc(sizeof(Object) * nObjects + 1);
	int* vCrt = malloc(sizeof(Object) * nObjects);
	for (int iSol = 0; iSol < nObjects; ++iSol)
	{
		vSol[iSol] = -1;
		vCrt[iSol] = -1;
	}
	Param param;

	param.vObjects = vObjects;
	param.nObjects = nObjects;
	param.level = param.sumCost = 0;
	int solCost = 0; param.adrSolCost = &solCost;
	param.tolerance = maxWeight;
	param.vCrt = vCrt;
	param.vSol = vSol;

	fBack(param); // void fBack(int level, int sumCost, int sumWeight, int* vSol)
	printf("\ns-au introdus obiectele cu indecsii:\n");
	int iLevel = 0;
	while (1)
	{
		if (iLevel > nObjects) break;
		int iObject = param.vSol[iLevel];
		if (iObject == -1) break;
		printf("%d ", param.vSol[iLevel]);
		++iLevel;
	}
	printf("\nrezultand un cost de : ");
	printf("%d", solCost);

	return 0;
}