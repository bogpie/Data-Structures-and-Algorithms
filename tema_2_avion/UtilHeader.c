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

void fPointerTest(void* ptr)
{
	if (ptr == NULL)
	{
		exit(1);
	}
}

void fSort(int* arr, int size)
{
	int sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		for (int i = 1; i < size; ++i)
		{
			if (arr[i] < arr[i - 1])
			{
				sorted = 0;
				fSwap(&arr[i], &arr[i - 1]);
			}
		}
	}

}

