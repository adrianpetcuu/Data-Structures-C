#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int numarVagon;
	char* firmaTransport;
	int numarBileteVandute;
	int capacitateVagon;
} vagon;

typedef struct
{
	vagon inf;
	struct nodLD* prev;
	struct nodLD* next;
} nodLD;

nodLD* inserareLD(nodLD* cap, nodLD** coada, vagon v)
{
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));
	nou->inf.numarVagon = v.numarVagon;
	nou->inf.firmaTransport = (char*)malloc((strlen(v.firmaTransport) + 1) * sizeof(char));
	strcpy(nou->inf.firmaTransport, v.firmaTransport);
	nou->inf.numarBileteVandute = v.numarBileteVandute;
	nou->inf.capacitateVagon = v.capacitateVagon;
	nou->prev = NULL;
	nou->next = NULL;
	if (cap == NULL)
	{
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodLD* temp = cap;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}
	return cap;
}

void traversare(nodLD* cap)
{
	nodLD* temp = cap;
	while (temp != NULL)
	{
		printf("\nNumar vagon: %d, Firma transport: %s, Numar bilete vandute: %d, Capacitate vagon: %d",
			temp->inf.numarVagon, temp->inf.firmaTransport, temp->inf.numarBileteVandute, temp->inf.capacitateVagon);
		temp = temp->next;
	}
}

void traversareInvers(nodLD* coada)
{
	nodLD* temp = coada;
	while (temp != NULL)
	{
		printf("\nNumar vagon: %d, Firma transport: %s, Numar bilete vandute: %d, Capacitate vagon: %d",
			temp->inf.numarVagon, temp->inf.firmaTransport, temp->inf.numarBileteVandute, temp->inf.capacitateVagon);
		temp = temp->prev;
	}
}

void dezalocareLD(nodLD* cap)
{
	nodLD* temp = cap;
	while (temp != NULL)
	{
		nodLD* aux = temp->next;
		free(temp->inf.firmaTransport);
		free(temp);
		temp = aux;
	}
}

void stergeVagoaneNumarBileteMinime(nodLD** cap, nodLD** coada)
{
	//verificam daca lista este goala
	if (*cap == NULL) { 
		printf("\nLista este goala.");
		return;
	}
	//daca lista nu este goala cautam minimul de bilete vandute in lista
	nodLD* temp = *cap;
	int min = temp->inf.numarBileteVandute;
	while (temp != NULL)
	{
		if (temp->inf.numarBileteVandute < min)
		{
			min = temp->inf.numarBileteVandute;
		}
		temp = temp->next;
	}
	printf("\n\nMinimul de bilete vandute: %d", min);

	//parcurgem lista pentru a sterge nodurile cu numar minim de bilete vandute
	//reinitializam temp cu adresa capului listei
	temp = *cap;
	nodLD* prev = NULL; //folosit pentru a tine evidenta nodului anterior in timpul iteratiei
	while (temp != NULL)
	{
		if (temp->inf.numarBileteVandute == min)
		{
			//daca nodul de sters este primul din lista
			if (temp == *cap)
			{
				*cap = temp->next; //actualizam capul listei
				if (*cap != NULL)
				{
					(*cap)->prev = NULL; //verificam daca lista nu a devenit goala si actualizam prev-ul capului
				}
				else
				{
					*coada = NULL; //daca lista devine goala, actualizam si coada
				}
				free(temp->inf.firmaTransport); //dezalocam memoria pentru firma de transport
				free(temp); //dezalocam memoria pentru tot nodul eliminat
				temp = *cap; //avansam la nodul urmator
			}
			//daca nodul de sters este ultimul din lista
			else if (temp == *coada)
			{
				*coada = temp->prev; //actualizam coada listei
				if (*coada != NULL)
				{
					(*coada)->next = NULL; //verificam daca lista nu a devenit goala si actualizam next-ul cozii
				}
				free(temp->inf.firmaTransport); //dezalocam memoria pentru firma de transport
				free(temp); //dezalocam memoria pentru tot nodul eliminat
				return; //terminam bucla daca am sters nodul coada
			}
			//daca nodul de sters este la mijlocul listei
			else
			{
				nodLD* anterior = temp->prev; //salvam nodul anterior
				nodLD* urmator = temp->next; //salvam nodul urmator
				anterior->next = urmator; //actualizam legatura nodului anterior cu nodul urmator
				urmator->prev = anterior; //actualizam legatura nodului urmator cu nodul anterior
				nodLD* aux = temp->next; //salvam temporar nodul anterior
				free(temp->inf.firmaTransport); //dezalocam memoria pentru firma de transport
				free(temp); //dezalocam memoria pentru tot nodul eliminat 
				temp = aux; //avansam la nodul urmator
			}
		}
		else
		{
			prev = temp; //actualizam nodul anterior
			temp = temp->next; //avansam la nodul urmator
		}
	}
}

typedef struct
{
	vagon* vector;
	int nrElem;
} heap;

