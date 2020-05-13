#pragma once

#ifndef DIJKSTRAHEADER

#define DIJKSTRAHEADER
void fPrintPath(FILE* output,int* vPrev, int source, int destination);
void fDijkstra(GraphMat* graphMat, int source, int destination, int* adrTime, int* vPrev, int wait);

#endif