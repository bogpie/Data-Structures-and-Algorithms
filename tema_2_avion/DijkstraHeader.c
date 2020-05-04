#include "MainHeader.h"

void fPrintPath(FILE* output,int* vPrev, int source, int destination)
{
	if (destination == -1)
	{
		return;
	}
	fPrintPath(output,vPrev, source,vPrev[destination]);
	if (destination != source)
	{
		fprintf(output, "Island%d ", destination);
	}
}

void fDijkstra(GraphMat* graphMat, int source, int destination, int* adrTime, int* vPrev, int wait)
{
	int nrVertexes = graphMat->nrVertexes;

	Heap* heap;
	fInitHeap(&heap, nrVertexes);
	HeapNode* heapNode = malloc(sizeof(HeapNode));

	int* vDist = malloc((nrVertexes+1) * sizeof(int));
	//int* vPrev = malloc(nrVertexes * sizeof(int));
	//int* vVisited = malloc((nrVertexes + 1) * sizeof(int));

	int i;
	for (i = 1; i <= nrVertexes; ++i)
	{
		vDist[i] = INT_MAX;
		vPrev[i] = -1;
	}
	vDist[source] = 0;
	heapNode->dist = 0;
	heapNode->index = source;
	fInsertInHeap(heap, heapNode);

	while (heap->size > 0)
	{
		HeapNode* minNode = heap->arr[0];
		fDeleteNode(heap, 0);
		int neighbourIndex;
		for (neighbourIndex = 1; neighbourIndex <= nrVertexes; ++neighbourIndex)
		{
			int cost = graphMat->mat[minNode->index][neighbourIndex];
			if (cost != 0)
			{
				int newDist = minNode->dist + cost;
				if (newDist < vDist[neighbourIndex])
				{
					vDist[neighbourIndex] = newDist;
					HeapNode* newNode = malloc(sizeof(HeapNode));
					newNode->dist = newDist;
					newNode->index = neighbourIndex;
					vPrev[neighbourIndex] = minNode->index;
					int crtTime = INT_MAX, foundPosition = -1;
					fFindInHeap(heap, neighbourIndex, &foundPosition, &crtTime);
					if (newNode->dist + wait < crtTime) // stationarea ar putea fi o problema
					{
						if (foundPosition != -1)
						{
							fDeleteNode(heap, foundPosition);
						}
						fInsertInHeap(heap, newNode);
					}


				}

			}
		}
	}

	
	*adrTime = vDist[destination];
	if (vDist != NULL) free(vDist);
	//if (vPrev != NULL) free(vPrev);
	//if (vVisited != NULL) free(vVisited);
}