#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem* armazem_novo(int comprimento, int altura)
{
	armazem *armz = malloc(sizeof(armazem));
	if(armz == NULL) return NULL;

	fila *f = fila_nova();
	if(f == NULL)
	{
		free(armz);
		return NULL;
	}

	armz->comprimento = comprimento;
	armz->altura = altura;
	armz->contentores = f;

	return armz;
}

/* alinea c) */
int armazem_vazio(armazem* armz)
{
	return armz == NULL || fila_tamanho(armz->contentores) == 0;
}

/* alinea d) */
int armazem_cheio(armazem* armz)
{
	return armz != NULL && fila_tamanho(armz->contentores) == armz->comprimento
		&& fila_back(armz->contentores) != NULL && pilha_tamanho(fila_back(armz->contentores)) == armz->altura;
}

/* alinea e) */
int armazenar_contentor(armazem* armz, contentor* contr)
{
	if(contr == NULL) return 0;
	if(armazem_cheio(armz))	return 0;

	pilha *p;

	if(fila_back(armz->contentores) != NULL && pilha_tamanho(fila_back(armz->contentores)) < armz->altura)
		p = fila_back(armz->contentores);
	else
	{
		p = pilha_nova();
		if(p == NULL) return 0;
		fila_push(armz->contentores, p);
	}

	pilha_push(p, contr);
	return 1;
}

/* alinea f) */
contentor* expedir_contentor(armazem* armz)
{
	if(armazem_vazio(armz))	return NULL;
	pilha *front = fila_front(armz->contentores);

	contentor *res = pilha_top(front);
	pilha_pop(front);

	if(pilha_tamanho(front) == 0)
		fila_pop(armz->contentores);

	return res;
}
