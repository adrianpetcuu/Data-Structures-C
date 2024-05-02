#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	char* cnp;
	char* nume;
	float salariu;
	int vechime;
	char* departament;
	char* adresa;
} angajat;

typedef struct
{
	angajat inf;
	struct nodLS* next;
} nodLS; //nod lista secundara

typedef struct
{
	struct nodLS* inf;
	struct nodLP* next;
} nodLP; //nod lista principala

void inserareLS(nodLS** capLS, angajat a)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.cnp = (char*)malloc((strlen(a.cnp) + 1) * sizeof(char));
	strcpy(nou->inf.cnp, a.cnp);
	nou->inf.nume = (char*)malloc((strlen(a.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, a.nume);
	nou->inf.salariu = a.salariu;
	nou->inf.vechime = a.vechime;
	nou->inf.departament = (char*)malloc((strlen(a.departament) + 1) * sizeof(char));
	strcpy(nou->inf.departament, a.departament);
	nou->inf.adresa = (char*)malloc((strlen(a.adresa) + 1) * sizeof(char));
	strcpy(nou->inf.adresa, a.adresa);
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
		printf("\nCNP: %s, Nume: %s, Salariu: %5.2f, Vechime: %d, Departament: %s, Adresa: %s",
			temp->inf.cnp, temp->inf.nume, temp->inf.salariu, temp->inf.vechime, temp->inf.departament, temp->inf.adresa);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->inf.cnp);
		free(temp->inf.nume);
		free(temp->inf.departament);
		free(temp->inf.adresa);
		free(temp);
		temp = aux;
	}
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

void traversareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	int i = 1;
	while (temp != NULL)
	{
		printf("\n\nSublista %d:", i);
		traversareLS(temp->inf);
		temp = temp->next;
		i++;
	}
}

void dezalocareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp != NULL)
	{
		nodLP* aux = temp->next;
		dezalocareLS(temp->inf);
		free(temp);
		temp = aux;
	}
}

void determinareAngajatiCuSalariuMaximPeDepartament(nodLP* capLP)
{
	nodLP* tempLP = capLP;
	while (tempLP != NULL)
	{
		nodLS* tempLS = tempLP->inf;
		float salariuMaxPeDepartament = tempLS->inf.salariu;
		angajat angajatCuSalariuMaxim = tempLS->inf;
		while (tempLS != NULL)
		{
			if (salariuMaxPeDepartament < tempLS->inf.salariu)
			{
				salariuMaxPeDepartament = tempLS->inf.salariu;
				angajatCuSalariuMaxim = tempLS->inf;
			}
			tempLS = tempLS->next;
		}
		printf("\nAngajatul cu salariul maxim pentru departamentul %s este:", angajatCuSalariuMaxim.departament);
		printf("\nCNP: %s, Nume: %s, Salariu: %5.2f, Vechime: %d, Adresa: %s\n",
			angajatCuSalariuMaxim.cnp, angajatCuSalariuMaxim.nume, angajatCuSalariuMaxim.salariu,
			angajatCuSalariuMaxim.vechime, angajatCuSalariuMaxim.adresa);
		tempLP = tempLP->next;
	}
}

void sortareAngajatiDupaVechime(nodLP* capLP) 
{
	nodLP* tempLP = capLP;
	while (tempLP != NULL)
	{
		nodLS* tempLS = tempLP->inf;
		while (tempLS != NULL)
		{
			nodLS* vechimeMax = tempLS;
			nodLS* current = tempLS->next;
			while (current != NULL)
			{
				if (vechimeMax->inf.vechime < current->inf.vechime)
				{
					vechimeMax = current;
				}
				current = current->next;
			}
			angajat temp = tempLS->inf;
			tempLS->inf = vechimeMax->inf;
			vechimeMax->inf = temp;

			tempLS = tempLS->next;
		}
		tempLP = tempLP->next;
	}
}


typedef struct
{
	angajat inf;
	struct nodCoada* next;
} nodCoada;

void put(nodCoada** prim, nodCoada** ultim, angajat a)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.cnp = (char*)malloc((strlen(a.cnp) + 1) * sizeof(char));
	strcpy(nou->inf.cnp, a.cnp);
	nou->inf.nume = (char*)malloc((strlen(a.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, a.nume);
	nou->inf.salariu = a.salariu;
	nou->inf.vechime = a.vechime;
	nou->inf.departament = (char*)malloc((strlen(a.departament) + 1) * sizeof(char));
	strcpy(nou->inf.departament, a.departament);
	nou->inf.adresa = (char*)malloc((strlen(a.adresa) + 1) * sizeof(char));
	strcpy(nou->inf.adresa, a.adresa);
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

int get(nodCoada** prim, nodCoada** ultim, angajat* extras)
{
	if (*prim == NULL && *ultim == NULL)
	{
		return -1;
	}
	else
	{
		extras->cnp = (char*)malloc((strlen((*prim)->inf.cnp) + 1) * sizeof(char));
		strcpy(extras->cnp, (*prim)->inf.cnp);
		extras->nume = (char*)malloc((strlen((*prim)->inf.nume) + 1) * sizeof(char));
		strcpy(extras->nume, (*prim)->inf.nume);
		extras->salariu = (*prim)->inf.salariu;
		extras->vechime = (*prim)->inf.vechime;
		extras->departament = (char*)malloc((strlen((*prim)->inf.departament) + 1) * sizeof(char));
		strcpy(extras->departament, (*prim)->inf.departament);
		extras->adresa = (char*)malloc((strlen((*prim)->inf.adresa) + 1) * sizeof(char));
		strcpy(extras->adresa, (*prim)->inf.adresa);
		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.cnp);
		free(temp->inf.nume);
		free(temp->inf.departament);
		free(temp->inf.adresa);
		free(temp);
		if (*prim == NULL && *ultim != NULL)
		{
			*ultim = NULL;
		}
		return 0;
	}
}

void traversareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nCNP: %s, Nume: %s, Salariu: %5.2f, Vechime: %d, Departament: %s, Adresa: %s",
			temp->inf.cnp, temp->inf.nume, temp->inf.salariu, temp->inf.vechime, temp->inf.departament, temp->inf.adresa);
		temp = temp->next;
	}
}

