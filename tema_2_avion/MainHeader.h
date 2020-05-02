#pragma once

#ifndef MAINHEADER

#define MAINHEADER
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Resource Resource;
struct Resource
{
	char* name;
	int quantity;
};

typedef struct Island Island;
struct Island
{
	char* name;
	int nrResources;
	Resource* vResources;
	int nrPlanes;
	int* vPlanes;
	int tolerance;
};

#include "UtilHeader.h"

#endif