#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* firmaTransport;
	int numarProduseComandate;
	float sumaPlata;
} comanda;

typedef struct
{
	comanda inf;
	struct nodCoada* next;
} nodCoada;


void put(nodCoada** prim, nodCoada** ultim, comanda c)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.cod = c.cod;
	nou->inf.firmaTransport = (char*)malloc((strlen(c.firmaTransport) + 1) * sizeof(char));
	strcpy(nou->inf.firmaTransport, c.firmaTransport);
	nou->inf.numarProduseComandate = c.numarProduseComandate;
	nou->inf.sumaPlata = c.sumaPlata;
	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

void traversareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nCod: %d, Firma transport: %s, Numar produse comandate: %d, Suma plata: %5.2f",
			temp->inf.cod, temp->inf.firmaTransport, temp->inf.numarProduseComandate, temp->inf.sumaPlata);
		temp = temp->next;
	}
}

int get(nodCoada** prim, nodCoada** ultim, comanda* extrasa)
{
	if (*prim == NULL && *ultim == NULL)
	{
		return -1;
	}
	else
	{
		extrasa->cod = (*prim)->inf.cod;
		extrasa->firmaTransport = (char*)malloc((strlen((*prim)->inf.firmaTransport) + 1) * sizeof(char));
		strcpy(extrasa->firmaTransport, (*prim)->inf.firmaTransport);
		extrasa->numarProduseComandate = (*prim)->inf.numarProduseComandate;
		extrasa->sumaPlata = (*prim)->inf.sumaPlata;
		nodCoada* temp = (*prim);
		(*prim) = (*prim)->next;
		free(temp->inf.firmaTransport);
		free(temp);
		if (*prim == NULL && *ultim != NULL)
		{
			*ultim = NULL;
		}
		return 0;
	}
}	

void extragereComenziInVector(nodCoada** prim, nodCoada** ultim, comanda* vector, int* nr, char* firmaTransport, float* sumaTotala)
{
	comanda extrasa;
	while (get(prim, ultim, &extrasa) == 0)
	{
		if (strcmp(extrasa.firmaTransport, firmaTransport) == 0)
		{
			vector[*nr].cod = extrasa.cod;
			vector[*nr].firmaTransport = (char*)malloc((strlen(extrasa.firmaTransport) + 1) * sizeof(char));
			strcpy(vector[*nr].firmaTransport, extrasa.firmaTransport);
			vector[*nr].numarProduseComandate = extrasa.numarProduseComandate;
			vector[*nr].sumaPlata = extrasa.sumaPlata;
			(*sumaTotala) += extrasa.sumaPlata;
			(*nr)++;
		}
	}
}

typedef struct
{
	comanda* vector;
	int nrElem;
} heap;

void filtrareHeap(heap h, int index)
{
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;
	if (indexSt < h.nrElem && h.vector[indexSt].sumaPlata > h.vector[indexRad].sumaPlata)
	{
		indexRad = indexSt;
	}
	if (indexDr < h.nrElem && h.vector[indexDr].sumaPlata > h.vector[indexRad].sumaPlata)
	{
		indexRad = indexDr;
	}
	//daca s-a facut interschimbarea
	if (indexRad != index)
	{
		comanda aux = h.vector[index];
		h.vector[index] = h.vector[indexRad];
		h.vector[indexRad] = aux;
		filtrareHeap(h, indexRad);
	}
}

