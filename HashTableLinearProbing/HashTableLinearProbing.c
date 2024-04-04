#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

//linear probing

typedef struct
{
	int anFabricatie;
	char* marca;
	float pret;
} masina;

typedef struct
{
	masina** vector;
	int nrElem;
} hashT;

int functieHash(hashT tabela, char* cheie)
{
	return cheie[0] % tabela.nrElem;
}

void inserareHash(hashT tabela, masina* m)
{
	int poz = functieHash(tabela, m->marca);
	if (tabela.vector[poz] == NULL)
	{
		tabela.vector[poz] = m;
	}
	else
	{
		int index = 1;
		while (poz + index < tabela.nrElem)
		{
			if (tabela.vector[poz + index] == NULL)
			{
				poz += index;
				tabela.vector[poz] = m;
				break;
			}
			else
			{
				index++;
			}
		}
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
				printf("\nPozitia %d", i);
				printf("\nAn Fabricatie: %d, Denumire: %s, Pret: %5.2f\n",
					tabela.vector[i]->anFabricatie, tabela.vector[i]->marca, tabela.vector[i]->pret);
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
				free(tabela.vector[i]->marca);
				free(tabela.vector[i]);
			}
		}
		free(tabela.vector);
	}
}

//stergere din hash table linear probing
void stergereDupaMarca(hashT tabela, char* marca)
{
	int poz = functieHash(tabela, marca);
	int index = 0;
	while (poz + index < tabela.nrElem)
	{
		if (tabela.vector[poz + index] != NULL)
		{
			if (strcmp(tabela.vector[poz + index]->marca, marca) == 0)
			{
				free(tabela.vector[poz + index]->marca);
				free(tabela.vector[poz + index]);
				tabela.vector[poz + index] = NULL;
				break;
			}
			else
			{
				index++;
			}
		}
	}
}


void salvareHashTableInVector(hashT tabela, masina* vector, int* nrElem, float pretMin, float pretMax)
{
	if (tabela.vector != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
		{
			if (tabela.vector[i] != NULL)
			{
				if (tabela.vector[i]->pret >= pretMin && tabela.vector[i]->pret <= pretMax)
				{
					vector[*nrElem].anFabricatie = tabela.vector[i]->anFabricatie;
					vector[*nrElem].marca = (char*)malloc((strlen(tabela.vector[i]->marca) + 1) * sizeof(char));
					strcpy(vector[*nrElem].marca, tabela.vector[i]->marca);
					vector[*nrElem].pret = tabela.vector[i]->pret;
					(*nrElem)++;
				}
			}
		}
	}

}



void main()
{
	hashT tabela;
	tabela.nrElem = 31;
	tabela.vector = (masina**)malloc(tabela.nrElem * sizeof(masina*));
	for (int i = 0; i < tabela.nrElem; i++)
	{
		tabela.vector[i] = NULL;
	}
	masina* m;
	char buffer[20];
	int nrMasini;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		m = (masina*)malloc(sizeof(masina));
		fscanf(f, "%d", &m->anFabricatie);
		fscanf(f, "%s", buffer);
		m->marca = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(m->marca, buffer);
		fscanf(f, "%f", &m->pret);
		inserareHash(tabela, m);
	}
	fclose(f);

	traversareHash(tabela);


	int nrElem = 0;
	masina* vector = (masina*)malloc(nrMasini * sizeof(masina));
	salvareHashTableInVector(tabela, vector, &nrElem, 10000, 30000);
	printf("\n-----------------Afisare vector-------------\n");
	for (int i = 0; i < nrElem; i++)
	{
		printf("\nAn Fabricatie: %d, Marca: %s, Pret: %5.2f\n",
			vector[i].anFabricatie, vector[i].marca, vector[i].pret);
	}
	for (int i = 0; i < nrElem; i++)
	{
		free(vector[i].marca);
	}
	free(vector);


	printf("\n------------------Dupa Stergere--------------\n");
	stergereDupaMarca(tabela, "Dacia");
	stergereDupaMarca(tabela, "Mazda");
	traversareHash(tabela);
	dezalocareHash(tabela);
}
