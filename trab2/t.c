#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int val;
    float prio;
} item, *pitem;

typedef struct 
{
    pitem *valores;
    int tamanho;
    int capacidade;
} heap, *pheap;

pheap criarHeap(int capacidade)
{
    pheap h = malloc(sizeof(heap));
    if(h == NULL) return NULL;

    h->tamanho = 0;
    h->capacidade = capacidade;
    h->valores = malloc(sizeof(pitem) * (capacidade + 1));
    return h;
}

void apagarHeap(pheap h)
{
    for(int i = 1; i <= h->tamanho; i++)
    {
        free(h->valores[i]);
    }
    free(h->valores);
    free(h);
}

int inserirNaHeap(pheap h, int val, float prio)
{
    if(!h) return -1;
    pitem itm = malloc(sizeof(item));
    itm->val = val;
    itm->prio = prio;

    if(h->capacidade == h->tamanho)
    {
        h->capacidade = h->capacidade * 2;
        h->valores = realloc(h->valores, sizeof(pitem) * (h->capacidade + 1));
    }

    h->valores[++h->tamanho] = itm;
    int curr = h->tamanho;
    int father = curr / 2;

    while(father > 0 && h->valores[curr]->prio < h->valores[curr]->prio)
    {
        pitem aux = h->valores[curr];
        h->valores[curr] = h->valores[father];
        h->valores[father] = aux;

        curr = father;
        father = curr / 2;
    }

    return 1;
}

pitem removeDaHeap(pheap hp)
{
    if(!hp) return NULL;
    pitem itm = hp->valores[1];

    hp->valores[1] = hp->valores[hp->tamanho];
    hp->valores--;

    int curr = 1;
    int leftChild = 2 * curr;
    int rightChild = 2 * curr + 1;
    int selectedChild;

    while(leftChild <= hp->tamanho)
    {
        selectedChild = leftChild;
        if(rightChild <= hp->tamanho && hp->valores[rightChild]->prio < hp->valores[leftChild]->prio)
            selectedChild = rightChild;
        
        if(hp->valores[curr]->prio > hp->valores[selectedChild]->prio)
        {
            pitem aux = hp->valores[curr];
            hp->valores[curr] = hp->valores[selectedChild];
            hp->valores[selectedChild] = aux;

            curr = selectedChild;
        } else break;
    }

    return itm;

}

int main()
{
    pheap h;
    h = criarHeap(0);
}
