#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* denumire;
	float pret;
} produs;

typedef struct
{
	produs inf;
	struct nodLS* next;
} nodLS; //lista secundara

typedef struct
{
	struct nodLS** vector;
	int nrElem;
} hashT; //tabela de dispersie, hash table, vector de liste

int functieHash(int cheie, hashT tabela)
{
	return cheie % tabela.nrElem;
}

void inserareHash(hashT tabela, produs p)
{
	int poz = functieHash(p.cod, tabela);
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->next = NULL;
	if (tabela.vector[poz] == NULL)
	{
		tabela.vector[poz] = nou;
	}
	else
	{
		nodLS* temp = tabela.vector[poz];
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void traversareHash(hashT tabela)
{
	if (tabela.vector != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
		{
			if (tabela.vector[i] != NULL)
			{
				printf("\nPozitia %d\n", i);
				nodLS* temp = tabela.vector[i];
				while (temp != NULL)
				{
					printf("\nCod: %d, Denumire: %s, Pret: %5.2f\n",
						temp->inf.cod, temp->inf.denumire, temp->inf.pret);
					temp = temp->next;
				}
				
			}
		}
	}
}



void dezalocareHash(hashT tabela)
{
	if (tabela.vector != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
		{
			if (tabela.vector[i] != NULL)
			{
				nodLS* temp = tabela.vector[i];
				while (temp != NULL)
				{
					nodLS* aux = temp->next;
					free(temp->inf.denumire);
					free(temp);
					temp = aux;
				}
			}
		}
		free(tabela.vector);
	}
}


void stergereProdusDupaCod(hashT tabela, int cod)
{
	int poz = functieHash(cod, tabela);
	nodLS* temp = tabela.vector[poz];
	nodLS* prev = NULL;

	while (temp != NULL) {
		if (temp->inf.cod == cod) {
			if (prev == NULL) {
				tabela.vector[poz] = temp->next;
			}
			else {
				prev->next = temp->next;
			}
			free(temp->inf.denumire);
			free(temp);
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}


int main()
{
	hashT tabela;
	//8 * 4 + 1 = 33 (8 elemente in fisier)
	tabela.nrElem = 33;
	tabela.vector = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
	{
		tabela.vector[i] = NULL;
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
	printf("\n---------------Afisare Hash Table---------------\n");
	traversareHash(tabela);

	printf("\n---------------Stergere Produs Dupa Cod-------------\n");
	stergereProdusDupaCod(tabela, 165);

	printf("\n---------------Afisare Hash Table Dupa Stergere---------------\n");
	traversareHash(tabela);

	dezalocareHash(tabela);
}  
