/*****************************************************************/
/*           Market | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "market.h"

#define RAIZ 		(1)
#define PAI(x) 		(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	(x*2+1)

//Declaracao funcoes auxiliares//
int maior_que(elemento_t * e1, elemento_t * e2);
int avl_altura(no_avl *no);
int calc_balanceamento(no_avl *N);
no_avl* roda_direita(no_avl *y);
no_avl* roda_esquerda(no_avl *x);
no_avl* avl_no_valormin(no_avl* no);
no_avl* avl_no_valormax(no_avl* no);
int max(int a, int b);
int min(int a, int b);
int enoughItems(heap* h, int numPorItem, int totalItems);
void avlNoApaga(no_avl* node);
void avlNoCopia(no_avl* nodeDest, no_avl* nodeSource);
void avlNoValorCopia(no_avl* nodeDest, no_avl* nodeSrc);


//////   Implementacao Elemento e Calculo Metrica (5.1)  ///////

elemento_t* elemento_novo(const char* nameItem, const char* expDate, int qty, int sellRate)
{
    if(nameItem == NULL || expDate == NULL) return NULL;

    elemento_t *elem = malloc(sizeof(elemento_t));
    if(elem == NULL) return NULL;

    strcpy(elem->nameItem, nameItem);
    strcpy(elem->expirationDate, expDate);
    elem->qty = qty;
    elem->sellRate = sellRate;
    elem->priorityVal = calcMetrica(elem);
    
    return elem;
}

void elemento_apaga(elemento_t* elem)
{
	if (elem)
		free(elem);
    elem = NULL;
}

//   Implementacao metrica prioridade  //
	
float calcMetrica(elemento_t* elem)
{
    if(elem == NULL) return -1;

    struct tm tm1 = { 0 }, tm2 = { 0 };
    char curr[] = CURDATE, expd[11];
    strcpy(expd, elem->expirationDate);

    tm1.tm_year = atoi(strtok(expd, "-")) - 1900;
    tm1.tm_mon = atoi(strtok(NULL, "-")) - 1;
    tm1.tm_mday = atoi(strtok(NULL, "-"));
    tm1.tm_hour = tm1.tm_min = tm1.tm_sec = 0;

    tm2.tm_year = atoi(strtok(curr, "-")) - 1900;
    tm2.tm_mon = atoi(strtok(NULL, "-")) - 1;
    tm2.tm_mday = atoi(strtok(NULL, "-"));
    tm2.tm_hour = tm2.tm_min = tm2.tm_sec = 0;

    time_t t1, t2;
    t1 = mktime(&tm1);
    t2 = mktime(&tm2);

    double diff = difftime(t1, t2) / 3600 / 24;

    return 1 / (diff + ((float) 1000 / elem->sellRate));
}


///////////////////////////////////////////////////

/// Implementacao Heaps (5.2) ///

heap* heap_nova(int capacidade)
{
	heap *h = malloc(sizeof(heap));
    if(h == NULL) return NULL;
    h->capacidade = capacidade;
    h->tamanho = 0;
    h->elementos = malloc(sizeof(elemento_t*) * (capacidade + RAIZ));
    if (h->elementos == NULL)
    {
        free(h);
        return NULL;
    }
    
    return h;
}

void heap_apaga(heap *h)
{
	for(int i = RAIZ; i <= h->tamanho; i++)
        elemento_apaga(h->elementos[i]);
    free(h->elementos);
    free(h);
}


int heap_insere(heap *h, elemento_t* elem)
{
	elemento_t * aux;
	int i;
	//gilc
	if(!h) return 0;
	/* se heap esta' cheia, nao insere elemento */
	if (h->tamanho >= h->capacidade)
		return 0;

	if (!elem)
		return 0;

	/* coloca elemento no fim da heap */
	h->tamanho++;
	i = h->tamanho;
	h->elementos[i] = elem;

 	/* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
	while (i != RAIZ && maior_que(h->elementos[i], h->elementos[PAI(i)]))
	{
		aux = h->elementos[PAI(i)];
		h->elementos[PAI(i)] = h->elementos[i];
		h->elementos[i] = aux;
		i = PAI(i);
	}
	return 1;

    //Default
    return 0;
}


elemento_t* heap_remove(heap * h)
{
	if(h == NULL) return NULL;
    elemento_t *item = h->elementos[1];

    h->elementos[RAIZ] = h->elementos[h->tamanho];
    h->tamanho--;

    int curr = RAIZ;
    int leftChild = FILHO_ESQ(curr);
    int rightChild = FILHO_DIR(curr);
    int selectedChild;

    while(leftChild <= h->tamanho)
    {
        selectedChild = leftChild;
        if(rightChild <= h->tamanho && h->elementos[rightChild]->priorityVal < h->elementos[leftChild]->priorityVal)
            selectedChild = rightChild;
        
        if(h->elementos[curr]->priorityVal > h->elementos[selectedChild]->priorityVal)
        {
            elemento_t *aux = h->elementos[curr];
            h->elementos[curr] = h->elementos[selectedChild];
            h->elementos[selectedChild] = aux;

            curr = selectedChild;
        } else break;
    }

    return item;
}



void mostraHeap(heap *h)
{
    if(!h)
        return;

    for(int indice =1; indice<=(h->tamanho); indice++)
    {
        printf("%s %s %d %d %f\n",h->elementos[indice]->nameItem, h->elementos[indice]->expirationDate,
                        h->elementos[indice]->qty,h->elementos[indice]->sellRate,
                        h->elementos[indice]->priorityVal);
    }
}


//////////////////////////////////////////////

/// Implementacao criacao categoria nova ///

category_t* novaCategoria(heap* itemTree, char* categName)
{
    category_t* retCat = (category_t*)malloc(sizeof(category_t));

    if(retCat == NULL)
    {
        return NULL;
    }

    retCat->itemTree = itemTree;

    retCat->categName = (char*)malloc((strlen(categName)+1)*sizeof(char));

    if(retCat->categName==NULL)
    {
        return NULL;
    }

    strcpy(retCat->categName,categName);

    return retCat;

    //Default
    return NULL;
}

void categoriaApaga(category_t* categ)
{
    if(categ==NULL)
        return;
    
    heap_apaga(categ->itemTree);
    free(categ->categName);
    categ->categName = NULL;
    free(categ);
    categ = NULL;
}


////////////////////////////////////////////

//////   Implementacao AVLs (5.3)  ///////

arvore_avl* avl_nova()
{
    // Implementacao exercicio 5.4.1
    arvore_avl *avl = (arvore_avl*) malloc(sizeof(arvore_avl));
    if(avl == NULL)
        return NULL;

    avl->raiz = NULL; /* arvore vazia */

    return avl;

    // Default
    return NULL;
}

