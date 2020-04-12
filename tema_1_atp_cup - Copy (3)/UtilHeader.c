#include "Header.h"

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

void fFindTarget(int nrCountries, int* adrTarget)
{
	//gasim noul numar de tari ce trebuie atins (tinta)
	//parametrii: nr de tari, tinta (referinta)

	int pwr = 0, nrCountriesBak = nrCountries;
	//aflam cea mai mare putere a lui 2 mai mica sau egala cu numarul de tari
	//adica impartim numarul de tari la 2 cat timp nu e nul si, in acelasi timp, incrementam puterea
	while (nrCountries)
	{
		nrCountries /= 2;
		++pwr;
	}
	nrCountries = nrCountriesBak;

	if (nrCountries == 1 << pwr)
	{
		//daca numarul e deja putere a lui 2, nu mai trebuie eliminate tari
		//tinta e chiar numarul de tari deja existent
		*adrTarget = nrCountries;
		return;
	}
	else
	{
		//altfel tinta este 2^(puterea-1)
		*adrTarget = 1 << (pwr - 1);
	}
}