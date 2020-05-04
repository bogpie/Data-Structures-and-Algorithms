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

void fReadIslands(FILE* input, int* adrNrIslands, Island** adrVectorIslands);
void fReadConnections(FILE* input, int nrIslands, GraphMat** adrGraphMat);
void fSolveConexiune(FILE* input, FILE* output, GraphMat* graphMat);
void fSolveLegatura(FILE* input, FILE* output, GraphMat* graphMat);
void fSolveAnulareZbor(FILE* input, GraphMat* graphMat);
void fSolveAdaugaZbor(FILE* input, GraphMat* graphMat);
void fSolveMaxResurse(FILE* input, FILE* output, int nrIslands, Island* vIslands);
void fSolveMaxCantitate(FILE* input, FILE* output, int nrIslands, Island* vIslands);
void fSolveDrumZbor(FILE* input, FILE* output, GraphMat* graphMat);
void fSolveTimpZbor(FILE* input, FILE* output, GraphMat* graphMat);
void fSolveMinZbor(FILE* input, FILE* output, GraphMat* graphMat);
void fNameToIndex(char* name, int* adrIndex);

#endif