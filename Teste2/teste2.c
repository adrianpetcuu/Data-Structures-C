#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	long cod;
	char* nume;
	float varsta;
} persoana;

typedef struct
{
	persoana inf;
	struct nodCoada* next;
} nodCoada;

typedef struct
{
	persoana inf;
	struct nodStiva* next;
} nodStiva;

void put(nodCoada** prim, nodCoada** ultim, persoana p)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.cod = p.cod;
	nou->inf.nume = (char*)malloc((strlen(p.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, p.nume);
	nou->inf.varsta = p.varsta;
	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL)
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

void traversareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nCod: %d, Nume: %s, Varsta: %5.2f\n", 
			temp->inf.cod, temp->inf.nume, temp->inf.varsta);
		temp = temp->next;
	}
}

int get(nodCoada** prim, nodCoada** ultim, persoana* p)
{
	if (*prim == NULL && *ultim == NULL)
	{
		return -1;
	}
	else
	{
		(*p).cod = (*prim)->inf.cod;
		(*p).nume = (char*)malloc((strlen((*prim)->inf.nume) - 1) * sizeof(char));
		strcpy((*p).nume, (*prim)->inf.nume);
		(*p).varsta = (*prim)->inf.varsta;
		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.nume);
		free(temp);
		if (*prim == NULL && *ultim != NULL)
		{
			*ultim = NULL;
		}
		return 0;
	}
}

void push(nodStiva** varf, persoana p)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.cod = p.cod;
	nou->inf.nume = (char*)malloc((strlen(p.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, p.nume);
	nou->inf.varsta = p.varsta;
	if (*varf == NULL)
	{
		nou->next = NULL;
		*varf = nou;
	}
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

void traversareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("\nCod: %d, Nume: %s, Varsta: %5.2f\n",
			temp->inf.cod, temp->inf.nume, temp->inf.varsta);
		temp = temp->next;
	}
}

void conversieCoadaInStiva(nodStiva** varf, nodCoada** prim, nodCoada** ultim)
{
	persoana p;
	while (get(prim, ultim, &p) == 0)
	{
		push(varf, p);
	}
}

void impletireCoziSiAfisare(nodCoada** prim, nodCoada** ultim, nodCoada** prim2, nodCoada** ultim2,
	nodCoada** prim3, nodCoada** ultim3)
{
	persoana p;
	while (get(prim, ultim, &p) == 0)
	{
		put(prim3, ultim3, p);
	}
	while (get(prim2, ultim2, &p) == 0)
	{
		put(prim3, ultim3, p);
	}

	FILE* f = fopen("rezultat_impletire.txt", "w");
	nodCoada* temp = *prim3;
	while (temp != NULL)
	{
		fprintf(f, "\nCod: %d, Nume: %s, Varsta: %5.2f\n",
			temp->inf.cod, temp->inf.nume, temp->inf.varsta);
		temp = temp->next;
	}
	fclose(f);
}


void main()
{
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	nodStiva* varf = NULL;
	nodCoada* prim2 = NULL;
	nodCoada* ultim2 = NULL;
	nodCoada* prim3 = NULL;
	nodCoada* ultim3 = NULL;
	persoana p;
	int nrPers;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrPers);
	for (int i = 0; i < nrPers; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.nume, buffer);
		fscanf(f, "%f", &p.varsta);
		put(&prim, &ultim, p);
		free(p.nume);
	}
	fclose(f);
	printf("\n----------Afisare Coada----------\n");
	traversareCoada(prim);

	//conversieCoadaInStiva(&varf, &prim, &ultim);
	//printf("\n----------Afisare Stiva----------\n");
	//traversareStiva(varf);

	int nrPers2;
	printf("\nNr persoane: ");
	scanf("%d", &nrPers2);
	for (int i = 0; i < nrPers2; i++)
	{
		printf("\n\nCod: ");
		scanf("%d", &p.cod);
		printf("\nNume: ");
		scanf("%s", buffer);
		p.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.nume, buffer);
		printf("\nVarsta: ");
		scanf("%f", &p.varsta);
		put(&prim2, &ultim2, p);
		free(p.nume);
	}
	traversareCoada(prim2);

	impletireCoziSiAfisare(&prim, &ultim, &prim2, &ultim2, &prim3, &ultim3);
	persoana pers;
	while (get(&prim3, &ultim3, &pers) == 0)
	{
		free(pers.nume);
	}
}
