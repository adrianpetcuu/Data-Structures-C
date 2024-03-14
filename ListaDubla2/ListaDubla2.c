#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
}produs;

typedef struct
{
	produs* inf;
	struct nodLD* next;
	struct nodLD* prev;
}nodLD;


nodLD* inserare(nodLD* cap, nodLD** coada, produs* p)
{
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));
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
		nodLD* temp = cap;
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


void traversare(nodLD* cap)
{
	nodLD* temp = cap;
	while (temp != NULL)
	{
		printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
			*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->next;
	}
}

void traversareInversa(nodLD* coada)
{
	nodLD* temp = coada;
	while (temp != NULL)
	{
		printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
			*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->prev;
	}
}

void dezalocare(nodLD* cap)
{
	nodLD* temp = cap;
	while (temp != NULL)
	{
		nodLD* aux = temp->next;
		free(temp->inf->cod);
		free(temp->inf->denumire);
		free(temp->inf);
		free(temp);
		temp = aux;
	}
}

void conversieListaVector(nodLD* cap, produs** vector, int* nr)
{
	nodLD* temp = cap;
	while (temp != NULL)
	{
		vector[*nr] = (produs*)malloc(sizeof(produs));
		vector[*nr]->cod = (int*)malloc(sizeof(int));
		*(vector[*nr]->cod) = *(temp->inf->cod);
		vector[*nr]->denumire = (char*)malloc((strlen(temp->inf->denumire) + 1) * sizeof(char));
		strcpy(vector[*nr]->denumire, temp->inf->denumire);
		vector[*nr]->pret = temp->inf->pret;
		vector[*nr]->cantitate = temp->inf->cantitate;
		(*nr)++;
		temp = temp->next;
	}
}

void stergereNodDupaNume(nodLD** cap, nodLD** coada, char* denumire)
{
	nodLD* temp = *cap;
	while (temp != NULL)
	{
		if (strcmp(temp->inf->denumire, denumire) == 0)
		{
			if (temp == *cap)
			{
				*cap = temp->next;
				if (*cap != NULL)
				{
					(*cap)->prev = NULL;
				}
			}
			else if (temp == *coada)
			{
				*coada = temp->prev;
				(*coada)->next = NULL;
			}
			else 
			{
				nodLD* anterior = temp->prev;
				nodLD* urmator = temp->next;
				anterior->next = urmator;
				urmator->prev = anterior;
			}
			free(temp->inf->cod);
			free(temp->inf->denumire);
			free(temp->inf);
			free(temp);
			return;
		}
		temp = temp->next;
	}
}

int main()
{
	nodLD* cap = NULL;
	nodLD* coada = NULL;
	int nrProd;
	char buffer[20];
	produs* p;
	printf("Numar produse: ");
	scanf("%d", &nrProd);
	for (int i = 0; i < nrProd; i++)
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
	printf("\n\n--------------traversare cap--------------\n");
	traversare(cap);
	printf("\n\n--------------traversare coada------------\n");
	traversareInversa(coada);
	int nr = 0;
	produs** vector = (produs**)malloc(nrProd * sizeof(produs*));
	printf("\n\n--------------conversie lista in vector-----------\n");
	conversieListaVector(cap, vector, &nr);
	for (int i = 0; i < nr; i++)
	{
		printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
			*(vector[i]->cod), vector[i]->denumire, vector[i]->pret, vector[i]->cantitate);
	}
	for (int i = 0; i < nr; i++)
	{
		free(vector[i]->cod);
		free(vector[i]->denumire);
		free(vector[i]);
	}
	free(vector);
	printf("\n\n----------------stergere nod dupa nume----------------\n");
	stergereNodDupaNume(&cap, &coada, "Apa");
	printf("\n\n--------------traversare cap--------------\n");
	traversare(cap);
	printf("\n\n--------------traversare coada------------\n");
	traversareInversa(coada);

	dezalocare(cap);
}
