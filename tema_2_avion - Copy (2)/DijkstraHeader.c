#include "MainHeader.h"

void fPrintPath(int* vPrev, int index)
{
	if (index == -1)
	{
		return;
	}
	fPrintPath(vPrev, vPrev[index]);
	printf("%d ", index);
}

void fDijkstra(GraphMat* graphMat, int source, int destination, int* adrTime, int wait)
{
	int nrVertexes = graphMat->nrVertexes;

	Heap* heap;
	fInitHeap(&heap, nrVertexes);
	HeapNode* heapNode = malloc(sizeof(HeapNode));

	int* vDist = malloc(nrVertexes * sizeof(int));
	int* vPrev = malloc(nrVertexes * sizeof(int));
	int* vVisited = malloc(nrVertexes * sizeof(int));

	int i;
	for (i = 0; i < nrVertexes; ++i)
	{
		vDist[i] = INT_MAX;
		vPrev[i] = -1;
		vVisited[i] = 0;
	}
	vDist[source] = 0;
	heapNode->dist = 0;
	heapNode->index = source;
	fInsertInHeap(heap, heapNode);

	while (heap->size > 0)
	{
		HeapNode* minNode = heap->arr[0];
		fDeleteNode(heap, 0);
		vVisited[minNode->index] = 1;
		int neighbourIndex;
		for (neighbourIndex = 0; neighbourIndex < nrVertexes; ++neighbourIndex)
		{
			int cost = graphMat->mat[minNode->index][neighbourIndex];
			if (cost != 0)
			{
				int newDist = minNode->dist + cost;
				if (newDist < vDist[neighbourIndex] && !vVisited[neighbourIndex])
				{
					vDist[neighbourIndex] = newDist;
					HeapNode* newNode = malloc(sizeof(HeapNode));
					newNode->dist = newDist;
					newNode->index = neighbourIndex;
					vPrev[neighbourIndex] = minNode->index;
					int crtTime = -1, foundPosition = -1;
					fFindInHeap(heap, neighbourIndex, &foundPosition, &crtTime);
					if (foundPosition != -1 && newNode->dist + wait < crtTime) // stationarea ar putea fi o problema
					{
						fDeleteNode(heap, foundPosition);
						fInsertInHeap(heap, newNode);
					}


				}

			}
		}
	}

	/*printf("\nde la nodul sursa %d la nodurile:", source);
	for (i = 0; i < nrVertexes; ++i)
	{
		printf("\n%d -> distanta %d pe traseul : ", i, vDist[i]);
		fPrintPath(vPrev, i);
	}*/

	*adrTime = vDist[destination];
	if (vDist != NULL) free(vDist);
	if (vPrev != NULL) free(vPrev);
	if (vVisited != NULL) free(vVisited);
}