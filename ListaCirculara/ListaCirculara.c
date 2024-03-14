#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int nrMatricol;
	char* nume;
	float medie;
} student;

typedef struct
{
	student inf; 
	struct nodLS* next, * prev;
} nodLS; 

nodLS* inserareNod(nodLS* cap, nodLS** coada, student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1 ) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	//nou->next = NULL;
	//nou->prev = NULL;
	if (cap == NULL)
	{
		nou->prev = nou;
		nou->next = nou;
		cap = nou;
		(*coada) = nou;
	}
	else
	{
		nodLS* temp = cap;
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

void traversare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		printf("Numar matricol: %d, Nume: %s, Medie: %5.2f\n",
			temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
	printf("Numar matricol: %d, Nume: %s, Medie: %5.2f\n",
		temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
}

void traversareInversa(nodLS* coada)
{
	nodLS* temp = coada;
	while (temp->prev != coada)
	{
		printf("Numar matricol: %d, Nume: %s, Medie: %5.2f\n",
			temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
		temp = temp->prev;
	}
	printf("Numar matricol: %d, Nume: %s, Medie: %5.2f\n",
		temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
}

void dezalocare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		nodLS* aux = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = aux;
	}
	free(temp->inf.nume);
	free(temp);
} 


void stergeNodDupaNume(nodLS** cap, nodLS** coada, char* nume)
{
	nodLS* temp = *cap;
	while (temp != NULL)
	{
		if (strcmp(temp->inf.nume, nume) == 0)
		{
			if (temp == *cap)
			{
				*cap = temp->next;
				(*cap)->prev = *coada;
				(*coada)->next = *cap;
			}
			else if(temp == *coada)
			{
				*coada = temp->prev;
				(*coada)->next = *cap;
			}
			else
			{
				nodLS* anterior = temp->prev;
				nodLS* urmator = temp->next;
				anterior->next = urmator;
				urmator->prev = anterior;
			}
			free(temp->inf.nume);
			free(temp);
			return;
		}
		temp = temp->next;
	}
}

void conversieListaInVector(nodLS* cap, student* vector, int* nr, float prag)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		if (temp->inf.medie > prag)
		{
			vector[*nr].nrMatricol = temp->inf.nrMatricol;
			vector[*nr].nume = (char*)malloc((strlen(temp->inf.nume) + 1) * sizeof(char));
			strcpy(vector[*nr].nume, temp->inf.nume);
			vector[*nr].medie = temp->inf.medie;
			(*nr)++;
		}
		temp = temp->next;
	}
	if (temp->inf.medie > prag)
	{
		vector[*nr].nrMatricol = temp->inf.nrMatricol;
		vector[*nr].nume = (char*)malloc((strlen(temp->inf.nume) + 1) * sizeof(char));
		strcpy(vector[*nr].nume, temp->inf.nume);
		vector[*nr].medie = temp->inf.medie;
		(*nr)++;
	}
}

int main()
{
	int nrStud;
	nodLS* cap = NULL;
	nodLS* coada = NULL;
	student s;
	char buffer[20];
	FILE* f = fopen("Fisier.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);
		cap = inserareNod(cap, &coada, s);
		free(s.nume); 
	}
	fclose(f);
	traversare(cap);
	printf("\n-----------------------------------\n");
	traversareInversa(coada);

	printf("\n--------------lista in vector doar stud cu medie > 9.5---------------\n");

	int nr = 0;
	student* vector = (student*)malloc(nrStud * sizeof(student));
	conversieListaInVector(cap, vector, &nr, 9.5f);
	for (int i = 0; i < nr; i++)
	{
		printf("Numar matricol: %d, Nume: %s, Medie: %5.2f\n",
			vector[i].nrMatricol, vector[i].nume, vector[i].medie);
	}

	for (int i = 0; i < nr; i++)
	{
		free(vector[i].nume);
	}
	free(vector);

	printf("\n---------------lista dupa stergere--------------------\n");

	stergeNodDupaNume(&cap, &coada, "Andreea");
	traversare(cap);
	printf("\n-----------------------------------\n");
	traversareInversa(coada);
	printf("\n-----------------------------------\n");

	
	dezalocare(cap);

}  
