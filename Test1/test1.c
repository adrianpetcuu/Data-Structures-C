#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* denumire;
	float dobanda;
} banca;

typedef struct
{
	banca inf;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS* inf;
	struct nodLP* next;
} nodLP;

void inserareLS(nodLS** cap, banca b)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.cod = b.cod;
	nou->inf.denumire = (char*)malloc((sizeof(b.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, b.denumire);
	nou->inf.dobanda = b.dobanda;
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
		printf("\nCod: %d, Denumire: %s, Dobanda: %5.2f\n", 
			temp->inf.cod, temp->inf.denumire, temp->inf.dobanda);
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

void stergereImpareSiSalvarePare(nodLS** cap)
{
	nodLS* temp = *cap;
	nodLS* prev = NULL;
	FILE* f = fopen("fisier_pare.txt", "w");
	while (temp != NULL)
	{
		if (temp->inf.cod % 2 == 1)
		{
			if (prev == NULL)
			{
				*cap = temp->next;
				free(temp->inf.denumire);
				free(temp);
				temp = *cap;
			}
			else
			{
				prev->next = temp->next;
				free(temp->inf.denumire);
				free(temp);
				temp = prev->next;
			}
		}
		else
		{
			fprintf(f, "%d %s %5.2f\n", temp->inf.cod, temp->inf.denumire, temp->inf.dobanda);
			prev = temp;
			temp = temp->next;
		}
	}
	fclose(f);
}

void inserareLP(nodLP** capLP, nodLS* capLS)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->inf = capLS;
	nou->next = NULL;
	if (*capLP == NULL)
	{
		*capLP = nou;
	}
	else
	{
		nodLP* temp = *capLP;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void conversieListaDeListe(nodLP** capLP, nodLS** capLS1, nodLS** capLS2, nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		if (temp->inf.cod % 2 == 0)
		{
			inserareLS(capLS1, temp->inf);
		}
		else
		{
			inserareLS(capLS2, temp->inf);
		}
		temp = temp->next;
	}
	inserareLP(capLP, *(capLS1));
	inserareLP(capLP, *(capLS2));

}

void traversareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	int i = 1;
	while (temp != NULL)
	{
		printf("\nSublista %d:\n", i);
		traversareLS(temp->inf);
		temp = temp->next;
		i++;
	}
}

void dezalocareLPsiLSsiScriereInFisier(nodLP* capLP, nodLS* capLS)
{
	nodLP* temp = capLP;
	FILE* f = fopen("afisare_structuri.txt", "w");
	fprintf(f, "\n-----------Lista de liste-----------\n");
	while (temp != NULL)
	{
		int i = 1;
		nodLP* aux = temp->next;
		fprintf(f, "\nSublista %d\n", i);
		nodLS* temp2 = temp->inf;
		while (temp2 != NULL)
		{
			fprintf(f, "\nCod: %d, Denumire: %s, Dobanda: %5.2f\n", 
				temp2->inf.cod, temp2->inf.denumire, temp2->inf.dobanda);
			temp2 = temp2->next;
		}
		dezalocareLS(temp->inf);
		free(temp);
		temp = aux;
		i++;
	}
	fprintf(f, "\n------------Lista simpla-----------\n");
	nodLS* temp3 = capLS;
	while (temp3 != NULL)
	{
		nodLS* aux = temp3->next;
		fprintf(f, "\nCod: %d, Denumire: %s, Dobanda: %5.2f\n",
			temp3->inf.cod, temp3->inf.denumire, temp3->inf.dobanda);
		free(temp3->inf.denumire);
		free(temp3);
		temp3 = aux;
	}

	fclose(f);
}

void main()
{
	nodLS* cap = NULL;
	nodLS* capLS1 = NULL;
	nodLS* capLS2 = NULL;
	nodLS* capLP = NULL;
	banca b;
	int nrBanci;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrBanci);
	for (int i = 0; i < nrBanci; i++)
	{
		fscanf(f, "%d", &b.cod);
		fscanf(f, "%s", buffer);
		b.denumire = (char*)malloc((sizeof(buffer) + 1) * sizeof(char));
		strcpy(b.denumire, buffer);
		fscanf(f, "%f", &b.dobanda);
		inserareLS(&cap, b);
		free(b.denumire);
	}
	fclose(f);
	
	traversareLS(cap);
	//printf("\n-------------Lista dupa stergere------------\n");
	//stergereImpareSiSalvarePare(&cap);
	//traversareLS(cap);
	//printf("\n----------------Lista 1------------------\n");
	//traversareLS(capLS1);
	//printf("\n----------------Lista 2------------------\n");
	//traversareLS(capLS2);

	conversieListaDeListe(&capLP, &capLS1, &capLS2, cap);
	traversareLP(capLP);
	dezalocareLPsiLSsiScriereInFisier(capLP, cap);
}
