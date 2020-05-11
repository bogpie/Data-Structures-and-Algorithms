#include "MainHeader.h"

int main(int argc,char* argv[])
{
	// bibliografie pentru teste input https://www.infoarena.ro/problema/rucsac?action=attach-list
	
	char* fileName = malloc(10);
	strcpy(fileName,argv[1]);
	//strcpy(fileName,"input1.in");	

	FILE* input = fopen(fileName, "r");
	//output in consola 

	printf("sunt descrise diferite situatii in fisierele de input");
	int nObjects, maxWeight;
	Heap* heap;
	fscanf(input, "%d%d", &nObjects, &maxWeight);

	printf("\nconform input.in sunt %d obiecte, rucsacul poate tine greutatea %d", nObjects, maxWeight);
	printf("\niar obiectele (indexate de la 0) sunt:\n");
		
	fInitHeap(&heap, nObjects);
	Object* arr = malloc(sizeof(Object) * nObjects);
	for (int iObject = 0; iObject < nObjects; ++iObject)
	{
		fscanf(input, "%d%d", &arr[iObject].weight, &arr[iObject].cost);
		arr[iObject].index = iObject;
		arr[iObject].efficiency = 1.0 * arr[iObject].cost / arr[iObject].weight;
		printf("%d : greutate = %d , cost = %d => eficienta = %f\n", 
			iObject, arr[iObject].weight, arr[iObject].cost,arr[iObject].efficiency);
	}
	heap->size = nObjects;
	heap->arr = arr;
	
	printf("\nse sorteaza dupa eficienta..:\n");

	fHeapSort(heap);

	arr = heap->arr;
	for (int iObject = 0; iObject < nObjects; ++iObject)
	{
		fscanf(input, "%d%d", &arr[iObject].weight, &arr[iObject].cost);
		
		printf("%d : greutate = %d , cost = %d => eficienta = %f\n", 
			arr[iObject].index, arr[iObject].weight, arr[iObject].cost,arr[iObject].efficiency);
	}

	printf("\nse rezolva problema rucsacului in varianta fractionara (0 pt NU, altceva pt da) : ");
	int query; scanf("%d", &query);

	printf("\n\nse introduc obiectele cu indecsii : ");
	int tolerance = maxWeight;
	float sum = 0;
	if (!query) // problema cu obiecte intregi
	{
		int iObject = 0;
		while (iObject < nObjects && tolerance)
		{
			Object object = heap->arr[iObject];
			if (object.weight <= tolerance)
			{
				tolerance -= object.weight;
				printf("%d ", object.index);
				sum += object.cost;
			}
			++iObject;
		}
	}
	else // problema fractionara
	{
		int iObject = 0;
		while (iObject < nObjects && tolerance)
		{
			Object object = heap->arr[iObject];
			if (object.weight <= tolerance)
			{
				tolerance -= object.weight;
				printf("%d ", object.index);
				sum += object.cost;
			}
			else
			{
				float fraction = 1.0 *  tolerance / object.weight;
				sum += (object.cost * fraction);
					
				printf("\nse mai introduce %f * obiectul cu indexul %d , costul sau devenind %f",
					fraction, object.index, 1.0 * object.cost * fraction);
				tolerance = 0;
				break;
			}
			++iObject;
		}
	}

	printf("\nruscacul avand obiecte de cost total %f si mai putand tine o greutate de %d", sum, tolerance);

	free(fileName);
	fErase(&heap);

}