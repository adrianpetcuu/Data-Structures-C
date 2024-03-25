#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* denumire;
	float pret;
}produs;

typedef struct
{
	produs inf;
	struct nodLS* next;
}nodLS; //lista secundara

typedef struct
{
	struct nodLS** vect;
	int nrElem;
}hashT;

int functieHash(int cheie, hashT tabela)
{
	return cheie % tabela.nrElem;
}

void inserareLS(nodLS** capLS, produs p)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->next = NULL;
	if (*capLS == NULL)
	{
		*capLS = nou;
	}
	else
	{
		nodLS* temp = *capLS;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		printf("\nCod: %d, Denumire: %s, Pret: %5.2f\n", temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = aux;
	}
}

void inserareHash(hashT tabela, produs p)
{
	int poz = functieHash(p.cod, tabela);
	inserareLS(&tabela.vect[poz], p);
}

void traversareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			printf("\nPozitia %d", i);
			traversareLS(tabela.vect[i]);
		}
	}
}

void dezalocareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			dezalocareLS(tabela.vect[i]);
		}
	}
	free(tabela.vect);
}

int main()
{
	hashT tabela;
	//4 * i + 3 => 4 * 8 + 3 = 33 (avem 8 elem in fisier)
	tabela.nrElem = 33;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
	{
		tabela.vect[i] = NULL;
	}
	produs p;
	char buffer[20];
	int nrProd;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrProd);
	for (int i = 0; i < nrProd; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);
		inserareHash(tabela, p);
		free(p.denumire);
	}
	fclose(f);

	traversareHash(tabela);
	dezalocareHash(tabela);

}
