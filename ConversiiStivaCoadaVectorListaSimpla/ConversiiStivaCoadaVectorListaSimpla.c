#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int zi;
	int luna;
	int an;
}data;

typedef struct
{
	data dataCalendaristica;
	int cod;
	char* denumire;
	float timp;
} aplicatie;

typedef struct
{
	aplicatie inf;
	struct nodStiva* next;
} nodStiva;

typedef struct
{
	aplicatie inf;
	struct nodCoada* next;
} nodCoada;

typedef struct
{
	aplicatie inf;
	struct nodLS* next;
} nodLS;

void push(nodStiva** varf, aplicatie a)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.dataCalendaristica.zi = a.dataCalendaristica.zi;
	nou->inf.dataCalendaristica.luna = a.dataCalendaristica.luna;
	nou->inf.dataCalendaristica.an = a.dataCalendaristica.an;
	nou->inf.cod = a.cod;
	nou->inf.denumire = (char*)malloc((strlen(a.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, a.denumire);
	nou->inf.timp = a.timp;
	nou->next = NULL;
	if (*varf == NULL)
	{
		*varf = nou;
	}
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, aplicatie* a)
{
	if (*varf == NULL)
	{
		return -1;
	}
	else
	{
		(*a).dataCalendaristica.zi = (*varf)->inf.dataCalendaristica.zi;
		(*a).dataCalendaristica.luna = (*varf)->inf.dataCalendaristica.luna;
		(*a).dataCalendaristica.an = (*varf)->inf.dataCalendaristica.an;
		(*a).cod = (*varf)->inf.cod;
		(*a).denumire = (char*)malloc((strlen((*varf)->inf.denumire) + 1) * sizeof(char));
		strcpy((*a).denumire, (*varf)->inf.denumire);
		(*a).timp = (*varf)->inf.timp;
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->inf.denumire);
		free(temp);
		return 0;
	}
}

void traversareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("Data: %d/%d/%d, Cod: %d, Denumire: %s, Timp: %5.2f\n",
			temp->inf.dataCalendaristica.zi, temp->inf.dataCalendaristica.luna,
			temp->inf.dataCalendaristica.an, temp->inf.cod, temp->inf.denumire, temp->inf.timp);
		temp = temp->next;
	}
}

void put(nodCoada** prim, nodCoada** ultim, aplicatie a)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.dataCalendaristica.zi = a.dataCalendaristica.zi;
	nou->inf.dataCalendaristica.luna = a.dataCalendaristica.luna;
	nou->inf.dataCalendaristica.an = a.dataCalendaristica.an;
	nou->inf.cod = a.cod;
	nou->inf.denumire = (char*)malloc((strlen(a.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, a.denumire);
	nou->inf.timp = a.timp;
	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, aplicatie* a)
{
	if (*prim == NULL && *ultim == NULL)
	{
		return -1;
	}
	else
	{
		(*a).dataCalendaristica.zi = (*prim)->inf.dataCalendaristica.zi;
		(*a).dataCalendaristica.luna = (*prim)->inf.dataCalendaristica.luna;
		(*a).dataCalendaristica.an = (*prim)->inf.dataCalendaristica.an;
		(*a).cod = (*prim)->inf.cod;
		(*a).denumire = (char*)malloc((strlen((*prim)->inf.denumire) + 1) * sizeof(char));
		strcpy((*a).denumire, (*prim)->inf.denumire);
		(*a).timp = (*prim)->inf.timp;
		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.denumire);
		free(temp);
		if (*prim == NULL && *ultim != NULL)
		{
			*ultim = NULL;
		}
		return 0;
	}
}

void traversareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("Data: %d/%d/%d, Cod: %d, Denumire: %s, Timp: %5.2f\n",
			temp->inf.dataCalendaristica.zi, temp->inf.dataCalendaristica.luna,
			temp->inf.dataCalendaristica.an, temp->inf.cod, temp->inf.denumire, temp->inf.timp);
		temp = temp->next;
	}
}


