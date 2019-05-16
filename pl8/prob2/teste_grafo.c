#include "grafo.h"
#include <stdio.h>

int main()
{
	/* exemplo da alinea 1.2 */
	int adj[] = {1,2,1,3,1,4,2,5,3,5,4,5};
	grafo *g12 = grafo_deLista(adj, 6);
	grafo_imprime(g12);

	vetor *v = grafo_arestasSaida(g12, 1);
	printf("arestasSaida(1) =");
	for(int i = 0; i < v->tamanho; i++)
		printf(" %d", vetor_elemento(v, i));
	printf("\n");
	vetor_apaga(v);

	v = grafo_arestasEntrada(g12, 5);
	printf("arestasEntrada(5) =");
	for(int i = 0; i < v->tamanho; i++)
		printf(" %d", vetor_elemento(v, i));
	printf("\n");
	vetor_apaga(v);

	for(int i = 1; i <= g12->tamanho; i++)
		printf("Nó %d é celebridade? %s\n", i, grafo_eCelebridade(g12, i) ? "Sim" : "Não");

	printf("Grafo tem celebridade? %s", grafo_temCelebridade(g12) ? "Sim" : "Não");

	grafo_apaga(g12);

	printf("\nFIM\n");

	return 0;
}
