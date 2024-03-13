#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int zi, luna, an;
}dataReceptionare;

typedef struct
{
	dataReceptionare data;
	int prioritate;
	char* aplicatie;
	float durata;
} notificare;

typedef struct
{
	notificare inf;
	struct nodStiva* next;
}nodStiva;

void push(nodStiva** varf, notificare notif)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.data.zi = notif.data.zi;
	nou->inf.data.luna = notif.data.luna;
	nou->inf.data.an = notif.data.an;
	nou->inf.prioritate = notif.prioritate;
	nou->inf.aplicatie = (char*)malloc((strlen(notif.aplicatie) + 1) * sizeof(char));
	strcpy(nou->inf.aplicatie, notif.aplicatie);
	nou->inf.durata = notif.durata;
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

int pop(nodStiva** varf, notificare* val)
{
	if (*varf == NULL)
	{
		return -1;
	}
	else
	{
		(*val).data.zi = (*varf)->inf.data.zi;
		(*val).data.luna = (*varf)->inf.data.luna;
		(*val).data.an = (*varf)->inf.data.an;
		(*val).prioritate = (*varf)->inf.prioritate;
		(*val).aplicatie = (char*)malloc((strlen((*varf)->inf.aplicatie) + 1) * sizeof(char));
		strcpy((*val).aplicatie, (*varf)->inf.aplicatie);
		(*val).durata = (*varf)->inf.durata;
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->inf.aplicatie);
		free(temp);
		return 0;
	}
}

void traversare(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("\nData: %d/%d/%d, Prioritate: %d, Aplicatie: %s, Durata: %5.2f",
			temp->inf.data.zi, temp->inf.data.luna, temp->inf.data.an,
			temp->inf.prioritate, temp->inf.aplicatie, temp->inf.durata);
		temp = temp->next;
	}
}

void salvareStivaVector(nodStiva* varf, notificare* vector, int* nr)
{
	notificare notif;
	while (pop(&varf, &notif) == 0)
	{
		vector[*nr] = notif;
		(*nr)++;
	}
}

int main()
{
	nodStiva* varf = NULL;
	notificare notif;
	int nrNotif;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrNotif);
	for (int i = 0; i < nrNotif; i++)
	{
		fscanf(f, "%d", &notif.data.zi);
		fscanf(f, "%d", &notif.data.luna);
		fscanf(f, "%d", &notif.data.an);
		fscanf(f, "%d", &notif.prioritate);
		fscanf(f, "%s", buffer);
		notif.aplicatie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(notif.aplicatie, buffer);
		fscanf(f, "%f", &notif.durata);
		push(&varf, notif);
		free(notif.aplicatie);
	}
	fclose(f);
	printf("\n-------------stiva------------\n");
	traversare(varf);
	//notificare* notific = (notificare*)malloc(sizeof(notificare));
	//sau asa dar e recomandata prima varianta
	//notificare notific;
	//pop(&varf, &notific);
	//printf("\n\n--------------stiva------------\n");
	//printf("-----------dupa extragere----------\n");
	//traversare(varf);
	printf("\n\n");  

	int nr = 0;
	notificare* vector = (notificare*)malloc(nrNotif * sizeof(notificare));
	salvareStivaVector(varf, vector, &nr);
	printf("-------------stiva in vector------------\n");
	for (int i = 0; i < nr; i++)
	{
		printf("\nData: %d/%d/%d, Prioritate: %d, Aplicatie: %s, Durata: %5.2f",
			vector[i].data.zi, vector[i].data.luna, vector[i].data.an,
			vector[i].prioritate, vector[i].aplicatie, vector[i].durata);
	}
	for (int i = 0; i < nr; i++)
	{
		free(vector[i].aplicatie);
	}
	free(vector);
}