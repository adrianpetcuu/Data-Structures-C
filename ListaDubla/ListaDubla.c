#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int* cod;  
	char* denumire;
	float pret;
	float cantitate;
} produs;

typedef struct
{
	produs* inf;
	struct nodLS* next, * prev;
} nodLS;

nodLS* inserare(nodLS* cap, nodLS** coada, produs* p)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf = (produs*)malloc(sizeof(produs));
	nou->inf->cod = (int*)malloc(sizeof(int));
	*(nou->inf->cod) = *(p->cod);
	nou->inf->denumire = (char*)malloc((strlen(p->denumire) + 1) * sizeof(char));
	strcpy(nou->inf->denumire, p->denumire);
	nou->inf->pret = p->pret;
	nou->inf->cantitate = p->cantitate;
	nou->prev = NULL;
	nou->next = NULL;
	if (cap == NULL)
	{
		cap = nou;
		(*coada) = nou;
	}
	else
	{
		nodLS* temp = cap;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		(*coada) = nou;
	}
	return cap;
}

void traversare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("Cod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f\n",
			*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->next; 
	}
}

void traversareInvers(nodLS* coada)
{
	nodLS* temp = coada;
	while (temp != NULL)
	{
		printf("Cod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f\n",
			*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->prev; 
	}
}

void dezalocare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->inf->cod);
		free(temp->inf->denumire);
		free(temp->inf);
		free(temp);
		temp = aux;
	}
}

void conversieListaVectori(nodLS* cap, produs** vect, int* n)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		//vect[*n] == temp->inf;
		vect[*n] = (produs*)malloc(sizeof(produs));
		vect[*n]->cod = (int*)malloc(sizeof(int));
		*(vect[*n]->cod) = *(temp->inf->cod);
		vect[*n]->denumire = (char*)malloc((strlen(temp->inf->denumire) + 1) * sizeof(char));
		strcpy(vect[*n]->denumire, temp->inf->denumire);
		vect[*n]->pret = temp->inf->pret;
		vect[*n]->cantitate = temp->inf->cantitate;
		(*n)++;
		temp = temp->next;
	}
}

int main()
{
	int nr;
	printf("Numar produse: ");
	scanf("%d", &nr);
	nodLS* cap, * coada;
	cap = NULL;
	coada = NULL;
	produs* p;
	char buffer[20];
	for (int i = 0; i < nr; i++)
	{
		p = (produs*)malloc(sizeof(produs));
		printf("Cod: ");
		p->cod = (int*)malloc(sizeof(int));
		scanf("%d", p->cod);
		printf("Denumire: ");
		scanf("%s", buffer);
		p->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->denumire, buffer);
		printf("Pret: ");
		scanf("%f", &p->pret);
		printf("Cantitate: ");
		scanf("%f", &p->cantitate);
		cap = inserare(cap, &coada, p);
		free(p->cod);
		free(p->denumire);
		free(p);
	}

	traversare(cap);
	printf("\n");
	traversareInvers(coada);
	printf("\n-------conversie-----------\n");
	produs** vect = (produs**)malloc(nr * sizeof(produs*));
	int n = 0;
	conversieListaVectori(cap, vect, &n);
	for (int i = 0; i < nr; i++)
	{
		printf("Cod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f\n",
			*(vect[i]->cod), vect[i]->denumire, vect[i]->pret, vect[i]->cantitate);
	}
	for (int i = 0; i < nr; i++)
	{
		free(vect[i]->cod);
		free(vect[i]->denumire);
		free(vect[i]);
	}
	free(vect);

	dezalocare(cap);
}