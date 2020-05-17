#pragma once

#ifndef MAINHEADER

#define MAINHEADER
#define _CRT_SECURE_NO_WARNINGS

#include "UtilHeader.h"

#include "GraphHeader.h"
#include "MinHeapHeader.h"
#include "DijkstraHeader.h"
#include "TrieHeader.h"
#include "QueueHeader.h"

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

typedef struct BackParam BackParam;
struct BackParam
{
	Island* vIslands; // vectorul de insule
	GraphMat* graphMat; // graful cu matricea de adiacenta
	int idIsland; // id-ul insulei cu exces
	int excess; // numarul de avioane cu care trece peste toleranta
	int* vLevel; // vectorul de niveluri specifice backtrackingului. nivelurile sunt avioane de transferat, valorile din vector sunt insule.
	int level; // nivelul curent
	int* vAlready; // vector de aparitii. marcheaza daca am gasit o corespondenta sau nu pentru o INSULA.
	Heap** vHeap; // heap cu solutii. explicatia in README
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
void fBack(BackParam backParam);
void fTryBack(FILE* output, GraphMat* graphMat, Island* vIslands, Heap** vHeap, int* adrChainTransfer);
void fChainTransfer(GraphMat* graphMat,Island* vIslands, int nrIslands, FILE* output);
void fSolvePart1(FILE* input, FILE* output, int* adrNrIslands);
void fSolvePart2(FILE* input, FILE* output, int nrIslands);

#endif