no_avl* avl_novo_no(category_t* categ)
{
    // Implementacao exercicio 5.4.2
    no_avl *no = (no_avl*) malloc(sizeof(no_avl));

    if(no==NULL)
        return NULL;

    no->categ = categ;
    no->esquerda = NULL;
    no->direita  = NULL;
    no->altura = 0;  /* novo no e' inicialmente uma folha */
    return no;

    // Default
    return NULL;
}


no_avl* avl_insere(no_avl *no, category_t* categ)
{
    //if(categ == NULL) return NULL;
    /* 1.  efetua insercao normal de arvore binaria de pesquisa */
    if (no == NULL)
        return avl_novo_no(categ);

    if (strcmp(categ->categName, no->categ->categName) < 0)
        no->esquerda  = avl_insere(no->esquerda, categ);
    else if(strcmp(categ->categName, no->categ->categName) > 0)
        no->direita = avl_insere(no->direita, categ);
    else
        return no;

    /* 2. atualiza a altura deste no ancestral */
    no->altura = max(avl_altura(no->esquerda), avl_altura(no->direita)) + 1;

    /* 3. calcula o fator de balanceamento deste no ancestral para verificar
       se deixou de estar balanceado */
    int balance = calc_balanceamento(no);

    /* se o no deixou de estar balanceado, existem 4 casos */

    if (balance > 1) {
        /* Arvore e' right-heavy */
    	if (calc_balanceamento(no->direita) < 0) {
    		/* Sub-arvore direita é left-heavy */
            /* Rotacao RL */
			no->direita = roda_direita(no->direita);
			return roda_esquerda(no);
    	} else {
    		/* Rotacao L */
    		return roda_esquerda(no);
    	}
    }
    else if (balance < -1) {
        /* Arvore e' left-heavy */
    	if (calc_balanceamento(no->esquerda) > 0) {
            /* Sub-arvore esquerda é right-heavy */
    		/* Rotacao LR */
			no->esquerda = roda_esquerda(no->esquerda);
			return roda_direita(no);
    	} else {
    		/* Rotacao R */
    		return roda_direita(no);
    	}
    }

    /* caso esteja balanceada retorna o apontador para o no (inalterado) */
    return no;
}

