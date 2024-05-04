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
	struct nodLS* prev;
	struct nodLS* next;	
} nodLS;

nodLS* inserare(nodLS* cap, nodLS** coada, student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	//nou->prev = NULL;
	//nou->next = NULL;
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
	if (temp != NULL)
	{
		while (temp->next != cap)
		{
			printf("\nNumar matricol: %d, Nume: %s, Medie: %5.2f\n",
				temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
			temp = temp->next;
		}
		printf("\nNumar matricol: %d, Nume: %s, Medie: %5.2f\n",
			temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
	}
	
}

void traversareInversa(nodLS* coada)
{
	nodLS* temp = coada;
	if (temp != NULL)
	{
		while (temp->prev != coada)
		{
			printf("\nNumar matricol: %d, Nume: %s, Medie: %5.2f\n",
				temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
			temp = temp->prev;
		}
		printf("\nNumar matricol: %d, Nume: %s, Medie: %5.2f\n",
			temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
	}
	
}

void dezalocare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = aux;
	}
}

void salvareVector(nodLS* cap, student* vector, int* nr)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		//vector[*nr] = temp->inf;
		vector[*nr].nrMatricol = temp->inf.nrMatricol;
		vector[*nr].nume = (char*)malloc((strlen(temp->inf.nume) + 1) * sizeof(char));
		strcpy(vector[*nr].nume, temp->inf.nume);
		vector[*nr].medie = temp->inf.medie;
		(*nr)++;
		temp = temp->next;
	}
	vector[*nr].nrMatricol = temp->inf.nrMatricol;
	vector[*nr].nume = (char*)malloc((strlen(temp->inf.nume) + 1) * sizeof(char));
	strcpy(vector[*nr].nume, temp->inf.nume);
	vector[*nr].medie = temp->inf.medie;
	(*nr)++;
}

void stergereStudentDupaNume(nodLS** cap, nodLS** coada, char* nume)
{
	if (*cap == NULL)
	{
		return;
	}
	nodLS* temp = *cap;
	if (temp->next == *cap && temp->prev == *cap && temp->next == *coada && temp->prev == *coada &&
		(strcmp(temp->inf.nume, nume) == 0))
	{
		*cap = NULL;
		*coada = NULL;
		free(temp->inf.nume);
		free(temp);
		return;
	}
	while (temp->next != *cap)
	{
		if (strcmp(temp->inf.nume, nume) == 0)
		{
			if (temp->prev == *coada)
			{
				*cap = temp->next;
				(*coada)->next = *cap;
				(*cap)->prev = *coada;

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
	if (strcmp(temp->inf.nume, nume) == 0)
	{
		nodLS* anterior = temp->prev;
		nodLS* urmator = temp->next;
		anterior->next = urmator;
		urmator->prev = anterior;
		if (temp == *coada)
		{
			(*coada) = (*coada)->prev;
		}
		free(temp->inf.nume);
		free(temp);
	}
}


int main()
{
	nodLS* cap = NULL;
	nodLS* coada = NULL;
	student s;
	int nrStud;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);
		cap = inserare(cap, &coada, s);
		free(s.nume);
	}
	fclose(f);

	printf("\n------------Afisare Lista-------------\n");
	traversare(cap);
	printf("\n------------Afisare Lista Inversata-------------\n");
	traversareInversa(coada);
	printf("\n------------Conversie din stiva in vector---------------\n");
	int nr = 0;
	student* vector = (student*)malloc(nrStud * sizeof(student));
	salvareVector(cap, vector, &nr);
	for (int i = 0; i < nr; i++)
	{
		printf("\nNumar matricol: %d, Nume: %s, Medie: %5.2f\n",
			vector[i].nrMatricol, vector[i].nume, vector[i].medie);
	}
	for (int i = 0; i < nr; i++)
	{
		free(vector[i].nume);
	}
	free(vector);
	printf("\n------------Afisare Lista-------------\n");
	traversare(cap);
	printf("\n------------Stergere Student Dupa Nume-----------\n");
	stergereStudentDupaNume(&cap, &coada, "Gigel");
	printf("\n------------Afisare Lista-------------\n");
	traversare(cap);
	printf("\n------------Afisare Lista Inversata-------------\n");
	traversareInversa(coada);
	stergereStudentDupaNume(&cap, &coada, "Dorel");
	printf("\n------------Afisare Lista-------------\n");
	traversare(cap);
	printf("\n------------Afisare Lista Inversata-------------\n");
	traversareInversa(coada);
	stergereStudentDupaNume(&cap, &coada, "Maricica");
	printf("\n------------Afisare Lista-------------\n");
	traversare(cap);
	printf("\n------------Afisare Lista Inversata-------------\n");
	traversareInversa(coada);
	stergereStudentDupaNume(&cap, &coada, "Vasile");
	printf("\n------------Afisare Lista-------------\n");
	traversare(cap);
	printf("\n------------Afisare Lista Inversata-------------\n");
	traversareInversa(coada);
	stergereStudentDupaNume(&cap, &coada, "Nicusor");
	printf("\n------------Afisare Lista-------------\n");
	traversare(cap);
	printf("\n------------Afisare Lista Inversata-------------\n");
	traversareInversa(coada);
	dezalocare(cap);
}