void inserareLS(nodLS** cap, aplicatie a)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.dataCalendaristica.zi = a.dataCalendaristica.zi;
	nou->inf.dataCalendaristica.luna = a.dataCalendaristica.luna;
	nou->inf.dataCalendaristica.an = a.dataCalendaristica.an;
	nou->inf.cod = a.cod;
	nou->inf.denumire = (char*)malloc((strlen(a.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, a.denumire);
	nou->inf.timp = a.timp;
	nou->next = NULL;
	if (*cap == NULL)
	{
		*cap = nou;
	}
	else
	{
		nodLS* temp = *cap;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("Data: %d/%d/%d, Cod: %d, Denumire: %s, Timp: %5.2f\n",
			temp->inf.dataCalendaristica.zi, temp->inf.dataCalendaristica.luna,
			temp->inf.dataCalendaristica.an, temp->inf.cod, temp->inf.denumire, temp->inf.timp);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = aux;
	}
}


void conversieStivaInVector(nodStiva** varf, aplicatie* vector, int* nr)
{
	aplicatie a;
	while (pop(varf, &a) == 0)
	{
		if (a.dataCalendaristica.an >= 2023)
		{
			vector[*nr] = a;
			(*nr)++;
		}	
	}
}

void conversieCoadaInVector(nodCoada** prim, nodCoada** ultim, aplicatie* vector2, int* nr2)
{
	aplicatie a;
	while (get(prim, ultim, &a) == 0)
	{
		vector2[*nr2] = a;
		(*nr2)++;
	}
}

void conversieStivaInCoada(nodStiva** varf, nodCoada** prim, nodCoada** ultim)
{
	aplicatie a;
	while (pop(varf, &a) == 0)
	{
		put(prim, ultim, a);
	}
}

void conversieCoadaInStiva(nodStiva** varf, nodCoada** prim, nodCoada** ultim)
{
	aplicatie a;
	while (get(prim, ultim, &a) == 0)
	{
		push(varf, a);
	}
}

void conversieStivaInListaSimpla(nodLS** cap, nodStiva** varf)
{
	aplicatie a;
	while (pop(varf, &a) == 0)
	{
		inserareLS(cap, a);
	}
}

void conversieCoadaInListaSimpla(nodLS** cap, nodCoada** prim, nodCoada** ultim)
{
	aplicatie a;
	while (get(prim, ultim, &a) == 0)
	{
		inserareLS(cap, a);
	}
}

void conversieListaSimplaInStiva(nodLS** cap, nodStiva** varf) {
	nodLS* temp = *cap;
	while (temp != NULL) {
		aplicatie a;
		a.dataCalendaristica.zi = temp->inf.dataCalendaristica.zi;
		a.dataCalendaristica.luna = temp->inf.dataCalendaristica.luna;
		a.dataCalendaristica.an = temp->inf.dataCalendaristica.an;
		a.cod = temp->inf.cod;
		a.denumire = (char*)malloc((strlen(temp->inf.denumire) + 1) * sizeof(char));
		strcpy(a.denumire, temp->inf.denumire);
		a.timp = temp->inf.timp;

		push(varf, a);

		nodLS* aux = temp->next;
		free(temp->inf.denumire);
		free(temp); 
		temp = aux;
	}
	*cap = NULL;
}

void conversieListaSimplaInCoada(nodLS** cap, nodCoada** prim, nodCoada** ultim)
{
	nodLS* temp = *cap;
	while (temp != NULL)
	{
		aplicatie a;
		a.dataCalendaristica.zi = temp->inf.dataCalendaristica.zi;
		a.dataCalendaristica.luna = temp->inf.dataCalendaristica.luna;
		a.dataCalendaristica.an = temp->inf.dataCalendaristica.an;
		a.cod = temp->inf.cod;
		a.denumire = (char*)malloc((strlen(temp->inf.denumire) + 1) * sizeof(char));
		strcpy(a.denumire, temp->inf.denumire);
		a.timp = temp->inf.timp;

		put(prim, ultim, a);

		nodLS* aux = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = aux;
	}
	*cap = NULL;
}

void main()
{
	nodStiva* varf = NULL;
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	nodLS* cap = NULL;
	int nrAplicatii;
	char buffer[20];
	aplicatie a;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrAplicatii);
	for (int i = 0; i < nrAplicatii; i++)
	{
		fscanf(f, "%d", &a.dataCalendaristica.zi);
		fscanf(f, "%d", &a.dataCalendaristica.luna);
		fscanf(f, "%d", &a.dataCalendaristica.an);
		fscanf(f, "%d", &a.cod);
		fscanf(f, "%s", buffer);
		a.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(a.denumire, buffer);
		fscanf(f, "%f", &a.timp);
		push(&varf, a);
		put(&prim, &ultim, a);
		free(a.denumire);
	}
	fclose(f);
	printf("-------------------Afisare Stiva-------------\n");
	traversareStiva(varf);
	aplicatie extrasa;
	pop(&varf, &extrasa);
	printf("\n-------------------Aplicatie extrasa-----------\n");
	printf("Data: %d/%d/%d, Cod: %d, Denumire: %s, Timp: %5.2f\n",
		extrasa.dataCalendaristica.zi, extrasa.dataCalendaristica.luna,
		extrasa.dataCalendaristica.an, extrasa.cod, extrasa.denumire, extrasa.timp);
	printf("\n\n-------------------Afisare Stiva-------------\n");
	traversareStiva(varf);
	//dezalocare stiva
	//while (pop(&varf, &extrasa) == 0)
	//{
	//	free(extrasa.denumire);
	//}
	/*int nr = 0;
	aplicatie* vector = (aplicatie*)malloc(nrAplicatii * sizeof(aplicatie));
	conversieStivaInVector(&varf, vector, &nr);
	printf("\n--------------Afisare Vector--------------------\n");
	for (int i = 0; i < nr; i++)
	{
		printf("Data: %d/%d/%d, Cod: %d, Denumire: %s, Timp: %5.2f\n",
			vector[i].dataCalendaristica.zi, vector[i].dataCalendaristica.luna,
			vector[i].dataCalendaristica.an, vector[i].cod, vector[i].denumire, vector[i].timp);
	}
	for (int i = 0; i < nr; i++)
	{
		free(vector[i].denumire);
	}
	free(vector);*/
	printf("\n\n-------------------Afisare Coada-------------\n");
	traversareCoada(prim);

	aplicatie extras;
	get(&prim, &ultim, &extras);
	printf("\n-------------------Aplicatie extrasa-----------\n");
	printf("Data: %d/%d/%d, Cod: %d, Denumire: %s, Timp: %5.2f\n",
		extras.dataCalendaristica.zi, extras.dataCalendaristica.luna,
		extras.dataCalendaristica.an, extras.cod, extras.denumire, extras.timp);
	printf("\n\n-------------------Afisare Coada-------------\n");
	traversareCoada(prim);
	//dezalocare coada
	/*while (get(&prim, &ultim, &extras) == 0)
	{
		free(extras.denumire);
	}*/
	/*int nr2 = 0;
	aplicatie* vector2 = (aplicatie*)malloc(nrAplicatii * sizeof(aplicatie));
	conversieCoadaInVector(&prim, &ultim, vector2, &nr2);
	printf("\n-------------------Afisare Vector------------------\n");
	for (int i = 0; i < nr2; i++)
	{
		printf("Data: %d/%d/%d, Cod: %d, Denumire: %s, Timp: %5.2f\n",
			vector2[i].dataCalendaristica.zi, vector2[i].dataCalendaristica.luna,
			vector2[i].dataCalendaristica.an, vector2[i].cod, vector2[i].denumire, vector2[i].timp);
	}
	for (int i = 0; i < nr2; i++)
	{
		free(vector2[i].denumire);
	}
	free(vector2);*/
	//printf("\n\n-------------------Afisare Coada-------------\n");
	//traversareCoada(prim);


	conversieStivaInCoada(&varf, &prim, &ultim);
	printf("\n\n-------------------Afisare Stiva-------------\n");
	traversareStiva(varf);
	printf("\n\n-------------------Afisare Coada-------------\n");
	traversareCoada(prim);

	//conversieCoadaInStiva(&varf, &prim, &ultim);
	//printf("\n\n-------------------Afisare Stiva-------------\n");
	//traversareStiva(varf);
	//printf("\n\n-------------------Afisare Coada-------------\n");
	//traversareCoada(prim);

	//conversieStivaInListaSimpla(&cap, &varf);
	//printf("\n\n-------------------Afisare Stiva-------------\n");
	//traversareStiva(varf);
	//printf("\n\n-------------------Afisare Lista-------------\n");
	//traversareLS(cap);

	conversieCoadaInListaSimpla(&cap, &prim, &ultim);
	printf("\n\n-------------------Afisare Coada-------------\n");
	traversareCoada(prim);
	printf("\n\n-------------------Afisare Lista-------------\n");
	traversareLS(cap);

	conversieListaSimplaInStiva(&cap, &varf);
	printf("\n\n-------------------Afisare Lista-------------\n");
	traversareLS(cap);
	printf("\n\n-------------------Afisare Stiva-------------\n");
	traversareStiva(varf);

	//conversieListaSimplaInCoada(&cap, &prim, &ultim);
	//printf("\n\n-------------------Afisare Lista-------------\n");
	//traversareLS(cap);
	//printf("\n\n-------------------Afisare Coada-------------\n");
	//traversareCoada(prim);
}