void salvareListaDeListeInCoada(nodLP* capLP, nodCoada** prim, nodCoada** ultim)
{
	nodLP* tempLP = capLP;
	while (tempLP != NULL)
	{
		nodLS* tempLS = tempLP->inf;
		while (tempLS != NULL)
		{
			put(prim, ultim, tempLS->inf);
			tempLS = tempLS->next;
		}
		tempLP = tempLP->next;	
	}
}

void determinareAngajatiCuAceeasiLitera(nodCoada** prim, nodCoada** ultim, nodCoada** prim2, nodCoada** ultim2, char litera)
{
	angajat extras;
	while (get(prim, ultim, &extras) == 0)
	{
		put(prim2, ultim2, extras);
		if (extras.nume[0] == litera)
		{
			printf("\nCNP: %s, Nume: %s, Salariu: %5.2f, Vechime: %d, Departament: %s, Adresa: %s",
				extras.cnp, extras.nume, extras.salariu, extras.vechime, extras.departament, extras.adresa);
		}
	}
}

void salvareAngajatiInVector(nodCoada** prim, nodCoada** ultim, angajat* vector, int* nr)
{
	angajat extras;
	while (get(prim, ultim, &extras) == 0)
	{
		int cifreAnNastere = (extras.cnp[1] - '0') * 10 + (extras.cnp[2] - '0');
		int varsta = 2024 - (cifreAnNastere + 1900);
		if (varsta == 60)
		{
			vector[*nr] = extras;
			(*nr)++;
		}
	}
}


void main()
{
	nodLP* capLP = NULL;
	nodLS* capLS1 = NULL;
	nodLS* capLS2 = NULL;
	nodLS* capLS3 = NULL;
	angajat a;
	int nrAngajati = 0;
	char buffer[150];
	FILE* f = fopen("fisier.txt", "r");
	if (f == NULL)
	{
		printf("Fisierul nu s-a putut deschide!");
		return;
	}
	fscanf(f, "%d", &nrAngajati);
	for (int i = 0; i < nrAngajati; i++)
	{
		fscanf(f, "%s", buffer);
		a.cnp = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(a.cnp, buffer);
		fscanf(f, "%s", buffer);
		a.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(a.nume, buffer);
		fscanf(f, "%f", &a.salariu);
		fscanf(f, "%d", &a.vechime);
		fscanf(f, "%s", buffer);
		a.departament = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(a.departament, buffer);
		fscanf(f, "%s", buffer);
		a.adresa = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(a.adresa, buffer);

		if (strcmp(a.departament, "IT") == 0)
		{
			inserareLS(&capLS1, a);
		}
		else if (strcmp(a.departament, "HR") == 0)
		{
			inserareLS(&capLS2, a);
		}
		else if (strcmp(a.departament, "Vanzari") == 0)
		{
			inserareLS(&capLS3, a);
		}

		free(a.cnp);
		free(a.nume);
		free(a.departament);
		free(a.adresa);
	}
	fclose(f);

	inserareLP(&capLP, capLS1);
	inserareLP(&capLP, capLS2);
	inserareLP(&capLP, capLS3);
	traversareLP(capLP);
	printf("\n\n---------Afisare angajati cu salariu maxim pentru fiecare departament:-------\n");
	determinareAngajatiCuSalariuMaximPeDepartament(capLP);


	printf("\n\n---------Lista de liste dupa sortare descrescatoare dupa vechime:-------\n");
	sortareAngajatiDupaVechime(capLP);
	traversareLP(capLP);

	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	salvareListaDeListeInCoada(capLP, &prim, &ultim);
	printf("\n\n-------------------Afisare coada:-------------------");
	traversareCoada(prim);

	nodCoada* prim2 = NULL;
	nodCoada* ultim2 = NULL;
	printf("\n\nAfisare angajati al caror nume incepe cu aceeasi litera:");
	determinareAngajatiCuAceeasiLitera(&prim, &ultim, &prim2, &ultim2, 'A');
	printf("\n\n-------------------Afisare coada:-------------------");
	traversareCoada(prim2);

	int nr = 0;
	angajat* vector = (angajat*)malloc(nrAngajati * sizeof(angajat));
	salvareAngajatiInVector(&prim2, &ultim2, vector, &nr);
	printf("\n\nAfisare vector:");
	for (int i = 0; i < nr; i++)
	{
		printf("\nCNP: %s, Nume: %s, Salariu: %5.2f, Vechime: %d, Departament: %s, Adresa: %s",
			vector[i].cnp, vector[i].nume, vector[i].salariu, vector[i].vechime, vector[i].departament, vector[i].adresa);
	}
	for (int i = 0; i < nr; i++)
	{
		free(vector[i].cnp);
		free(vector[i].nume);
		free(vector[i].departament);
		free(vector[i].adresa);
	}
	free(vector);
	dezalocareLP(capLP);
}