void filtrareHeap(heap h, int index)
{
	int indexRad = index;
	int indexDr = 2 * index + 1;
	int indexSt = 2 * index + 2;

	if (indexSt < h.nrElem && h.vector[indexSt].numarBileteVandute < h.vector[indexRad].numarBileteVandute)
	{
		indexRad = indexSt;
	}
	if (indexDr < h.nrElem && h.vector[indexDr].numarBileteVandute < h.vector[indexRad].numarBileteVandute)
	{
		indexRad = indexDr;
	}
	//daca s-a facut interschimbarea
	if (indexRad != index)
	{
		vagon aux = h.vector[index];
		h.vector[index] = h.vector[indexRad];
		h.vector[indexRad] = aux;
		filtrareHeap(h, indexRad);
	}
}

heap inserareHeap(heap h, vagon v)
{
	vagon* vectorNou = (vagon*)malloc((h.nrElem + 1) * sizeof(vagon));
	for (int i = 0; i < h.nrElem; i++)
	{
		vectorNou[i].numarVagon = h.vector[i].numarVagon;
		vectorNou[i].firmaTransport = (char*)malloc((strlen(h.vector[i].firmaTransport) + 1) * sizeof(char));
		strcpy(vectorNou[i].firmaTransport, h.vector[i].firmaTransport);
		vectorNou[i].numarBileteVandute = h.vector[i].numarBileteVandute;
		vectorNou[i].capacitateVagon = h.vector[i].capacitateVagon;
	}
	h.nrElem++;
	vectorNou[h.nrElem - 1].numarVagon = v.numarVagon;
	vectorNou[h.nrElem - 1].firmaTransport = (char*)malloc((strlen(v.firmaTransport) + 1) * sizeof(char));
	strcpy(vectorNou[h.nrElem - 1].firmaTransport, v.firmaTransport);
	vectorNou[h.nrElem - 1].numarBileteVandute = v.numarBileteVandute;
	vectorNou[h.nrElem - 1].capacitateVagon = v.capacitateVagon;
	free(h.vector);
	h.vector = vectorNou;
	for (int i = (h.nrElem / 2) - 1; i >= 0; i--)
	{
		filtrareHeap(h, i);
	}
	return h;
}

heap salvareListaDublaInCoadaDePrioritati(heap h, nodLD* cap)
{
	nodLD* temp = cap;
	while (temp != NULL)
	{
		h = inserareHeap(h, temp->inf);
		temp = temp->next;
	}
	return h;
}

void afisareHeap(heap h)
{
	if (h.vector != NULL)
	{
		for (int i = 0; i < h.nrElem; i++)
		{
			printf("\nNumar vagon: %d, Firma transport: %s, Numar bilete vandute: %d, Capacitate vagon: %d",
				h.vector[i].numarVagon, h.vector[i].firmaTransport, h.vector[i].numarBileteVandute, h.vector[i].capacitateVagon);
		}
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

heap modificaNumarBileteVandute(heap h, int nrVagon, int nrBileteVandute)
{
	if (h.vector != NULL)
	{
		for (int i = 0; i < h.nrElem; i++)
		{
			if (h.vector[i].numarVagon == nrVagon)
			{
				h.vector[i].numarBileteVandute = nrBileteVandute;
			}
		}
		return h;
	}
	else
	{
		return h;
	}
}



void main()
{
	nodLD* cap = NULL;
	nodLD* coada = NULL;
	vagon v;
	int nrVagoane;
	char buffer[30];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrVagoane);
	for (int i = 0; i < nrVagoane; i++)
	{
		fscanf(f, "%d", &v.numarVagon);
		fscanf(f, "%s", buffer);
		v.firmaTransport = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(v.firmaTransport, buffer);
		fscanf(f, "%d", &v.numarBileteVandute);
		fscanf(f, "%d", &v.capacitateVagon);

		cap = inserareLD(cap, &coada, v);
		free(v.firmaTransport);
	}
	fclose(f);
	printf("Traversare lista dubla: ");
	traversare(cap);
	printf("\n\nTraversare inversa lista dubla:");
	traversareInvers(coada);

	stergeVagoaneNumarBileteMinime(&cap, &coada);
	printf("\n\n");
	printf("Traversare lista dubla dupa stergere: ");
	traversare(cap);
	printf("\n\nTraversare inversa lista dubla dupa stergere:");
	traversareInvers(coada);


	heap h;
	h.nrElem = 0;
	h.vector = NULL;
	h = salvareListaDublaInCoadaDePrioritati(h, cap);
	printf("\n\nAfisare coada de prioritati filtrata: ");
	afisareHeap(h);
	h.vector[1].capacitateVagon = 80;
	printf("\n\nAfisare coada de prioritati filtrata: ");
	afisareHeap(h);
	printf("\n\nAfisare lista (verificare deep copy): ");
	traversare(cap);
	printf("\n\nAfisare coada de prioritati dupa modificare: ");
	h = modificaNumarBileteVandute(h, 2, 40);
	afisareHeap(h);
	printf("\n\nAfisare coada de prioritati dupa modificare si filtrata: ");
	for (int i = (h.nrElem / 2) - 1; i >= 0; i--)
	{
		filtrareHeap(h, i);
	}
	afisareHeap(h);
	dezalocareHeap(h);
	dezalocareLD(cap);
	

}