no_avl* avl_remove(no_avl* no, const char *categStr)
{
    /* 1. efetua remocao normal de arvore binaria de pesquisa */

    if (no == NULL)
        return no;
    /* se a str a ser removida é menor do que a str da raiz,
       entao esta' na sub-arvore esquerda */
    if ( strcmp(categStr, no->categ->categName) < 0 )
        no->esquerda = avl_remove(no->esquerda, categStr);

    /* se a str a ser removida é maior do que a str da raiz,
       entao esta' na sub-arvore direita */
    else if( strcmp(categStr, no->categ->categName) > 0 )
        no->direita = avl_remove(no->direita, categStr);

    /* se a str a ser removida é igual a str da raiz,
       entao e' este no a remover */
    else
    {
        /* no' com apenas um filho ou sem filhos */
        if( (no->esquerda == NULL) || (no->direita == NULL) )
        {
            no_avl *temp = no->esquerda ? no->esquerda : no->direita;

            /* caso sem filhos */
            if(temp == NULL)
            {
                temp = no;
                no = NULL;
            }
            else /* caso de um filho */
            {
                /* copia os conteudos do filho que não está vazio */
                avlNoCopia(no,temp);
				//
            }
            avlNoApaga(temp);
        }
        else
        {
            /* no' com dois filhos: obtem sucessor em-ordem (menor da arvore direita) */
            no_avl* temp = avl_no_valormin(no->direita);

            /* copia o valor em.ordem do sucessor para este no' */
            avlNoValorCopia(no,temp);
            /* apaga o sucessor em-ordem */
            no->direita = avl_remove(no->direita, temp->categ->categName);
        }
    }
	
    /* se a arvore tinha apenas um no, então retorna */
    if (no == NULL)
      return no;
	
    /* 2. atualiza a altura do no corrente */
    no->altura = max(avl_altura(no->esquerda), avl_altura(no->direita)) + 1;

    /* 3. calcula o fator de balanceamento deste no ancestral para verificar
       se deixou de estar balanceado */
    int balance = calc_balanceamento(no);

    /* se o no deixou de estar balanceado, existem 4 casos */
    if (balance > 1) {
        /* Arvore e' right-heavy */
        if (calc_balanceamento(no->direita) < 0) {
            /* Sub-arvore direita é left-heavy */
            /* Rotacao RL */
            no->direita = roda_direita(no->direita);
            return roda_esquerda(no);
        } else {
            /* Rotacao L */
            return roda_esquerda(no);
        }
    }
    else if (balance < -1) {
        /* Arvore e' left-heavy */
        if (calc_balanceamento(no->esquerda) > 0) {
            /* Sub-arvore esquerda é right-heavy */
            /* Rotacao LR */
            no->esquerda = roda_esquerda(no->esquerda);
            return roda_direita(no);
        } else {
            /* Rotacao R */
            return roda_direita(no);
        }
    }
    /* caso esteja balanceada retorna o apontador para o no (inalterado) */
    return no;
}

no_avl* avl_pesquisa(no_avl *no, const char* categStr)
{
    if(no == NULL || categStr == NULL)
        return NULL;

    if(strcmp(categStr, no->categ->categName) < 0)
        return avl_pesquisa(no->esquerda, categStr);
    else if(strcmp(categStr, no->categ->categName) > 0)
        return avl_pesquisa(no->direita, categStr);
    else
        return no;
}

void avl_apaga_i(no_avl *no)
{
	if (!no)
		return;
	avl_apaga_i(no->esquerda);
	avl_apaga_i(no->direita);
	avlNoApaga(no);
}

