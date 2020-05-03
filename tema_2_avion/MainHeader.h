#pragma once

#ifndef MAINHEADER

#define MAINHEADER
#define _CRT_SECURE_NO_WARNINGS

#include "UtilHeader.h"
#include "GraphHeader.h"
#include "MinHeapHeader.h"
#include "DijkstraHeader.h"
#include "TrieHeader.h"

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

void fReadIslands(FILE* input, int* adrNrIslands, Island* vIslands);
void fReadConnections(FILE* input, int nrIslands, GraphMat** adrGraphMat);

#endif