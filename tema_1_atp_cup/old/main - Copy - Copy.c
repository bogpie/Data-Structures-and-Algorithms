#define _CRT_SECURE_NO_WARNINGS
#define NAMELENGTH 50
//#pragma warning( push )
//#pragma warning( disable : 6054 )

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player Player;
struct Player
{
	char* lastName;
	char* firstName;
	int score;
};

typedef struct Country Country;
struct Country
{
	char* name;
	int nrPlayers;
	int globalScore;
	Player* vPlayers;
};

typedef struct Element Element;
struct Element
{
	Element* prev;
	Country country;
	Element* next;
};

void fParseDate(FILE* dateIn,Country** adr_vCountries)
{
	Country* vCountries = *adr_vCountries;

	//dateIn = fopen("date.in", "r");
	
	int nrCountries;
	char countryName[NAMELENGTH];
	
	char firstName[NAMELENGTH], lastName[NAMELENGTH];
	int score;

	fscanf(dateIn, "%d%s", &nrCountries,countryName);
	
	vCountries = malloc(sizeof(Country) * nrCountries);

	for (int iCountry = 0; iCountry < nrCountries; ++iCountry)
	{
		int nrPlayers;
		fscanf(dateIn, "%d", &nrPlayers);
		vCountries[iCountry].nrPlayers = nrPlayers;

		vCountries[iCountry].vPlayers = malloc(sizeof(Player) * nrPlayers);
		for (int iPlayer = 0; iPlayer < nrPlayers; ++iPlayer)
		{
			fscanf(dateIn, "%s%s%d", firstName, lastName, &vCountries[iCountry].vPlayers[iPlayer].score);
			
			vCountries[iCountry].vPlayers[iPlayer].firstName = malloc(sizeof(char) * strlen(firstName));
			vCountries[iCountry].vPlayers[iPlayer].lastName = malloc(sizeof(char) * strlen(lastName));
			strcpy(vCountries[iCountry].vPlayers[iPlayer].firstName, firstName);
			strcpy(vCountries[iCountry].vPlayers[iPlayer].lastName, lastName);
		}
	}

	*adr_vCountries = vCountries;
}

void fParseCerinte(FILE * cerinteIn,int vCerinte[5],Player vTwoPlayers[2])
{	
	//cerinteIn = fopen("cerinte.in", "r");
	for (int i = 0; i < 5; ++i)
	{
		fscanf(cerinteIn, "%d", &vCerinte[i]);
	}

	if (vCerinte[4] == 1)
	{
		char firstName[NAMELENGTH], lastName[NAMELENGTH];
		int score;

		for (int i = 0; i < 2; ++i)
		{
			fscanf(cerinteIn, "%s%s%d", firstName, lastName, &vTwoPlayers[i].score);
			vTwoPlayers[i].firstName = malloc(strlen(firstName) * sizeof(char));
			vTwoPlayers[i].lastName = malloc(strlen(lastName) * sizeof(char));
			strcpy(vTwoPlayers[i].firstName, firstName);
			strcpy(vTwoPlayers[i].lastName, lastName);
		}
	}
}

int main()
{
	FILE* cerinteOut = fopen("date.out", "w");
	FILE* rezultateOut = fopen("rezultate.out", "w");
	
	FILE* dateIn = fopen("date.in", "r");
	
	
	//Country* vCountries;
	

	Element* start;

	fParseDate(dateIn,&vCountries);

	FILE* cerinteIn = fopen("cerinte.in", "r");
	int vCerinte[5];
	Player vTwoPlayers[2]; // se memoreaza?
	fParseCerinte(cerinteIn,vCerinte,vTwoPlayers);

	Element* start;
	Element* finish;

	//fMakeCountryList(vCountries);


	return 0;
}
//#pragma warning( pop )