void avl_apaga(arvore_avl* avl)
{
	if (!avl) return;
	
	avl_apaga_i(avl->raiz);
	
/*    while(avl->raiz != NULL)
    {
        avl->raiz = avl_remove(avl->raiz, avl->raiz->categ->categName);
    }*/
    
    free(avl);
}

///////////////////////////////////////



///   Implementacao adicao artigo (5.4)
int artigo_adiciona(arvore_avl *avl, elemento_t* elem, char *categName, int capCateg)
{
    if(avl == NULL || elem == NULL || categName == NULL || capCateg == 0) return 0;
    category_t *categ;
    no_avl *no = avl_pesquisa(avl->raiz, categName);
    if(no != NULL)
    {
        categ = no->categ;
        if(categ->itemTree->tamanho >= capCateg)
            return 0;

        if(!heap_insere(categ->itemTree, elem))
            return 0;
    }
    else
    {
        heap *h = heap_nova(capCateg);
        if(!h) return 0;
        if(!heap_insere(h, elem))
        {
            heap_apaga(h);
            return 0;
        }

        categ = novaCategoria(h, categName);
        if(!categ)
        {
            heap_apaga(h);
            return 0;
        }
        avl->raiz = avl_insere(avl->raiz, categ);

        if(!avl->raiz)
        {
            categoriaApaga(categ);
            return 0;
        }
    }

    return 1;
}

//////////////////////////////////////////////

elemento_t *elemento_cpy(elemento_t *ori)
{
    elemento_t *cpy = malloc(sizeof(elemento_t));
    if(cpy == NULL) return NULL;

    strcpy(cpy->nameItem, ori->nameItem);
    strcpy(cpy->expirationDate, ori->expirationDate);
    cpy->priorityVal = ori->priorityVal;
    cpy->sellRate = ori->sellRate;
    cpy->qty = ori->qty;
    return cpy;
}

///   Implementacao montagem montra (5.5)   ///
elemento_t** criar_montra(arvore_avl* avl, const char* categName, int numPorItem, int totalItems, int* tamanhoArray)
{
    if(avl == NULL || categName == NULL) return NULL;

    no_avl *no = avl_pesquisa(avl->raiz, categName);
    if(no == NULL || no->categ == NULL) return NULL;
    heap *hp = no->categ->itemTree;

    if(!enoughItems(hp, numPorItem, totalItems))
        return NULL;

    heap *haux = heap_nova(hp->capacidade);
    if(haux == NULL)
        return NULL;

    elemento_t **arr = malloc(sizeof(elemento_t*) * totalItems);
    if(arr == NULL)
    {
        heap_apaga(haux);
        return NULL;
    }
    *tamanhoArray = 0;

    elemento_t *new, *cur;

    while(totalItems > 0 || hp->tamanho > 0)
    {
        cur = heap_remove(hp);
        new = elemento_cpy(cur);
        new->qty = min(min(numPorItem, totalItems), cur->qty);
        
        totalItems -= new->qty;

        arr[*tamanhoArray] = new;
        (*tamanhoArray)++;

        if(cur->qty > 0)
        {
            heap_insere(haux, cur);
        }
    }

    while(haux->tamanho > 0)
        heap_insere(hp, heap_remove(haux));

    heap_apaga(haux);
    return arr;
}

//////////////////////////////////////////////





// Auxiliary functions

int maior_que(elemento_t* e1, elemento_t* e2)
{
	if (e1 == NULL || e2 == NULL)
	{
		return 0;
	}

	return e1->priorityVal > e2->priorityVal;
}

int avl_altura(no_avl *no)
{
    if (no == NULL)
        return -1;
    return no->altura;
}

int calc_balanceamento(no_avl *N)
{
    if (N == NULL)
        return 0;
    return avl_altura(N->direita) - avl_altura(N->esquerda);
}

no_avl* roda_direita(no_avl *y)
{
    no_avl *x = y->esquerda;
    no_avl *T2 = x->direita;

    /* efetua rotacao */
    x->direita = y;
    y->esquerda = T2;

    /* atualiza alturas */
    y->altura = max(avl_altura(y->esquerda), avl_altura(y->direita))+1;
    x->altura = max(avl_altura(x->esquerda), avl_altura(x->direita))+1;

    /* retorna novo no' */
    return x;
}

