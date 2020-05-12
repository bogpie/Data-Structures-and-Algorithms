#include "MainHeader.h"

int main(int argc, char* argv[])
{
	// bibliografie pentru teste input https://www.infoarena.ro/problema/rucsac?action=attach-list
	char* fileName = malloc(10);
	strcpy(fileName, argv[1]);
	//strcpy(fileName, "input2.in");
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
	param.foundCost=0;

	//rulam backtrackingul de 2 ori - o data ca sa gasim costul maxim (foundCost=0)
	fBack(param); 
	

	//si o data ca sa afisam solutiile;
	param.foundCost = 1;
	fBack(param); 
	// este asemanator algoritmului de gasit maximuri fara structuri auxiliare cum ar fi vector. 
	//gasim maximul, il memoram intr-o variabila (aici solCost sau mai exact *adrSolCost) si iteram solutiile din nou cautand solutiile cu costul egal cu costul maxim (optim)

	// in caz ca dorim afisarea in main a unei solutii : 
	/*	printf("\ns-au introdus obiectele cu indecsii:\n");
	int iLevel = 0;
	while (1)
	{
		if (iLevel > nObjects) break;
		int iObject = param.vSol[iLevel];
		if (iObject == -1) break;
		printf("%d ", param.vSol[iLevel]);
		++iLevel;
	}
	*/

	printf("\ncostul optim fiind : ");
	printf("%d\n", solCost);

	return 0;
}