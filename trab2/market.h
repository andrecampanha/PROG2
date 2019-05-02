/*****************************************************************/
/*           Arvore AVL | PROG2 | MIEEC | 2017/18                */
/*****************************************************************/

#ifndef MARKET_H
#define MARKET_H

#define CURDATE "2019-05-12"

/**
 * Registo que contem os dados de cada elemento armazenado
 * */
typedef struct elemento_
{
	char nameItem[100];
	char expirationDate[11];
	int qty;
	int sellRate;
	float priorityVal;
} elemento_t;

/**
 * Heap contem apenas um apontador para a raiz do vector de itens
 */
typedef struct {
	/* numero de elementos no vetor */
	int tamanho;
	/* tamanho maximo do vetor */
	int capacidade;
	/* vetor de apontadores para elementos*/
	elemento_t** elementos;
} heap;

typedef struct category_
{
	char* categName;
	heap* itemTree;
} category_t;


/**
 * Registo para armazenar cada no da arvore AVL de categorias
 */
typedef struct no_avl_
{
	category_t *categ;
	struct no_avl_ *esquerda;
	struct no_avl_ *direita;
	int altura;
} no_avl;

/**
 * arvore_avl contem apenas um apontador para a raiz
 */
typedef struct
{
	no_avl *raiz;
} arvore_avl;

/**
 *  Cria novo elemento
 * 	parametros: nome do item, data de validade, quantidade, taxa de saida
 * 	retorno: apontador para elemento criado */
elemento_t* elemento_novo(const char* nameItem, const char* expDate, int qty, int sellRate);

/**
 * Apaga um elemento
 * parametros: apontador para o elemento
 * */
void elemento_apaga(elemento_t* elem);

/**
 *  Calcula a prioridade associada a um elemento
 * 	parametros: instância do elemento a calcular prioridade
 *  retorno: prioridade do elemento
 */
float calcMetrica(elemento_t* elem);

/**
 *  Cria nova heap
 * 	parametros: capacidade da heap
 * 	retorno: apontador para heap ou NULL se erro
 */
heap* heap_nova(int tamanho_maximo);

/**
 *  Insere elemento na heap
 * 	parametros: apontador para heap, apontador para elemento a inserir
 * 	retorno: 1 se sucesso, 0 se erro
 */
int heap_insere(heap *h, elemento_t* elem);

/**
 *  Remove elemento da heap
 * 	parametros: apontador para heap
 * 	retorno: apontador para elemento removido, NULL em caso de erro
 */
elemento_t* heap_remove(heap *h);

/**
 *  Apaga a heap
 * 	parametros: apontador para heap a apagar
 */
void heap_apaga(heap *h);

/**
 *  Imprime a heap a partir do indice indicado
 * 	parametros: apontador para heap a imprimir
 */
void mostraHeap(heap *h);

/**
 * Cria uma nova categoria
 * parametros: apontador para a heap, nome da categoria
 * retorno: apontador para a instancia da categoria, NULL se erro
 * */
category_t* novaCategoria(heap* itemTree, char* categName);

/**
 * Apaga uma categoria
 * parametros: apontador para a categoria
 * */
void categoriaApaga(category_t* categ);

/**
 *  cria uma nova arvore avl vazia
 *  retorno: apontador para a arvore criada ou NULL em caso de erro
 */
arvore_avl* avl_nova();

/**
 *  cria um no para arvore avl
 * 	parametros: apontador para instância da categoria
 *  retorno: apontador para o no criado ou NULL em caso de erro
 */
no_avl* avl_novo_no(category_t * categ);

/**
 *  insere um no numa arvore avl
 * 	parametros: no onde inserir, apontador para instância da categoria ()
 *  retorno: apontador para o no inserido ou NULL em caso de erro
 */
no_avl* avl_insere(no_avl *no, category_t * categ);

/**
 *  remove no correspondente a prioridade pedida
 * 	parametros: no a remover, nome da categoria 
 *  retorno: apontador para o no removido ou NULL em caso de erro
 */
no_avl* avl_remove(no_avl *no, const char* categStr);

/**
 *  pesquisa um no numa arvore avl correspondente a prioridade pedida
 * 	parametros: no a pesquisar, nome da categoria 
 *  retorno: apontador para o no ou NULL se não encontrou
 */
no_avl* avl_pesquisa(no_avl *no, const char* categStr);

/**
 * 	Apaga arvore AVL
 * 	parametros: apontador para avl a remover
 * */
void avl_apaga(arvore_avl* avl);

/**
 *  Adiciona um artigo ao armazem
 * 	parametros: arvore do armazem (avl), apontador para elemento, nome de categoria do item,
 * 				capacidade do armazem para a categoria do item
 *  retorno: 1 se adicao teve sucesso, 0 caso contrário
 */
int artigo_adiciona(arvore_avl *avl, elemento_t* elem, char* categName, int capCateg);


/**
 *  Cria montra
 * 	parametros: arvore do armazem (avl), categoria da montra, numero de artigos de cada item,
 * 				numero total de artigos, referência para tamanho do array retornado pela funcao 
 *  retorno: vetor de itens colocados para a montra
 */
elemento_t** criar_montra(arvore_avl* avl, const char* categName, int numPorItem, int totalItems,
						  int* tamanhoArray);


#endif  /* MARKET_H */
