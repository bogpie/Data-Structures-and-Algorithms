#pragma once

#ifndef HEADER
	#define HEADER
	#include "UtilHeader.h"

	typedef struct Player Player;
	struct Player
	{
		char* prenume;
		char* numeFamilie;
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

	#include "ListHeader.h"
	#include "StackHeader.h"
	#include "QueueHeader.h"
	#include "TreeHeader.h"

	void fPlayMatch(Player* adrPlayer1, Player* adrPlayer2, int* vLocal);
	void fTournament(Stack* stack, FILE* rezultateOut, Stack** adrFourStack);
	void fRanking(FILE* rezultateOut, Stack* fourStack, Tree* tree);
	void fParseDate(FILE* dateIn, int* adrNrCountries, ListNode* start);
	void fParseCerinte(FILE* cerinteIn, int* vCerinte, Player* vTwoPlayers);
	void fOpenAllCommandLine(FILE** adrCerinteIn, FILE** adrDateIn, FILE** adrRezultateOut, int argc, char* argv[]);

#endif