#include "Header.h"

int main()
{
	printf("se vor crea grafuri neorientate cu noduri de la 0 la nr de noduri-1");
	GraphMat* graphMat = NULL;
	GraphList* graphList = NULL;	// le initializez in functiile de jos
	int nrVertexes;
	printf("\nnr de noduri:");
	scanf("%d", &nrVertexes);
	fInitGraphMat(&graphMat, nrVertexes);

	int orientat = 0;
	printf("\neste graf orientat (0 daca nu, altfel valoare nenula) ? ");
	scanf("%d", &orientat);
	fCreateGraphMat(graphMat, orientat);
	fInitGraphList(&graphList, graphMat->nrVertexes);
	fMatToList(graphMat, &graphList);
	printf("\n\nam creat graful cu liste din graful cu matrice (de adiacenta):");
	fPrintGraphList(graphList);

	fEraseGraphMat(graphMat);
	fInitGraphMat(&graphMat, nrVertexes);


	fListToMat(graphList, &graphMat);
	printf("\n\nam (re)creat graful cu matrice din graful cu liste:");
	fPrintGraphMat(graphMat);


	printf("\n\nverificarea existentei unei muchii intre x si y");
	int x, y;
	printf("\nunde x=");
	scanf("%d", &x);
	printf("si y=");
	scanf("%d", &y);
	fTestEdgeMat(graphMat, x, y);
	fTestEdgeList(graphList, x, y);

	printf("\n\ngasirea nodurilor vecine cu x,unde x=");
	scanf("%d", &x);
	printf("test pentru graful cu matrice:");
	fFindNeighbourMat(graphMat, x);
	printf("\ntest graful cu liste:");
	fFindNeighbourList(graphList, x);

	printf("\n\naplicam algoritmul roy-warshall:");
	fRoy(graphMat, nrVertexes);
	
	fEraseGraphMat(graphMat);
	fEraseGraphList(graphList);

	
	return 0;
}