#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{ 
	int varsta;
	char* nume;
	float medie;
}student;

typedef struct
{
	student inf;
	struct nodCoada* next;
}nodCoada;

void put(nodCoada** prim, nodCoada** ultim, student s)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.varsta = s.varsta;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
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

int get(nodCoada** prim, nodCoada** ultim, student* s)
{
	if (*prim == NULL && *ultim == NULL)
	{
		return -1;
	}
	else
	{
		(*s).varsta = (*prim)->inf.varsta;
		(*s).nume = (char*)malloc((strlen((*prim)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*prim)->inf.nume);
		(*s).medie = (*prim)->inf.medie;
		nodCoada* temp = (*prim);
		(*prim) = (*prim)->next;
		free(temp->inf.nume);
		free(temp);
		if (*prim == NULL && *ultim != NULL)
		{
			*ultim = NULL;
		}
		return 0;
	}
}

void traversare(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nVarsta: %d, Nume: %s, Medie: %5.2f",
			temp->inf.varsta, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void conversieCoadaVector(nodCoada** prim, nodCoada** ultim, student* vector, int* nr, char* nume)
{
	student stud;
	while (get(prim, ultim, &stud) == 0)
	{
		if (strcmp(stud.nume, nume) == 0)
		{
			vector[*nr] = stud;
			(*nr)++;
		}
	}
}

int main()
{
	int nrStud;
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	student s;
	char buffer[20];
	printf("Numarul studenti: ");
	scanf("%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		printf("Varsta: ");
		scanf("%d", &s.varsta);
		printf("Nume: ");
		scanf("%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("Medie: ");
		scanf("%f", &s.medie);
		put(&prim, &ultim, s);
		free(s.nume);
	}
	printf("\n------------coada-----------\n"); 
	traversare(prim);
	//dezalocare coada
	while (get(&prim, &ultim, &s) == 0)
	{
		free(s.nume);
	}
	traversare(prim);
	//student stud;
	//get(&prim, &ultim, &stud);
	//get(&prim, &ultim, &stud);
	//get(&prim, &ultim, &stud);
	//get(&prim, &ultim, &stud);
	//printf("\n-----------coada--------------\n");
	//printf("----------dupa stergere---------\n");
	//traversare(prim);
	/*int nr = 0;
	printf("\n\n----------conversie coada vector----------\n");
	student* vector = (student*)malloc(nrStud * sizeof(student));
	conversieCoadaVector(&prim, &ultim, vector, &nr, "Adrian");
	for (int i = 0; i < nr; i++)
	{
		printf("\nVarsta: %d, Nume: %s, Medie: %5.2f",
			vector[i].varsta, vector[i].nume, vector[i].medie);
	}
	for (int i = 0; i < nr; i++)
	{
		free(vector[i].nume);  
	}
	free(vector);*/

}
