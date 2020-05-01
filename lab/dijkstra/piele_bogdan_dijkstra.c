/*
	se considera un graf orientat citit in input.txt sub forma:

	nr noduri nr muchii
		"nod stanga" "nod dreapta" cost
		"nod stanga" "nod dreapta" cost
		..
	nod sursa dijkstra
	momentan, un graf neorientat ar fi echivalent , pentru dijkstra, in programul meu, cu un graf orientat cu muchii duble (stanga dreapta, dreapta stanga)
*/


#include "MainHeader.h"

int main()
{
	GraphMat* graphMat;
	FILE* input = fopen("input.txt", "r");
	int nrVertexes, nrEdges, source;
	fscanf(input, "%d%d", &nrVertexes, &nrEdges);
	fInitGraphMat(&graphMat, nrVertexes, nrEdges);
	fCreateGraphMat(graphMat, input);
	fscanf(input, "%d", &source);
	fDijkstra(graphMat, source);
	return 0;
}