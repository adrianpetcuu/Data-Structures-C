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
	int BF;
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
void inserareStudentiGinLista(nodArb* rad, nodLS** cap, char c)
{
	if (rad != NULL)
	{
		if (rad->inf.nume[0] == c)
		{
			*cap = inserareLS(*cap, rad->inf);
		}
		inserareStudentiGinLista(rad->stanga, cap, c);
		inserareStudentiGinLista(rad->dreapta, cap, c);
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
			return cautare(rad->stanga, cheie);
		}
		else
		{
			return cautare(rad->dreapta, cheie);
		}
	}
	else
	{
		return NULL;
	}
}

nodArb* stergeRad(nodArb* rad)
{
	nodArb* aux = rad;
	if (aux->stanga != NULL)
	{
		rad = aux->stanga;
		if (aux->dreapta != NULL)
		{
			nodArb* temp = aux->stanga;
			while (temp->dreapta != NULL)
			{
				temp = temp->dreapta;
			}
			temp->dreapta = aux->dreapta;
		}
	}
	else if (aux->dreapta != NULL)
	{
		rad = aux->dreapta;
	}
	else
	{
		rad = NULL;
	}
	free(aux->inf.nume);
	free(aux);
	return rad;
}

nodArb* stergeNod(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->inf.nrMatricol)
		{
			rad = stergeRad(rad);
		}
		else if (cheie < rad->inf.nrMatricol)
		{
			rad->stanga = stergeNod(rad->stanga, cheie);
		}
		else
		{
			rad->dreapta = stergeNod(rad->dreapta, cheie);
		}
		return rad;
	}
	else
	{
		return NULL;
	}
}

void calculBF(nodArb* rad)
{
	if (rad != NULL)
	{
		rad->BF = inaltimeArbore(rad->dreapta) - inaltimeArbore(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}


nodArb* rotatieDreapta(nodArb* rad)
{
	printf("\nRotatie dreapta\n");
	nodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatieStanga(nodArb* rad)
{
	printf("\nRotatie stanga\n");
	nodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatieStangaDreapta(nodArb* rad)
{
	printf("\nRotatie stanga-dreapta\n");
	nodArb* nod1 = rad->stanga;
	nodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2->dreapta = rad;
	rad = nod2;
	return rad;
}

nodArb* rotatieDreaptaStanga(nodArb* rad)
{
	printf("\nRotatie dreapta-stanga\n");
	nodArb* nod1 = rad->dreapta;
	nodArb* nod2 = nod1->stanga;
	nod1->stanga = nod2->dreapta;
	nod2->dreapta = nod1;
	rad->dreapta = nod2->stanga;
	nod2->stanga = rad;
	rad = nod2;
	return rad;
}

nodArb* reechilibrare(nodArb* rad)
{
	calculBF(rad);
	nodArb* fiuSt = rad->stanga;
	nodArb* fiuDr = rad->dreapta;
	if (rad->BF <= -2 && fiuSt->BF <= -1)
	{
		rad = rotatieDreapta(rad);
		calculBF(rad);
	}
	else if (rad->BF >= 2 && fiuDr->BF >= 1)
	{
		rad = rotatieStanga(rad);
		calculBF(rad);
	}
	else if (rad->BF <= -2 && fiuSt->BF >= 1)
	{
		rad = rotatieStangaDreapta(rad);
		calculBF(rad);
	}
	else if (rad->BF >= 2 && fiuDr->BF <= -1)
	{
		rad = rotatieStangaDreapta(rad);
		calculBF(rad);
	}
	return rad;
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
	inserareStudentiGinLista(rad, &cap, 'G');
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
	printf("\n\nAfisare arbore:");
	preordine(rad);
	//printf("\n\nAfisare arbore dupa stergerea radacinii:");
	//rad = stergeRad(rad);
	//preordine(rad);
	//printf("\n---------------\n");
	//preordine(rad->stanga);
	//printf("\n---------------\n");
	//preordine(rad->dreapta);

	//printf("\n\nAfisare arbore dupa stergerea unui nod:");
	//rad = stergeNod(rad, 17);
	//preordine(rad);

	calculBF(rad);
	rad = reechilibrare(rad);
	printf("\nAfisare arbore dupa reechilibrare:");
	preordine(rad);

	dezalocare(rad);
}
