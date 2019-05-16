/*****************************************************************/
/*   Grafo c/ matriz de adjacencias | PROG2 | MIEEC | 2018/19    */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/* cria grafo com n vertices */
grafo* grafo_novo(int n)
{
    int v;
    grafo* g;
    
    g = (grafo*)malloc(sizeof(grafo));
    g->tamanho = n;

    /* cria array de listas de adjacencias */
    g->adjacencias = (int**)malloc(n * sizeof(int*));
    for(v=0; v<n; v++)
    {
        g->adjacencias[v] = (int*)calloc(v, sizeof(int));
    }

    return g;
}

/* apaga grafo e liberta memoria */
void grafo_apaga(grafo* g)
{
    if(g == NULL)
        return;

    if(g->adjacencias != NULL)
    {
        int v;
        for (v = 0; v < g->tamanho; v++)
            free(g->adjacencias[v]);
        free(g->adjacencias);
    }
    free(g);
}

/* adiciona no grafo g uma aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta ja existir e 1 se foi adicionada */
int grafo_adiciona(grafo *g, int origem, int dest)
{
    // Complexidade O(1)
    if(!g || origem < 1 || origem > g->tamanho || dest < 1 || dest > g->tamanho || origem == dest) return -1;

    int a = origem > dest ? origem : dest;
    int b = origem > dest ? dest : origem;

    if(g->adjacencias[a - 1][b - 1]) return 0;
    g->adjacencias[a - 1][b - 1] = 1;

    return 1;
}

/* remove do grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se foi removida */
int grafo_remove(grafo *g, int origem, int dest)
{
    // Complexidade O(1)
    if(!g || origem < 1 || origem > g->tamanho || dest < 1 || dest > g->tamanho || origem == dest) return -1;

    int a = origem > dest ? origem : dest;
    int b = origem > dest ? dest : origem;

    if(!g->adjacencias[a - 1][b - 1]) return 0;
    g->adjacencias[a - 1][b - 1] = 0;
    return 1;
}

/* testa no grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se existir */
int grafo_aresta(grafo *g, int origem, int dest)
{
    // Complexidade O(1)
    if(!g || origem < 1 || origem > g->tamanho || dest < 1 || dest > g->tamanho || origem == dest) return -1;
    return origem > dest ? g->adjacencias[origem - 1][dest - 1] : g->adjacencias[dest - 1][origem - 1];
}

/* cria um novo grafo com base numa lista de adjacencias
   parametro adjacencies e' um array de inteiros, representado
   um numero n_edges de arestas.
   retorna um apontador para o grafo criado */
grafo* grafo_deLista(int* adjacencias, int n_arestas)
{
    int n_vertices = -1;
    for(int i = 0; i < 2 * n_arestas; i++)
        if(adjacencias[i] > n_vertices) n_vertices = adjacencias[i];
    grafo *g = grafo_novo(n_vertices);

    if(!g) return NULL;

    int a, b;

    for(int i = 0; i < 2 * n_arestas; i += 2)
    {
        if(grafo_adiciona(g, adjacencias[i], adjacencias[i + 1]) != 1)
        {
            grafo_apaga(g);
            return NULL;
        }
    }
    return g;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de destino de todas as arestas com origem em i */
vetor* grafo_arestasSaida(grafo* g, int i)
{
    if(!g || i < 1 || i > g->tamanho) return NULL;
    vetor *v = vetor_novo();
    if(!v) return NULL;
    for(int j = 1; j <= g->tamanho; j++)
    {
        if(grafo_aresta(g, i, j))
        {
            if(vetor_insere(v, j, -1) == -1)
            {
                vetor_apaga(v);
                return NULL;
            }
        }
    }
    return v;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de origem de todas as arestas com destino a i */
vetor* grafo_arestasEntrada(grafo* g, int i)
{
    return grafo_arestasSaida(g, i);
}

/* verifica se o grafo g e' completo
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o grafo for completo e 0 se nao o for */
int grafo_completo(grafo* g)
{
    if(!g) return -1;
    
    for(int i = 1; i <= g->tamanho - 1; i++)
    {
        for(int j = 1; j < i; j++)
        {
            if(!grafo_aresta(g, i, j)) return 0;
        }
    }
    return 1;
}

/* verifica se o vertice i do grafo g e' uma celebridade
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o vertice for uma celebridade e 0 se nao o for */
int grafo_eCelebridade(grafo* g, int i)
{
    // Complexidade: O(1)
    return 0;
}

/* verifica se o grafo g tem pelo menos uma celebridade
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se existir uma celebridade e 0 se nao existir */
int grafo_temCelebridade(grafo* g)
{
    // Complexidade: O(1)
    return 0;
}

/* imprime as adjacencias do grafo */
void grafo_imprime(grafo* g)
{
    int i, j;

    if (g == NULL)
        return;

    for (i = 1; i <= g->tamanho; i++)
    {
        printf("%d: ", i);
        for(j = 1; j <= g->tamanho; j++)
        {
            if(grafo_aresta(g, i, j) != 0)
                printf("%d ", j);
        }
        printf("\n");
    }
}

