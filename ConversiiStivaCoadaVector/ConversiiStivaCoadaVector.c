#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* nume;
	float medie;
} student;

typedef struct
{
	student inf;
	struct nodStiva* next;
} nodStiva;

typedef struct
{
	student inf;
	struct nodCoada* next;
} nodCoada;

void push(nodStiva** varf, student s)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
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

int pop(nodStiva** varf, student* s)
{
	if (*varf == NULL)
	{
		return -1;
	}
	else
	{
		s->cod = (*varf)->inf.cod;
		s->nume = (char*)malloc((strlen((*varf)->inf.nume) + 1) * sizeof(char));
		strcpy(s->nume, (*varf)->inf.nume);
		s->medie = (*varf)->inf.medie;
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->inf.nume);
		free(temp);
		return 0;
	}
}

void traversareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("\nCod: %d, Nume: %s, Medie: %5.2f\n", temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void put(nodCoada** prim, nodCoada** ultim, student s)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->next = NULL;
	if (*prim == NULL || *ultim == NULL)
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

int get(nodCoada** prim, nodCoada** ultim, student* s)
{
	if(*prim != NULL && *ultim != NULL)
	{
		s->cod = (*prim)->inf.cod;
		s->nume = (char*)malloc((strlen((*prim)->inf.nume) + 1) * sizeof(char));
		strcpy(s->nume, (*prim)->inf.nume);
		s->medie = (*prim)->inf.medie;
		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.nume);
		free(temp);
		return 0;
	}
	if (*prim == NULL)
	{
		*ultim == NULL;
		return -1;
	}
}

void traversareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nCod: %d, Nume: %s, Medie: %5.2f\n", temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void conversieStivaInCoada(nodStiva** varf, nodCoada** prim, nodCoada** ultim)
{
	student s;
	while (pop(varf, &s) == 0)
	{
		put(prim, ultim, s);
	}
}

void conversieCoadaInStiva(nodStiva** varf, nodCoada** prim, nodCoada** ultim)
{
	student s;
	while (get(prim, ultim, &s) == 0)
	{
		push(varf, s);
	}
}

void salvareCoadaInVector(nodCoada** prim, nodCoada** ultim, student* vector, int* nr)
{
	student s;
	while (get(prim, ultim, &s) == 0)
	{
		vector[*nr] = s;
		(*nr)++;
	}
}

void salvareStivaInVector(nodStiva** varf, student* vector, int* nr)
{
	student s;
	while (pop(varf, &s) == 0)
	{
		vector[*nr] = s;
		(*nr)++;
	}
}


int main()
{
	nodStiva* varf = NULL;
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	student s;
	int nrStud;
	char buffer[20];
	printf("Numar studenti: ");
	scanf("%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		printf("Cod: ");
		scanf("%d", &s.cod);
		printf("Nume: ");
		scanf("%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("Medie: ");
		scanf("%f", &s.medie);
		push(&varf, s);
		put(&prim, &ultim, s);
		free(s.nume);
	}
	printf("\n---------------Stiva--------------------\n");
	traversareStiva(varf);
	//printf("\n--------------Studentul extras---------------\n");
	//student* stud = (student*)malloc(sizeof(student));
	//pop(&varf, stud);
	//printf("\nCod: %d, Nume: %s, Medie: %5.2f\n", stud->cod, stud->nume, stud->medie); 
	//printf("\n---------------Stiva--------------------\n");
	//traversareStiva(varf);*/
	printf("\n---------------Coada--------------------\n");
	traversareCoada(prim);
	//printf("\n--------------Studentul extras--------------\n");
	//student* stud2 = (student*)malloc(sizeof(student));
	//get(&prim, &ultim, stud2);
	//printf("\nCod: %d, Nume: %s, Medie: %5.2f\n", stud2->cod, stud2->nume, stud2->medie); 
	//printf("\n----------------Coada--------------------\n");
	//traversareCoada(prim);

	/*printf("\n-----------------Conversie din stiva in coada-----------------\n");
	conversieStivaInCoada(&varf, &prim, &ultim);
	printf("\n---------------Stiva--------------------\n");
	traversareStiva(varf);
	printf("\n---------------Coada--------------------\n");
	traversareCoada(prim);

	printf("\n------------------Conversie din coada in stiva-----------------\n");
	conversieCoadaInStiva(&varf, &prim, &ultim);
	printf("\n---------------Stiva--------------------\n");
	traversareStiva(varf);
	printf("\n---------------Coada--------------------\n");
	traversareCoada(prim);*/

	printf("\n------------------Salvare din coada in vector----------------\n");
	int nr = 0;
	student* vector = (student*)malloc(nrStud * sizeof(student));
	salvareCoadaInVector(&prim, &ultim, vector, &nr);
	for (int i = 0; i < nr; i++)
	{
		printf("\nCod: %d, Nume: %s, Medie: %5.2f\n", vector[i].cod, vector[i].nume, vector[i].medie);
	}
	for (int i = 0; i < nr; i++)
	{
		free(vector[i].nume);
	}
	free(vector);




	printf("\n------------------Salvare din stiva in vector----------------\n");
	int nr2 = 0;
	student* vector2 = (student*)malloc(nrStud * sizeof(student));
	salvareStivaInVector(&varf, vector2, &nr2);
	for (int i = 0; i < nr; i++)
	{
		printf("\nCod: %d, Nume: %s, Medie: %5.2f\n", vector2[i].cod, vector2[i].nume, vector2[i].medie);
	}
	for (int i = 0; i < nr2; i++)
	{
		free(vector2[i].nume);
	}
	free(vector2);
	printf("\n---------------Stiva----------------\n");
	traversareStiva(varf);
	printf("\n---------------Coada----------------\n");
	traversareCoada(prim);


	
}
