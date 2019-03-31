#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
vetor* contar_remetente_destinatario(vetor *vrem, vetor *vdest)
{
	if(vrem == NULL || vdest == NULL) return NULL;
	int *soma = calloc(vrem->tamanho, sizeof(int));
	if(soma == NULL) return NULL;
	vetor *res = vetor_novo();
	if(res == NULL)
	{
		free(soma);
		return NULL;
	}
	int pos;

	for(int i = 0; i < vrem->tamanho; i++)
	{
		pos = vetor_pesquisa(res, vetor_elemento(vrem, i));
		if(pos == -1)
		{
			pos = vetor_insere(res, vetor_elemento(vrem, i), -1);
			if(pos == -1)
			{
				free(soma);
				vetor_apaga(res);
				return NULL;
			}
		}
		soma[pos]++;

		pos = vetor_pesquisa(res, vetor_elemento(vdest, i));
		if(pos == -1)
		{
			pos = vetor_insere(res, vetor_elemento(vdest, i), -1);
			if(pos == -1)
			{
				free(soma);
				vetor_apaga(res);
				return NULL;
			}
		}
		soma[pos]++;
	}

	for(int i = 0; i < res->tamanho; i++)
	{
		printf("%s : %d cartas\n", vetor_elemento(res, i), soma[i]);
	}


	free(soma);
	return res;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256

void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest);

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

	vetor *cp = contar_remetente_destinatario(vrem, vdest);

	if (cp == NULL)
		printf("\nFuncao retornou erro.\n");
	else {
		printf("\nNumero de pessoas distintas: %d\n", vetor_tamanho(cp));
	}

	vetor_apaga(cp);

	return 0;
}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/
void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest)
{
	char buffer[256], *nlptr;

	if (ficheiro == NULL)
		return;

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vrem, buffer, -1);

		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vdest, buffer, -1);

		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vcp_dest, buffer, -1);
	}
}