no_avl* roda_esquerda(no_avl *x)
{
    no_avl *y = x->direita;
    no_avl *T2 = y->esquerda;

    /* efetua rotacao */
    y->esquerda = x;
    x->direita = T2;

    /*  atualiza alturas */
    x->altura = max(avl_altura(x->esquerda), avl_altura(x->direita))+1;
    y->altura = max(avl_altura(y->esquerda), avl_altura(y->direita))+1;

    /* retorna novo no' */
    return y;
}


no_avl* avl_no_valormin(no_avl* no)
{
    no_avl* curr = no;

    /* percorre a arvore para encontrar o filho mais 'a esquerda */
    while (curr->esquerda != NULL)
        curr = curr->esquerda;

    return curr;
}

no_avl* avl_no_valormax(no_avl* no)
{
    no_avl* curr = no;

    /* percorre a arvore para encontrar o filho mais 'a direita */
    while (curr->direita != NULL)
        curr = curr->direita;

    return curr;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int min(int a, int b)
{
    return (a < b)? a : b;
}

int enoughItems(heap* h, int numPorItem, int totalItems)
{
    int qtyCounter = 0;
    for (int i=1; i<=(h->tamanho); i++)
    {
        qtyCounter += min(h->elementos[i]->qty,numPorItem);
        if(qtyCounter>=totalItems)
        {
            return 1;
        }
    }
    return 0;
}

void avlNoApaga(no_avl* node)
{

    if(!node)
        return;

    categoriaApaga(node->categ);
    node->esquerda = NULL;
    node->direita = NULL;
    node->altura = 0;
    free(node);
    node = NULL;
}

void avlNoCopia(no_avl* nodeDest, no_avl* nodeSrc)
{

    if(!nodeSrc || !nodeDest)
        return;

    nodeDest->categ->categName = realloc(nodeDest->categ->categName, (strlen(nodeSrc->categ->categName)+1)*sizeof(char));
    strcpy(nodeDest->categ->categName, nodeSrc->categ->categName);
    heap_apaga(nodeDest->categ->itemTree);
    nodeDest->categ->itemTree = heap_nova(nodeSrc->categ->itemTree->capacidade);

    for(int i=RAIZ; i<=(nodeSrc->categ->itemTree->tamanho); i++)
    {
        nodeDest->categ->itemTree->elementos[i] = elemento_novo(nodeSrc->categ->itemTree->elementos[i]->nameItem,
        nodeSrc->categ->itemTree->elementos[i]->expirationDate,nodeSrc->categ->itemTree->elementos[i]->qty,
        nodeSrc->categ->itemTree->elementos[i]->sellRate);
    }
	nodeDest->categ->itemTree->tamanho = nodeSrc->categ->itemTree->tamanho;
    nodeDest->esquerda = nodeSrc->esquerda;
    nodeDest->direita = nodeSrc->direita;
    nodeDest->altura = nodeSrc->altura;

}

void avlNoValorCopia(no_avl* nodeDest, no_avl* nodeSrc)
{

    if(!nodeSrc || !nodeDest)
        return;

    nodeDest->categ->categName = realloc(nodeDest->categ->categName, (strlen(nodeSrc->categ->categName)+1)*sizeof(char));
    strcpy(nodeDest->categ->categName, nodeSrc->categ->categName);
    heap_apaga(nodeDest->categ->itemTree);
    nodeDest->categ->itemTree = heap_nova(nodeSrc->categ->itemTree->capacidade);

    for(int i=RAIZ; i<=(nodeSrc->categ->itemTree->tamanho); i++)
    {
        nodeDest->categ->itemTree->elementos[i] = elemento_novo(nodeSrc->categ->itemTree->elementos[i]->nameItem,
        nodeSrc->categ->itemTree->elementos[i]->expirationDate,nodeSrc->categ->itemTree->elementos[i]->qty,
        nodeSrc->categ->itemTree->elementos[i]->sellRate);
    }
	nodeDest->categ->itemTree->tamanho = nodeSrc->categ->itemTree->tamanho;
}
