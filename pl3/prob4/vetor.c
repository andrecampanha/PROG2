/*****************************************************************/
/*          Biblioteca vetor | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/

#include "vetor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

vetor* vetor_novo()
{
	vetor* vec;

	/* aloca memoria para a estrutura vetor */
	vec = (vetor*)malloc(sizeof(vetor));
	if(vec == NULL)
	return NULL;

	vec->tamanho = 0;
	vec->capacidade = 0;
	vec->elementos = NULL;

	return vec;
}


int vetor_tamanho(vetor* vec)
{
	if(vec == NULL)
	return -1;

	return vec->tamanho;
}

int vetor_insere(vetor *vec, const char* titulo, int votos, float classificacao, int ano, int pos)
{
	int i, n;

	if(vec == NULL || pos < -1 || pos > vec->tamanho)
		return -1;

	/* aumenta elementos do vetor se capacidade nao for suficiente */
	if(vec->tamanho == vec->capacidade)
	{
		if(vec->capacidade == 0)
			vec->capacidade = 1;
		else
			vec->capacidade *= 2;

		vec->elementos = (v_elemento*)realloc(vec->elementos, vec->capacidade * sizeof(v_elemento));
		if(vec->elementos == NULL)
			return -1;
	}

	/* se pos=-1 insere no fim do vetor */
	if(pos == -1)
		pos = vec->tamanho;

	/* copia todos os elementos a partir da posicao pos ate' ao fim do vetor para pos+1 */
	for(i=vec->tamanho-1; i>=pos; i--)
	{
		vec->elementos[i+1] = vec->elementos[i];
	}

	/* aloca espaco para a nova string na posicao pos */
	vec->elementos[pos].titulo = (char*)calloc(strlen(titulo)+1, sizeof(char));
	if(vec->elementos[pos].titulo == NULL)
		return -1;

	/* copia valor */
	strcpy(vec->elementos[pos].titulo, titulo);

	vec->elementos[pos].ano = ano;
	vec->elementos[pos].classificacao = classificacao;
	vec->elementos[pos].votos = votos;

	vec->tamanho++;

	return pos;
}

int vetor_pesquisa(vetor* vec, const char* valor)
{
	int i;

	if(vec == NULL)
	return -1;

	/* pesquisa sequencial */
	for (i = 0; i < vec->tamanho; i++)
	{
		if (strcmp(vec->elementos[i].titulo, valor) == 0)
		return i;
	}

	return -1;
}

int vetor_ordena_ano(vetor* vec)
{
	int i, j;
	v_elemento tmp;

	if(vec == NULL)
	return -1;

	/* ordenacao por insercao */
	for (i = 1; i < vec->tamanho; i++)
	{
		tmp = vec->elementos[i];
		for (j = i; j > 0 && tmp.ano < vec->elementos[j-1].ano; j--)
		{
			vec->elementos[j] = vec->elementos[j-1];
		}
		vec->elementos[j] = tmp;
	}

	return 0;
}

vetor* vetor_pesquisa_ano(vetor *vec, int ano)
{
	vetor *res = vetor_novo();
	for (int i = 0; i < vec->tamanho; i++)
	{
		if (vec->elementos[i].ano == ano)
			vetor_insere(res, vec->elementos[i].titulo, vec->elementos[i].votos,
				vec->elementos[i].classificacao, vec->elementos[i].ano, res->tamanho);
	}

	return res;
}	
