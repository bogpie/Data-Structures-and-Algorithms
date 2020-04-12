#pragma once

#ifndef STACKHEADER
	#define STACKHEADER
	typedef struct StackNode StackNode;
	struct StackNode
	{
		Country* adrCountry;
		StackNode* next;
	};
	typedef struct Stack Stack;
	struct Stack
	{
		StackNode* top;
		int size;
	};

	void fInitStack(Stack** adrStack);
	void fEraseStack(Stack* stack);
	void fPush(Stack** adrStack, Country* adrCountry);
	void fPop(Stack** adrStack);
	void fPopulateStack(ListNode* start, Stack** adrStack);
	void fPrintStack(Stack* stack, FILE* rezultateOut);
	void fCopyStack(Stack** adrDestination, Stack* source);


#endif