heap inserareHeap(heap h, comanda c)
{
	comanda* vectorNou = (comanda*)malloc((h.nrElem + 1) * sizeof(comanda));
	for (int i = 0; i < h.nrElem; i++)
	{
		vectorNou[i].cod = h.vector[i].cod;
		vectorNou[i].firmaTransport = (char*)malloc((strlen(h.vector[i].firmaTransport) + 1) * sizeof(char));
		strcpy(vectorNou[i].firmaTransport, h.vector[i].firmaTransport);
		vectorNou[i].numarProduseComandate = h.vector[i].numarProduseComandate;
		vectorNou[i].sumaPlata = h.vector[i].sumaPlata;
	}
	h.nrElem++;
	vectorNou[h.nrElem - 1].cod = c.cod;
	vectorNou[h.nrElem - 1].firmaTransport = (char*)malloc((strlen(c.firmaTransport) + 1) * sizeof(char));
	strcpy(vectorNou[h.nrElem - 1].firmaTransport, c.firmaTransport);
	vectorNou[h.nrElem - 1].numarProduseComandate = c.numarProduseComandate;
	vectorNou[h.nrElem - 1].sumaPlata = c.sumaPlata;
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
			printf("\nCod: %d, Firma transport: %s, Numar produse comandate: %d, Suma plata: %5.2f",
			h.vector[i].cod, h.vector[i].firmaTransport, h.vector[i].numarProduseComandate, h.vector[i].sumaPlata);
		}
	}
}

heap modificareNumarProduseComandate(heap h, int cod, int nrProduseComandate)
{
	if (h.vector != NULL)
	{
		for (int i = 0; i < h.nrElem; i++)
		{
			if (h.vector[i].cod == cod)
			{
				h.vector[i].numarProduseComandate = nrProduseComandate;
			}
		}
		return h;
	}
	else
	{
		return h;
	}
}

void dezalocareHeap(heap h)
{
	if (h.vector != NULL)
	{
		for (int i = 0; i < h.nrElem; i++)
		{
			free(h.vector[i].firmaTransport);
		}
		free(h.vector);
	}
}

void main()
{
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	comanda c;
	int nrComenzi;
	char buffer[30];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrComenzi);
	for (int i = 0; i < nrComenzi; i++)
	{
		fscanf(f, "%d", &c.cod);
		fscanf(f, "%s", buffer);
		c.firmaTransport = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.firmaTransport, buffer);
		fscanf(f, "%d", &c.numarProduseComandate);
		fscanf(f, "%f", &c.sumaPlata);

		put(&prim, &ultim, c);
		free(c.firmaTransport);
	}
	fclose(f);


	nodCoada* prim2 = NULL;
	nodCoada* ultim2 = NULL;
	printf("Afisare coada: ");
	comanda extrasa;
	while (get(&prim, &ultim, &extrasa) == 0)
	{
		printf("\nCod: %d, Firma transport: %s, Numar produse comandate: %d, Suma plata: %5.2f",
			extrasa.cod, extrasa.firmaTransport, extrasa.numarProduseComandate, extrasa.sumaPlata);
		put(&prim2, &ultim2, extrasa);
	}
	printf("\n\nAfisare coada dupa reconstruire:");
	traversareCoada(prim2);

	comanda* vector = (comanda*)malloc(nrComenzi * sizeof(comanda));
	int nr = 0;
	float sumaTotala = 0.0f;
	extragereComenziInVector(&prim2, &ultim2, vector, &nr, "Glovo", &sumaTotala);
	printf("\n\nAfisare elementele vector:");
	for (int i = 0; i < nr; i++)
	{
		printf("\nCod: %d, Firma transport: %s, Numar produse comandate: %d, Suma plata: %5.2f",
			vector[i].cod, vector[i].firmaTransport, vector[i].numarProduseComandate, vector[i].sumaPlata);
	}
	printf("\nSuma totala de plata este: %5.2f", sumaTotala);

	heap h;
	h.nrElem = 0;
	h.vector = NULL;
	for (int i = 0; i < nr; i++)
	{
		h = inserareHeap(h, vector[i]);
	}
	//dezalocare vector
	for (int i = 0; i < nr; i++)
	{
		free(vector[i].firmaTransport);
	}
	free(vector);

	printf("\n\nAfisare coada de prioritati:");
	afisareHeap(h);

	h = modificareNumarProduseComandate(h, 7, 8);
	printf("\n\nAfisare coada de prioritati dupa modificare:");
	afisareHeap(h);

	dezalocareHeap(h);
}
