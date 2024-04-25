#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int nrMatricol;
	char* nume;
	float medie;
} student;


//arbore binar de cautare
typedef struct
{
	student inf;
	struct nodArb* stanga;
	struct nodArb* dreapta;
} nodArb;

typedef struct
{
	student inf;
	struct nodLS* next;
} nodLS;

nodLS* inserareLS(nodLS* cap, student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->next = NULL;
	if (cap == NULL)
	{
		cap = nou;
	}
	else
	{
		nodLS* temp = cap;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
	return cap;
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f", temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* cap)
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

//functie creare nod
nodArb* creareNod(student s, nodArb* dr, nodArb* st)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

//functie inserare nod
nodArb* inserareNod(nodArb* rad, student s)
{
	if (rad != NULL)
	{
		if (s.nrMatricol < rad->inf.nrMatricol)
		{
			rad->stanga = inserareNod(rad->stanga, s);
			return rad;
		}
		else if (s.nrMatricol > rad->inf.nrMatricol)
		{
			rad->dreapta = inserareNod(rad->dreapta, s);
			return rad;
		}
		else
		{
			return rad;
		}
	}
	else
	{
		rad = creareNod(s, NULL, NULL);
		return rad;
	}
}


//parcurgere radacina-stanga-dreapta
void preordine(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
			rad->inf.nrMatricol, rad->inf.nume, rad->inf.medie);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

//parcurgere stanga-radacina-dreapta
void inordine(nodArb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->stanga);
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f", 
			rad->inf.nrMatricol, rad->inf.nume, rad->inf.medie);
		inordine(rad->dreapta);
	}
}

//parcurgere stanga-dreapta-radacina
void postordine(nodArb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->stanga);
		postordine(rad->dreapta);
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
			rad->inf.nrMatricol, rad->inf.nume, rad->inf.medie);
	}
}


void dezalocare(nodArb* rad)
{
	if (rad != NULL)
	{
		//dezalocare preordine
		//nodArb* st = rad->stanga;
		//nodArb* dr = rad->dreapta;
		//free(rad->inf.nume);
		//free(rad);
		//dezalocare(st);
		//dezalocare(dr);

		//dezalocare postordine
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->inf.nume);
		free(rad);
	}
}

//salvare noduri frunza in vector
void salvareVectorFrunze(nodArb* rad, student* vector, int* nr)
{
	if (rad != NULL)
	{
		if (rad->stanga == NULL && rad->dreapta == NULL)
		{
			vector[*nr] = rad->inf; //shallow copy
			(*nr)++;
		}
		salvareVectorFrunze(rad->stanga, vector, nr);
		salvareVectorFrunze(rad->dreapta, vector, nr);
	}
}

//numara cati studenti au media peste 9
void nrStudentiMediePrag(nodArb* rad, int* nr, float prag)
{
	if (rad != NULL)
	{
		if (rad->inf.medie >= prag)
		{
			(*nr)++;
		}
		nrStudentiMediePrag(rad->stanga, nr, prag);
		nrStudentiMediePrag(rad->dreapta, nr, prag);
	}
}

//inserare intr-o lista simpla doar studentii al caror nume incepe cu litera G
void inserareStudentiGinLista(nodArb* rad, nodLS** cap)
{
	if (rad != NULL)
	{
		if (rad->inf.nume[0] == 'G')
		{
			*cap = inserareLS(*cap, rad->inf);
		}
		inserareStudentiGinLista(rad->stanga, cap);
		inserareStudentiGinLista(rad->dreapta, cap);
	}
}

//functie de maxim
int maxim(int a, int b)
{
	int max = a;
	if (max < b)
	{
		max = b;
	}
	return max;
}

//functie pentru a determina inaltimea arborelui
int inaltimeArbore(nodArb* rad)
{
	if (rad != NULL)
	{
		return 1 + maxim(inaltimeArbore(rad->stanga), inaltimeArbore(rad->dreapta));
	}
	else
	{
		return 0;
	}
}

//functie pentru cautarea unui nod
nodArb* cautare(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->inf.nrMatricol)
		{
			return rad;
		}
		else if (cheie < rad->inf.nrMatricol)
		{
			rad->stanga = cautare(rad->stanga, cheie);
		}
		else if (cheie > rad->inf.nrMatricol)
		{
			rad->dreapta = cautare(rad->dreapta, cheie);
		}
	}
	else
	{
		return NULL;
	}
}


void main()
{
	nodArb* rad = NULL;
	nodLS* cap = NULL;
	int nrStud;
	char buffer[20];
	student s;
	//datele in fisier trebuie sa fie nrMatricol mai mic/mai mare/etc
	//NU IN ORDINE CRESCATOARE PENTRU CA TOATE SE DUC SPRE DREAPTA;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		rad = inserareNod(rad, s);
		free(s.nume);
	}
	fclose(f);

	preordine(rad);
	printf("\n-----------------\n");
	preordine(rad->stanga);
	//inordine(rad);
	printf("\n-----------------\n");
	preordine(rad->dreapta);
	//postordine(rad);


	printf("\n\n-----------------Salvare noduri frunza in vector------------------------\n");
	int nr = 0;
	student* vector = (student*)malloc(nrStud * sizeof(student));
	salvareVectorFrunze(rad, vector, &nr);
	for (int i = 0; i < nr; i++)
	{
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f", vector[i].nrMatricol, vector[i].nume, vector[i].medie);
	}
	//fara free(vector[i].nume) pentru ca am facut shallow copy in functie
	free(vector);

	nr = 0;
	nrStudentiMediePrag(rad, &nr, 9.0f);
	printf("\n\n---------------------------------------\n");
	printf("\nNumar studenti cu medie >= 9 este %d\n", nr);
	printf("\n-----------------------------------------\n");
	printf("\nAfisare lista cu studentii al caror nume incepe cu litera 'G':\n");
	inserareStudentiGinLista(rad, &cap);
	traversareLS(cap);
	dezalocareLS(cap);

	printf("\n----------------------------\n");
	printf("\nInaltime arbore = %d", inaltimeArbore(rad));
	printf("\nInaltime subarbore stang = %d", inaltimeArbore(rad->stanga));
	printf("\nInaltime subarbore drept = %d", inaltimeArbore(rad->dreapta));
	printf("\n\n----------------------------\n");

	nodArb* nodCautat = NULL;
	nodCautat = cautare(rad, 42);
	if (nodCautat != NULL)
	{
		printf("\nNumele persoanei cautate este %s", nodCautat->inf.nume);
	}
	else
	{
		printf("\Persoana nu exista!");
	}
	

	dezalocare(rad);
}
