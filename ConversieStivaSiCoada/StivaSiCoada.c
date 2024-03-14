#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* nume;
	float medie;
}student;

typedef struct
{
	student inf;
	struct nodStiva* next;
}nodStiva;

typedef struct
{
	student inf;
	struct nodCoada* next;
}nodCoada;

void put(nodCoada** prim, nodCoada** ultim, student s)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
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

int get(nodCoada** prim, nodCoada** ultim, student* s)
{
	if (*prim == NULL && *ultim == NULL)
	{
		return -1;
	}
	else
	{
		(*s).cod = (*prim)->inf.cod;
		(*s).nume = (char*)malloc((strlen((*prim)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*prim)->inf.nume);
		(*s).medie = (*prim)->inf.medie;
		nodCoada* temp = (*prim);
		(*prim) = temp->next;
		free(temp->inf.nume);
		free(temp);
		if (*prim == NULL)
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
		printf("\nCod: %d, Nume: %s, Medie: %5.2f",
			temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

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
		(*s).cod = (*varf)->inf.cod;
		(*s).nume = (char*)malloc((strlen((*varf)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*varf)->inf.nume);
		(*s).medie = (*varf)->inf.medie;
		nodStiva* temp = (*varf);
		(*varf) = (*varf)->next;
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
		printf("\nCod: %d, Nume: %s, Medie: %5.2f",
			temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void conversieCoadaInStiva(nodCoada** prim, nodCoada** ultim, nodStiva** varf)
{
	student s;
	while (get(prim, ultim, &s) == 0)
	{
		push(varf, s);
	}
}

void conversieStivaInCoada(nodCoada** prim, nodStiva** ultim, nodStiva** varf)
{
	student s;
	while (pop(varf, &s) == 0)
	{
		put(prim, ultim, s);
	}
}

int main()
{
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
		getchar(); // Consuma newline-ul ramas in buffer dupa scanf
		printf("Nume: ");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0'; // Elimina caracterul newline
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("Medie: ");
		scanf("%f", &s.medie);
		put(&prim, &ultim, s);
		free(s.nume);
	}
	printf("\n----------------traversare coada-----------\n");
	traversareCoada(prim);
	student stud;
	get(&prim, &ultim, &stud);
	printf("\nStudentul extras are numele %s, codul %d si media %5.2f",
			stud.nume,stud.cod, stud.medie);
	free(stud.nume);
	/*get(&prim, &ultim, &stud);
	printf("\nStudentul extras are numele %s, codul %d si media %5.2f", 
			stud.nume,stud.cod, stud.medie);
	free(stud.nume);
	get(&prim, &ultim, &stud);
	printf("\nStudentul extras are numele %s, codul %d si media %5.2f",
			stud.nume, stud.cod, stud.medie);
	free(stud.nume);*/
	nodStiva* varf = NULL;
	conversieCoadaInStiva(&prim, &ultim, &varf); 
	printf("\n\n-----------conversie coada in stiva--------------\n");
	printf("\n--------------afisare stiva-----------------\n");
	traversareStiva(varf);
	printf("\n--------------afisare coada-----------------\n");
	traversareCoada(prim);
	conversieStivaInCoada(&prim, &ultim, &varf);
	printf("\n\n-----------conversie stiva in coada--------------\n");
	printf("\n--------------afisare stiva-----------------\n");
	traversareStiva(varf);
	printf("\n--------------afisare coada-----------------\n");
	traversareCoada(prim);
	//dezalocare coada
	while (get(&prim, &ultim, &stud) == 0)
	{
		free(stud.nume);
	}
	return 0;
} 