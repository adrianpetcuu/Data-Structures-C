#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int prioritate;
	char* denumire;
	float efortOre;
} task;

typedef struct
{
	task* vector;
	int nrElem;
} heap;

void filtrareHeap(heap h, int index)
{
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElem && h.vector[indexSt].prioritate > h.vector[indexRad].prioritate)
	{
		indexRad = indexSt;
	}
	if (indexDr < h.nrElem && h.vector[indexDr].prioritate > h.vector[indexRad].prioritate)
	{
		indexRad = indexDr;
	}
	//daca s-a facut interschimbarea
	if (indexRad != index)
	{
		task aux = h.vector[index];
		h.vector[index] = h.vector[indexRad];
		h.vector[indexRad] = aux;
		filtrareHeap(h, indexRad);
	}
}

heap inserareHeap(heap h, task nou)
{
	task* vectorNou = (task*)malloc((h.nrElem + 1) * sizeof(task));
	for (int i = 0; i < h.nrElem; i++)
	{
		vectorNou[i] = h.vector[i];
	}
	h.nrElem++;
	vectorNou[h.nrElem - 1] = nou;
	free(h.vector);
	h.vector = vectorNou;
	for (int i = (h.nrElem + 1) / 2; i >= 0; i--)
	{
		filtrareHeap(h, i);
	}
	return h;
}


//task* ca sa l referentiem pentru a face ceva cu el pe viitor => ex: pus in alt vector
heap extragereHeap(heap h, task* extras)
{
	task* vectorNou = (task*)malloc((h.nrElem - 1) * sizeof(task));
	//*extras = h.vect[0]; //gresit, nu stergem radacina 
	//interschimbam primul cu ultimul element
	task aux = h.vector[0];
	h.vector[0] = h.vector[h.nrElem - 1];
	h.vector[h.nrElem - 1] = aux;

	*extras = h.vector[h.nrElem - 1];
	h.nrElem--;

	for (int i = 0; i < h.nrElem; i++)
	{
		vectorNou[i] = h.vector[i];
	}
	free(h.vector);
	h.vector = vectorNou;

	for (int i = (h.nrElem / 2) - 1; i >= 0; i--)
	{
		filtrareHeap(h, i);
	}
	return h;
}




void afisareHeap(heap h)
{
	if (h.vector != NULL)
	{
		for (int i = 0; i < h.nrElem; i++)
		{
			printf("\nPrioritate: %d, Denumire: %s, Efort: %5.2f\n",
				h.vector[i].prioritate, h.vector[i].denumire, h.vector[i].efortOre);
		}
	}
}

void dezalocareHeap(heap h)
{
	if (h.vector != NULL)
	{
		for (int i = 0; i < h.nrElem; i++)
		{
			free(h.vector[i].denumire);
		}
		free(h.vector);
	}
}

void main()
{
	heap h;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &h.nrElem);
	h.vector = (task*)malloc(h.nrElem * sizeof(task));
	for (int i = 0; i < h.nrElem; i++)
	{
		fscanf(f, "%d", &h.vector[i].prioritate);
		fscanf(f, "%s", buffer);
		h.vector[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vector[i].denumire, buffer);
		fscanf(f, "%f", &h.vector[i].efortOre);
	}
	fclose(f);

	afisareHeap(h);
	printf("\n----------------Filtrare Heap-----------------\n");
	for (int i = (h.nrElem / 2) - 1; i >= 0; i--)
	{
		filtrareHeap(h, i);
	}
	afisareHeap(h);

	printf("\n----------------Inserare Heap-----------------\n");
	task nou;
	printf("\nPrioritate: ");
	scanf("%d", &nou.prioritate);
	printf("\nDenumire: ");
	scanf("%s", buffer);
	nou.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(nou.denumire, buffer);
	printf("\nEfort: ");
	scanf("%f", &nou.efortOre);
	h = inserareHeap(h, nou);
	afisareHeap(h);

	printf("\n----------------Extragere Heap-----------------\n");
	//intotdeauna se extrage primul - cel mai mare , nodul radacina
	//sortare heap sort - extrage mereu maximul din cele ramase
	task extras;
	h = extragereHeap(h, &extras);
	printf("\nExtras => Prioritate: %d, Denumire: %s, Efort: %5.2f\n",
		extras.prioritate, extras.denumire, extras.efortOre);
	afisareHeap(h);

	printf("\n-----------------Punere elemente in vector sortat-------------\n");
	int nr = h.nrElem; // pentru ca la extragere h.nrElem se modifica si il pastram in nr;
	task* vectorSortat = (task*)malloc(nr * sizeof(task));
	for (int i = 0; i < nr; i++)
	{
		h = extragereHeap(h, &extras);
		vectorSortat[i] = extras;
	}
	for (int i = 0; i < nr; i++)
	{
		printf("\nPrioritate: %d, Denumire: %s, Efort: %5.2f ",
			vectorSortat[i].prioritate, vectorSortat[i].denumire, vectorSortat[i].efortOre);
	}
	for (int i = 0; i < nr; i++)
	{
		free(vectorSortat[i].denumire);
	}
	//dezalocare vector
	free(vectorSortat);

	//prin extragere se dezaloca singur heap , nu mai are rost dezalocarea acum => crapa
	//dezalocareHeap(h);
}
