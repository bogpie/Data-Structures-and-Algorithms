#pragma once

#ifndef LISTHEADER
	#define LISTHEADER

	typedef struct ListNode ListNode;
	struct ListNode
	{
		ListNode* prev;
		Country* adrCountry; // sunt alocate dinamic, dorim sincronizarea punctajelor si deci folosim adrese la tari
		ListNode* next;
	};

	void fInitList(ListNode** adrStart);
	void fEraseList(ListNode* start);
	void fAddInList(ListNode* start, ListNode* listNode, ListNode* prev, int iCountry, int nrCountries);
	void fDeleteListNode(ListNode* listNode);
	void fPrintList(ListNode* start, FILE* rezultateOut);	
	void fFindMinim(ListNode* start, float* adrMinim);	
	void fDeleteMinim(ListNode* start, int nrCountries, float minim);
	void fEliminateUntilTarget(ListNode* start, int* adrNrCountries);

#endif // !LISTHEADER

