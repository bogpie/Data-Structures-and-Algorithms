#pragma once

#ifndef UTILHEADER
	#define _CRT_SECURE_NO_WARNINGS
	#define UTILHEADER
	#define NAMELENGTH 50
	#define HEADER

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int fMin(int a, int b);
	int fMax(int a, int b);
	void fStrAlloc(char** adrPtr, char str[]);
	void fPointerTest(void* ptr);

#endif