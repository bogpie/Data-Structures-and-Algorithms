#pragma once

#ifndef DIJKSTRAHEADER

#define DIJKSTRAHEADER
void fPrintPath(int* vPrev, int index);
void fDijkstra(GraphMat* graphMat, int source, int destination, int* adrTime, int wait);

#endif