#include "MainHeader.h"

int fMin(int a, int b)
{
	//calcularea minimului
	if (a < b) return a;
	return b;
}

int fMax(int a, int b)
{
	//calcularea maximului
	if (a > b) return a;
	return b;
}

void fStrAlloc(char** adrPtr, char str[])
{
	//daca citim direct intr-o variabila alocata dinamic un sir de caractere exista riscul sa fi alocat prea putin
	//asa ca folosim un string str[] pentru memorarea sirului de caractere, pe care il copiem intr-un vector din heap, folosindu-ne de lungimea sirului
	char* ptr = *adrPtr;
	ptr = malloc(sizeof(char) * strlen(str));
	if (ptr != 0)
	{
		strcpy(ptr, str);
	}
	else
	{
		exit(1);
	}
	*adrPtr = ptr;
}
