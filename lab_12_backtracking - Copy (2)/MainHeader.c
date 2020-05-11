#include "MainHeader.h"

void fBack(Param param)
{
	int idLastAdded = param.vCrt[param.level-1];
	// daca nu mai poate tolera greutate sau nu mai putem pune obiecte sau dupa ultimul obiect nu mai sunt alte elemente in vectorul vObjects
	if (param.tolerance <= 0 || param.level > param.nObjects || idLastAdded >= param.nObjects-1) 
	{
		if (param.tolerance < 0) // daca nu mai poate tolera greutate
		{
			if (param.level - 1 >= 1)
			{
				int indexPopped = param.vCrt[param.level - 1];
				param.sumCost -= param.vObjects[indexPopped].cost ;
				param.tolerance += param.vObjects[indexPopped].weight;
				param.vCrt[--param.level] = -1; // scoatem ultimul obiect daca poate fi scos
			}
			else exit(1);
		}
		if (param.sumCost > * param.adrSolCost) // verificam daca solutia curenta este o solutie mai profitabila
		{
			for (int iLevel = 0; iLevel < param.level; ++iLevel)
			{
				param.vSol[iLevel] = param.vCrt[iLevel];
			}
			param.vSol[param.level + 1] = -1;
			*param.adrSolCost = param.sumCost;
		}
		return;
	}

	int start = 0;
	if (param.level != 0)
	{
		start = param.vCrt[param.level - 1] + 1;
	}
	// incepem de la primul element daca "rucsacul curent" e gol sau de la urmatorul obiect ca index dupa cel introdus in "rucsacul curent"

	for (int iObject = start; iObject < param.nObjects; ++iObject)
	{
		Object object = param.vObjects[iObject];
		//if (param.tolerance - object.weight >= 0)
		//{
		Param newParam = param;
		newParam.tolerance -= object.weight;
		newParam.sumCost += object.cost;
		newParam.vCrt[param.level] = iObject; // object.index
		newParam.level = param.level + 1;
		newParam.vCrt[newParam.level] = -1; // siguranta ca nu a mai ramas vreun element de la un pas recursiv anterior
		fBack(newParam);
		param.vCrt[param.level] = -1;
		//}
	}
}