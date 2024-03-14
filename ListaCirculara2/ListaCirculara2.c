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
	struct nodLC* prev;
	struct nodLC* next;
}nodLC;

nodLC* inserare(nodLC* cap, nodLC** coada, produs* p)
{
	nodLC* nou = (nodLC*)malloc(sizeof(nodLC));
	nou->inf = (produs*)malloc(sizeof(produs));
	nou->inf->cod = (int*)malloc(sizeof(int));
	*(nou->inf->cod) = *(p->cod);
	nou->inf->denumire = (char*)malloc((strlen(p->denumire) + 1) * sizeof(char));
	strcpy(nou->inf->denumire, p->denumire);
	nou->inf->pret = p->pret;
	nou->inf->cantitate = p->cantitate;
	if (cap == NULL)
	{
		cap = nou;
		(*coada) = nou;
		nou->prev = nou;
		nou->next = nou;
	}
	else
	{
		nodLC* temp = cap;
		while (temp->next != cap)
		{
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		(*coada) = nou;
		(*coada)->next = cap;
		cap->prev = (*coada);
	}
	return cap;
}

void traversare(nodLC* cap)
{
	nodLC* temp = cap;
	while (temp->next != cap)
	{
		printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
			*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->next;
	}
	printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
		*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
}

void traversareInversa(nodLC* coada)
{
	nodLC* temp = coada;
	while (temp->prev != coada)
	{
		printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
			*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->prev;
	}
	printf("\nCod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f",
		*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
}

void dezalocare(nodLC* cap)
{
	nodLC* temp = cap;
	while (temp->next != cap)
	{
		nodLC* aux = temp->next;
		free(temp->inf->cod);
		free(temp->inf->denumire);
		free(temp->inf);
		free(temp);
		temp = aux;
	}
	free(temp->inf->cod);
	free(temp->inf->denumire);
	free(temp->inf);
	free(temp);
}

void conversieListaVector(nodLC* cap, produs** vector, int* nr)
{
	nodLC* temp = cap;
	while (temp->next != cap)
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
	vector[*nr] = (produs*)malloc(sizeof(produs));
	vector[*nr]->cod = (int*)malloc(sizeof(int));
	*(vector[*nr]->cod) = *(temp->inf->cod);
	vector[*nr]->denumire = (char*)malloc((strlen(temp->inf->denumire) + 1) * sizeof(char));
	strcpy(vector[*nr]->denumire, temp->inf->denumire);
	vector[*nr]->pret = temp->inf->pret;
	vector[*nr]->cantitate = temp->inf->cantitate;
	(*nr)++;
}

void stergereNodDupaDenumire(nodLC** cap, nodLC** coada, char* denumire)
{
	nodLC* temp = *cap;
	while (temp != NULL)
	{
		if (strcmp(temp->inf->denumire, denumire) == 0)
		{
			if (temp == *cap)
			{
				*cap = temp->next;
				(*cap)->prev = *coada;
				(*coada)->next = *cap;
			}
			else if (temp == *coada)
			{
				*coada = temp->prev;
				(*coada)->next = *cap;	
			} 
			else
			{
				nodLC* anterior = temp->prev; 
				nodLC* urmator = temp->next;
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
	nodLC* cap = NULL;
	nodLC* coada = NULL;
	produs* p;
	int nrProd;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrProd);
	for (int i = 0; i < nrProd; i++)
	{
		p = (produs*)malloc(sizeof(produs));
		p->cod = (int*)malloc(sizeof(int));
		fscanf(f, "%d", p->cod);
		fscanf(f, "%s", buffer);
		p->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->denumire, buffer);
		fscanf(f, "%f", &p->pret);
		fscanf(f, "%f", &p->cantitate);
		cap = inserare(cap, &coada, p);
		free(p->cod);
		free(p->denumire);
		free(p);
	}
	fclose(f);
	printf("\n--------------traversare cap-----------\n");
	traversare(cap);
	printf("\n\n--------------traversare coada---------\n");
	traversareInversa(coada);
	printf("\n\n--------------conversie lista vector------------\n");
	produs** vector = (produs**)malloc(nrProd * sizeof(produs*));
	int nr = 0;
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

	printf("\n\n---------------------stergere nod----------------\n");
	stergereNodDupaDenumire(&cap, &coada, "Apa");  
	printf("\n--------------traversare cap-----------\n");
	traversare(cap);
	printf("\n\n--------------traversare coada---------\n");
	traversareInversa(coada);

	dezalocare(cap);
}
