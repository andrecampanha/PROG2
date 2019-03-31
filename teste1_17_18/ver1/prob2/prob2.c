#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
vetor* contar_correspondencia(vetor *vcp_dest)
{
	if(vcp_dest == NULL) return NULL;
	vetor *v = vetor_novo();
	if(v == NULL) return NULL;
	int *occr = malloc(vcp_dest->tamanho * sizeof(int));
	if(occr == NULL)
	{
		free(v);
		return NULL;
	}
	int found;
	for(int i = 0; i < vcp_dest->tamanho; i++)
	{
		found = 0;
		for(int j = 0; j < v->tamanho; j++)
		{
			if(strcmp(vcp_dest->elementos[i].str, v->elementos[j].str) == 0)
			{
				occr[j]++;
				found = 1;
				break;
			}
		}

		if(!found)
		{
			vetor_insere(v, vcp_dest->elementos[i].str, -1);
			occr[v->tamanho - 1] = 1;
		}
	}

	for(int i = 0; i < v->tamanho; i++)
	{
		printf("%s: %d cartas\n", v->elementos[i].str, occr[i]);
	}

	free(occr);
	return v;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest)
{
	char buffer[BUFFER], *nlptr;

	if (ficheiro == NULL)
		return;

	while(fgets(buffer, BUFFER, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vrem, buffer, -1);

		fgets(buffer, BUFFER, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vdest, buffer, -1);

		fgets(buffer, BUFFER, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vcp_dest, buffer, -1);
	}
}

int main()
{
	FILE *fin;
	char linha[BUFFER];
	vetor* vrem;
	vetor* vdest;
	vetor *vcp_dest;
	vrem=NULL; vdest=NULL; vcp_dest=NULL;

	fin = fopen("correspondencia.txt", "r");
	if(fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	vrem = vetor_novo();
	vdest = vetor_novo();
	vcp_dest = vetor_novo();
	lerParaVetores(fin, vrem, vdest, vcp_dest);

	fclose(fin);

	vetor *cp = contar_correspondencia(vcp_dest);

	if (cp == NULL)
		printf("\nFuncao retornou erro.\n");
	else if(vetor_tamanho(cp) != 11)
		printf("\nERRO.. Numero de codigos postais distinto(%d; esperado: 11)\n", vetor_tamanho(cp));
	else {
		printf("\nNumero de codigos postais distintos: %d\n", vetor_tamanho(cp));
	}

	vetor_apaga(cp);
	vetor_apaga(vrem);
	vetor_apaga(vdest);
	vetor_apaga(vcp_dest);

	return 0;
}
