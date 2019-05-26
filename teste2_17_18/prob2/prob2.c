#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabdispersao.h"
#include "grafo.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
int distancia_cache(grafo *g, int origem, int destino, tabela_dispersao *cache)
{
    if(!g || !cache || origem < 0 || origem >= g->tamanho || destino < 0 || destino >= g->tamanho) return -1;

    char chave[50];
    sprintf(chave, "%d/%d", origem, destino);

    if(tabela_existe(cache, chave) == TABDISPERSAO_EXISTE)
    {
        return atoi(tabela_valor(cache, chave));
    }

    int res;
    if(origem == destino) res = 0;
    else {
        int *caminho = grafo_bfs(g, origem, destino, &res);
        free(caminho);
        if(res == 0) return -1;
        res--;
    }

    char valor[24];
    sprintf(valor, "%d", res);
    if(tabela_adiciona(cache, chave, valor) == TABDISPERSAO_ERRO)
        return -1;
    return res;
}

/*** problema 2.2 ***/
/*
complexidade do algoritmo:

justificacao:

*/

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define MAX_STR 500

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	
	/* inicio teste prob2.1 */
	{
		grafo *g;
		int dist, i, origem, destino, n;
        tabela_dispersao *cache;
        
		puts("\n* Problema 2.1 *");
		g = grafo_novo(8, DIGRAFO);
		grafo_adiciona(g,0,4);
		grafo_adiciona(g,1,0);
		grafo_adiciona(g,1,5);
		grafo_adiciona(g,2,1);
		grafo_adiciona(g,3,2);
		grafo_adiciona(g,4,3);
		grafo_adiciona(g,5,4);
		grafo_adiciona(g,6,3);
		grafo_adiciona(g,7,2);
		grafo_adiciona(g,7,6);
		grafo_adiciona(g,1,7);

        cache = tabela_nova(1000, hash_djbm);

		dist = distancia_cache(g, 0, 5, cache);
		printf("Distancia do vertice 0 a 5: %d\n", dist);
		if(dist == -1)
        {
            tabela_apaga(cache);
            grafo_apaga(g);
            puts("");  
            return 0; 
        }
        
        n = tabela_numelementos(cache);
        if (n != 1) 
			printf("ERRO: a cache tem %d elementos e devia ter 1\n", n);
            
		dist = distancia_cache(g, 0, 5, cache);
		if(dist != -1)
			printf("Distancia (na cache) do vertice 0 a 5: %d\n", dist);
          
        int real_dist[8] = {0, 4, 3, 2, 1, 5, 6, 5};
        for (i = 0; i < 8; i++) {
            dist = distancia_cache(g, 0, i, cache);
            if(i % 3 == 0)
            {
                printf("Distancia do vertice 0 a %d: %d", i, dist);
                if (dist == real_dist[i]) printf(" OK\n");
                else printf(" ERRO: deveria ser %d\n", real_dist[i]);
            }
        }
        
        n = tabela_numelementos(cache);
        if (n != 8) 
			printf("ERRO: a cache tem %d elementos e devia ter 8\n", n);

        for (i = 0; i < 8; i++) {
            dist = distancia_cache(g, 0, i, cache);
            if(i % 3 == 1)
            {
                printf("Distancia (na cache) do vertice 0 a %d: %d", i, dist);
                if (dist == real_dist[i]) printf(" OK\n");
                else printf(" ERRO: deveria ser %d\n", real_dist[i]);
            }
        }
        n = tabela_numelementos(cache);
        if (n != 8) 
			printf("ERRO: a cache tem %d elementos e devia ter 8\n", n);

        puts("");
        tabela_apaga(cache);
		grafo_apaga(g);
	}
    /* fim teste prob2.1 */

	return 0;
}
