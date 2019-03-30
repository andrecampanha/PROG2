/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#include "vetor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// vetor
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

// vetor_equipas
vetor_equipas* vetor_equipas_novo()
{
	vetor_equipas* vec_eq;

	/* aloca memoria para a estrutura vetor_equipas */
	vec_eq = (vetor_equipas*)malloc(sizeof(vetor_equipas));
	if(vec_eq == NULL)
	return NULL;

	vec_eq->tamanho = 0;
	vec_eq->capacidade = 0;
	vec_eq->elementos = NULL;

	return vec_eq;
}

// vetor
void vetor_apaga(vetor* vec)
{
	if(vec == NULL)
	return;

	/* liberta memoria dos apontares para as strings */
	free(vec->elementos);

	/* liberta memoria da estrutura vetor */
	free(vec);
}

// vetor_equipas
void vetor_equipas_apaga(vetor_equipas* vec_eq)
{
	if(vec_eq == NULL)
	return;

	/* liberta memoria dos apontares para as strings */
	free(vec_eq->elementos);

	/* liberta memoria da estrutura vetor */
	free(vec_eq);
}

// vetor
int vetor_atribui(vetor* vec, int pos, jogo jogo1)
{
	if (vec == NULL || pos < 0 || pos >= vec->tamanho)
	return -1;

	/* copia valor */
	vec->elementos[pos] = jogo1;

	return pos;
}

// vetor_equipas
int vetor_equipas_atribui(vetor_equipas* vec_eq, int pos, equipa equipa1)
{
	if (vec_eq == NULL || pos < 0 || pos >= vec_eq->tamanho)
	return -1;

	/* copia valor */
	vec_eq->elementos[pos] = equipa1;

	return pos;
}

// vetor
int vetor_tamanho(vetor* vec)
{
	if(vec == NULL)
	return -1;

	return vec->tamanho;
}

// vetor_equipas
int vetor_equipas_tamanho(vetor_equipas* vec_eq)
{
	if(vec_eq == NULL)
	return -1;

	return vec_eq->tamanho;
}

// vetor
jogo *vetor_elemento(vetor* vec, int pos)
{
	if (vec == NULL || pos < 0 || pos >= vec->tamanho)
		return NULL;

	return &vec->elementos[pos];
}

// vetor_equipas
equipa *vetor_equipas_elemento(vetor_equipas* vec_eq, int pos)
{
	if (vec_eq == NULL || pos < 0 || pos >= vec_eq->tamanho)
		return NULL;

	return &vec_eq->elementos[pos];
}

// vetor
int vetor_insere(vetor* vec, jogo jogo1, int pos)
{
	int i;

	if(vec == NULL || pos < -1 || pos > vec->tamanho)
		return -1;

	/* aumenta elementos do vetor se capacidade nao for suficiente */
	if(vec->tamanho == vec->capacidade)
	{
		if(vec->capacidade == 0)
			vec->capacidade = 1;
		else
			vec->capacidade *= 2;

		vec->elementos = (jogo*)realloc(vec->elementos, vec->capacidade * sizeof(jogo));
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

	/* copia valor */
	vec->elementos[pos] = jogo1;

	vec->tamanho++;

	return pos;
}


// vetor_equipas
int vetor_equipas_insere(vetor_equipas* vec_eq, equipa equipa1, int pos)
{
	int i;

	if(vec_eq == NULL || pos < -1 || pos > vec_eq->tamanho)
		return -1;

	/* aumenta elementos do vetor se capacidade nao for suficiente */
	if(vec_eq->tamanho == vec_eq->capacidade)
	{
		if(vec_eq->capacidade == 0)
			vec_eq->capacidade = 1;
		else
			vec_eq->capacidade *= 2;

		vec_eq->elementos = (equipa*)realloc(vec_eq->elementos, vec_eq->capacidade * sizeof(equipa));
		if(vec_eq->elementos == NULL)
		return -1;
	}

	/* se pos=-1 insere no fim do vetor */
	if(pos == -1)
		pos = vec_eq->tamanho;

	/* copia todos os elementos a partir da posicao pos ate' ao fim do vetor para pos+1 */
	for(i=vec_eq->tamanho-1; i>=pos; i--)
	{
		vec_eq->elementos[i+1] = vec_eq->elementos[i];
	}

	/* copia valor */
	vec_eq->elementos[pos] = equipa1;

	vec_eq->tamanho++;

	return pos;
}

// vetor
int vetor_remove(vetor* vec, int pos)
{
	int i;

	if(vec == NULL || pos < 0 || pos >= vec->tamanho)
	return -1;

	/* copia todos os elementos a partir da posicao pos+1 ate' ao fim do vetor para pos */
	for(i=pos+1; i<vec->tamanho; i++)
	{
		vec->elementos[i-1] = vec->elementos[i];
	}

	vec->tamanho--;

	return 0;
}

// vetor_equipas
int vetor_equipas_remove(vetor_equipas* vec_eq, int pos)
{
	int i;

	if(vec_eq == NULL || pos < 0 || pos >= vec_eq->tamanho)
	return -1;

	/* copia todos os elementos a partir da posicao pos+1 ate' ao fim do vetor para pos */
	for(i=pos+1; i<vec_eq->tamanho; i++)
	{
		vec_eq->elementos[i-1] = vec_eq->elementos[i];
	}

	vec_eq->tamanho--;

	return 0;
}
